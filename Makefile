CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= -lsfml-window -lsfml-system -lsfml-audio -lopenal32 -lopengl32
EXECUTABLE	:= GROUND.exe

EXTERNAL	:= external

ENGINE		:= src/Engine
ENGINE_G	:= src/Engine/graphics
ENGINE_A	:= src/Engine/audio
ENGINE_S	:= src/Engine/system
ENGINE_C	:= src/Engine/Components

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(EXTERNAL)/*.c $(SRC)/*.cpp $(ENGINE)/*.cpp $(ENGINE_G)/*.cpp $(ENGINE_S)/*.cpp $(ENGINE_C)/*.cpp $(ENGINE_A)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES) -municode

clean:
	-rm $(BIN)/*
