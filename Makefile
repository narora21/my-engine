# Makefile used to build project

flags = -Wall -O2
executable = engine

build:
	g++ $(flags) -o $(executable) src/main.cpp

run:
	./$(executable)

clean:
	rm -f $(executable)