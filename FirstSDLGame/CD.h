#pragma once

#include "FloatA.h"
#include "SDL_image.h"

// Struct for collision detection (axis aligned bounding box)
struct CD {

	static bool intersectAABB(CD A, CD B) {

		return (fabs(A.pos.x - B.pos.x) < (A.w + B.w) &&
				fabs(A.pos.y - B.pos.y) < (A.h + B.h));
	}


	// Centre point of bounding box
	FloatA		pos;

	// Half-width and half-height of the AABB
	float		w;
	float		h;

	CD() {

		pos = FloatA();
		w = 0.0f;
		h = 0.0f;
	}

	CD(float init_x, float init_y, float init_w, float init_h) {

		pos = FloatA(init_x, init_y);

		w = init_w;
		h = init_h;
	}

	CD(FloatA init_pos, float init_w, float init_h) {

		pos = init_pos;

		w = init_w;
		h = init_h;
	}

	void move(float dx, float dy) {

		pos.x += dx;
		pos.y += dy;
	}

	void draw(SDL_Renderer* renderer) {

		SDL_Rect targetRect;

		targetRect.x = int(pos.x - w);
		targetRect.y = int(pos.y - h);
		targetRect.w = int(w * 2.0f);
		targetRect.h = int(h * 2.0f);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &targetRect);
	}
};

