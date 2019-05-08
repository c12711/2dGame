#pragma once

#include <cstdint>

// Key states used for player control

typedef uint32_t KeyFlags;

// Which bits are set / unset when a key is pressed / released
enum Keys {

	Up = 0b00001,
	Down = 0b00010,
	Left = 0b00100,
	Right = 0b01000,
	Fire = 0b10000
};