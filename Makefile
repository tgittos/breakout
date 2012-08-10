# OSTYPE is not set by default on OS X
ifndef OSTYPE
	OSTYPE = $(shell uname -s)
endif

CC = g++
CFLAGS = -Wall -g -m32
# Linux flags
LDFLAGS = -lGL -lGLU -lglut -lGLEW
IFLAGS = -Ilib -Iinclude
# Override if we're in OS X
ifeq "$(OSTYPE)" "Darwin"
	LDFLAGS = -framework sfml-system -framework sfml-graphics -framework sfml-window -framework sfml-audio
endif
# Pass compiler preprocessor variables in
#-DFREEGLUT FREEGLUT # gcc
#/DFREEGLUT FREEGLUT # windows
EXECUTABLES = breakout

.PHONY: all clean includes assets
.DEFAULT: all

all: includes $(EXECUTABLES) assets

breakout: includes 

%: %.o
	$(CC) out/$< $(IFLAGS) $(LDFLAGS) $(CFLAGS) -o bin/$@

%.o: %.cpp
	$(CC) $(IFLAGS) $(CFLAGS) -c -o out/$@ src/$<

%.cpp:
	mkdir -p out
	literati tangle -o src/. lit/src/$@.lit

%.hpp:
	mkdir -p out
	literati tangle -o include/. lit/include/$@.lit

clean:
	rm -Rf out
	rm -Rf bin

includes:
	literati tangle -o include/. lit/include

assets:
	mkdir -p bin/assets
	cp -r assets/* bin/assets/.