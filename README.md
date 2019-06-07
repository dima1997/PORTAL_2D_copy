# Portal
Implementación del Portal 1 en 2D como TP final de la materia Taller de Programación I (FIUBA).

## Compilar
Crear carpeta de compilacion (ejemplo build/)
Desde carpeta de compilacion ejecutar:

cmake ..
make && make install

(Puede ser que make install tire algunos errores debido a problemas de la libreria yaml, en cuyo caso ignorarlos)

## Ejecutar:
Servidor:
	./PORTAL-server
Se cierra escribiendo 'q', por consola.

Cliente:
	./PORTAL 
	(modo con ventanas qT, que hace que el juego ande trabado)
	Ejecutar en dos terminales:
		En la primera: utilizar la opcion new
		En la segunda: utilizar la opcion join, tras haber 			realizado el primer paso 

	./PORTAL localhost 8082 new 0
	(Inicia partida)
	./PORTAl localhost 8082 join 1
	(Unirse a partida que se inicio desde otra terminal)

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
