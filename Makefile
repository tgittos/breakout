####################################################################
# Binaries to create
####################################################################

# The game binary
EXECUTABLES = breakout

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = Ball_unittest Brick_unittest EventManager_unittest Input_unittest Paddle_unittest Score_unittest ComposableObject_unittest Collidable_unittest Dimension_unittest

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
CXXFLAGS = -g -Wall -Wextra -m32

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
LDFLAGS = -lGL -lGLU -lglut -lGLEW

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
	$(addprefix ./,$(TESTS))

assets:
	mkdir -p bin/assets
	cp -r assets/* bin/assets/.

breakout: includes Main.o Game.o
	mkdir -p bin
	$(CXX) Main.o Game.o $(IFLAGS) $(LDFLAGS) $(CXXFLAGS) -o bin/$@

####################################################################
# Auto generated build targets
####################################################################
Ball.hpp:
	literati tangle -o src/. lit/include/$@.lit

Breakout.hpp:
	literati tangle -o src/. lit/include/$@.lit

Brick.hpp:
	literati tangle -o src/. lit/include/$@.lit

Collidable.hpp:
	literati tangle -o src/. lit/include/$@.lit

ComponentFeature.hpp:
	literati tangle -o src/. lit/include/$@.lit

ComposableObject.hpp:
	literati tangle -o src/. lit/include/$@.lit

Dimension.hpp:
	literati tangle -o src/. lit/include/$@.lit

Event.hpp:
	literati tangle -o src/. lit/include/$@.lit

EventManager.hpp:
	literati tangle -o src/. lit/include/$@.lit

Game.hpp:
	literati tangle -o src/. lit/include/$@.lit

Input.hpp:
	literati tangle -o src/. lit/include/$@.lit

Paddle.hpp:
	literati tangle -o src/. lit/include/$@.lit

Score.hpp:
	literati tangle -o src/. lit/include/$@.lit

MockBall.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockBreakout.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockBrick.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockCollidable.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockComponentFeature.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockComposableObject.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockDimension.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockEventManager.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockInput.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockPaddle.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

MockScore.hpp:
	literati tangle -o src/. lit/mocks/$@.lit

Ball.cpp:
	literati tangle -o src/. lit/src/$@.lit

Breakout.cpp:
	literati tangle -o src/. lit/src/$@.lit

Brick.cpp:
	literati tangle -o src/. lit/src/$@.lit

Collidable.cpp:
	literati tangle -o src/. lit/src/$@.lit

ComponentFeature.cpp:
	literati tangle -o src/. lit/src/$@.lit

ComposableObject.cpp:
	literati tangle -o src/. lit/src/$@.lit

Dimension.cpp:
	literati tangle -o src/. lit/src/$@.lit

Event.cpp:
	literati tangle -o src/. lit/src/$@.lit

EventManager.cpp:
	literati tangle -o src/. lit/src/$@.lit

Game.cpp:
	literati tangle -o src/. lit/src/$@.lit

Input.cpp:
	literati tangle -o src/. lit/src/$@.lit

Main.cpp:
	literati tangle -o src/. lit/src/$@.lit

Paddle.cpp:
	literati tangle -o src/. lit/src/$@.lit

Score.cpp:
	literati tangle -o src/. lit/src/$@.lit

Ball.o: Ball.hpp Ball.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Ball.cpp

Breakout.o: Breakout.hpp Breakout.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Breakout.cpp

Brick.o: Brick.hpp Brick.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Brick.cpp

Collidable.o: Collidable.hpp Collidable.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Collidable.cpp

ComponentFeature.o: ComponentFeature.hpp ComponentFeature.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/ComponentFeature.cpp

ComposableObject.o: ComposableObject.hpp ComposableObject.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/ComposableObject.cpp

Dimension.o: Dimension.hpp Dimension.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Dimension.cpp

Event.o: Event.hpp Event.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Event.cpp

EventManager.o: EventManager.hpp EventManager.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/EventManager.cpp

Game.o: Game.hpp Game.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Game.cpp

Input.o: Input.hpp Input.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Input.cpp

Main.o:  Main.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Main.cpp

Paddle.o: Paddle.hpp Paddle.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Paddle.cpp

Score.o: Score.hpp Score.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/Score.cpp

Ball_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Breakout_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Brick_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Collidable_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

ComposableObject_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Dimension_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

EventManager_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Input_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Paddle_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Score_unittest.cpp:
	literati tangle -o src/. lit/test/$@.lit

Ball_unittest.o: Ball_unittest.cpp Ball.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Ball_unittest.cpp -o $@

Breakout_unittest.o: Breakout_unittest.cpp Breakout.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Breakout_unittest.cpp -o $@

Brick_unittest.o: Brick_unittest.cpp Brick.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Brick_unittest.cpp -o $@

Collidable_unittest.o: Collidable_unittest.cpp Collidable.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Collidable_unittest.cpp -o $@

ComposableObject_unittest.o: ComposableObject_unittest.cpp ComposableObject.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/ComposableObject_unittest.cpp -o $@

Dimension_unittest.o: Dimension_unittest.cpp Dimension.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Dimension_unittest.cpp -o $@

EventManager_unittest.o: EventManager_unittest.cpp EventManager.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/EventManager_unittest.cpp -o $@

Input_unittest.o: Input_unittest.cpp Input.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Input_unittest.cpp -o $@

Paddle_unittest.o: Paddle_unittest.cpp Paddle.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Paddle_unittest.cpp -o $@

Score_unittest.o: Score_unittest.cpp Score.hpp $(GTEST_HEADERS)
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/Score_unittest.cpp -o $@

Ball_unittest: Ball_unittest.o Ball.o  gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Ball.o Ball_unittest.o  gtest_main.a libgmock.a -o $@

Breakout_unittest: Breakout_unittest.o Breakout.o  gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Breakout.o Breakout_unittest.o  gtest_main.a libgmock.a -o $@

Brick_unittest: Brick_unittest.o Brick.o  gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Brick.o Brick_unittest.o  gtest_main.a libgmock.a -o $@

Collidable_unittest: Collidable_unittest.o Collidable.o Dimension.o ComponentFeature.o ComposableObject.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Collidable.o Collidable_unittest.o Dimension.o ComponentFeature.o ComposableObject.o gtest_main.a libgmock.a -o $@

ComposableObject_unittest: ComposableObject_unittest.o ComposableObject.o ComponentFeature.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) ComposableObject.o ComposableObject_unittest.o ComponentFeature.o gtest_main.a libgmock.a -o $@

Dimension_unittest: Dimension_unittest.o Dimension.o ComponentFeature.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Dimension.o Dimension_unittest.o ComponentFeature.o gtest_main.a libgmock.a -o $@

EventManager_unittest: EventManager_unittest.o EventManager.o ComposableObject.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) EventManager.o EventManager_unittest.o ComposableObject.o gtest_main.a libgmock.a -o $@

Input_unittest: Input_unittest.o Input.o  gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Input.o Input_unittest.o  gtest_main.a libgmock.a -o $@

Paddle_unittest: Paddle_unittest.o Paddle.o Dimension.o Collidable.o ComposableObject.o gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Paddle.o Paddle_unittest.o Dimension.o Collidable.o ComposableObject.o gtest_main.a libgmock.a -o $@

Score_unittest: Score_unittest.o Score.o  gtest_main.a libgmock.a
	$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) Score.o Score_unittest.o  gtest_main.a libgmock.a -o $@
