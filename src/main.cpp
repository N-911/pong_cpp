#include "Game.h"

int main() {

  Game game;
  game.game_loop();
  system ("leaks -q pong");
  return (0);
}
