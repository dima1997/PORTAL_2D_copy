# Portal
Implementación del Portal 1 en 2D como TP final de la materia Taller de Programación I (FIUBA).

## Protocolo

### Crear nuevo juego
El cliente le envía al servidor el comando _new_game_ (enum definido en common/protocol_code.h), seguido del _map_id_ que quiere utilizar (uint8_t) y un string con el nombre de partida.

El servidor le responde un status (otro enum definido en el mismo archivo). Si el status es _command_ok_, le envía el _game_id_ (uint8_t).

### Unirse a un juego
El cliente le envía al servidor el comando _join_game_, a lo cual el servidor le responde:
- Un uint_8 con la cantidad de partidas disponibles.
- Por cada partida, un uint_8 con el _game_id_ y un string con el nombre.

El cliente le envía el _game_id_ al que se quiere unir (uint8_t).

Si este juego no existe, el servidor le responde con un status _non_existent_game_.
Si la partida está llena, el servidor le responde con un status _game_is_full_.
Si se puede unir exitosamente, el servidor le responde con un status _command_ok_, seguido del _player_id_ (uint8_t).

## Modos de ejecucion

El server se inica ejecutando el comando (por terminal):  
	./PORTAL-server  
  
El Cliente se inicia ejecutando el comando (por terminal):  
	./PORTAL -c (interfaz por comando de linea)  
	./PORTAl -v (interfaz por ventanas QT)
	./PORTAL <ip> <port> <command> <id> (forma rapida, leer manual de usuario)

## Controles del juego (Jugador)

TECLADO:  
  
- A/FLECHA IZQUIERDA -> Moverse hacia izquierda  
- W/FLECHA ARRIBA -> Saltar  
- D/FLECHA DERECHA -> Moverse hacia derecha  
- ESPACIO/CONTROL DERECHO -> Tomar una roca  
- E/SHIFT DERECHO -> Soltar una roca a derecha  
- Q/MENOS -> Soltar una roca a izquierda  
- M -> Pausar/Continuar musica de fondo  
- V -> Pausar/Continuar grabacion del video  
	(Por defecto comienza pausado)  
	Durante el modo grabacion, la ventana toma dimensiones fijas, 
	que no podran redimensionarse hasta tanto no pausar la 
	grabacion. Ademas durante la grabacion se vera un icono rojo
	de play (>) en l esquina superior izquierda. 
- R/RETORNO -> Reset portales  
- K -> Mata al propio jugador  

MOUSE:  

- CLICK IZQUIERDO -> Abrir portal azul  
- CLICK DERECHO -> Abrir portal naranja  
- CLICK MEDIO -> Pin tool  



