#pragma once

#include "Actor.h"

class Laser : public Actor
{
public:
	Laser(class Game* game);

	void UpdateActor(float deltaTime) override;

	class MoveComponent* GetMove() { return mMove; }

private:
	class CircleComponent* mCircle;
	float mDeathTimer;

	class MoveComponent* mMove;
};