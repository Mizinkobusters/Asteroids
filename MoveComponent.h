#pragma once

#include "Component.h"
#include "Math.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }

	float GetMass() const { return mMass; }
	Vector2 GetSumOfForces() const { return mSumOfForces; }
	Vector2 GetVelocity() const { return mVelocity; }
	
	void SetMass(float mass) { mMass = mass; }
	void SetSumOfForces(Vector2 sumOfForces) { mSumOfForces = sumOfForces; }
	void SetVelocity(Vector2 velocity) { mVelocity = velocity; }

	void AddForce(Vector2 force) { mSumOfForces += force; }

private:
	float mAngularSpeed;
	float mForwardSpeed;

	float mMass;
	Vector2 mSumOfForces;
	Vector2 mVelocity;
};