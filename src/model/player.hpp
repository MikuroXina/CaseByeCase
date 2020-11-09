#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "./direction.hpp"
#include "./pos.hpp"

class Player {
  Pos _pos;

public:
  Player(Pos initialPos) : _pos(initialPos) {}

  void move(Dir dir);
};

#endif // PLAYER_HPP
