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
};

class PlayerObject : public ObjectBase {
public:
	PlayerObject(int&, int&);
	virtual ~PlayerObject();

	virtual bool isCutUp();
	virtual bool isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

class MediumCase : public ObjectBase {
public:
	virtual ~MediumCase();

	virtual bool isCutUp();
	virtual bool isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

class LargeCase : public ObjectBase {
public:
	virtual ~LargeCase();

	virtual bool isCutUp();
	virtual bool isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

class Wall : public ObjectBase {
public:
	virtual ~Wall();

	virtual bool isCutUp();
	virtual bool isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

class LockedDoor : public ObjectBase {
public:
	LockedDoor(bool const&);
	virtual ~LockedDoor();

	virtual bool isCutUp();
	virtual bool isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

#endif /* end of include guard: OBJECTS_HPP */
