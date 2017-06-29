#ifndef STAGEDATA_HPP
#define STAGEDATA_HPP

#include <vector>
#include <initializer_list>

class ObjectBase;

class StageData {
private:
	std::vector<int> stageTileMap;// 5x5, 0.Wall, 1.Space, 2.Start, 3.Goal, 4.Medium Case, 5.Large Case
	ObjectBase* player;
	std::vector<ObjectBase*> objects;
public:
	StageData(std::initializer_list<int>);
	void mainLoop();
}

#endif /* end of include guard: STAGEDATA_HPP */
