# Makefile
# Usage:
# make          # Compile binaries
# make clean    # Remove all binaries and objects

CC=g++


all: huffskew

huffskew: main.o compress.o uncompress.o bit_reader.o bit_writer.o file_analyzer.o huffman_tree_builder.o huffman_tree_node.o huffman_code.o
	$(CC) $^ -o $@

main.o: src/main.cpp src/main.hpp src/compress.hpp src/uncompress.hpp
	$(CC) -c $< -o $@

compress.o: src/compress.cpp src/compress.hpp src/file_analyzer.hpp src/bit_reader.hpp src/bit_writer.hpp src/huffman_tree_builder.hpp src/huffman_tree_node.hpp src/huffman_code.hpp src/vector_hash.hpp
	$(CC) -c $< -o $@

uncompress.o: src/uncompress.cpp src/uncompress.hpp src/bit_reader.hpp
	$(CC) -c $< -o $@

bit_reader.o: src/bit_reader.cpp src/bit_reader.hpp
	$(CC) -c $< -o $@

bit_writer.o: src/bit_writer.cpp src/bit_writer.hpp
	$(CC) -c $< -o $@

file_analyzer.o: src/file_analyzer.cpp src/file_analyzer.hpp src/vector_hash.hpp
	$(CC) -c $< -o $@

huffman_tree_builder.o: src/huffman_tree_builder.cpp src/huffman_tree_builder.hpp src/huffman_tree_node.hpp src/huffman_code.hpp src/vector_hash.hpp
	$(CC) -c $< -o $@

huffman_tree_node.o: src/huffman_tree_node.cpp src/huffman_tree_node.hpp src/huffman_code.hpp
	$(CC) -c $< -o $@

huffman_code.o: src/huffman_code.cpp src/huffman_code.hpp
	$(CC) -c $< -o $@

clean:
	@rm -rvf huffskew main.o compress.o uncompress.o bit_reader.o bit_writer.o file_analyzer.o huffman_tree_builder.o huffman_tree_node.o huffman_code.o

install:
	install huffskew /usr/bin/huffskew

uninstall: /usr/bin/huffskew
	@rm -rvf $?
