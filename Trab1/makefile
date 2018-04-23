main: main.o 
	g++ -o main main.o View.o -lglut -lGLU -lGL -lm 

main.o: main.cpp View.o  
	g++ -c main.cpp 

View.o: View.cpp
	g++ -c View.cpp -lglut -lGLU -lGL -lm 
