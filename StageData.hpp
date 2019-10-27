#ifndef STAGEDATA_HPP
#define STAGEDATA_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>

#include "Objects.hpp"

class SoundHandler {
public:
  virtual void lightSE() = 0;
  virtual void heavySE() = 0;
  virtual void goalSE() = 0;
};

class StageData {
private:
  // TileMap's format:
  // 5x5, 0.Wall, 1.Space, 2.Start, 3.Goal, 4.Locked Door
  // 5~8.Medium Case(Left, Down, Right, Up), 9~12.Large Case(Left, Down, Right,
  // Up) 13~16.Medium Key Case(Left, Down, Right, Up), 17~20.Large Key
  // Case(Left, Down, Right, Up)
  std::unique_ptr<PlayerObject> player;
  std::vector<int> tileMap;
  std::vector<ObjectBase *> objects;
  bool isDoorLocked = true;
  int goalPosX, goalPosY;
  SDL_Renderer *renderer;
  std::vector<ObjectBase *> stack;
  SoundHandler *sound;
  int stackX = 0, stackY = 0;
  bool flag = false;

  void findObjectsAt(std::vector<ObjectBase *> *, int, int);
  void moveLeft();
  void moveDown();
  void moveRight();
  void moveUp();

public:
  StageData(std::initializer_list<int> &&);
  StageData(StageData &&) = default;
  ~StageData() = default;

  void setSoundHandler(SoundHandler *handler) { sound = handler; }
  bool mainLoop(SDL_Window *);
};

#endif /* end of include guard: STAGEDATA_HPP */
