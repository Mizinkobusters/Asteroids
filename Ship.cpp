#include "Ship.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Laser.h"

#include "CircleComponent.h"
#include "Asteroid.h"

#include "Random.h"

Ship::Ship(Game* game)
	:Actor(game)
	,mLaserCooldown(0.0f)
	,mRespawnTimer(0.0f)
{
	mSprite = new SpriteComponent(this, 150);
	//mSprite->SetTexture(game->GetTexture("Assets/Ship.png"));
	mNormalTexture = game->GetTexture("Assets/Ship.png");
	mThrustTexture = game->GetTexture("Assets/ShipWithThrust.png");
	mSprite->SetTexture(mNormalTexture);

	InputComponent* ic = new InputComponent(this);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxAngularSpeed(Math::TwoPi);

	//ic->SetForwardKey(SDL_SCANCODE_W);
	//ic->SetBackKey(SDL_SCANCODE_S);
	//ic->SetMaxForwardSpeed(300.0f);

	ic->SetMass(8.0f);

	mMove = ic;

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(30.0f);
}

void Ship::UpdateActor(float deltaTime)
{
	for (auto aster : GetGame()->GetAsteroids())
	{
		if (Intersect(*mCircle, *(aster->GetCircle())))
		{
			SetPosition(Vector2(512.0f, 384.0f));
			SetRotation(0.0f);
			aster->SetState(EDead);

			mMove->SetVelocity(Vector2::Zero);
			break;
		}
	}

	mLaserCooldown -= deltaTime;
	mRespawnTimer -= deltaTime;
}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
	{
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		laser->GetMove()->SetVelocity(laser->GetForward() * 800.0f);

		mLaserCooldown = 0.5f;
	}

	if (keyState[SDL_SCANCODE_W])
	{
		mMove->AddForce(GetForward() * 4000.0f);
		mSprite->SetTexture(mThrustTexture);
	}
	else
	{
		mSprite->SetTexture(mNormalTexture);
	}
	if (keyState[SDL_SCANCODE_S] && mRespawnTimer <= 0.0f)
	{
		mMove->SetVelocity(Vector2::Zero);
		SetPosition(Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f)));
		mRespawnTimer = 2.0f;
	}
}