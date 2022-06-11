CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

ifeq ($(OS),Windows_NT)
	LIBRARIES	:= -lsndfile -lFLAC -logg -lvorbis -lvorbisenc -lfreetype -lglfw3 -lopenal32 -lopengl32 -luser32 -lkernel32 -municode -lgdi32
else
	LIBRARIES	:= -lglfw3 -lGL
endif

EXECUTABLE_R	:= GROUND_release.exe
EXECUTABLE_D	:= GROUND_debug.exe

EXTERNAL	:= external

ENGINE		:= src/Engine
ENGINE_G	:= src/Engine/graphics
ENGINE_GB	:= src/Engine/graphics/base
ENGINE_A	:= src/Engine/audio
ENGINE_S	:= src/Engine/system
ENGINE_C	:= src/Engine/Components

all: debug

ifeq ($(OS),Windows_NT)
release: $(EXTERNAL)/*.c $(EXTERNAL)/*.cpp $(SRC)/*.cpp $(ENGINE)/*.cpp $(ENGINE_G)/*.cpp $(ENGINE_GB)/*.cpp $(ENGINE_S)/*.cpp $(ENGINE_C)/*.cpp $(ENGINE_A)/*.cpp
		$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $(BIN)/$(EXECUTABLE_R) $(LIBRARIES) -D _RELEASE

debug: $(EXTERNAL)/*.c  $(EXTERNAL)/*.cpp $(SRC)/*.cpp $(ENGINE)/*.cpp $(ENGINE_G)/*.cpp $(ENGINE_GB)/*.cpp $(ENGINE_S)/*.cpp $(ENGINE_C)/*.cpp $(ENGINE_A)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $(BIN)/$(EXECUTABLE_D) $(LIBRARIES)
# Linux case or any other system:
#	Install GLFW, OpenAL and glew
else
release: $(SRC)/*.cpp $(ENGINE)/*.cpp $(ENGINE_G)/*.cpp $(ENGINE_GB)/*.cpp $(ENGINE_S)/*.cpp $(ENGINE_C)/*.cpp $(ENGINE_A)/*.cpp
		$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $(BIN)/$(EXECUTABLE_R) $(LIBRARIES) -D _RELEASE

debug: $(SRC)/*.cpp $(ENGINE)/*.cpp $(ENGINE_G)/*.cpp $(ENGINE_GB)/*.cpp $(ENGINE_S)/*.cpp $(ENGINE_C)/*.cpp $(ENGINE_A)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $(BIN)/$(EXECUTABLE_D) $(LIBRARIES)
endif

clean:
	-rm $(BIN)/*
