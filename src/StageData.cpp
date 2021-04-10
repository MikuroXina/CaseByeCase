#include <OpenGL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <algorithm>
#include <iostream>

#include "Objects.hpp"
#include "StageData.hpp"

StageData::StageData(Tile tiles[25])
    : player(std::make_unique<PlayerObject>()) {

  // TileMap setup
  for (int i = 0; i < 25; ++i) {
    if (tiles[i] == Tile::Wall) {
      auto newWall = new Wall;
      int x = i / 5, y = i % 5;
      newWall->moveTo(x, y);
      objects.push_back(newWall);
      std::cout << "Made a wall at " << i << std::endl;
    } else if (tiles[i] == Tile::Start) {
      int x = i / 5, y = i % 5;
      player->moveTo(x, y);

      std::cout << "Made a player at " << i << std::endl;
    } else if (tiles[i] == Tile::Goal) {
      goalPosX = i / 5;
      goalPosY = i % 5;
      std::cout << "The goal at (" << goalPosX << "," << goalPosY << ")"
                << std::endl;
    } else if (tiles[i] == Tile::LockedDoor) {
      isDoorLocked = true;
      int x = i / 5, y = i % 5;
      auto newLockedDoor = new LockedDoor(&isDoorLocked);
      newLockedDoor->moveTo(x, y);
      objects.push_back(newLockedDoor);
      std::cout << "Made a locked door at " << i << std::endl;
    } else if (Tile::LeftMediumCase <= tiles[i] &&
               tiles[i] <= Tile::UpMediumCase) {
      auto direction = (int)tiles[i] - 5;
      int x = i / 5, y = i % 5;
      auto newMediumCase = new MediumCase(direction, false);
      newMediumCase->moveTo(x, y);
      objects.push_back(newMediumCase);
      std::cout << "Made a medium case at " << i << ". Dir:" << direction
                << std::endl;
    } else if (Tile::LeftLargeCase <= tiles[i] &&
               tiles[i] <= Tile::UpLargeCase) {
      auto direction = (int)tiles[i] - 9;
      int x = i / 5, y = i % 5;
      auto newLargeCase = new LargeCase(direction, false);
      newLargeCase->moveTo(x, y);
      objects.push_back(newLargeCase);
      std::cout << "Made a large case at " << i << ". Dir:" << direction
                << std::endl;
    } else if (Tile::KeyLeftMediumCase <= tiles[i] &&
               tiles[i] <= Tile::KeyUpMediumCase) {
      auto direction = (int)tiles[i] - 13;
      int x = i / 5, y = i % 5;
      auto newLargeCase = new MediumCase(direction, true);
      newLargeCase->moveTo(x, y);
      objects.push_back(newLargeCase);
      std::cout << "Made a medium key case at " << i << ". Dir:" << direction
                << std::endl;
    } else if (Tile::KeyLeftLargeCase <= tiles[i] &&
               tiles[i] <= Tile::KeyUpLargeCase) {
      auto direction = (int)tiles[i] - 17;
      int x = i / 5, y = i % 5;
      auto newLargeCase = new LargeCase(direction, true);
      newLargeCase->moveTo(x, y);
      objects.push_back(newLargeCase);
      std::cout << "Made a large key case at " << i << ". Dir:" << direction
                << std::endl;
    }
  }
}

void StageData::findObjectsAt(std::vector<ObjectBase *> *stack, int x, int y) {
  for (auto &object : objects) {
    if (object->getPosX() == x && object->getPosY() == y) {
      stack->push_back(object);
    }
  }
}

bool StageData::mainLoop(SDL_Window *window) {
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

  SDL_Event event;
  bool quit = false, reset = false;
  while (!quit) {
    // If on the goal
    if (player->getPosX() == goalPosX && player->getPosY() == goalPosY) {
      SDL_Delay(500);
      sound->goalSE();
      SDL_Delay(1500);
      quit = true;
    }

    // If unlocked the key
    if (player->holdedMedCase != nullptr && player->holdedLarCase != nullptr) {
      if (player->holdedMedCase->isKeyCase() &&
          player->holdedLarCase->isKeyCase()) {
        isDoorLocked = false;
      }
    }

    // Events
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          std::cout << "Pressed ESC key!" << std::endl;
          quit = true;
          break;
        case SDLK_r:
          std::cout << "Resetting..." << std::endl;
          reset = true;
          quit = true;
          break;
        case SDLK_DOWN:
          moveDown();
          break;
        case SDLK_UP:
          moveUp();
          break;
        case SDLK_LEFT:
          moveLeft();
          break;
        case SDLK_RIGHT:
          moveRight();
          break;
        }
      }
    }

    // Render
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render the goal
    glColor3f(0, 1.0, 0);
    glRectd(goalPosY * 100 + 30, goalPosX * 100 + 30, goalPosY * 100 + 70,
            goalPosX * 100 + 70);
    for (auto &object : objects) {
      object->render();
    }
    player->render();

    SDL_GL_SwapWindow(window);

    SDL_Delay(1);
  }

  for (auto &object : objects) {
    delete object;
  }
  objects.clear();

  return reset;
}

void StageData::moveLeft() {
  findObjectsAt(&stack, player->getPosX(), player->getPosY() - 1);

  flag = (player->getPosY() > 0);
  for (auto &object : stack) {
    flag = (flag ? object->isCutRight() : false);
    if (player->holdedMedCase != nullptr && player->holdedLarCase != nullptr) {
      flag =
          (flag ? object->getSize() <= 3 || (object->isCutRight() &&
                                             player->holdedLarCase->isCutLeft())
                : false);
    } else if (player->holdedMedCase != nullptr) {
      flag =
          (flag ? object->getSize() > 1 || (object->isCutRight() &&
                                            player->holdedMedCase->isCutLeft())
                : false);
    } else if (player->holdedLarCase != nullptr) {
      flag =
          (flag ? object->getSize() > 2 || (object->isCutRight() &&
                                            player->holdedLarCase->isCutLeft())
                : false);
    }
  }
  stack.clear();

  if (flag) {
    stackX = player->getPosX();
    stackY = player->getPosY() - 1;
    player->moveTo(stackX, stackY);
    if (player->holdedLarCase != nullptr) {
      if (player->holdedLarCase->isCutLeft()) {
        if (player->holdedMedCase != nullptr) {
          if (!(player->holdedMedCase->isCutLeft())) {
            player->holdedMedCase->moveTo(stackX, stackY);
          } else {
            player->holdedMedCase = nullptr;
          }
          player->holdedLarCase = nullptr;
        } else {
          player->holdedLarCase = nullptr;
        }
      } else {
        player->holdedLarCase->moveTo(stackX, stackY);
        if (player->holdedMedCase != nullptr) {
          player->holdedMedCase->moveTo(stackX, stackY);
        }
      }
    } else {
      if (player->holdedMedCase != nullptr) {
        if (!(player->holdedMedCase->isCutLeft())) {
          player->holdedMedCase->moveTo(stackX, stackY);
        } else {
          player->holdedMedCase = nullptr;
        }
      }
    }
    findObjectsAt(&stack, player->getPosX(), player->getPosY());
    for (auto &object : stack) {
      if (object->getSize() == 1) {
        player->holdedMedCase = dynamic_cast<MediumCase *>(object);
      }
      if (object->getSize() == 2) {
        player->holdedLarCase = dynamic_cast<LargeCase *>(object);
      }
    }
    stack.clear();
    sound->lightSE();
  } else {
    sound->heavySE();
  }
}

void StageData::moveDown() {
  findObjectsAt(&stack, player->getPosX() + 1, player->getPosY());

  flag = (player->getPosX() < 4);
  for (auto &object : stack) {
    flag = (flag ? object->isCutUp() : false);
    if (player->holdedMedCase != nullptr && player->holdedLarCase != nullptr) {
      flag =
          (flag ? object->getSize() <= 3 ||
                      (object->isCutUp() && player->holdedLarCase->isCutDown())
                : false);
    } else if (player->holdedMedCase != nullptr) {
      flag =
          (flag ? object->getSize() > 1 ||
                      (object->isCutUp() && player->holdedMedCase->isCutDown())
                : false);
    } else if (player->holdedLarCase != nullptr) {
      flag =
          (flag ? object->getSize() > 2 ||
                      (object->isCutUp() && player->holdedLarCase->isCutDown())
                : false);
    }
  }
  stack.clear();

  if (flag) {
    stackX = player->getPosX() + 1;
    stackY = player->getPosY();
    player->moveTo(stackX, stackY);
    if (player->holdedLarCase != nullptr) {
      if (player->holdedLarCase->isCutDown()) {
        if (player->holdedMedCase != nullptr) {
          if (!(player->holdedMedCase->isCutDown())) {
            player->holdedMedCase->moveTo(stackX, stackY);
          } else {
            player->holdedMedCase = nullptr;
          }
          player->holdedLarCase = nullptr;
        } else {
          player->holdedLarCase = nullptr;
        }
      } else {
        player->holdedLarCase->moveTo(stackX, stackY);
        if (player->holdedMedCase != nullptr) {
          player->holdedMedCase->moveTo(stackX, stackY);
        }
      }
    } else {
      if (player->holdedMedCase != nullptr) {
        if (!(player->holdedMedCase->isCutDown())) {
          player->holdedMedCase->moveTo(stackX, stackY);
        } else {
          player->holdedMedCase = nullptr;
        }
      }
    }
    findObjectsAt(&stack, player->getPosX(), player->getPosY());
    for (auto &object : stack) {
      if (object->getSize() == 1) {
        player->holdedMedCase = dynamic_cast<MediumCase *>(object);
      }
      if (object->getSize() == 2) {
        player->holdedLarCase = dynamic_cast<LargeCase *>(object);
      }
    }
    stack.clear();
    sound->lightSE();
  } else {
    sound->heavySE();
  }
}

void StageData::moveRight() {
  findObjectsAt(&stack, player->getPosX(), player->getPosY() + 1);

  flag = (player->getPosY() < 4);
  for (auto &object : stack) {
    flag = (flag ? object->isCutLeft() : false);
    if (player->holdedMedCase != nullptr && player->holdedLarCase != nullptr) {
      flag = (flag ? object->getSize() <= 3 ||
                         (object->isCutLeft() &&
                          player->holdedLarCase->isCutRight())
                   : false);
    } else if (player->holdedMedCase != nullptr) {
      flag =
          (flag ? object->getSize() > 1 || (object->isCutLeft() &&
                                            player->holdedMedCase->isCutRight())
                : false);
    } else if (player->holdedLarCase != nullptr) {
      flag =
          (flag ? object->getSize() > 2 || (object->isCutLeft() &&
                                            player->holdedLarCase->isCutRight())
                : false);
    }
  }
  stack.clear();

  if (flag) {
    stackX = player->getPosX();
    stackY = player->getPosY() + 1;
    player->moveTo(stackX, stackY);
    if (player->holdedLarCase != nullptr) {
      if (player->holdedLarCase->isCutRight()) {
        if (player->holdedMedCase != nullptr) {
          if (!(player->holdedMedCase->isCutRight())) {
            player->holdedMedCase->moveTo(stackX, stackY);
          } else {
            player->holdedMedCase = nullptr;
          }
          player->holdedLarCase = nullptr;
        } else {
          player->holdedLarCase = nullptr;
        }
      } else {
        player->holdedLarCase->moveTo(stackX, stackY);
        if (player->holdedMedCase != nullptr) {
          player->holdedMedCase->moveTo(stackX, stackY);
        }
      }
    } else {
      if (player->holdedMedCase != nullptr) {
        if (!(player->holdedMedCase->isCutRight())) {
          player->holdedMedCase->moveTo(stackX, stackY);
        } else {
          player->holdedMedCase = nullptr;
        }
      }
    }
    findObjectsAt(&stack, player->getPosX(), player->getPosY());
    for (auto &object : stack) {
      if (object->getSize() == 1) {
        player->holdedMedCase = dynamic_cast<MediumCase *>(object);
      }
      if (object->getSize() == 2) {
        player->holdedLarCase = dynamic_cast<LargeCase *>(object);
      }
    }
    stack.clear();
    sound->lightSE();
  } else {
    sound->heavySE();
  }
}

void StageData::moveUp() {
  findObjectsAt(&stack, player->getPosX() - 1, player->getPosY());

  flag = (player->getPosX() > 0);
  for (auto &object : stack) {
    flag = (flag ? object->isCutDown() : false);
    if (player->holdedMedCase != nullptr && player->holdedLarCase != nullptr) {
      flag =
          (flag ? object->getSize() <= 3 ||
                      (object->isCutDown() && player->holdedLarCase->isCutUp())
                : false);
    } else if (player->holdedMedCase != nullptr) {
      flag = (flag ? object->getSize() > 1 || (object->isCutDown() &&
                                               player->holdedMedCase->isCutUp())
                   : false);
    } else if (player->holdedLarCase != nullptr) {
      flag = (flag ? object->getSize() > 2 || (object->isCutDown() &&
                                               player->holdedLarCase->isCutUp())
                   : false);
    }
  }
  stack.clear();

  if (flag) {
    stackX = player->getPosX() - 1;
    stackY = player->getPosY();
    player->moveTo(stackX, stackY);
    if (player->holdedLarCase != nullptr) {
      if (player->holdedLarCase->isCutUp()) {
        if (player->holdedMedCase != nullptr) {
          if (!(player->holdedMedCase->isCutUp())) {
            player->holdedMedCase->moveTo(stackX, stackY);
          } else {
            player->holdedMedCase = nullptr;
          }
          player->holdedLarCase = nullptr;
        } else {
          player->holdedLarCase = nullptr;
        }
      } else {
        player->holdedLarCase->moveTo(stackX, stackY);
        if (player->holdedMedCase != nullptr) {
          player->holdedMedCase->moveTo(stackX, stackY);
        }
      }
    } else {
      if (player->holdedMedCase != nullptr) {
        if (!(player->holdedMedCase->isCutUp())) {
          player->holdedMedCase->moveTo(stackX, stackY);
        } else {
          player->holdedMedCase = nullptr;
        }
      }
    }
    findObjectsAt(&stack, player->getPosX(), player->getPosY());
    for (auto &object : stack) {
      if (object->getSize() == 1) {
        player->holdedMedCase = dynamic_cast<MediumCase *>(object);
      }
      if (object->getSize() == 2) {
        player->holdedLarCase = dynamic_cast<LargeCase *>(object);
      }
    }
    stack.clear();
    sound->lightSE();
  } else {
    sound->heavySE();
  }
}
