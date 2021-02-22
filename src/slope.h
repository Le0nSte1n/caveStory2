#pragma once
#ifndef SLOPE_H
#define SLOPE_H

#include "graphics.h"
#include "rectangle.h"

class Slope{
public:
	Slope() {}

	Slope(Vector2 p1, Vector2 p2) :
		p1_(p1), 
		p2_(p2) {
		if (p2_.x - p1_.x != 0) {
			slope_ = (fabs(p2_.y) - fabs(p1_.y)) / (fabs(p2_.x) - fabs(p1_.x));
		}
	}

	const inline float getSlope() const {
		return slope_;
	}

	const bool collidesWith(const Rectangle& other) const {
		// top right to down left
		// down left to top right
		// down right to top left
		// top left to down right
		return
			(other.getRight() >= p2_.x &&
				other.getLeft() <= p1_.x &&
				other.getTop() <= p2_.y &&
				other.getBottom() >= p1_.y) ||
			(other.getRight() >= p1_.x &&
				other.getLeft() <= p2_.x &&
				other.getTop() <= p1_.y &&
				other.getBottom() >= p2_.y) ||
			(other.getRight() >= p2_.x &&
				other.getLeft() <= p1_.x &&
				other.getTop() <= p1_.y &&
				other.getBottom() >= p2_.y) ||
			(other.getRight() >= p1_.x &&
				other.getLeft() <= p2_.x &&
				other.getTop() <= p2_.y &&
				other.getBottom() >= p1_.y);
	}

	const inline Vector2 getP1() const {
		return p1_;
	}

	const inline Vector2 getP2() const {
		return p2_;
	}

	~Slope() {}

private:
	Vector2 p1_, p2_;
	float slope_;
};


#endif // !SLOPE_H

