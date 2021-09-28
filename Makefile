#
#  Makefile
#  My Engine
#
#  Created by Nikhil Arora on 9/22/2021.
#  Copyright © 2021 Nikhil Arora. All rights reserved.
#
# Makefile used to build project

CC = g++
CFLAGS = -Wall -O2
EXE = engine
TESTEXE = test
BIN = bin
SRC = src
DFLAGS = -DDEBUG

# all
all:
	build

# build the executable
build:
	$(CC) $(CFLAGS) -o $(BIN)/$(EXE) $(SRC)/*.cpp

# run the executable
run:
	./$(BIN)/$(EXE)

# clean up files
clean:
	rm -f $(BIN)/$(EXE)
	rm -f $(BIN)/$(TESTEXE)

# build unit tests
test:
	$(CC) $(CFLAGS) $(DFLAGS) -o $(BIN)/$(TESTEXE) $(SRC)/*.cpp

# run unit tests
runtest:
	./$(BIN)/$(TESTEXE)

# run sanity check
check:
