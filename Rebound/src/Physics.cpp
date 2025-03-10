#include "Physics.h"

Physics::Physics() {
	m_gravity_const = 10.0f;
}

void Physics::setGravityConstant(float gravity) {
	m_gravity_const = gravity;
}