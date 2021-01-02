# Huffskew

### An Optimization of the Huffman Compression Algorithm for Highly Skewed Alphabet Distributions


## Description

**Huffskew** is a variant of the Huffman compression algorithm that optimizes the algorithm for alphabet symbols with singular occurrences.
Huffman compression relies on symbol frequency analysis to determine a mapping for variable-length coding.
Due to the natural tendency toward uniformity for an increasing sample size, Huffman compression is generally used only for small to medium compression tasks, or otherwise done in smaller "chunks" for larger data, thus yielding a greater skew in the distribution to maximize use of its frequency-based variable-length coding.
Nevertheless, even for highly skewed distributions, the "tail" end of the data remains unoptimized, and for certain symbols in the tail (specifically, those with singular/almost singular occurrences) the Huffman compression algorithm takes more space than the original symbol itself.
Therefore, this optimization minimizes the unnecessary storage space for symbols with singular occurrences using an ordered replacement method.


## Installation

Build **Huffskew** with Make:

```
make clean
make
```

Install/Uninstall:

```
sudo make install
sudo make uninstall
```


## Usage

```
huffskew [action] [filename] -o [filename]

Option          Description
-h              Show this help screen
-c [filename]   Compress action
-u [filename]   Uncompress action
-o [filename]   Output filename
```


## Developers

Ashish D'Souza - [@computer-geek64](https://github.com/computer-geek64)


## Releases

**Huffskew** is currently under development, no stable releases exist yet.
<!--The current stable release for **Huffskew** is [v1.0.0](https://github.com/computer-geek64/huffskew/releases/latest)-->


## Versioning

This project uses the [Git](https://git-scm.com/) Version Control System (VCS).


## License

This project is licensed under the [MIT License](LICENSE).
