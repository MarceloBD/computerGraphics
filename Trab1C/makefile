GLUT = -lglut -lGLU -lGL -lm 


main: main.o
	g++ -o main main.o $(GLUT)

main.o: main.cpp main.hpp
	g++ -c main.cpp 
