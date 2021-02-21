#pragma once
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "globals.h"


class Rectangle{
public:
	Rectangle();

	Rectangle(int x, int y, int width, int height) :
		x_(x),
		y_(y),
		width_(width),
		height_(height) {

	}

	const int getCenterX() const { return x_ + width_ / 2; }
	const int getCenterY() const { return y_ + height_ / 2; }
	const int getWidth() const { return width_; }
	const int getHeight() const { return height_; }

	const int getLeft() const { return x_; }
	const int getRight() const { return x_ + width_; }
	const int getTop() const { return y_; }
	const int getBottom() const { return y_ + height_; }

	const int getSide(const sides::Side side) const {
		return
			side == sides::TOP ? getTop() :
			side == sides::BOTTOM ? getBottom() :
			side == sides::LEFT ? getRight() :
			side == sides::RIGHT ? getLeft() :
			sides::NONE;
	}
	/* bool collidesWith
	 * Takes in another rectangle and checks if the two are colliding
	 */
	const bool collidesWith(const Rectangle& other) const {
		// The y increases from 0 at the top to y at the bottom
		// It is not like the normal situation
		// normal:                  screen:  (0,0) ________x_
		//           y|                           |
		//            |                           |
		//            |________x                 y|
		//        (0,0)
		// so it's getTop() <= other.getBottom() rather than getTop() >= other.getBottom()
		// and it's getBottom() >= other.getTop() rather than getBottom() <= other.getTop()
		return
			getRight() >= other.getLeft() &&
			getLeft() <= other.getRight() &&
			getTop() <= other.getBottom() &&
			getBottom() >= other.getTop();
	}

	const bool isValidRectangle() const {
		return (x_ >= 0 && y_ >= 0 && width_ >= 0 && height_ >= 0);
	}

	~Rectangle();

private:
	int x_, y_, width_, height_;
};


#endif // !RECTANGLE_H
