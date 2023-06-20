#include <cstdlib>
#include "../state/state.hpp"
#include "./submission.hpp"


/**
 * @brief get a legal action by alpha-beta
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int minValue = -1000000;
int maxValue = 1000000;

Move Submission::get_move(State* state, int depth) {
  if (!state->legal_actions.size())
    state->get_legal_actions();

  int IdealScore = 0;
  Move FinalMove;

  if(state->player == 0){
    IdealScore = minValue;
  }
  else if(state->player == 1){
    IdealScore = maxValue;
  }

  for (auto action : state->legal_actions) {
    State* nextState = state->next_state(action);
    int point = algo(nextState, depth - 1, minValue, maxValue, state->player );
    delete nextState;

    if(state->player == 0 && point > IdealScore){
      IdealScore = point;
      FinalMove = action;
    }
    else if(state->player == 1 && point < IdealScore){
      IdealScore = point;
      FinalMove = action;
    }
  }

  return FinalMove;
}

int Submission::algo(State* state, int depth, int alpha, int beta, bool maxPlay) {
  int score, FinalScore;
  if(!state->legal_actions.size()){
      state->get_legal_actions();
  }
  if (depth == 0 || state->legal_actions.empty()) {
    return state->evaluate();
  }

  if (maxPlay) {
    FinalScore = minValue;
    for (auto action : state->legal_actions) {
      State* nextState = state->next_state(action);
      score = algo(nextState, depth - 1, alpha, beta, false);
      delete nextState;

      FinalScore = std::max(FinalScore, score);
      alpha = std::max(alpha, score);

      if (alpha >= beta) {
        break;  
        // Beta cutoff
      }
    }
    return FinalScore;
  } else {
    FinalScore = maxValue;
    for (const auto& action : state->legal_actions) {
      State* nextState = state->next_state(action);
      score = algo(nextState, depth - 1, alpha, beta, true);
      delete nextState;

      FinalScore = std::min(FinalScore, score);
      beta = std::min(beta, score);

      if (beta <= alpha) {
        break;  
        // Alpha cutoff
      }
    }
    return FinalScore;
  }
}