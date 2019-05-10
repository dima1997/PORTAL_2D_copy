# Portal
Implementación del Portal 1 en 2D como TP final de la materia Taller de Programación I (FIUBA).

## Protocolo

### Crear nuevo juego
El cliente le envía al servidor el comando _new_game_ (enum definido en common/protocol_code.h), seguido del _map_id_ que quiere utilizar (uint8_t).

El servidor le responde un status (otro enum definido en el mismo archivo). Si el status es _command_ok_, le envía el _game_id_ (uint_8).

### Unirse a un juego
El cliente le envía al servidor el comando _join_game_, seguido del _game_id_ al que se quiere unir (uint8_t).

Si este juego no existe, el servidor le responde con un status _non_existent_game_.
Si la partida está llena, el servidor le responde con un status _game_is_full_.
Si se puede unir exitosamente, el servidor le responde con un status _command_ok_, seguido del _player_id_ (uint8_t).