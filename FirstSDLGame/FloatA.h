#pragma once

// Struct representing a point in 2D space
struct FloatA
{
	float	x;
	float	y;

	FloatA() {

		x = 0.0f;
		y = 0.0f;
	}

	FloatA(float init_x, float init_y) {

		x = init_x;
		y = init_y;
	}
};

