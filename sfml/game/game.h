#pragma once

#include <vector>
#include "../gamestate/gamestate.h"

class Game
{
public:
    Game();
    
    void setGameState(game_states gamestate);
    
    void draw();
    void update();
private:
    //game_state* current_game_state_ptr;
    std::vector<game_state*> current_game_states;
};