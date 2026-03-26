#ifndef SETTINGS_H
#define SETTINGS_H
#include "glm/glm.hpp"



constexpr int NUM_PARTICLE_SQR_ROOT = 10;
constexpr float RESTITUTION = 1.0f;
constexpr float Y_FLOOR = -1.0f;
constexpr float Y_CEILING = 1.0f;
constexpr float LEFT_WALL = -1.0f;
constexpr float RIGHT_WALL = 1.0f;
constexpr float FIXED_DT = 1.0f / 60.0f;
constexpr float TIMESCALE = 1.0f;
constexpr glm::vec3 GRAVITY = { 0.0f, -9.81f, 0.0f };

constexpr float SMOOTHING_RADIUS = 1.0f;
constexpr float PRESSURE_MULTIPLIER = 1000.0f;
constexpr float TARGET_DENSITY = 10.0f;

#endif