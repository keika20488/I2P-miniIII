#include <cstdlib>

#include "../state/state.hpp"
#include "./random2.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Random2::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  int k = depth;
  auto actions = state->legal_actions;
  for (int i=0; i<depth; i++){
    k = rand()/k;
  }
  return actions[k%actions.size()];
}