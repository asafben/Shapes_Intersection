/**
 * Represents a basic shape.
 */

#include <iostream>
#include "Shape.h"

//Initialize the static variables.
/**
 * Defines a default base name for the class, in case it wasn't given.
 */
const std::string Shape::s_baseName = "Default_Shape_Name";

/**
 * Defines a default value for direction other than 0, 1, -1.
 * 0, 1, -1 are being received from the _sign function.
 */
const CordType Shape::s_initDirection = 2;

/**
 * Empty constructor.
 */
Shape::Shape() : Shape(s_baseName) {}

/**
 * Constructor with the name of the shape.
 */
Shape::Shape(const std::string &shapeName) : pointsCounter(0), errorMsg(""),
											 _shapeName(shapeName) {}

/**
 * Destructor.
 */
Shape::~Shape() {}

/**
 * Add a new point object to the given shape.
 * @Return True upon success, else False.
 */
void Shape::addPoint(const std::pair <CordType, CordType> newPair)
{
	pointsVec.push_back(Point(newPair)); //Add desired point to the vector.
	pointsCounter++;
}

/**
 * Checks if all points up to this point are legal.
 * isLegal is overloaded in inheriting classes for more checks.
 * In the case of a shape, we check that both of the points of the edge aren't identical.
 * @Returns True if the shape's points form a legal shape, else False.
 */
bool Shape::isLegal()
{
	bool is_success = true;

	std::vector<Point>::iterator it = pointsVec.begin();
	for(; it != (pointsVec.end() - 1); ++it) //This way we iterate over 'edges'.
	{
		if(Point::areCordsEqu((*it).getX(), (*(it + 1)).getX()) &&
		   Point::areCordsEqu((*it).getY(), (*(it + 1)).getY()))
		{
			errorMsg = "There is an edge of length 0.";
			is_success = false;
			break;
		}
	}
	return is_success;
}

/**
 * Calculate half of the determinant of the following matrix:
 * | x0  y0  1 |
 * | x1  y1  1 |
 * | x2  y2  1 |
 * Returns a value that is used for the following:
 * A. Absolute value of the result is the area of a triangle built from p0, p1, p2.
 * B. k < 0  means p0 is on the RIGHT of the edge (p1, p2).
 * C. k > 0  means p0 is on the LEFT of the edge (p1, p2).
 * D. k == 0 means p0 is on edge (p1, p2) itself.
 * To calculate the determinant of 3x3 we use the formula:
 * |A| = a(ei - fh) - b(di - fg) + c(dh - eg)
 * when the matrix is:
 * | a  b  c |
 * | d  e  f |
 * | g  h  i |
 * @Returns K value is the result of the calculation described above.
 */
CordType Shape::pointsDeterminant(const Point &p0, const Point &p1, const Point &p2)
{
	CordType k;
	k =  p0.getX() * Point::sub(p1.getY(), p2.getY());
	k -= p0.getY() * Point::sub(p1.getX(), p2.getX());
	k += (Point::sub((p1.getX() * p2.getY()), (p1.getY()*p2.getX())));
	return 0.5 * k;
}

/**
 * To be implemented in every inheriting polygon.
 * @Returns the area of the given shape's object, by default a Shape class object returns 0.
 */
CordType Shape::calcArea()
{
	return 0;
}

/**
 * To be implemented in every inheriting polygon.
 * Uses PrintOuts printing style.
 * @Prints to the screen the points of the given polygon.
 */
void Shape::printShape()
{
	std::cout << "Shape: ";
	for(Point const& point: pointsVec)
	{
		std::cout << "(" << point.getY() << ", " << point.getY() << ")  ";
	}
	std::cout << std::endl;
}

/**
 * _sign function.
 * @Returns: if val is 0 returns 0;
 *           if val is > 0 returns 1;
 *           if val is < 0 returns -1;
 */
CordType Shape::_sign(CordType val)
{
	return (val > 0) - (val < 0);
}

/**
 * The edges (p0, p1) and (p2, p3) intersect iff:
 * A. p0, p1 are on opposite sides of the edge (p2, p3).
 * B. p2, p3 are on opposite sides of the edge (p0, p1).
 */
bool Shape::_doEdgesIntersect(Point &p0, Point &p1, Point &p2, Point &p3)
{
	bool intersect = false;
	if((_sign(pointsDeterminant(p0, p2, p3)) != _sign(pointsDeterminant(p1, p2, p3))) &&
	   (_sign(pointsDeterminant(p2, p0, p1)) != _sign(pointsDeterminant(p3, p0, p1))))
	{
		intersect = true;
	}

	return intersect;
}

/**
 * Point is inside Shape iff:
 * Point is ALWAYS on the same side of all of Shape edges.
 */
bool Shape::_isPointInsideShape(Point &point, Shape &shape)
{
	bool inside = true;
	CordType curDirection = s_initDirection;
	CordType tmpDirection;

	shape.pointsVec.push_back(shape.pointsVec[0]); //For creating the last edge.
	std::vector<Point>::iterator it = shape.pointsVec.begin();

	for(; it != (shape.pointsVec.end() - 1); ++it) //This way we iterate over 'edges'.
	{
		tmpDirection = _sign(pointsDeterminant(point, *it, *(it + 1)));

		if(curDirection == s_initDirection)
		{
			curDirection = tmpDirection;
		}
		else if(curDirection != tmpDirection)
		{
			inside = false;
			break;
		}
	}
	shape.pointsVec.pop_back(); //Restoring original shape state.
	return inside;
}

/**
 * Shape s1 is inside s2 iff there is at least one point from s1, that is inside s2.
 */
bool Shape::_isShapeInsideShape(Shape &s1, Shape &s2)
{
	bool pointInside = false;
	//Points of s1 inside s2.
	for(Point &point: s1.pointsVec)
	{
		if(_isPointInsideShape(point, s2))
		{
			pointInside = true;
			break;
		}
	}

	//Points of s2 inside s1.
	for(Point &point: s2.pointsVec)
	{
		//Exists also if pointInside==true, means already found.
		if(_isPointInsideShape(point, s1) || pointInside)
		{
			pointInside = true;
			break;
		}
	}
	return pointInside;
}

/**
 *	For every edge in s1, check if it intersects with an edge of s2.
 */
bool Shape::_doShapesEdgesIntersect(Shape &s1, Shape &s2)
{
	bool intersect = false;

	s1.pointsVec.push_back(s1.pointsVec[0]); //For creating the last edge.
	s2.pointsVec.push_back(s2.pointsVec[0]); //For creating the last edge.

	std::vector<Point>::iterator itS1 = s1.pointsVec.begin();
	std::vector<Point>::iterator itS2;

	for(; itS1 != (s1.pointsVec.end() - 1); ++itS1) //This way we iterate over 'edges'.
	{
		for(itS2 = s2.pointsVec.begin(); itS2 != (s2.pointsVec.end() - 1); ++itS2)
		{
			if(_doEdgesIntersect(*itS1, *(itS1 + 1), *itS2, *(itS2 + 1)))
			{
				intersect = true;
				break;
			}
		}
	}
	s1.pointsVec.pop_back(); //Restoring original shape state.
	s2.pointsVec.pop_back(); //Restoring original shape state.
	return intersect;
}

/**
 * @Returns True if shape is inside shape, or there edges that intersect, else False.
 */
bool Shape::doShapesIntersect(Shape &shape)
{
	return _isShapeInsideShape(*this, shape) || _doShapesEdgesIntersect(*this, shape);
}

/**
 * @Returns the string of the error message received after checking if the shape is legal.
 * If no error occurred, returns an empty string.
 */
std::string Shape::getErrMsg()
{
	return errorMsg;
}