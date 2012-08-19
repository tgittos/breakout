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
IFLAGS = -Iinclude

# Link flags for Linux
LDFLAGS = -lGL -lGLU -lglut -lGLEW

# Link flags for OS X, overrides Linux
ifeq "$(OSTYPE)" "Darwin"
	LDFLAGS = -framework sfml-system -framework sfml-graphics -framework sfml-window -framework sfml-audio
endif

# The game binary
EXECUTABLES = breakout

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

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = sample1_unittest

####################################################################
# General build targets
####################################################################

.PHONY: all clean includes assets
.DEFAULT: all

all: includes tests $(EXECUTABLES) assets

clean :
	rm -Rf bin
	rm -f $(TESTS) gtest.a gtest_main.a *.o

####################################################################
# Game build targets
####################################################################

breakout: includes 

%: %.o
	$(CXX) $< $(IFLAGS) $(LDFLAGS) $(CXXFLAGS) -o bin/$@

%.o: %.cpp
	$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/$<

%.cpp:
	literati tangle -o src/. lit/src/$@.lit

%.hpp:
	literati tangle -o src/. lit/include/$@.lit

includes:
	literati tangle -o src/. lit/include

assets:
	mkdir -p bin/assets
	cp -r assets/* bin/assets/.

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

# Build rules for the tests themselves
tests : $(TESTS)
	$(addprefix ./,$(TESTS))
	
.SECONDEXPANSION:
%_unittest.o: $(SRC_DIR)/$$*_unittest.cpp $(SRC_DIR)/$$*.h $(GTEST_HEADERS)
	$(CXX) $(GTEST_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/$*_unittest.cpp -o $@

.SECONDEXPANSION:
%_unittest: $$*.o $$@.o gtest_main.a
	$(CXX) $(GTEST_IFLAGS) $(CXXFLAGS) $*.o $*_unittest.o gtest_main.a -o $@
