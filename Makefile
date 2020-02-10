GCC = g++
CPPFLAGS = -Wextra -Wall -Wvla -pthread -c -g -std=c++11

#run
all: Shapes

#Object Files
Point.o: Point.h Point.cpp Defs.h
	$(GCC) $(CPPFLAGS) Point.cpp

Shapes.o: Shapes.cpp Shape.h Defs.h ShapesFactory.h
	$(GCC) $(CPPFLAGS) Shapes.cpp

Shape.o: Shape.cpp Shape.h Defs.h Point.h PrintOuts.h
	$(GCC) $(CPPFLAGS) Shape.cpp

Triangle.o: Triangle.cpp Triangle.h Shape.h
	$(GCC) $(CPPFLAGS) Triangle.cpp

Trapez.o: Trapez.cpp Trapez.h Shape.h
	$(GCC) $(CPPFLAGS) Trapez.cpp

PrintOuts.o: PrintOuts.cpp PrintOuts.h Defs.h
	$(GCC) $(CPPFLAGS) PrintOuts.cpp

ShapesFactory.o: ShapesFactory.cpp ShapesFactory.h Shape.h Triangle.h Trapez.h
	$(GCC) $(CPPFLAGS) ShapesFactory.cpp

#Executable Files
Shapes: Shapes.o Shape.o Trapez.o Triangle.o Point.o PrintOuts.o ShapesFactory.o
	$(GCC) Shapes.o Shape.o Trapez.o Triangle.o Point.o PrintOuts.o ShapesFactory.o -o Shapes

tar:
	tar cvf ex2.tar Point.h Point.cpp Shape.h Shape.cpp Triangle.h Triangle.cpp ShapesFactory.cpp \
	ShapesFactory.h Trapez.h Trapez.cpp Shapes.cpp Defs.h PrintOuts.h PrintOuts.cpp Makefile README

clean:
	-rm -f *.o Shapes

valgrind:
	valgrind --leak-check=full --show-possibly-lost=yes --show-reachable=yes \
	--undef-value-errors=yes Shapes /cs/stud/asafbe/safe/cpp_summer/ex2/input

.PHONY: clean
