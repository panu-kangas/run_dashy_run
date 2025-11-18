#pragma once

#include <SFML/Graphics.hpp>

// Screen
const unsigned ScreenWidth = 1400;
const unsigned ScreenHeight = 1024;

// Text utils
const unsigned HeaderTextSize = 70;
const unsigned RegularTextSize = 40;

// Environment
const float GroundLevel = 800.0f;
const float GroundDissappearInterval = 10.f;
const float GroundReturnTime = 4.f;
const float GroundBlinkInterval = 0.2f;
const float GroundBlinkEffectTime = 3.5f;

// Platforms
const float PlatformInitSpawnTime = 3.0f;
const float PlatformHeight = 20.f;
const float PlatformSpeed = -200.f;

// Normal jumping
const float PlayerJumpPower = -750.f;
const float Gravity = 800.f;

// Turbo jump
const float TurboJumpLoadTime = 0.8f;
const float TurboJumpEffectTime = 0.4f;
const float TurboJumpPower = -800.f;
const float TurboJumpBarLength = 100.f;

// Meteor Attack
const float MeteorAttackSpeed = 1300.f;

// Dash
const float DashSpeed = 1200.f;
const float DashEffectTime = 0.2f;
const float DashCooldown = 1.0f;

// Player movement
const float PlayerSpeed = 400.f;

// Enemy movement
const float GroundEnemyBaseSpeed = 200.f;
const float AirEnemyBaseSpeed = 300.f;
const float EnemySpeedAddition = 50.f;
const float EnemyMaxSpeedAddition = 1000.f;

// Enemy Spawning
const float EnemyInitSpawnInterval = 2.0f;
const float EnemyMinSpawnInterval = 0.3f;
const float EnemyMinSpawnHeight = GroundLevel;
const float EnemyMaxSpawnHeight = 100.f;
const int EnemySpawnUpdateLimit = 6;

// Score

const float ScoreInterval = 0.5f;

// Colors
const sf::Color HeaderTextColor = sf::Color(227, 203, 66);
const sf::Color GroundColor = sf::Color(21, 71, 35);
const sf::Color PlayerDashColor = sf::Color(250, 99, 35);
const sf::Color PlayerDashCooldownColor = sf::Color(148, 79, 6);