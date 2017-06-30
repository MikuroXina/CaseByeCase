#include <OpenGL/gl.h>
#include <SDL.h>
#include <iostream>
#include <algorithm>

#include "StageData.hpp"
#include "Objects.hpp"

StageData::StageData(std::vector<int>&& tileMap) {
	bool isPlayerMade = false;
	for(int i=0; i<tileMap.size(); i+=1) {
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

void StageData::mainLoop(SDL_Window *window) {
	SDL_Event event;
  bool quit=false;
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

					break;
				case SDLK_UP:

					break;
				case SDLK_LEFT:

					break;
				case SDLK_RIGHT:

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
}
