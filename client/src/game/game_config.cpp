GameConfig::GameConfig() {}

GameConfig::~GameConfig() = default;

void GameConfig::setConnector(Connector & connector){
    this->connector = std::move(connector);
}

void GameConfig::setGameId(uint8_t id){
    this->gameId = id;
}

void GameConfig::setPlayerId(uint32_t id){
    this->playerId = id;
}

void GameConfig::setMapId(uint8_t id){
    this->mapId = id;
}

Game GameConfig::createGame(){
    return std::move(Game(
        this->connector, 
        this->gameId, 
        this->playerId, 
        this->mapId
    ));
}