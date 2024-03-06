#include "GGE/Physics/PhysicsManager.hpp"
#include "GGE/Gobjects/Sprite.hpp"

// Sprite
using gge::obj::Sprite;

const float Sprite::SPRITE_SCALE = 7;

// Physics
using gge::PhysicsManager;

const ushort PhysicsManager::UPDATE_RATE = 60;
const float PhysicsManager::GFORCE = 0.08;
const float PhysicsManager::AIR_FRICTION = 0.015;
const float PhysicsManager::GROUND_FRICTION = 0.3;
const float PhysicsManager::ACCEL_COEFF = 0.1;