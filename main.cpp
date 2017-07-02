#include <OpenGL/gl.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>

#include "StageData.hpp"

void checkError() {
	const char *error = SDL_GetError();
	if (*error != '\0') {
		std::cout<<"SDL Error:"<<error<<std::endl;
		SDL_ClearError();
	}
}

int main() {
	std::cout<<"Readying to lunch..."<<std::endl;

	SDL_Window* window{};
	SDL_GLContext context = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout<<std::string(SDL_GetError())<<std::endl;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024);

	constexpr Uint32 width = 500;
	constexpr Uint32 height = 500;
	window = SDL_CreateWindow("Case Bye Case", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window) {
		std::cout<<"Unable to create a window!"<<std::endl;
	}
	checkError();

	context = SDL_GL_CreateContext(window);
	checkError();

	SDL_GL_SetSwapInterval(1);

	glViewport(0, 0, width, height);

	// TileMap's format:
	// 5x5, 0.Wall, 1.Space, 2.Start, 3.Goal, 4.Locked Door
	// 5~8.Medium Case(Left, Down, Right, Up), 9~12.Large Case(Left, Down, Right, Up)
	// 13~16.Medium Key Case(Left, Down, Right, Up), 17~20.Large Key Case(Left, Down, Right, Up)
	StageData stage1({
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		2, 1, 1, 1, 3,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
	});
	while (stage1.mainLoop(window)) {;}

	StageData stage2({
		2, 0, 0, 0, 0,
		1, 1, 0, 0, 0,
		0, 1, 1, 0, 0,
		0, 0, 1, 1, 0,
		0, 0, 0, 1, 3,
	});
	while (stage2.mainLoop(window)) {;}

	StageData stage3({
		0, 0, 0, 0, 0,
		1, 1,17, 0, 0,
		2, 1, 1, 4, 3,
		1,13, 1, 0, 0,
		0, 0, 0, 0, 0,
	});
	while (stage3.mainLoop(window)) {;}

	StageData stage4({
		0, 0, 0, 0, 0,
		0, 2, 1, 9, 0,
		0, 1,20, 1, 0,
		0,16, 1, 1, 4,
		0, 0, 0, 0, 3,
	});
	while (stage4.mainLoop(window)) {;}

	StageData stage5({
		0, 0, 0, 0, 0,
		1,10, 1, 0, 0,
		15, 2,18, 4, 3,
		1,12, 1, 0, 0,
		0, 0, 0, 0, 0,
	});
	while (stage5.mainLoop(window)) {;}

	StageData stage6({
		1, 1,19, 1, 0,
		1, 8,16, 2, 0,
		0, 4, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 3, 0, 0, 0,
	});
	while (stage6.mainLoop(window)) {;}

	StageData stage7({
		0, 0, 0, 0, 0,
		1, 1, 1,10, 1,
		1,20, 9, 2,16,
		0, 4, 0, 0, 0,
		0, 3, 0, 0, 0,
	});
	while (stage7.mainLoop(window)) {;}

	std::cout<< "Exiting..."<<std::endl;

	Mix_CloseAudio();
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
