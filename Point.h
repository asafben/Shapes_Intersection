/**
 * Euclidean space point object.
 */

#ifndef EX2_POINT_H
#define EX2_POINT_H

#include <bits/stl_pair.h>
#include <string>
#include "Defs.h"
#include <cmath>

class Point
{
public:
	/**
	 * Empty constructor with default: x = 0, y = 0.
	 */
	Point();

	/**
	 * Destructor.
	 */
	~Point();

	/**
	 * Constructor that receives a pair of x,y.
	 */
	Point(std::pair <CordType, CordType> newCords);

	/**
	 * Getters.
	 */
	/**
	 * Returns X cord.
	 */
	CordType getX() const;

	/**
	 * Returns Y cord.
	 */
	CordType getY() const;

	/**
	 * Returns x,y pair.
	 */
	std::pair <CordType, CordType> getXY() const;

	/**
	 * Setters.
	 */
	/**
	 * Sets new value to X cord.
	 */
	void setX(const CordType newX);

	/**
	 * Sets a new value to Y cord.
	 */
	void setY(const CordType newY);

	/**
	 * Sets a new value to x,y pair.
	 */
	void setXY(const std::pair <CordType, CordType>& newXY);

	/**
	 * Calculates the SQUARED (positive) Euclidean distance between two points.
	 * @param other another point.
	 * @return the Euclidean distance between two points.
	 */
	static CordType calcSquaredDistance(const Point& p1, const Point& p2);

	/**
	 * Calculates the Euclidean distance between two points.
	 * @param other another point.
	 * @return the Euclidean distance between two points.
	 */
	static CordType calcDistance(const Point& p1, const Point& p2);

	/**
	 * @Return True if cords are equal with precision of a pre-defined Epsilon value.
	 */
	static bool areCordsEqu(CordType firstCord, CordType secondCord);

	/**
	 * @Return the result of subtracting two CordType  with precision of a pre-defined Epsilon
	 * value.
	 */
	static CordType sub(CordType firstCord, CordType secondCord);

private:
	/**
	 * A pair to holds the x,y cords.
	 */
	std::pair <CordType, CordType> _cords;

	/**
	 * The name of the shape can't be changed.
	 */
	static const std::string s_baseName;
};


#endif //EX2_POINT_H
