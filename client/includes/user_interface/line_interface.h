#ifndef LINE_INTERFACE_H
#define LINE_INTERFACE_H

#include "../../includes/game/game_config.h"

#include <connector/connector.h>
#include <cstdint>
#include <map>

class LineInterface {
private:
    bool & keepInput;
    
    void keep_input(std::string & wantToQuit);
    Connector log_to_server();
    std::string choose_game_mode();

    uint8_t choose_map_id(std::vector<uint8_t> & mapIds);
    std::string choose_game_name();
    GameConfig _get_new_game(Connector & connector, 
                        uint8_t mapId, 
                        std::string & gameName);
    GameConfig get_new_game(Connector & connector);
    
    uint8_t choose_game_id(std::map<uint8_t,std::string> 
                            & stockGames);
    GameConfig _get_join_game(Connector & connector, uint8_t gameId);
    GameConfig get_join_game(Connector & connector);

    void wait_game_starts(Connector & connector);

public:
    LineInterface(bool & keepInput);
    ~LineInterface();
    GameConfig create_game();
};

#endif // LINE_INTERFACE_H
