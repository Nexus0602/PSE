OBJS= main.cpp
OBJ_NAME = main
CPP=g++
INCLUDE_PATHS = -I/usr/local/include -D_THREAD_SAFE
LIBRARY_PATHS =
COMPILER_FLAGS = -std=c++17 -Wall
LINKER_FLAGS = -L/usr/local/lib -lSDL2 -lSDL2_image  

build:
	$(CPP) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
