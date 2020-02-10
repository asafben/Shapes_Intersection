/**
 * Represents a trapez, inherits from Shape.
 */

#ifndef EX2_TRAPEZ_H
#define EX2_TRAPEZ_H

#include "Shape.h"
#include <cmath>

class Trapez  : public Shape
{
public:
	/**
	 * Empty constructor.
	 */
	Trapez();

	/**
	 * Destructor.
	 */
	~Trapez();

	/**
	 * Checks if all points up to this point are legal.
	 * isLegal is overloaded in inheriting classes for more checks.
	 * In the case of a trapez, we check that:
	 * 	  A. Every two edges are not on the same line.
	 *	  B.‪ (x1,y1),(x2,y2)‪ && (x3,y3),(x4,y4‬‬) are parallel to the X axis.
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
	/**
	 * Count for how many triangles were created.
	 */
	static int s_trapezCounter;

	/**
	 * Defines a base name for the class. Each new instance will be numbered:
	 * <baseName><instanceNumber>, e.g: "Trapez_1".
	 */
	static const std::string s_baseName;
};


#endif //EX2_TRAPEZ_H
