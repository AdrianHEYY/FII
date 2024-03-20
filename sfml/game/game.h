#pragma once

#include <vector>
#include "../gamestate/gamestate.h"

class Game
{
public:
    Game();
    
    void setGameState(game_states gamestate);
    void removeGameState(game_states gamestate);

    void draw();
    void update();
private:
    void clear_states();
    std::vector<game_state*> current_game_states;
    game_states next_game_state, next_remove_game_state;
};