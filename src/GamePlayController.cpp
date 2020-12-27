#include "GamePlayController.h"

GamePlayController::GamePlayController() {
  m_score_left = 0;
  m_score_right = 0;
  m_game_count = 0;
  m_score_target = 21;
  m_game_count = 0;
}

void GamePlayController::add_score(int side) {
  if (side == 0) {
    m_score_left++;
  } else if (side == 1) {
    m_score_right++;
  } else {
    return;
  }
}

void GamePlayController::check_win() {
  if (m_score_left >= m_score_target || m_score_right >= m_score_target) {
      m_game_count++;
  }
  if (m_score_left >= m_score_target) {
    m_count_win_left++;
    reset_score();
  } else if (m_score_right >= m_score_target) {
    m_count_win_right++;
    reset_score();
  }
}

void GamePlayController::reset_score() {
  m_score_right = 0;
  m_score_left = 0;
}
GamePlayController::~GamePlayController() {

}
