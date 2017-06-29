#include "Objects.hpp"

// ObjectBase member functions
int ObjectBase::getPosX() const {
	return posX:
}
int ObjectBase::getPosY() const {
	return posY;
}

// PlayerObject member functions
PlayerObject::PlayerObject(int&, int&);
virtual PlayerObject::~PlayerObject();

virtual bool PlayerObject::isCutUp();
virtual bool PlayerObject::isCutDown();
virtual bool PlayerObject::isCutLeft();
virtual bool PlayerObject::isCutRight();

virtual void PlayerObject::render();

// MediumCase member functions
virtual MediumCase::~MediumCase();

virtual bool MediumCase::isCutUp();
virtual bool MediumCase::isCutDown();
virtual bool MediumCase::isCutLeft();
virtual bool MediumCase::isCutRight();

virtual void MediumCase::render();

// LargeCase member functions
virtual LargeCase::~LargeCase();

virtual bool LargeCase::isCutUp();
virtual void LargeCase::isCutDown();
virtual bool LargeCase::isCutLeft();
virtual bool LargeCase::isCutRight();

virtual void LargeCase::render();

// Wall member functions
virtual Wall::~Wall();

virtual bool Wall::isCutUp();
virtual void Wall::isCutDown();
virtual bool Wall::isCutLeft();
virtual bool Wall::isCutRight();

virtual void Wall::render();

// LockedDoor member functions
LockedDoor::LockedDoor(bool const&);
virtual LockedDoor::~LockedDoor();

virtual bool LockedDoor::isCutUp();
virtual void LockedDoor::isCutDown();
virtual bool LockedDoor::isCutLeft();
virtual bool LockedDoor::isCutRight();

virtual void LockedDoor::render();
