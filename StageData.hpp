#ifndef STAGEDATA_HPP
#define STAGEDATA_HPP

#include <vector>
#include <SDL.h>

class ObjectBase;

class StageData {
private:
	// TileMap's format:
	// 5x5, 0.Wall, 1.Space, 2.Start, 3.Goal, 4.Locked Door
	// 4~7.Medium Case(Left, Down, Right, Up), 8~11.Large Case(Left, Down, Right, Up)
	// Note: Don't set the start at (5,5)
	ObjectBase *player;
	std::vector<ObjectBase*> objects;
	bool isDoorLocked = true;
	int goalPosX, goalPosY;
	SDL_Renderer *renderer;
public:
	StageData(std::vector<int>&&);
	~StageData();
	void mainLoop(SDL_Window*);
};

#endif /* end of include guard: STAGEDATA_HPP */
