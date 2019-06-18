#include "../../../includes/window/record/codec_context_wrapper.h"

#include "../../../includes/window/record/sws_context_wrapper.h"

#include "../../../includes/window/os_exception.h" 

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
}

#include <cstdio>
#include <string>
#include <stdexcept>
/*
PRE: Recibe: 
    el nombre del archivo de salido de 
    grabacion;
    ancho y alto (int) del buffer 
    que se va a decodificar;
POST: Inicializa un wrapper del contexto 
de codec.
Levanta OSException en caso de error.
*/
CodecContextWrapper::CodecContextWrapper(
    const std::string& fileName,
    int bufferWidth, 
    int bufferHeight
)
:   bufferWidth(bufferWidth),
    bufferHeight(bufferHeight), 
    swsContextWrapper(bufferWidth, bufferHeight)
    {
    AVOutputFormat * avOutputFormat = this->get_av_output_format(fileName);
    AVCodec *codec = this->get_av_codec(avOutputFormat);
    this->init_codec_context(codec);
    this->outputFile = fopen(fileName.c_str(), "wb");
    this->init_frame();
    this->init_packet();
}

/*Cierra el stream del video.*/
void CodecContextWrapper::close() {
    _encode(NULL);
    /* add sequence end code to have a real MPEG file */
    uint8_t endcode[] = { 0, 0, 1, 0xb7 };
    fwrite(endcode, 1, sizeof(endcode), this->outputFile);
}


/*Destruye el wrapper del contexto de codec.*/
CodecContextWrapper::~CodecContextWrapper(){
    this->close();
    avcodec_close(this->codecContext);
    avcodec_free_context(&this->codecContext);
    av_packet_free(&pkt);
    av_frame_free(&frame);
    fclose(this->outputFile);
}

/*
PRE: Recibe el nombre (const std::string &) 
del archivo grabacion de salida.
POST: Devuelve el formato de salida a 
utilizar (AVOutputFormat *).
Levanta OSException en caso de error.
*/
AVOutputFormat * CodecContextWrapper::get_av_output_format(
    const std::string & fileName
){
    // Intenta deducir formato según extensión
    AVOutputFormat* avOutputFormat;
    avOutputFormat = av_guess_format(NULL, fileName.c_str(), NULL);
    if (!avOutputFormat) {
        // Intenta usar el formato standard
        avOutputFormat = av_guess_format("mpeg", NULL, NULL);
    }
    if (!avOutputFormat) {
        throw OSException("RECORD: Not output format found.","");
    }
    // h.264 es bastante popular, pero hay mejores
    avOutputFormat->video_codec = AV_CODEC_ID_H264;
    return avOutputFormat;
} 

/*
PRE: Recibe el formato de salida (AVOutputFormat *) 
del archivo de grabacion.
POST: Devuelve una instancia de codec (AVCodec *), 
para dicho formato.
Levanta OSException en caso de error.
*/
AVCodec * CodecContextWrapper::get_av_codec(
    AVOutputFormat * avOutputFormat
){
    AVCodec *codec = avcodec_find_encoder(avOutputFormat->video_codec);
    if (!codec) {
        throw OSException("RECORD: Codec initialization failed.","");
    }
    return codec;
}

/*
PRE: Recibe el codec especifico para el 
archivo de grabacion de salida.
POST: Inicializa el contexto de codec.
*/
void CodecContextWrapper::init_codec_context(AVCodec* codec){
    this->codecContext = avcodec_alloc_context3(codec);
    // La resolución debe ser múltiplo de 2
    this->codecContext->width = this->bufferWidth;
    this->codecContext->height = this->bufferHeight;
    this->codecContext->time_base = {1,25};
    this->codecContext->framerate = {25,1};
    this->codecContext->pix_fmt = AV_PIX_FMT_YUV420P;
    this->codecContext->gop_size = 10;
    this->codecContext->max_b_frames = 2;
    if (codec->id == AV_CODEC_ID_H264) {
        this->codecContext->profile = FF_PROFILE_H264_BASELINE;
        av_opt_set(this->codecContext->priv_data, "preset", "slow", 0);
    }
    avcodec_open2(this->codecContext, codec, NULL);
}

/*
PRE: El contexto de codec debe estar 
inicializado.
POST: Inicializa el frame.
Levanta OSException en caso de error.
*/
void CodecContextWrapper::init_frame() {
    this->frame = av_frame_alloc();
    if (!this->frame) {
        throw OSException("RECORD: Frame alloc failed.","");
    }
    this->frame->format = this->codecContext->pix_fmt;
    this->frame->width  = this->codecContext->width;
    this->frame->height = this->codecContext->height;
    av_frame_get_buffer(this->frame, 0);
    this->currentPts = 0;
}

/*
Inicializa el packet.
Levanta OSException en caso de error.
*/
void CodecContextWrapper::init_packet() {
    this->pkt = av_packet_alloc();
    if (!this->pkt) {
        throw OSException("RECORD: Packet alloc failed.","");
    }
}

/*
PRE: Recibe un buffer de bytes (const u_int8_t*) 
del frame a escribir.
POST: Escribe el frame de la grabacion al disco 
(al archivo de salida de grabacion).
*/
void CodecContextWrapper::encode(const u_int8_t* bufferData) {
    // El ancho del video x3 por la cantidad de bytes
    int width = this->bufferWidth * 3;
    this->swsContextWrapper.scale(
        bufferData, 
        this->frame->height, 
        this->frame->data, 
        this->frame->linesize
    );
    this->frame->pts = currentPts;
    ++this->currentPts;
    /* encode the image */
    this->_encode(this->frame);
}

/*
PRE: Recibe el frame (AVFrame* frame) 
a codificar, NULL para finalizar el 
stream.
POST: Codifica y escribe al archivo de 
salida de grabacion el frame actual.
Levanta OSException en caso de error.
*/
void CodecContextWrapper::_encode(AVFrame* frame){
    int ret = avcodec_send_frame(this->codecContext, frame);
    if (ret < 0) {
        throw OSException("RECORD: Frame send failed.","");
    }
    while (ret >= 0) {
        ret = avcodec_receive_packet(this->codecContext, this->pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0) {
            throw OSException("RECORD: Codification failed.","");
        }
        fwrite(this->pkt->data, 1, this->pkt->size, this->outputFile);
        av_packet_unref(this->pkt);
    }
}