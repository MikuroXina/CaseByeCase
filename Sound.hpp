#ifndef SOUND_HPP
#define SOUND_HPP

#include "StageData.hpp"

struct Mix_Chunk;

class SEManager : public SoundHandler {
  Mix_Chunk *light, *heavy, *goal;

public:
  SEManager();
  virtual ~SEManager() override;

public:
  virtual void lightSE() override;
  virtual void heavySE() override;
  virtual void goalSE() override;
};

#endif