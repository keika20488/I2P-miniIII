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
  int score, MAX = -__INT_MAX__;
  for (auto move: state->legal_actions) {
    score = minimax(state->next_state(move), depth-1, false);
    if (score > MAX) {
      MAX = score;
      best = move;
    }
  }
  return best;
}

int Minimax::minimax(State *state, int depth, bool maximize) {
  if (!state->legal_actions.size())
    state->get_legal_actions();

  if (state->legal_actions.empty()) {
    if (state->game_state == WIN)
      return maximize ? __INT_MAX__ : -__INT_MAX__;
    else return maximize ? -__INT_MAX__ : __INT_MAX__;
  }

  if (!depth) return state->evaluate();

  int value;
  auto actions = state->legal_actions;
  State *next;
  if (maximize) {
    value = -__INT_MAX__;
    for (auto move: actions){
      next = state->next_state(move);
      value = std::max(value, minimax(next, depth-1, false));
    }
  } else {
    value = __INT_MAX__;
    for (auto move: actions){
      next = state->next_state(move);
      value = std::min(value, minimax(next, depth-1, true));
    }
  }
  return value;
}