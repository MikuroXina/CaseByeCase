#ifndef STAGEDATA_HPP
#define STAGEDATA_HPP

#include <vector>
#include <initializer_list>

class ObjectBase;

class StageData {
private:
	// TileMap's format:
	// 5x5, 0.Wall, 1.Space, 2.Start, 3.Goal, 4.Medium Case, 5.Large Case, 6.Locked Door
	// Note: Don't set the start at (5,5)
	ObjectBase* player;
	std::vector<ObjectBase*> objects;
	bool isDoorLocked = true;
public:
	StageData(std::initializer_list<int>);
	~StageData();
	void mainLoop(SDL_Window*);
};

#endif /* end of include guard: STAGEDATA_HPP */
