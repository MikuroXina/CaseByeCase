#ifndef OBJECTS_HPP
#define OBJECTS_HPP

class ObjectBase {
private:
	int posX=0, posY=0;
public:
	ObjectBase() = default;
	virtual ~ObjectBase() = default;

	virtual bool isCutUp() = 0;
	virtual bool isCutDown() = 0;
	virtual bool isCutLeft() = 0;
	virtual bool isCutRight() = 0;

	virtual void render() = 0;

	int getPosX() const;
	int getPosY() const;
	virtual void moveTo(int&, int&);// move to (x, y)
};

class PlayerObject : public ObjectBase {
public:
	PlayerObject(int&, int&);

	virtual bool isCutUp();
	virtual bool isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

class MediumCase : public ObjectBase {
private:
	int direction;// 0.Left, 1.Down, 2.Right, 3.Up
public:
	MediumCase(int&);// Direction

	virtual bool isCutUp();
	virtual bool isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

class LargeCase : public ObjectBase {
private:
	int direction;//0.Left, 1.Down, 2.Right, 3.Up
public:
	LargeCase(int&); // Direction

	virtual bool isCutUp();
	virtual bool isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

class Wall : public ObjectBase {
public:
	virtual bool isCutUp();
	virtual bool isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

class LockedDoor : public ObjectBase {
private:
	bool *pFlag;
public:
	LockedDoor(bool const*);

	virtual bool isCutUp();
	virtual bool isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

#endif /* end of include guard: OBJECTS_HPP */
