#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
  if (!state->legal_actions.size())
    state->get_legal_actions();
  
  Move best;
  int MAX = -__INT_MAX__, score;
  for (auto move: state->legal_actions) {
    score = minimax(state->next_state(move), depth, true);
    if (score > MAX) {
      MAX = score;
      best = move;
    }
  }
  return best;
}

int Minimax::minimax(State *state, int depth, bool maximize) {
  if (!depth) return state->evaluate();
  if (!state->legal_actions.size())
    state->get_legal_actions();
  int value;
  if (maximize) {
    value = -__INT_MAX__;
    for (auto move: state->legal_actions)
      value = std::max(value, minimax(state->next_state(move), depth-1, false));
  } else {
    value = __INT_MAX__;
    for (auto move: state->legal_actions)
      value = std::min(value, minimax(state->next_state(move), depth-1, true));
  }
  return value;
}