/**
 * By a pre-defined const string determines which shape object should be returned.
 */

#include "ShapesFactory.h"

//Initialize the static variables.
const std::string ShapesFactory::triangle = "T";
const std::string ShapesFactory::trapez = "t";

/**
 * Empty constructor.
 */
ShapesFactory::ShapesFactory() {}
/**
 * @Returns a pointer to a new shape object.
 * In case no such object exists, returns nullptr.
 */
Shape* ShapesFactory::createShape(const std::string &shapeType)
{
	if(shapeType == ShapesFactory::triangle)
	{
		return new Triangle();
	}
	else if(shapeType == ShapesFactory::trapez)
	{
		return new Trapez();
	}
	return nullptr;
}