#ifndef LINE_INTERFACE_H
#define LINE_INTERFACE_H

#include "../../includes/game/game.h"

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
    Game _get_new_game(Connector & connector, 
                        uint8_t mapId, 
                        std::string & gameName);
    Game get_new_game(Connector & connector);
    
    uint8_t choose_game_id(std::map<uint8_t,std::string> 
                            & stockGames);
    Game _get_join_game(Connector & connector, uint8_t gameId);
    Game get_join_game(Connector & connector);

public:
    LineInterface(bool & keepInput);
    ~LineInterface();
    Game create_game();
};

#endif // LINE_INTERFACE_H
