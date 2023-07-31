#pragma once

#include "Actor.h"
#include "Game.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

private:
	float mLaserCooldown;

	class CircleComponent* mCircle;

	float mRespawnTimer;

	SDL_Texture* mNormalTexture;
	SDL_Texture* mThrustTexture;

	class SpriteComponent* mSprite;
	class MoveComponent* mMove;
};