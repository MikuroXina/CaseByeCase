#ifndef OBJECTS_HPP
#define OBJECTS_HPP

class ObjectBase {
protected:
	int posX=0, posY=0, size=0;
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
	int getSize() const;
	virtual void moveTo(int&, int&);// move to (x, y)
};

class PlayerObject : public ObjectBase {
public:
	class MediumCase *holdedMedCase = nullptr;
	class LargeCase *holdedLarCase = nullptr;

	virtual ~PlayerObject() = default;

	virtual bool isCutUp();
	virtual bool isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

class MediumCase : public ObjectBase {
private:
	int direction;// 0.Left, 1.Down, 2.Right, 3.Up
	bool isKey=false;
public:
	MediumCase(int&, bool);// Direction, isKey
	virtual ~MediumCase() = default;

	virtual bool isCutUp();
	virtual bool isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();

	bool isKeyCase() const;
};

class LargeCase : public ObjectBase {
private:
	int direction;//0.Left, 1.Down, 2.Right, 3.Up
	bool isKey=false;
public:
	LargeCase(int&, bool); // Direction, isKey
	virtual ~LargeCase() = default;

	virtual bool isCutUp();
	virtual bool isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();

	bool isKeyCase() const;
};

class Wall : public ObjectBase {
public:
	virtual ~Wall() = default;

	virtual bool isCutUp();
	virtual bool isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

class LockedDoor : public ObjectBase {
private:
	bool const *pFlag;
public:
	LockedDoor(bool const*);
	virtual ~LockedDoor() = default;

	virtual bool isCutUp();
	virtual bool isCutDown();
	virtual bool isCutLeft();
	virtual bool isCutRight();

	virtual void render();
};

#endif /* end of include guard: OBJECTS_HPP */
