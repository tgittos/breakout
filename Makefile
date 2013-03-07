####################################################################
# Binaries to create
####################################################################

# The game binary
EXECUTABLES = breakout editor

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = Ball_unittest Brick_unittest EventManager_unittest Paddle_unittest Score_unittest ComposableObject_unittest Collidable_unittest Dimension_unittest Clickable_unittest Level_unittest Button_unittest

####################################################################
# Base variables
####################################################################

# OSTYPE is not set by default on OS X
ifndef OSTYPE
	OSTYPE = $(shell uname -s)
endif

# Select compiler
CXX = g++

# Flags passed to the C++ compiler.
CXXFLAGS = -g -Wall -Wextra -m32 -pthread

# Source code directory
SRC_DIR = src

# Test dir
TEST_DIR = tests

####################################################################
# Game related variables
####################################################################

# Include directory
IFLAGS = -Isrc

# Link flags for Linux
LDFLAGS = -lGL -lGLU -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio

# Link flags for OS X, overrides Linux
ifeq "$(OSTYPE)" "Darwin"
	LDFLAGS = -framework sfml-system -framework sfml-graphics -framework sfml-window -framework sfml-audio
endif

####################################################################
# Google Test related variables
####################################################################

# Include Google Test headers
GTEST_IFLAGS = -I$(GTEST_DIR)/include

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = ../googletest

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

####################################################################
# Google Mock related variables
####################################################################

# Include Google Test headers
GMOCK_IFLAGS = -I$(GMOCK_DIR)/include

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GMOCK_DIR = ../googlemock

####################################################################
# Google Test build targets
####################################################################

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(GTEST_IFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc -o $@

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(GTEST_IFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc -o $@

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ gtest-all.o gtest_main.o

####################################################################
# Google Mock build targets
####################################################################

gmock-all.o:
	$(CXX) $(GTEST_IFLAGS) -I${GTEST_DIR} $(GMOCK_IFLAGS) -I${GMOCK_DIR} $(CXXFLAGS) -c ${GMOCK_DIR}/src/gmock-all.cc

libgmock.a: gtest-all.o gmock-all.o
	ar -rv libgmock.a gtest-all.o gmock-all.o

####################################################################
# Project build targets
####################################################################

.PHONY: all clean includes assets
.DEFAULT: all

all: tests $(EXECUTABLES) assets

clean :
	rm -Rf bin
	rm -f $(TESTS) gtest.a gtest_main.a libgmock.a *.o

includes:
	literati tangle -o src/. lit/include

mocks:
	literati tangle -o src/. lit/mocks

tests : includes mocks $(TESTS)
	$(subst $(eval) , && ,$(addprefix ./,$(TESTS)))

assets:
	mkdir -p bin/assets
	cp -r assets/* bin/assets/.

breakout: includes Main.o Game.o
	mkdir -p bin
	$(CXX) Main.o Game.o $(IFLAGS) $(LDFLAGS) $(CXXFLAGS) -o bin/$@

editor: includes gamecore.o ui.o sfmlview.o Editor.o EditorMain.o
	mkdir -p bin
	$(CXX) gamecore.o ui.o sfmlview.o Editor.o EditorMain.o $(IFLAGS) $(LDFLAGS) $(CXXFLAGS) -o bin/$@

####################################################################
# Library build targets
####################################################################

components.o: includes ComposableObject.o Collidable.o Dimension.o Clickable.o
	ld -r ComposableObject.o Collidable.o Dimension.o Clickable.o -o components.o

gamecore.o: includes components.o Level.o Brick.o Ball.o Paddle.o Input.o Score.o
	ld -r components.o Level.o Brick.o Ball.o Paddle.o Input.o Score.o -o gamecore.o

ui.o: includes EventManager.o Button.o SFMLButtonView.o
	ld -r EventManager.o Button.o SFMLButtonView.o -o ui.o

sfmlview.o: includes SFMLLevelView.o SFMLBrickView.o
	ld -r SFMLLevelView.o SFMLBrickView.o -o sfmlview.o

####################################################################
# Auto generated build targets
####################################################################

Clickable.hpp:
	literati tangle -o src/. lit/include/$@.lit

Ball.hpp:
	literati tangle -o src/. lit/include/$@.lit

Editor.hpp:
	literati tangle -o src/. lit/include/$@.lit

SFMLUIView.hpp:
	literati tangle -o src/. lit/include/$@.lit

Event.hpp:
	literati tangle -o src/. lit/include/$@.lit

ComposableObject.hpp:
	literati tangle -o src/. lit/include/$@.lit

SFMLButtonView.hpp:
	literati tangle -o src/. lit/include/$@.lit

Level.hpp:
	literati tangle -o src/. lit/include/$@.lit

Collidable.hpp:
	literati tangle -o src/. lit/include/$@.lit

SFMLLevelView.hpp:
	literati tangle -o src/. lit/include/$@.lit

LevelView.hpp:
	literati tangle -o src/. lit/include/$@.lit

Paddle.hpp:
	literati tangle -o src/. lit/include/$@.lit

EventHandler.hpp:
	literati tangle -o src/. lit/include/$@.lit

SFMLView.hpp:
	literati tangle -o src/. lit/include/$@.lit

Game.hpp:
	literati tangle -o src/. lit/include/$@.lit

Dimension.hpp:
	literati tangle -o src/. lit/include/$@.lit

Input.hpp:
	literati tangle -o src/. lit/include/$@.lit

EventManager.hpp:
	literati tangle -o src/. lit/include/$@.lit

Button.hpp:
	literati tangle -o src/. lit/include/$@.lit

Score.hpp:
	literati tangle -o src/. lit/include/$@.lit

SFMLBrickView.hpp:
	literati tangle -o src/. lit/include/$@.lit

Brick.hpp:
	literati tangle -o src/. lit/include/$@.lit

ComponentFeature.hpp:
	literati tangle -o src/. lit/include/$@.lit

GameObjectManager.hpp:
	literati tangle -o src/. lit/include/$@.lit

Breakout.hpp:
	literati tangle -o src/. lit/include/$@.lit

MockCollidable.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockComponentFeature.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockInput.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockComposableObject.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockScore.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockDimension.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockBreakout.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockLevel.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockBall.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockEventManager.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockPaddle.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockBrick.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

Level.cpp:
	literati tangle -o src/. lit/src/$@.lit

SFMLBrickView.cpp:
	literati tangle -o src/. lit/src/$@.lit

Collidable.cpp:
	literati tangle -o src/. lit/src/$@.lit

EditorMain.cpp:
	literati tangle -o src/. lit/src/$@.lit

Event.cpp:
	literati tangle -o src/. lit/src/$@.lit

EventManager.cpp:
	literati tangle -o src/. lit/src/$@.lit

SFMLLevelView.cpp:
	literati tangle -o src/. lit/src/$@.lit

Editor.cpp:
	literati tangle -o src/. lit/src/$@.lit

Button.cpp:
	literati tangle -o src/. lit/src/$@.lit

ComposableObject.cpp:
	literati tangle -o src/. lit/src/$@.lit

Breakout.cpp:
	literati tangle -o src/. lit/src/$@.lit

ComponentFeature.cpp:
	literati tangle -o src/. lit/src/$@.lit

Clickable.cpp:
	literati tangle -o src/. lit/src/$@.lit

Score.cpp:
	literati tangle -o src/. lit/src/$@.lit

GameObjectManager.cpp:
	literati tangle -o src/. lit/src/$@.lit

Main.cpp:
	literati tangle -o src/. lit/src/$@.lit

Ball.cpp:
	literati tangle -o src/. lit/src/$@.lit

Dimension.cpp:
	literati tangle -o src/. lit/src/$@.lit

Brick.cpp:
	literati tangle -o src/. lit/src/$@.lit

Input.cpp:
	literati tangle -o src/. lit/src/$@.lit

Paddle.cpp:
	literati tangle -o src/. lit/src/$@.lit

SFMLButtonView.cpp:
	literati tangle -o src/. lit/src/$@.lit

Game.cpp:
	literati tangle -o src/. lit/src/$@.lit

Level.o: Level.hpp Level.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Level.cpp

SFMLBrickView.o: SFMLBrickView.hpp SFMLBrickView.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/SFMLBrickView.cpp

Collidable.o: Collidable.hpp Collidable.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Collidable.cpp

EditorMain.o:  EditorMain.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/EditorMain.cpp

Event.o: Event.hpp Event.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Event.cpp

EventManager.o: EventManager.hpp EventManager.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/EventManager.cpp

SFMLLevelView.o: SFMLLevelView.hpp SFMLLevelView.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/SFMLLevelView.cpp

Editor.o: Editor.hpp Editor.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Editor.cpp

Button.o: Button.hpp Button.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Button.cpp

ComposableObject.o: ComposableObject.hpp ComposableObject.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/ComposableObject.cpp

Breakout.o: Breakout.hpp Breakout.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Breakout.cpp

ComponentFeature.o: ComponentFeature.hpp ComponentFeature.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/ComponentFeature.cpp

Clickable.o: Clickable.hpp Clickable.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Clickable.cpp

Score.o: Score.hpp Score.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Score.cpp

GameObjectManager.o: GameObjectManager.hpp GameObjectManager.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/GameObjectManager.cpp

Main.o:  Main.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Main.cpp

Ball.o: Ball.hpp Ball.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Ball.cpp

Dimension.o: Dimension.hpp Dimension.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Dimension.cpp

Brick.o: Brick.hpp Brick.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Brick.cpp

Input.o: Input.hpp Input.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Input.cpp

Paddle.o: Paddle.hpp Paddle.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Paddle.cpp

SFMLButtonView.o: SFMLButtonView.hpp SFMLButtonView.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/SFMLButtonView.cpp

Game.o: Game.hpp Game.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Game.cpp

Button_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Dimension_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Score_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Breakout_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Clickable_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Collidable_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

GameObjectManager_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

EventManager_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Brick_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Ball_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Paddle_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Level_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Input_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

ComposableObject_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Button_unittest.o: Button_unittest.cpp Button.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Button_unittest.cpp -o $@

Dimension_unittest.o: Dimension_unittest.cpp Dimension.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Dimension_unittest.cpp -o $@

Score_unittest.o: Score_unittest.cpp Score.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Score_unittest.cpp -o $@

Breakout_unittest.o: Breakout_unittest.cpp Breakout.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Breakout_unittest.cpp -o $@

Clickable_unittest.o: Clickable_unittest.cpp Clickable.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Clickable_unittest.cpp -o $@

Collidable_unittest.o: Collidable_unittest.cpp Collidable.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Collidable_unittest.cpp -o $@

GameObjectManager_unittest.o: GameObjectManager_unittest.cpp GameObjectManager.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/GameObjectManager_unittest.cpp -o $@

EventManager_unittest.o: EventManager_unittest.cpp EventManager.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/EventManager_unittest.cpp -o $@

Brick_unittest.o: Brick_unittest.cpp Brick.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Brick_unittest.cpp -o $@

Ball_unittest.o: Ball_unittest.cpp Ball.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Ball_unittest.cpp -o $@

Paddle_unittest.o: Paddle_unittest.cpp Paddle.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Paddle_unittest.cpp -o $@

Level_unittest.o: Level_unittest.cpp Level.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Level_unittest.cpp -o $@

Input_unittest.o: Input_unittest.cpp Input.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Input_unittest.cpp -o $@

ComposableObject_unittest.o: ComposableObject_unittest.cpp ComposableObject.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/ComposableObject_unittest.cpp -o $@

Button_unittest: Button_unittest.o Button.o Dimension.o ComponentFeature.o Clickable.o ComposableObject.o EventManager.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Button_unittest.o Button.o Dimension.o ComponentFeature.o Clickable.o ComposableObject.o EventManager.o gtest_main.a libgmock.a -o $@

Dimension_unittest: Dimension_unittest.o Dimension.o ComponentFeature.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Dimension_unittest.o Dimension.o ComponentFeature.o gtest_main.a libgmock.a -o $@

Score_unittest: Score_unittest.o Score.o Brick.o Dimension.o ComponentFeature.o Collidable.o ComposableObject.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Score_unittest.o Score.o Brick.o Dimension.o ComponentFeature.o Collidable.o ComposableObject.o gtest_main.a libgmock.a -o $@

Breakout_unittest: Breakout_unittest.o Breakout.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Breakout_unittest.o Breakout.o gtest_main.a libgmock.a -o $@

Clickable_unittest: Clickable_unittest.o Clickable.o EventManager.o ComponentFeature.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Clickable_unittest.o Clickable.o EventManager.o ComponentFeature.o gtest_main.a libgmock.a -o $@

Collidable_unittest: Collidable_unittest.o Collidable.o Dimension.o ComponentFeature.o ComposableObject.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Collidable_unittest.o Collidable.o Dimension.o ComponentFeature.o ComposableObject.o gtest_main.a libgmock.a -o $@

GameObjectManager_unittest: GameObjectManager_unittest.o  gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) GameObjectManager_unittest.o  gtest_main.a libgmock.a -o $@

EventManager_unittest: EventManager_unittest.o EventManager.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) EventManager_unittest.o EventManager.o gtest_main.a libgmock.a -o $@

Brick_unittest: Brick_unittest.o Brick.o Dimension.o ComponentFeature.o Collidable.o ComposableObject.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Brick_unittest.o Brick.o Dimension.o ComponentFeature.o Collidable.o ComposableObject.o gtest_main.a libgmock.a -o $@

Ball_unittest: Ball_unittest.o Ball.o Dimension.o ComponentFeature.o ComposableObject.o Collidable.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Ball_unittest.o Ball.o Dimension.o ComponentFeature.o ComposableObject.o Collidable.o gtest_main.a libgmock.a -o $@

Paddle_unittest: Paddle_unittest.o Paddle.o Dimension.o ComponentFeature.o Collidable.o ComposableObject.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Paddle_unittest.o Paddle.o Dimension.o ComponentFeature.o Collidable.o ComposableObject.o gtest_main.a libgmock.a -o $@

Level_unittest: Level_unittest.o Level.o Dimension.o ComponentFeature.o Collidable.o Brick.o ComposableObject.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Level_unittest.o Level.o Dimension.o ComponentFeature.o Collidable.o Brick.o ComposableObject.o gtest_main.a libgmock.a -o $@

Input_unittest: Input_unittest.o Input.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Input_unittest.o Input.o gtest_main.a libgmock.a -o $@

ComposableObject_unittest: ComposableObject_unittest.o ComposableObject.o ComponentFeature.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) ComposableObject_unittest.o ComposableObject.o ComponentFeature.o gtest_main.a libgmock.a -o $@
