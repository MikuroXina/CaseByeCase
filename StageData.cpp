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

		} else if (tileMap[i] == 5) {

		} else if (tileMap[i] == 6) {

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
	Mix_Chunk *lightSE, *heavySE;

	lightSE = Mix_LoadWAV("lightSE.wav");
	heavySE = Mix_LoadWAV("heavySE.wav");

	std::vector<ObjectBase*> stack;

	SDL_Event event;
	int stackX=0, stackY=0;
  bool quit=false, flag=false;
  while (!quit) {
    // Events
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          std::cout<<"Pressed ESC key!"<<std::endl;
          quit=true;
					break;
				case SDLK_DOWN:
					if (Mix_PlayChannel(-1, lightSE, 0) == -1) {
						std::cout<<"Error to play lightSE"<<std::endl;
					}

					break;
				case SDLK_UP:
					if (Mix_PlayChannel(-1, lightSE, 0) == -1) {
						std::cout<<"Error to play lightSE"<<std::endl;
					}

					break;
				case SDLK_LEFT:
					if (Mix_PlayChannel(-1, lightSE, 0) == -1) {
						std::cout<<"Error to play lightSE"<<std::endl;
					}

					findObjectsAt(&stack, player->getPosX(), player->getPosY() - 1);

					flag = false;
					for (auto& object : stack) {
						flag = (flag ? true : object->isCutRight());
					}
					flag = (player->getPosY() <= 0);
					stack.clear();

					if (!flag) {
						stackX=player->getPosX();
						stackY=player->getPosY() - 1;
						player->moveTo(stackX, stackY);
						findObjectsAt(&stack, player->getPosX(), player->getPosY());
						for (auto& object : stack) {
							if (!(object->isCutLeft())) {
								stackX=player->getPosX();
								stackY=player->getPosY();
								object->moveTo(stackX, stackY);
							}
						}
						stack.clear();
					}
					break;
				case SDLK_RIGHT:
					if (Mix_PlayChannel(-1, lightSE, 0) == -1) {
						std::cout<<"Error to play lightSE"<<std::endl;
					}

					findObjectsAt(&stack, player->getPosX(), player->getPosY() + 1);

					flag = false;
					for (auto& object : stack) {
						flag = (flag ? true : object->isCutLeft());
					}
					flag = (player->getPosY() >= 4);
					stack.clear();

					if (!flag) {
						stackX=player->getPosX();
						stackY=player->getPosY() + 1;
						player->moveTo(stackX, stackY);
						findObjectsAt(&stack, player->getPosX(), player->getPosY());
						for (auto& object : stack) {
							if (!(object->isCutRight())) {
								stackX=player->getPosX();
								stackY=player->getPosY();
								object->moveTo(stackX, stackY);
							}
						}
						stack.clear();
					}
					break;
        }
      }
    }

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

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

}
