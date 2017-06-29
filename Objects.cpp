#include "Objects.hpp"

// ObjectBase member functions
int ObjectBase::getPosX() const {
	return posX:
}
int ObjectBase::getPosY() const {
	return posY;
}

virtual void ObjectBase::moveTo(int& x, int& y) {
	posX += x;
	posY += y;
}

// PlayerObject member functions
PlayerObject::PlayerObject(int& x, int& y) : posX(x), posY(y) {
	;
}

virtual bool PlayerObject::isCutUp() { return false; }
virtual bool PlayerObject::isCutDown() { return false; }
virtual bool PlayerObject::isCutLeft() { return false; }
virtual bool PlayerObject::isCutRight() { return false; }

virtual void PlayerObject::render() {
	;
}

// MediumCase member functions
MediumCase::MediumCase(int& dir) : direction(dir) {
	;
}

virtual bool MediumCase::isCutUp() { return direction == 3; }
virtual bool MediumCase::isCutDown() { return direction == 1; }
virtual bool MediumCase::isCutLeft() { return direction == 0; }
virtual bool MediumCase::isCutRight() { return direction == 2; }

virtual void MediumCase::render() {
	;
}

// LargeCase member functions
LargeCase::LargeCase(int& dir) : direction(dir) {
	;
}

virtual bool LargeCase::isCutUp() { return direction == 3; }
virtual void LargeCase::isCutDown() { return direction == 1; }
virtual bool LargeCase::isCutLeft() { return direction == 0; }
virtual bool LargeCase::isCutRight() { return direction == 2; }

virtual void LargeCase::render() {
	;
}

// Wall member functions
virtual bool Wall::isCutUp() { return false; }
virtual void Wall::isCutDown() { return false; }
virtual bool Wall::isCutLeft() { return false; }
virtual bool Wall::isCutRight() { return false; }

virtual void Wall::render() {
	;
}

// LockedDoor member functions
LockedDoor::LockedDoor(bool const* flag) : pFlag(flag) {
	;
}

// It don't have a collision if unlocked the door
virtual bool LockedDoor::isCutUp() { return !(*pFlag); }
virtual void LockedDoor::isCutDown() { return !(*pFlag); }
virtual bool LockedDoor::isCutLeft() { return !(*pFlag); }
virtual bool LockedDoor::isCutRight() { return !(*pFlag); }

virtual void LockedDoor::render() {
	;
}
