/**
 * By a pre-defined const string determines which shape object should be returned.
 */

#ifndef EX2_SHAPESFACTORY_H
#define EX2_SHAPESFACTORY_H
#include <string>
#include "Shape.h"
#include "Triangle.h"
#include "Trapez.h"

class ShapesFactory
{
public:
	/**
	 * Empty constructor.
	 */
	ShapesFactory();

	/**
	 * Returns a pointer to a new shape object.
	 */
	static Shape* createShape(const std::string &shapeType);
	static std::string const triangle;
	static std::string const trapez;
};


#endif //EX2_SHAPESFACTORY_H
