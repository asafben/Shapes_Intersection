/**
 * Represents a triangle, inherits from Shape.
 */

#ifndef EX2_TRIANGLE_H
#define EX2_TRIANGLE_H

#include "Shape.h"
#include <cmath>
#include <iostream>

class Triangle : public Shape
{
public:
	/**
	 * Empty constructor.
	 */
	Triangle();

	/**
	 * Destructor.
	 */
	~Triangle();

	/**
	 * Checks if all points up to this point are legal.
	 * isLegal is overloaded in inheriting classes for more checks.
	 * In the case of a triangle, we check that all three points aren't on the same line.
	 * @Returns True if the shape's points form a legal shape, else False.
	 */
	virtual bool isLegal();

	/**
	 * To be implemented in every inheriting polygon.
	 * @Returns the area of the given shape's object.
	 */
	virtual CordType calcArea();

	/**
	 * To be implemented in every inheriting polygon.
	 * @Prints to the screen the points of the given polygon.
	 */
	virtual void printShape();

private:
	//Variables.
	/**
	 * Count for how many triangles were created.
	 */
	static int s_triangleCounter;

	/**
	 * Defines a base name for the class. Each new instance will be numbered:
	 * <baseName><instanceNumber>, e.g: "Triangle_1".
	 */
	static const std::string s_baseName;

	//Methods.
	/**
	 * Findes the direction of the three points.
	 * @ Return:  0 If all three points on the same line,
	 *            1 ClockWise,
	 *           -1 CounterClockWise.
	 */
	int _tripletDirection(const Point &p0, const Point &p1, const Point &p2);
};


#endif //EX2_TRIANGLE_H
