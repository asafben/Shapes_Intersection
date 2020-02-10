//
// Created by asafbe on 9/11/16.
//

#ifndef EX2_SHAPE_H
#define EX2_SHAPE_H
/**
 * Represents a basic shape.
 */

#include <string>
#include <vector>
#include "Defs.h"
#include "Point.h"
#include "PrintOuts.h"

class Shape
{
public:
	/**
	 * Empty constructor.
	 */
	Shape();

	/**
	 * Destructor.
	 */
	virtual ~Shape();

	/**
	 * Constructor with the name of the shape.
	 */
	Shape(const std::string &shapeName);

	/**
	 * Add a new point object to the given shape.
	 * @Return True upon success, else False.
	 */
	void addPoint(const std::pair <CordType, CordType> newPair);

	/**
	 * Checks if all points up to this point are legal.
	 * isLegal is overloaded in inheriting classes for more checks.
	 * In the case of a shape, we check that both of the points of the edge aren't identical.
	 * @Returns True if the shape's points form a legal shape, else False.
	 */
	virtual bool isLegal();

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
	static CordType pointsDeterminant(const Point &p0, const Point &p1, const Point &p2);

	/**
	 * @Returns True if shape is inside shape, or there edges that intersect, else False.
	 */
	bool doShapesIntersect(Shape &shape);

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

	/**
	 * @Returns the string of the error message received after checking if the shape is legal.
	 * If no error occurred, returns an empty string.
	 */
	std::string getErrMsg();

protected:
	//Variables.
	/**
	 * Counts how many points were added so far to the shape.
	 */
	int pointsCounter;

	/**
	 * Vector that holds all of the points.
	 */
	std::vector<Point> pointsVec;

	/**
	 * The error which occurred while creating the shape from the points given.
	 * If the shape was created correctly, this string's value is "".
	 */
	std::string errorMsg;

private:
	//Variables.
	/**
	 * Defines a default base name for the class, in case it wasn't given.
	 */
	static const std::string s_baseName;

	/**
	 * Defines a default value for direction other than 0, 1, -1.
	 * 0, 1, -1 are being received from the _sign function.
	 */
	static const CordType s_initDirection;

	/**
	 * The name of the shape can't be changed.
	 */
	const std::string _shapeName;

	//Methods.
	/**
	 * The edges (p0, p1) and (p2, p3) intersect iff:
	 * A. p0, p1 are on opposite sides of the edge (p2, p3).
	 * B. p2, p3 are on opposite sides of the edge (p0, p1).
	 */
	bool _doEdgesIntersect(Point &p0, Point &p1, Point &p2, Point &p3);

	/**
	 * Point is inside Shape iff:
	 * Point is ALWAYS on the same side of all of Shape edges.
	 */
	bool _isPointInsideShape(Point &point, Shape &shape);

	/**
	 * Shape s1 is inside s2 iff there is at least one point from s1, that is inside s2.
	 */
	bool _isShapeInsideShape(Shape &s1, Shape &s2);

	/**
	 *	For every edge in s1, check if it intersects with an edge of s2.
	 */
	bool _doShapesEdgesIntersect(Shape &s1, Shape &s2);

	/**
	 * _sign function.
	 * @Returns: if val is 0 returns 0;
	 *           if val is > 0 returns 1;
	 *           if val is < 0 returns -1;
	 */
	CordType _sign(CordType val);
};


#endif //EX2_SHAPE_H
