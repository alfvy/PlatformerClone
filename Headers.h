#include <cstdio>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int const GAME_SCALE = 32;
#define uint unsigned int;
float const gravity = 5.4f;

//const sf::Color winningColor(255, 255, 95, 0);

#pragma once