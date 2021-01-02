#ifndef PONG_SRC_GAMEPLAYCONTROLLER_H_
#define PONG_SRC_GAMEPLAYCONTROLLER_H_
#include <vector>

class GamePlayController {
 public:
  struct Score {
    int left;
    int right;
  };

 public:
  GamePlayController();
  virtual ~GamePlayController();
  void add_score(int side);
  void check_win();

  Score get_score() const { return {m_score_left, m_score_right}; }

 private:
  std::vector<int> m_score;

  int m_score_left;
  int m_score_right;
  int m_count_win_right;
  int m_count_win_left;
  int m_game_count;
  int m_score_target;  // количество очков доя победи
  void reset_score();
};

#endif //PONG_SRC_GAMEPLAYCONTROLLER_H_
