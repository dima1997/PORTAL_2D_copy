
/*Inicializa un mixer encargado de manejar todos los sonidos.*/
Mixer::Mixer(){
    if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0){
        std::cout << "Debo imprmir error";
    }
}

/*Destruye el mixer.*/
Mixer::Mixer(){
    Mix_Quit();
}