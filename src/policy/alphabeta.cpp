#include <cstdlib>

#include "../state/state.hpp"
#include "./alphabeta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move AlphaBeta::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  Move best;
  int MAX = -__INT_MAX__, score;
  for (auto move: state->legal_actions) {
    score = alphabeta(state->next_state(move), depth, -__INT_MAX__, __INT_MAX__, true);
    if (score > MAX) {
      MAX = score;
      best = move;
    }
  }
  return best;
}

int AlphaBeta::alphabeta(State *state, int depth, int a, int b, bool maximize) {
  if (!depth) return state->evaluate();
  if (!state->legal_actions.size())
    state->get_legal_actions();
  int value;
  if (maximize) {
    value = -__INT_MAX__;
    for (auto move: state->legal_actions) {
      value = std::max(value, alphabeta(state->next_state(move), depth-1, a, b, false));
      a = std::max(a, value);
      if (a >= b) break;
    }
  } else {
    value = __INT_MAX__;
    for (auto move: state->legal_actions) {
      value = std::min(value, alphabeta(state->next_state(move), depth-1, a, b, false));
      b = std::min(b, value);
      if (b <= a) break;
    }
  }
  return value;
}