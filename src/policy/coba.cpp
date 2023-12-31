#include <cstdlib>
#include "../state/state.hpp"
#include "./coba.hpp"


/**
 * @brief get a legal action by alpha-beta
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int min = -1000000;
int max = 1000000;

Move Minimax::get_move(State* state, int depth) {
  if (!state->legal_actions.size())
    state->get_legal_actions();

  int bestScore = 0;
  Move bestMove;

  if(state->player == 0){
    bestScore = min;
  }
  else if(state->player == 1){
    bestScore = max;
  }

  for (auto action : state->legal_actions) {
    State* nextState = state->next_state(action);
    int score = minimax(nextState, depth - 1, min, max, state->player );
    delete nextState;

    if(state->player == 0 && score > bestScore){
      bestScore = score;
      bestMove = action;
    }
    else if(state->player == 1 && score < bestScore){
      bestScore = score;
      bestMove = action;
    }
  }

  return bestMove;
}

int Minimax::minimax(State* state, int depth, int alpha, int beta, bool maximizingPlayer) {
  if(!state->legal_actions.size()){
      state->get_legal_actions();
  }
  if (depth == 0 || state->legal_actions.empty()) {
    return state->evaluate();
  }

  if (maximizingPlayer) {
    int maxScore = min;
    for (auto action : state->legal_actions) {
      State* nextState = state->next_state(action);
      int score = minimax(nextState, depth - 1, alpha, beta, false);
      delete nextState;

      maxScore = std::max(maxScore, score);
      alpha = std::max(alpha, score);

      if (beta <= alpha) {
        break;  // Beta cutoff
      }
    }
    return maxScore;
  } else {
    int minScore = max;
    for (const auto& action : state->legal_actions) {
      State* nextState = state->next_state(action);
      int score = minimax(nextState, depth - 1, alpha, beta, true);
      delete nextState;

      minScore = std::min(minScore, score);
      beta = std::min(beta, score);

      if (beta <= alpha) {
        break;  // Alpha cutoff
      }
    }
    return minScore;
  }
}