/**
 * Euclidean space point object.
 */

#include "Point.h"

//Initialize the static variables.
const std::string Point::s_baseName = "Point";

/**
 * Empty constructor with default: x = 0, y = 0.
 */
Point::Point() : Point(std::make_pair(0, 0)) {}

/**
 * Constructor that receives a pair of x,y.
 */
Point::Point(std::pair <CordType, CordType> newCords)
{
	_cords.first = newCords.first;
	_cords.second = newCords.second;
}

/**
 * Destructor.
 */
Point::~Point() {}

/**
 * Getters.
 */
//Returns X cord.
CordType Point::getX() const
{
	return _cords.first;
}

//Returns Y cord.
CordType Point::getY() const
{
	return _cords.second;
}

//Returns x,y pair.
std::pair <CordType, CordType> Point::getXY() const
{
	return _cords;
}

/**
 * Setters.
 */
//Sets new value to X cord.
void Point::setX(const CordType newX)
{
	_cords.first = newX;
}

//Sets a new value to Y cord.
void Point::setY(const CordType newY)
{
	_cords.second = newY;
}

//Sets a new value to x,y pair.
void Point::setXY(const std::pair <CordType, CordType>& newXY)
{
	_cords.first = newXY.first;
	_cords.second = newXY.second;
}

/**
 * Calculates the SQUARED (positive) Euclidean distance between two points.
 * @param other another point.
 * @return the Euclidean distance between two points.
 */
CordType Point::calcSquaredDistance(const Point& p1, const Point& p2)
{
	return (p1._cords.first - p2._cords.first)*(p1._cords.first - p2._cords.first) +
		   (p1._cords.second - p2._cords.second)*(p1._cords.second - p2._cords.second);
}

/**
 * Calculates the Euclidean distance between two points.
 * @param other another point.
 * @return the Euclidean distance between two points.
 */
CordType Point::calcDistance(const Point& p1, const Point& p2)
{
	return std::sqrt(calcSquaredDistance(p1, p2));
}

/**
 * @Return True if cords are equal with precision of a pre-defined Epsilon value.
 */
bool Point::areCordsEqu(CordType firstCord, CordType secondCord)
{
	return (std::abs(firstCord - secondCord) < EPSILON);
}

/**
 * @Return the result of subtracting two CordType  with precision of a pre-defined Epsilon
 * value.
 */
CordType Point::sub(CordType firstCord, CordType secondCord)
{
	return (std::abs(firstCord - secondCord) < EPSILON) ? 0 : (firstCord - secondCord);
}