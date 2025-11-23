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
const float PlatformHeight = 30.f;
const float PlatformSpeed = -200.f;

// Walls
const float WallThickness = 70.f;
const float WallGap = 100.f;

// Normal jumping
const float PlayerJumpPower = -780.f;
const float Gravity = 800.f;

// Turbo jump
const float TurboJumpLoadTime = 0.8f;
const float TurboJumpEffectTime = 0.4f;
const float TurboJumpPower = -820.f;
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
const float ShootEnemyBaseSpeed = 100.f;
const float EnemySpeedAddition = 30.f;
const float EnemyMaxSpeedAddition = 1000.f;

// Enemy Spawning
const float EnemyInitSpawnInterval = 2.0f;
const float EnemyMinSpawnInterval = 0.3f;
const float EnemyMinSpawnHeight = 100.f;
const float EnemyMaxSpawnHeight = GroundLevel;
const int EnemySpeedUpdateInterval = 10.0f;

// Enemy shooting
const float ShootEnemyShootInterval = 3.0f;
const float ShootEnemyFireEffectTime = 2.0f;
const float ShootEnemyProjSpeed = 450.f;

// Score
const float ScoreInterval = 0.5f;

// Score limits
const int ShootEnemyScoreLimit = 120;
const int WallScoreLimit = 200;
const int GroundVanishScoreLimit = 300;

// Colors
const sf::Color HeaderTextColor = sf::Color(227, 203, 66);
const sf::Color GroundColor = sf::Color(21, 71, 35);
const sf::Color PlayerDashColor = sf::Color(250, 99, 35);
const sf::Color PlayerDashCooldownColor = sf::Color(148, 79, 6);

// Structs


struct GameData
{
	int playerScore = 0;
};