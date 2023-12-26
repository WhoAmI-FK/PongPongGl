#pragma once
#include <bitset>
#include <array>

class Component;

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

using ComponentID = std::size_t;
using Group = std::size_t;


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;
const int NET_WIDTH = 4;
const int NET_HEIGHT = 60;
const int NET_SPACE = 12;
