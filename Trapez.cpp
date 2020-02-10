/**
 * Represents a trapez, inherits from Shape.
 */

#include "Trapez.h"

//Initialize the static variables.
int Trapez::s_trapezCounter = 0;
const std::string Trapez::s_baseName = "Trapez_";

/**
 * Empty constructor.
 * Initializes base name const, gives the current triangle instance a name and advanced counter by
 * one.
 */
Trapez::Trapez(): Shape(s_baseName + std::to_string(s_trapezCounter))
{
	s_trapezCounter++;
}

/**
 * Destructor.
 */
Trapez::~Trapez() {}

/**
 * Checks if all points up to this point are legal.
 * isLegal is overloaded in inheriting classes for more checks.
 * In the case of a trapez, we check that:
 * 	  A. All edges are not on the same line.
 *	  B.‪ (x1,y1),(x2,y2)‪ && (x3,y3),(x4,y4‬‬) are parallel to the X axis.
 * @Returns True if the shape's points form a legal shape, else False.
 */
bool Trapez::isLegal()
{
	bool is_success = true;
	if(!Shape::isLegal() || (pointsCounter != 4))
	{
		//errorMsg is set in the fathers isLegal function.
		is_success = false;
	}
	//All edges are not on the same line.
	if(Point::areCordsEqu(pointsVec[0].getY(), pointsVec[2].getY()))
	{
		errorMsg = "All trapez edges are on the same line.";
		is_success = false;
	}

	//parallel to the X axis.
	if(!(Point::areCordsEqu(pointsVec[0].getY(), pointsVec[1].getY())) ||
	   !(Point::areCordsEqu(pointsVec[2].getY(), pointsVec[3].getY())))
	{
		errorMsg = "One or two of trapez edges aren't parallel to the X axis.";
		is_success = false;
	}
	return is_success;
}

/**
 * To be implemented in every inheriting polygon.
 * @Returns the area of the given shape's object.
 */
CordType Trapez::calcArea()
{
	CordType result = 0;
	result =  Point::calcDistance(pointsVec[0], pointsVec[1]); //First  x axis parallel edge.
	result += Point::calcDistance(pointsVec[2], pointsVec[3]); //Second x axis parallel edge.
	result *= Point::sub(pointsVec[0].getY(), pointsVec[2].getY());     //height.
	return (std::abs(result) / 2);
}

/**
 * To be implemented in every inheriting polygon.
 * @Prints to the screen the points of the given polygon.
 */
void Trapez::printShape()
{
	printTrapez(pointsVec[0].getX(), pointsVec[0].getY(), pointsVec[1].getX(), pointsVec[1].getY(),
			    pointsVec[2].getX(), pointsVec[2].getY(), pointsVec[3].getX(), pointsVec[3].getY());
}