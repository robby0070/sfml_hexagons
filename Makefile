CXX      := g++
CXXPARAMS:= -pedantic-errors -Wall -Wextra -Werror 
LIBS     := -lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS := $(PARAMS) $(LIBS)
LDFLAGS  := -L/usr/lib  -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)
TARGET   := game
INCLUDE  := -Iinclude/
MODULES  := hexagon
SRC      := $(foreach module, $(MODULES), $(wildcard src/$(module)/*.cpp)) \
            $(wildcard src/*.cpp)

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET) link

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ $(LDFLAGS)

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

link:

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	@rm -rvf $(OBJ_DIR)/*
	@rm -rvf $(APP_DIR)/*
