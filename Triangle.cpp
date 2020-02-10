/**
 * Represents a triangle, inherits from Shape.
 */

#include "Triangle.h"

//Initialize the static variables.
int Triangle::s_triangleCounter = 0;
const std::string Triangle::s_baseName = "Triangle_";

/**
 * Empty constructor.
 * Initializes base name const, gives the current triangle instance a name and advanced counter by
 * one.
 */
Triangle::Triangle(): Shape(s_baseName + std::to_string(s_triangleCounter))
{
	s_triangleCounter++;
}

/**
 * Destructor.
 */
Triangle::~Triangle() {}

/**
 * Findes the direction of the three points.
 * @ Return:  0 If all three points on the same line,
 *            1 ClockWise,
 *           -1 CounterClockWise.
 */
int Triangle::_tripletDirection(const Point &p0, const Point &p1, const Point &p2)
{
	int retVal = 0;
	CordType result = Point::sub(p1.getY(), p0.getY()) * Point::sub(p2.getX(), p1.getX());
	         result -= Point::sub(p1.getX(), p0.getX()) * Point::sub(p2.getY(), p1.getY());

	if(result > 0)
	{
		retVal = 1;
	}
	else if(0 > result)
	{
		retVal = -1;
	}
	return retVal;
}

/**
 * Checks if all points up to this point are legal.
 * isLegal is overloaded in inheriting classes for more checks.
 * In the case of a triangle, we check that all three points aren't on the same line.
 * @Returns True if the shape's points form a legal shape, else False.
 */
bool Triangle::isLegal()
{
	bool is_success = true;
	if(!Shape::isLegal() || (pointsCounter != 3))
	{
		//errorMsg is set in the fathers isLegal function.
		is_success = false;
	}

	if(_tripletDirection(pointsVec[0], pointsVec[1], pointsVec[2]) == 0)
	{
		errorMsg = "All triangle points are on the same line.";
		is_success = false;
	}
	return is_success;
}

/**
 * To be implemented in every inheriting polygon.
 * @Returns the area of the given shape's object.
 */
CordType Triangle::calcArea()
{
	return std::abs(pointsDeterminant(pointsVec[0], pointsVec[1], pointsVec[2]));
}

/**
 * To be implemented in every inheriting polygon.
 * @Prints to the screen the points of the given polygon.
 */
void Triangle::printShape()
{
	printTrig(pointsVec[0].getX(), pointsVec[0].getY(), pointsVec[1].getX(), pointsVec[1].getY(),
			  pointsVec[2].getX(), pointsVec[2].getY());
}