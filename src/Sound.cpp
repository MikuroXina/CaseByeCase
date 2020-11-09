#include "Sound.hpp"

#include <SDL2/SDL_mixer.h>
#include <iostream>

SEManager::SEManager() {
  light = Mix_LoadWAV("assets/lightSE.wav");
  heavy = Mix_LoadWAV("assets/heavySE.wav");
  goal = Mix_LoadWAV("assets/goalSE.wav");
}

SEManager::~SEManager() {
  Mix_FreeChunk(light);
  Mix_FreeChunk(heavy);
  Mix_FreeChunk(goal);
}

void SEManager::lightSE() {
  if (Mix_PlayChannel(-1, light, 0) == -1) {
    std::cerr << "Error to play light SE" << std::endl;
  }
}

void SEManager::heavySE() {
  if (Mix_PlayChannel(-1, heavy, 0) == -1) {
    std::cerr << "Error to play heavy SE" << std::endl;
  }
}

void SEManager::goalSE() {
  if (Mix_PlayChannel(-1, goal, 0) == -1) {
    std::cerr << "Error to play goal SE" << std::endl;
  }
}
