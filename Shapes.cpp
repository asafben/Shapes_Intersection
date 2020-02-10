/**
 * This file receives the input from the user, process it, and gives the correct output.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Defs.h"
#include "Shape.h"
#include "ShapesFactory.h"

/**
 * Open input and output sources.
 * @Returns 0 upon success, else -1.
 */
int openInputOutputFiles(std::ifstream *inputFile, std::ofstream *outputFile, int argc, char*
                         argv[])
{
	if(argc == 3)
	{
		inputFile -> open(argv[1], std::ifstream::in);
		outputFile -> open(argv[2], std::ofstream::out);
		std::cout.rdbuf(outputFile -> rdbuf());
	}
	else if(argc == 2)
	{
		inputFile -> open(argv[1], std::ifstream::in);
	}
	else
	{
		std::cerr << "Wrong number of parameters." << std::endl;
		return -1;
	}

	//Checks if opening input and output sources succeed.
	if(!inputFile)
	{
		std::cerr << "Error while opening input file." << std::endl;
		return -1;
	}

	if(!outputFile)
	{
		std::cerr << "Error while opening output file." << std::endl;
		return -1;
	}
	return 0;
}

/**
 * Parsing and shapes storage variables.
 */
int parseInput(std::vector<Shape *> &shapesVec, std::ifstream *inputFile)
{
	//Variables.
	Shape *tempShape = nullptr;
	std::string outString = "", lineString = "";
	std::stringstream ss;
	int inputCounter = 1;
	std::pair <CordType, CordType> tmpCord(0, 0);

	//Parser.
	//Parsing of the input file.
	while(std::getline(*inputFile, lineString)) //Read a whole line.
	{
		ss.clear(); //End of line of previous line.
		ss << lineString; //Move to stream to take one parameter at a time.
		while (ss >> outString)
		{
			if (outString == ShapesFactory::triangle)
			{
				tempShape = ShapesFactory::createShape(ShapesFactory::triangle);
				inputCounter = 1;
			}
			else if (outString == ShapesFactory::trapez)
			{
				tempShape = ShapesFactory::createShape(ShapesFactory::trapez);
				inputCounter = 1;
			}
			else if ((inputCounter % 2) == 0) //From the second input on (First number).
			{
				tmpCord.first = std::stod(outString);
			}
			else //With the next number we have the full point coordinate.
			{
				tmpCord.second = std::stod(outString);
				tempShape->addPoint(tmpCord);
			}
			inputCounter++;
		}

		//Add the new shape to the shapes vector.
		if(tempShape -> isLegal())
		{
			shapesVec.push_back(tempShape);
		}
		else
		{
			std::cerr << tempShape -> getErrMsg() << std::endl;

			//Free memory because of unexpected exit.
			delete tempShape;
			for(Shape* const& shape: shapesVec)
			{
				delete shape;
			}
			return -1;
		}
	}
	return 0;
}

/**
 * Checks for intersections.
 * If they do, prints them. Else, prints their total sum of area.
 */
void findIntersections(std::vector<Shape*> &shapesVec)
{
	bool intersect = false;
	std::vector<Shape*>::iterator itS1 = shapesVec.begin();
	std::vector<Shape*>::iterator itS2;
	for(; itS1 != shapesVec.end(); ++itS1) //This way we iterate over 'edges'.
	{
		for(itS2 = itS1 + 1; itS2 != shapesVec.end(); ++itS2)
		{
			//If there is a match, stop the loop.
			if((*itS1) -> doShapesIntersect(*(*itS2)))
			{
				intersect = true;
				break;
			}
		}

		//Exit also from the outer loop.
		if(intersect)
		{
			break;
		}
	}

	if(intersect)
	{
		(*itS1) -> printShape();
		(*itS2) -> printShape();
		reportDrawIntersect();
	}
	else
	{
		CordType totalAreaSum = 0;
		for(Shape* const& shape: shapesVec)
		{
			totalAreaSum += shape -> calcArea();
		}
		printArea(totalAreaSum);
	}
}

int main(int argc, char* argv[])
{
	//Set precsion for the output.
	std::cout << std::fixed;
	std::cout << std::setprecision(2);

	//File handling variables.
	std::ifstream inputFile;
	std::ofstream outputFile;
	std::streambuf *coutTmpBuf = std::cout.rdbuf(); //To restore buffer later on.

	if(openInputOutputFiles(&inputFile, &outputFile, argc, argv) != 0)
	{
		return -1;
	}

	std::vector<Shape*> shapesVec;
	if(parseInput(shapesVec, &inputFile) != 0)
	{
		return -1;
	}

	findIntersections(shapesVec);

	//Restoring cout's buffer.
	inputFile.close();
	outputFile.close();
	std::cout.rdbuf(coutTmpBuf); //reset to standard output again

	//Free memory.
	for(Shape* const& shape: shapesVec)
	{
		delete shape;
	}
	return 0;
}