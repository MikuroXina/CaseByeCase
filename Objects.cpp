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
	;
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
	;
}

// Wall member functions
bool Wall::isCutUp() { return false; }
bool Wall::isCutDown() { return false; }
bool Wall::isCutLeft() { return false; }
bool Wall::isCutRight() { return false; }

void Wall::render() {
	;
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
	;
}
