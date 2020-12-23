# Makefile
# Usage:
# make          # Compile binaries
# make clean    # Remove all binaries and objects

CC=g++


all: huffskew

huffskew: main.o file_reader.o
	$(CC) $^ -o $@

main.o: src/main.cpp src/main.hpp src/file_reader.hpp
	$(CC) -c $< -o $@

file_reader.o: src/file_reader.cpp src/file_reader.hpp
	$(CC) -c $< -o $@

clean:
	@rm -rvf huffskew main.o file_reader.o

install:
	install huffskew /usr/bin/huffskew

uninstall: /usr/bin/huffskew
	@rm -rvf $?
