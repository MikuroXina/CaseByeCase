#ifndef OBJECTS_HPP
#define OBJECTS_HPP

class ObjectBase {
private:
	int posX=0, posY=0;
public:
	virtual ObjectBase() = default;
	virtual ~ObjectBase() = default;

	virtual void moveUp() = 0;
	virtual void moveDown() = 0;
	virtual void moveLeft() = 0;
	virtual void moveRight() = 0;

	virtual void render() = 0;

	int getPosX() const;
	int getPosY() const;
}

#endif /* end of include guard: OBJECTS_HPP */
