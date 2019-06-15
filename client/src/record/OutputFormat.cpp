#include "OutputFormat.h"
#include "FormatContext.h"
#include <cstdio>
#include <string>
#include <stdexcept>
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
}

static void encode(AVCodecContext *enc_ctx, AVFrame *frame, AVPacket *pkt,
                   FILE *outfile) {
    int ret = avcodec_send_frame(enc_ctx, frame);
    if (ret < 0) {
        throw std::runtime_error("Error al enviar frame");
    }
    while (ret >= 0) {
        ret = avcodec_receive_packet(enc_ctx, pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0) {
            throw std::runtime_error("Error al codificar");
        }
        fwrite(pkt->data, 1, pkt->size, outfile);
        av_packet_unref(pkt);
    }
}

/*Inicializa un formato de salida.*/
OutputFormat::OutputFormat(
    const std::string& fileName, 
    int bufferWidth, 
    int bufferHeight) 
:   context(), 
    bufferWidth(bufferWidth), 
    bufferHeight(bufferHeight) {
    this->init_packet();
    AVOutputFormat * avOutputFormat = this->get_av_output_format(fileName);
    AVCodec *codec = this->get_av_codec(avOutputFormat);
    this->init_codec_context(codec);
    this->outputFile = fopen(fileName.c_str(), "wb");
    this->init_frame();
    this->init_sws_context();
}

/*
PRE: Recibe el nombre (const std::string &) 
del archivo grabacion de salida.
POST: Devuelve el formato de salida a 
utilizar (AVOutputFormat *).
*/
AVOutputFormat * OutputFormat::get_av_output_format(
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
        throw std::runtime_error("No se encontró formato de salida"); // Usar errores propios
    }
    
    // h.264 es bastante popular, pero hay mejores
    avOutputFormat->video_codec = AV_CODEC_ID_H264;
    return avOutputFormat;
} 

/*
PRE: Recibe el formato de salida del 
archivo de grabacion.
POST: Devuelve una instancia de codec 
(AVCodec *), para 
dicho formato.
*/
AVCodec * OutputFormat::get_av_codec(
    AVOutputFormat * avOutputFormat
){
    AVCodec *codec = avcodec_find_encoder(avOutputFormat->video_codec);
    if (!codec) {
        throw std::runtime_error("No se pudo instanciar codec");
    }
    return codec;
}

/*
PRE: Las dimensiones del formato de salida 
deben estar inicializados.
POST: Inicializa el contexto de SWS.
*/
void OutputFormat::init_sws_context(){
    this->swsContext = sws_getContext(
        this->bufferWidth, 
        this->bufferHeight,
        AV_PIX_FMT_RGB24, 
        this->bufferWidth, 
        this->bufferHeight,
        AV_PIX_FMT_YUV420P,
        0, 
        0, 
        0, 
        0
    );
}

/*
PRE: El contexto de codec debe estar 
inicializado.
POST: Inicializa el frame.
*/
void OutputFormat::init_frame() {
    this->frame = av_frame_alloc();
    if (!this->frame) {
        throw std::runtime_error("No se pudo reservar memoria para frame");
    }
    this->frame->format = this->codecContext->pix_fmt;
    this->frame->width  = this->codecContext->width;
    this->frame->height = this->codecContext->height;
    av_frame_get_buffer(this->frame, 0);
    this->currentPts = 0;
}

/*Inicializa el packet.*/
void OutputFormat::init_packet() {
    this->pkt = av_packet_alloc();
    if (!this->pkt) {
        throw std::runtime_error("No se pudo reservar memoria para packet");
    }
}

/*
PRE: Recibe el codec especifico para el 
archivo de grabacion de salida.
POST: Inicializa el contexto de codec.
*/
void OutputFormat::init_codec_context(AVCodec* codec){
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

/*Cierra el stream del video.*/
void OutputFormat::close() {
    encode(this->codecContext, NULL, this->pkt, this->outputFile);
    /* add sequence end code to have a real MPEG file */
    uint8_t endcode[] = { 0, 0, 1, 0xb7 };
    fwrite(endcode, 1, sizeof(endcode), this->outputFile);
}

/*
Destruye el formate de salida, 
primero cerrando el stream de 
video.
*/
OutputFormat::~OutputFormat() {
    // Termino grabacion.
    this->close();
    // Cierro contexto de SWS
    sws_freeContext(this->swsContext);
    // Etc ...
    avcodec_close(this->codecContext);
    avcodec_free_context(&this->codecContext);
    av_packet_free(&pkt);
    av_frame_free(&frame);
    fclose(this->outputFile);
}

void OutputFormat::writeFrame(const char* data) {
    const u_int8_t* tmp = (const u_int8_t*) data;
    // El ancho del video x3 por la cantidad de bytes
    int width = this->bufferWidth * 3;
    sws_scale(
        this->swsContext, 
        &tmp, 
        &width, 
        0, 
        this->frame->height, 
        this->frame->data, 
        this->frame->linesize
    );
    this->frame->pts = currentPts;
    this->currentPts++;
    /* encode the image */
    encode(this->codecContext, frame, pkt, this->outputFile);
}
