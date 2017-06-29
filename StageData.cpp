#include <OpenGL/gl.h>
#include <SDL.h>
#include <iostream>
#include <algorithm>

#include "StageData.hpp"
#include "Objects.hpp"

StageData::StageData(std::initializer_list<int> tileMap) {
	bool isPlayerMade = false
	for(int i=0; i<tileMap.count(); i+=1) {
		if (i == 2 && !isPlayerMade) {
			int x = static_cast<int>(i / 3);
			int y = static_cast<int>(i % 3);
			player= new PlayerObject(x, y);

			isPlayerMade = true;
		} else if (i == 4) {

		} else if (i == 5) {

		} else if (i == 6) {

		}
	}

	if (isPlayerMade) {
		std::cout<<"Error! The player creating has failed!"<<std::endl;
	}
}

StageData::~StageData() {
	delete player;
}

void StageData::mainLoop() {
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

    // Render
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

		for(auto& object : objects) {
			object.render();
		}

    SDL_GL_SwapWindow(window);

    SDL_Delay(1);
  }
}
