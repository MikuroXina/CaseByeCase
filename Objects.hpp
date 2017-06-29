#ifndef OBJECTS_HPP
#define OBJECTS_HPP

class ObjectBase {
private:
	int posX=0, posY=0;
public:
	ObjectBase() = default;
	virtual ~ObjectBase() = default;

	virtual void isCutUp() = 0;
	virtual void isCutDown() = 0;
	virtual void isCutLeft() = 0;
	virtual void isCutRight() = 0;

	virtual void render() = 0;

	int getPosX() const;
	int getPosY() const;
};

class PlayerObject : public ObjectBase {
public:
	PlayerObject(int&, int&);
	virtual ~ObjectBase();

	virtual bool isCutUp();
	virtual bool isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

class MediumCase : public ObjectBase {
public:
	virtual ~ObjectBase();

	virtual bool isCutUp();
	virtual bool isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

class LargeCase : public ObjectBase {
public:
	virtual ~ObjectBase();

	virtual bool isCutUp();
	virtual void isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

class Wall : public ObjectBase {
public:
	virtual ~ObjectBase();

	virtual bool isCutUp();
	virtual void isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

class LockedDoor : public ObjectBase {
public:
	LockedDoor(bool const&);
	virtual ~ObjectBase();

	virtual bool isCutUp();
	virtual void isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

#endif /* end of include guard: OBJECTS_HPP */
