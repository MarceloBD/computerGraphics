GLUT = -lglut -lGLU -lGL -lm 

SRCS = main.cpp View.cpp Controller.cpp Model.cpp
OBJS = $(subst .cpp,.o,$(SRCS))

# dependencies of classes  
MADP = View.o Controller.o Model.o
CODP = View.o Model.o

main: $(OBJS) 
	g++ -o main $(OBJS) $(GLUT)

main.o: main.cpp $(MADP)
	g++ -c main.cpp 

View.o: View.cpp
	g++ -c View.cpp 

Controller.o: Controller.cpp $(CODP)
	g++ -c Controller.cpp 

Model.o: Model.cpp
	g++ -c Model.cpp
