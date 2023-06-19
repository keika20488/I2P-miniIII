#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
const int MAX_DEPTH = 4;
class AlphaBeta{
public:
  static Move get_move(State *state, int depth);
  static int alphabeta(State *state, int depth, int a, int b, bool maximize);
};