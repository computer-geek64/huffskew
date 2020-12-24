# Makefile
# Usage:
# make          # Compile binaries
# make clean    # Remove all binaries and objects

CC=g++


all: huffskew

huffskew: main.o file_reader.o huffman_tree_builder.o huffman_tree_node.o huffman_code.o
	$(CC) $^ -o $@

main.o: src/main.cpp src/main.hpp src/file_reader.hpp
	$(CC) -c $< -o $@

file_reader.o: src/file_reader.cpp src/file_reader.hpp
	$(CC) -c $< -o $@

huffman_tree_builder.o: src/huffman_tree_builder.cpp src/huffman_tree_builder.hpp src/huffman_tree_node.hpp src/huffman_code.hpp
	$(CC) -c $< -o $@

huffman_tree_node.o: src/huffman_tree_node.cpp src/huffman_tree_node.hpp src/huffman_code.hpp
	$(CC) -c $< -o $@

huffman_code.o: src/huffman_code.cpp src/huffman_code.hpp
	$(CC) -c $< -o $@

clean:
	@rm -rvf huffskew main.o file_reader.o huffman_tree_builder.o huffman_tree_node.o huffman_code.o

install:
	install huffskew /usr/bin/huffskew

uninstall: /usr/bin/huffskew
	@rm -rvf $?
