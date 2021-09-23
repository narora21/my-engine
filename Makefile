#
#  Makefile
#  My Engine
#
#  Created by Nikhil Arora on 9/22/2021.
#  Copyright © 2021 Nikhil Arora. All rights reserved.
#
# Makefile used to build project

flags = -Wall -O2
executable = engine
exe_path = bin

# build the executable
build:
	g++ $(flags) -o $(exe_path)/$(executable) src/*.cpp

# run the executable
run:
	./$(exe_path)/$(executable)

# clean up files
clean:
	rm -f $(exe_path)/$(executable)

# run sanity check
check: