LIBS = -lglut -lGLU -lGL 
CFLAGS = -std=gnu++0x
SOURCE = main.cpp Node.cpp particle.cpp point.cpp QuadTree.cpp
OBJ = main.o Node.o particle.o point.o QuadTree.o
BIN = particle
all: $(OBJ)
	g++  $(OBJ) $(LIBS) -o $(BIN)
$(OBJ):$(SOURCE)
	g++ -c $(CFLAGS) $(SOURCE)

