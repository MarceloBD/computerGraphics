main: main.o
	g++ -o main main.o 

main.o: main.cpp View.o 
	g++ -c main.cpp -lglut -lGLU -lGL -lm

View.o: View.cpp
	g++ -c View.cpp 
