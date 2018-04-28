main: main.o 
	g++ -o main main.o View.o Controller.o -lglut -lGLU -lGL -lm 

main.o: main.cpp View.o Controller.o
	g++ -c main.cpp 

View.o: View.cpp
	g++ -c View.cpp 

Controller.o: Controller.cpp View.o
	g++ -c Controller.cpp 
