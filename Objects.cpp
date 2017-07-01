#include <OpenGL/gl.h>
#include <iostream>

#include "Objects.hpp"

// ObjectBase member functions
int ObjectBase::getPosX() const {
	return posX;
}
int ObjectBase::getPosY() const {
	return posY;
}

void ObjectBase::moveTo(int& x, int& y) {
	posX = x;
	posY = y;
}

// PlayerObject member functions
bool PlayerObject::isCutUp() { return false; }
bool PlayerObject::isCutDown() { return false; }
bool PlayerObject::isCutLeft() { return false; }
bool PlayerObject::isCutRight() { return false; }

void PlayerObject::render() {
	glColor3f(1.0, 1.0, 0);
	glRectd(posY*100+35, posX*100+35, posY*100+65, posX*100+65);
}

// MediumCase member functions
MediumCase::MediumCase(int& dir) : direction(dir) {
	;
}

bool MediumCase::isCutUp() { return direction == 3; }
bool MediumCase::isCutDown() { return direction == 1; }
bool MediumCase::isCutLeft() { return direction == 0; }
bool MediumCase::isCutRight() { return direction == 2; }

void MediumCase::render() {
	;
}

// LargeCase member functions
LargeCase::LargeCase(int& dir) : direction(dir) {
	;
}

bool LargeCase::isCutUp() { return direction == 3; }
bool LargeCase::isCutDown() { return direction == 1; }
bool LargeCase::isCutLeft() { return direction == 0; }
bool LargeCase::isCutRight() { return direction == 2; }

void LargeCase::render() {
	glBegin(GL_LINES);
}

// Wall member functions
bool Wall::isCutUp() { return false; }
bool Wall::isCutDown() { return false; }
bool Wall::isCutLeft() { return false; }
bool Wall::isCutRight() { return false; }

void Wall::render() {
	glColor3f(0.5, 0.8, 1);
	glBegin(GL_LINES);
	glVertex2i(posY*100, posX*100);
	glVertex2i(posY*100, (posX+1)*100);

	glVertex2i(posY*100, (posX+1)*100);
	glVertex2i((posY+1)*100, (posX+1)*100);

	glVertex2i((posY+1)*100, (posX+1)*100);
	glVertex2i((posY+1)*100, posX*100);

	glVertex2i((posY+1)*100, posX*100);
	glVertex2i(posY*100, posX*100);

	glVertex2i(posY*100, posX*100);
	glVertex2i((posY+1)*100, (posX+1)*100);

	glVertex2i(posY*100, (posX+1)*100);
	glVertex2i((posY+1)*100, posX*100);
	glEnd();
}

// LockedDoor member functions
LockedDoor::LockedDoor(bool const* flag) : pFlag(flag) {
	;
}

// It don't have a collision if unlocked the door
bool LockedDoor::isCutUp() { return !(*pFlag); }
bool LockedDoor::isCutDown() { return !(*pFlag); }
bool LockedDoor::isCutLeft() { return !(*pFlag); }
bool LockedDoor::isCutRight() { return !(*pFlag); }

void LockedDoor::render() {
	if (*pFlag) { // If door locked
		glColor3f(1.0, 0.6, 0);
		glBegin(GL_LINES);
		glVertex2i(posY*100+5, posX*100+5);
		glVertex2i(posY*100+5, (posX+1)*100-5);

		glVertex2i(posY*100+5, (posX+1)*100-5);
		glVertex2i((posY+1)*100-5, (posX+1)*100-5);

		glVertex2i((posY+1)*100-5, (posX+1)*100-5);
		glVertex2i((posY+1)*100-5, posX*100+5);

		glVertex2i((posY+1)*100-5, posX*100+5);
		glVertex2i(posY*100+5, posX*100+5);
		glEnd();
	}
}
