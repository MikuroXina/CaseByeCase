#include <OpenGL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>

#include "Sound.hpp"
#include "StageData.hpp"

void checkError() {
  const char *error = SDL_GetError();
  if (*error != '\0') {
    std::cout << "SDL Error:" << error << std::endl;
    SDL_ClearError();
  }
}

int main() {
  std::cout << "Readying to lunch..." << std::endl;

  // TileMap's format:
  // 5x5, 0.Wall, 1.Space, 2.Start, 3.Goal, 4.Locked Door
  // 5~8.Medium Case(Left, Down, Right, Up), 9~12.Large Case(Left, Down,
  // Right, Up) 13~16.Medium Key Case(Left, Down, Right, Up), 17~20.Large Key
  // Case(Left, Down, Right, Up)
  std::vector<StageData> stages;
  stages.emplace_back<Tile[25]>({
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,
      Tile::Start, Tile::Space, Tile::Space, Tile::Space, Tile::Goal,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,
      Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,  Tile::Wall,
  });
  /*{
      Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,
  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Start, Tile::Space,
  Tile::Space, Tile::Space, Tile::Goal, Tile::Wall, Tile::Wall, Tile::Wall,
  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,
  Tile::Wall,
  },
  {
      Tile::Start, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Space,
  Tile::Space, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Space,
  Tile::Space, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Space,
  Tile::Space, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Space,
  Tile::Goal,
  },
  {
      Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Space,
  Tile::Space, 17, Tile::Wall, Tile::Wall, Tile::Start, Tile::Space,
  Tile::Space, 4, Tile::Goal, Tile::Space, 13, Tile::Space, Tile::Wall,
  Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,
  },
  {
      Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Wall,
  Tile::Start, Tile::Space, 9, Tile::Wall, Tile::Wall, Tile::Space, 20,
      Tile::Space, Tile::Wall, Tile::Wall, 16, Tile::Space, Tile::Space, 4,
  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Goal,
  },
  {
      Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Space,
  10, Tile::Space, Tile::Wall, Tile::Wall, 15, Tile::Start, 18, 4, Tile::Goal,
  Tile::Space, 12, Tile::Space, Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Wall,
  Tile::Wall, Tile::Wall,  Tile::Wall,
  },
  {
      Tile::Space, Tile::Space, 19, Tile::Space, Tile::Wall, Tile::Space, 8, 16,
  Tile::Start, Tile::Wall, Tile::Wall, 4, Tile::Wall, Tile::Wall, Tile::Wall,
  Tile::Wall,  Tile::Space, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall,
  Tile::Goal, Tile::Wall, Tile::Wall, Tile::Wall,
  },
  {
      Tile::Wall, Tile::Wall,  Tile::Wall, Tile::Wall, Tile::Wall, Tile::Space,
  Tile::Space, Tile::Space, 10, Tile::Space, Tile::Space, 20, 9, Tile::Start,
  16, Tile::Wall, 4, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Goal,
  Tile::Wall, Tile::Wall, Tile::Wall,
  },
  {
      Tile::Wall, Tile::Wall, Tile::Start, Tile::Space, Tile::Space,
  Tile::Space, Tile::Space, 11, 7, Tile::Space, 20, 13, Tile::Wall, Tile::Space,
  9, Tile::Space, 5, Tile::Wall, Tile::Wall, Tile::Wall, Tile::Space,
  Tile::Space, Tile::Space, 4,  Tile::Goal,
  },
  {
      Tile::Space, Tile::Space,  Tile::Space, Tile::Space, 10, 14, Tile::Space,
  6,  12, Tile::Space,  Tile::Space, 7, Tile::Start, Tile::Wall, 20,
  Tile::Space, 9, Tile::Wall,  Tile::Wall,  4, 11, Tile::Space,  17, 4,
  Tile::Goal,
  },
  {
      Tile::Start,  5, Tile::Space, Tile::Wall, Tile::Space,  Tile::Wall,
  Tile::Space, Tile::Space, Tile::Space, 14, Tile::Space, 18, Tile::Wall, 12,
  Tile::Space, Tile::Space, Tile::Space, 11, Tile::Space, Tile::Wall,
  Tile::Space, Tile::Wall, Tile::Space,  4, Tile::Goal,
  },
  {
      Tile::Start, 6, Tile::Space, 7, Tile::Space, 8, Tile::Space, 5,
  Tile::Space, 5, Tile::Space, 8, Tile::Wall, 8, Tile::Space, 8, Tile::Start, 5,
  Tile::Wall, 8, Tile::Space, 7, Tile::Space, 5, Tile::Goal,
  },
  {
      Tile::Start, 6, Tile::Space, 7, Tile::Space, 8, Tile::Space, 5,
  Tile::Space, 5, Tile::Space, 8, Tile::Wall, 8, Tile::Space, 8, Tile::Start, 5,
  Tile::Wall, 8, Tile::Space, 7, Tile::Space, 5, Tile::Goal,
  },
  {
      11, Tile::Start, Tile::Space, Tile::Space, Tile::Space, Tile::Space, 16,
  8, 8, 8,  Tile::Wall,  Tile::Wall, Tile::Wall, Tile::Wall,  Tile::Space, 4,
  Tile::Space, Tile::Space, Tile::Space, Tile::Space,  Tile::Goal, Tile::Wall,
  20, 12, Tile::Wall,
  },
  {
      Tile::Start, Tile::Space, Tile::Space, Tile::Space,  Tile::Space,  13, 14,
  15, 16, Tile::Space, Tile::Space, Tile::Space, Tile::Space, Tile::Space,
  Tile::Space, Tile::Space, 17, 18, 19, 20, Tile::Space,  Tile::Space,
  Tile::Space, Tile::Space, Tile::Goal,
  }*/

  SDL_Window *window{};
  SDL_GLContext context = NULL;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << std::string(SDL_GetError()) << std::endl;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024);

  constexpr Uint32 width = 500;
  constexpr Uint32 height = 500;
  window = SDL_CreateWindow("Case Bye Case", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, width, height,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (!window) {
    std::cout << "Unable to create a window!" << std::endl;
  }
  checkError();

  context = SDL_GL_CreateContext(window);
  checkError();

  SDL_GL_SetSwapInterval(1);

  glViewport(0, 0, width, height);

  std::unique_ptr<SoundHandler> se = std::make_unique<SEManager>();

  stages[0].setSoundHandler(se.get());
  stages[0].mainLoop(window);
  /*
  bool quit = false;
  do {
    for (auto &stage : stages) {
      if (stage.mainLoop(window)) {
        quit = true;
        break;
      }
    }
  } while (!quit);
  */

  std::cout << "Exiting..." << std::endl;

  Mix_CloseAudio();
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
