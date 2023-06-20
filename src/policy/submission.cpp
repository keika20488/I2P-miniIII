#include <cstdlib>

#include "../state/state.hpp"
#include "./alphabeta.hpp"


/**
 * @brief get a legal action by alpha beta
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move AlphaBeta::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  Move best = state->legal_actions[0];
  int MAX = -__INT_MAX__, score;
  for (auto move: state->legal_actions) {
    score = alphabeta(state->next_state(move), depth, -__INT_MAX__, __INT_MAX__, false);
    if (score > MAX) {
      MAX = score;
      best = move;
    }
  }
  return best;
}

int AlphaBeta::alphabeta(State *state, int depth, int a, int b, bool maximize) {
  if (!state->legal_actions.size())
    state->get_legal_actions();

  if (state->game_state == WIN)
    return maximize ? __INT_MAX__ : -__INT_MAX__;

  if (!depth) return state->evaluate();
  
  int value;
  auto actions = state->legal_actions;
  State *next;
  if (maximize) {
    value = -__INT_MAX__;
    for (auto move: actions) {
      next = state->next_state(move);
      value = std::max(value, alphabeta(next, depth-1, a, b, false));
      a = std::max(a, value);
      if (a >= b) break;
    }
  } else {
    value = __INT_MAX__;
    for (auto move: actions) {
      next = state->next_state(move);
      value = std::min(value, alphabeta(next, depth-1, a, b, true));
      b = std::min(b, value);
      if (b <= a) break;
    }
  }
  return value;
}