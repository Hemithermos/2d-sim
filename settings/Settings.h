#ifndef SETTINGS_H
#define SETTINGS_H
#include "glm/glm.hpp"
constexpr float RESTITUTION = 1.0f;
constexpr float Y_FLOOR = -4.5f;
constexpr float Y_CEILING = 4.5f;
constexpr float LEFT_WALL = -8.0f;
constexpr float FIXED_DT = 1.0f / 60.0f;
constexpr float TIMESCALE = 1.0f;
constexpr float RIGHT_WALL = 8.0f;
constexpr glm::vec3 GRAVITY = { 0.0f, -9.81f, 0.0f };
#endif