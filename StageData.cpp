#include <OpenGL/gl.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <algorithm>

#include "StageData.hpp"
#include "Objects.hpp"

StageData::StageData(std::vector<int>&& tileMap) {
	bool isPlayerMade = false;
	for(int i=0; i<static_cast<int>(tileMap.size()); i+=1) {
		if (tileMap[i] == 0) {
			auto newWall = new Wall;
			int x = i / 5, y = i % 5;
			newWall->moveTo(x, y);
			objects.push_back(newWall);
			std::cout << "Made a wall at " << i << std::endl;
		} else if (tileMap[i] == 2 && !isPlayerMade) {
			int x = i / 5;
			int y = i % 5;
			player= new PlayerObject;
			player->moveTo(x, y);

			std::cout << "Made a player at " << i << std::endl;
			isPlayerMade = true;
		} else if (tileMap[i] == 3) {
			goalPosX = i / 5;
			goalPosY = i % 5;
			std::cout << "The goal at ("<<goalPosX<<","<<goalPosY<<")"<< std::endl;
		} else if (tileMap[i] == 4) {
			isDoorLocked = true;
			auto newLockedDoor = new LockedDoor(&isDoorLocked);
			objects.push_back(newLockedDoor);
		} else if (tileMap[i] >= 5 && tileMap[i] <= 8) {
			auto direction = i - 5;
			auto newMediumCase = new MediumCase(direction);
			objects.push_back(newMediumCase);
		} else if (tileMap[i] >= 9 && tileMap[i] <= 12) {
			auto direction = i - 9;
			auto newLargeCase = new LargeCase(direction);
			objects.push_back(newLargeCase);
		}
	}

	if (!isPlayerMade) {
		std::cout<<"Error! The player creating has failed!"<<std::endl;
	}
}

StageData::~StageData() {
	delete player;
	for(auto& object : objects) {
		delete object;
	}
}

void StageData::findObjectsAt(std::vector<ObjectBase*> *stack, int x, int y) {
	for (auto& object : objects) {
		if (object->getPosX() == x && object->getPosY() == y) {
			stack->push_back(object);
		}
	}
}

void StageData::mainLoop(SDL_Window *window) {
	// Audio setup
	lightSE = Mix_LoadWAV("lightSE.wav");
	heavySE = Mix_LoadWAV("heavySE.wav");
	goalSE = Mix_LoadWAV("goalSE.wav");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	SDL_Event event;
  bool quit=false, flag=false;
  while (!quit) {
		// If on the goal
		if (player->getPosX() == goalPosX && player->getPosY() == goalPosY) {
			if (Mix_PlayChannel(-1, goalSE, 0) == -1) {
				std::cout<<"Error to play goalSE"<<std::endl;
			}
			SDL_Delay(3000);
			quit = true;
		}

		// If unlocked the key
		if (player->holdedMedCase != nullptr && player->holdedLarCase != nullptr) {
			isDoorLocked = false;
		}

    // Events
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          std::cout<<"Pressed ESC key!"<<std::endl;
          quit=true;
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

		for(auto& object : objects) {
			object->render();
		}
		player->render();

    SDL_GL_SwapWindow(window);

    SDL_Delay(1);
  }

	// Audio desturction
	Mix_FreeChunk(lightSE);
	Mix_FreeChunk(heavySE);
	Mix_FreeChunk(goalSE);

}

void StageData::moveLeft() {
	findObjectsAt(&stack, player->getPosX(), player->getPosY() - 1);

	flag = (player->getPosY() <= 0);
	for (auto& object : stack) {
		flag = (flag ? true : !(object->isCutRight()));
		if (player->holdedMedCase != nullptr) {
			flag = object->getSize() == 0;
		} else if (player->holdedLarCase != nullptr) {
			flag = object->getSize() <= 1;
		}
	}
	stack.clear();

	if (!flag) {
		stackX=player->getPosX();
		stackY=player->getPosY() - 1;
		player->moveTo(stackX, stackY);
		if (player->holdedLarCase != nullptr) {
			if (player->holdedLarCase->isCutLeft()) {
				if (player->holdedMedCase != nullptr) {
					if (!(player->holdedMedCase->isCutLeft())) {
						player->holdedMedCase->moveTo(stackX, stackY);
					}
				}
			} else {
				if (player->holdedMedCase != nullptr) {
					player->holdedMedCase->moveTo(stackX, stackY);
					player->holdedLarCase->moveTo(stackX, stackY);
				}
			}
		} else {
			if (player->holdedMedCase != nullptr) {
				if (!(player->holdedMedCase->isCutLeft())) {
					player->holdedMedCase->moveTo(stackX, stackY);
				}
			}
		}
		findObjectsAt(&stack, player->getPosX(), player->getPosY());
		for (auto& object : stack) {
			if (object->getSize() == 1) {
				player->holdedMedCase = object;
			}
			if (object->getSize() == 2) {
				player->holdedLarCase = object;
			}
		}
		stack.clear();
		if (Mix_PlayChannel(-1, lightSE, 0) == -1) {
			std::cout<<"Error to play lightSE"<<std::endl;
		}
	} else {
		if (Mix_PlayChannel(-1, heavySE, 0) == -1) {
			std::cout<<"Error to play heavySE"<<std::endl;
		}
	}
}

void StageData::moveDown() {
	findObjectsAt(&stack, player->getPosX() + 1, player->getPosY());

	flag = (player->getPosY() >= 4);
	for (auto& object : stack) {
		flag = (flag ? true : !(object->isCutUp()));
		if (player->holdedMedCase != nullptr) {
			flag = object->getSize() == 0;
		} else if (player->holdedLarCase != nullptr) {
			flag = object->getSize() <= 1;
		}
	}
	stack.clear();

	if (!flag) {
		stackX=player->getPosX() + 1;
		stackY=player->getPosY();
		player->moveTo(stackX, stackY);
		if (player->holdedLarCase != nullptr) {
			if (player->holdedLarCase->isCutDown()) {
				if (player->holdedMedCase != nullptr) {
					if (!(player->holdedMedCase->isCutDown())) {
						player->holdedMedCase->moveTo(stackX, stackY);
					}
				}
			} else {
				if (player->holdedMedCase != nullptr) {
					player->holdedMedCase->moveTo(stackX, stackY);
					player->holdedLarCase->moveTo(stackX, stackY);
				}
			}
		} else {
			if (player->holdedMedCase != nullptr) {
				if (!(player->holdedMedCase->isCutDown())) {
					player->holdedMedCase->moveTo(stackX, stackY);
				}
			}
		}
		findObjectsAt(&stack, player->getPosX(), player->getPosY());
		for (auto& object : stack) {
			if (object->getSize() == 1) {
				player->holdedMedCase = object;
			}
			if (object->getSize() == 2) {
				player->holdedLarCase = object;
			}
		}
		stack.clear();
		if (Mix_PlayChannel(-1, lightSE, 0) == -1) {
			std::cout<<"Error to play lightSE"<<std::endl;
		}
	} else {
		if (Mix_PlayChannel(-1, heavySE, 0) == -1) {
			std::cout<<"Error to play heavySE"<<std::endl;
		}
	}
}

void StageData::moveRight() {
	findObjectsAt(&stack, player->getPosX(), player->getPosY() + 1);

	flag = (player->getPosY() >= 4);
	for (auto& object : stack) {
		flag = (flag ? true : !(object->isCutLeft()));
		if (player->holdedMedCase != nullptr) {
			flag = object->getSize() == 0;
		} else if (player->holdedLarCase != nullptr) {
			flag = object->getSize() <= 1;
		}
	}
	stack.clear();

	if (!flag) {
		stackX=player->getPosX();
		stackY=player->getPosY() + 1;
		player->moveTo(stackX, stackY);
		if (player->holdedLarCase != nullptr) {
			if (player->holdedLarCase->isCutRight()) {
				if (player->holdedMedCase != nullptr) {
					if (!(player->holdedMedCase->isCutRight())) {
						player->holdedMedCase->moveTo(stackX, stackY);
					}
				}
			} else {
				if (player->holdedMedCase != nullptr) {
					player->holdedMedCase->moveTo(stackX, stackY);
					player->holdedLarCase->moveTo(stackX, stackY);
				}
			}
		} else {
			if (player->holdedMedCase != nullptr) {
				if (!(player->holdedMedCase->isCutRight())) {
					player->holdedMedCase->moveTo(stackX, stackY);
				}
			}
		}
		findObjectsAt(&stack, player->getPosX(), player->getPosY());
		for (auto& object : stack) {
			if (object->getSize() == 1) {
				player->holdedMedCase = object;
			}
			if (object->getSize() == 2) {
				player->holdedLarCase = object;
			}
		}
		stack.clear();
		if (Mix_PlayChannel(-1, lightSE, 0) == -1) {
			std::cout<<"Error to play lightSE"<<std::endl;
		}
	} else {
		if (Mix_PlayChannel(-1, heavySE, 0) == -1) {
			std::cout<<"Error to play heavySE"<<std::endl;
		}
	}
}

void StageData::moveUp() {
	findObjectsAt(&stack, player->getPosX() - 1, player->getPosY());

	flag = (player->getPosX() <= 0);
	for (auto& object : stack) {
		flag = (flag ? true : !(object->isCutDown()));
		if (player->holdedMedCase != nullptr) {
			flag = object->getSize() == 0;
		} else if (player->holdedLarCase != nullptr) {
			flag = object->getSize() <= 1;
		}
	}
	stack.clear();

	if (!flag) {
		stackX=player->getPosX() - 1;
		stackY=player->getPosY();
		player->moveTo(stackX, stackY);
		if (player->holdedLarCase != nullptr) {
			if (player->holdedLarCase->isCutUp()) {
				if (player->holdedMedCase != nullptr) {
					if (!(player->holdedMedCase->isCutUp())) {
						player->holdedMedCase->moveTo(stackX, stackY);
					}
				}
			} else {
				if (player->holdedMedCase != nullptr) {
					player->holdedMedCase->moveTo(stackX, stackY);
					player->holdedLarCase->moveTo(stackX, stackY);
				}
			}
		} else {
			if (player->holdedMedCase != nullptr) {
				if (!(player->holdedMedCase->isCutUp())) {
					player->holdedMedCase->moveTo(stackX, stackY);
				}
			}
		}
		findObjectsAt(&stack, player->getPosX(), player->getPosY());
		for (auto& object : stack) {
			if (object->getSize() == 1) {
				player->holdedMedCase = object;
			}
			if (object->getSize() == 2) {
				player->holdedLarCase = object;
			}
		}
		stack.clear();
		if (Mix_PlayChannel(-1, lightSE, 0) == -1) {
			std::cout<<"Error to play lightSE"<<std::endl;
		}
	} else {
		if (Mix_PlayChannel(-1, heavySE, 0) == -1) {
			std::cout<<"Error to play heavySE"<<std::endl;
		}
	}
}
