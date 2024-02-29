#pragma once

namespace gge {

// Scale of every sprite
constexpr float SPRITE_SCALE = 7;

// Framerate limits
constexpr unsigned MAX_FPS = 150;
constexpr unsigned MIN_FPS = 120;
constexpr unsigned UPDATE_RATE = 60;

// sizes of the game
constexpr unsigned GAME_WIDTH = 1440;
constexpr unsigned GAME_HEIGHT = 880;

// Physics
constexpr float GFORCE = 0.08;
constexpr float AIR_FRICTION = 0.015;
constexpr float GROUND_FRICTION = 0.3;
constexpr float ACCEL_COEFF = 0.1;

}