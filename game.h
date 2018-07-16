struct GameState {
    const uint8_t patternLen = 8; // TODO pass in constructor
    const uint8_t availableItemsLen = 4; // TODO pass in constructor

    uint8_t gameStep;
    uint8_t gameLevel;
    uint8_t attempt;
    uint8_t pattern[8];
    bool playerTurn;

    void reset() {
        gameStep = 0;
        gameLevel = 0;
        attempt = 0;
        playerTurn = false;
        newPattern(pattern, patternLen);
    }

    void newPattern(uint8_t pattern[], uint8_t len) {
        for (uint8_t i = 0; i < len; i++){
            pattern[i] = random(0, availableItemsLen);
        }
    }
};
