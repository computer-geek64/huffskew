# Storage Format

### File Bit/Byte Organization for Huffskew

Position | Size | Purpose
---------|------|--------
1. | 2 bytes | Number of rows (*a*) in symbol table
2. | 1 byte | Number of bytes (*b*) in each symbol
3. | *b* bytes | Symbol
4. | 1 byte | Number of bits (*c*) in code
5. | *c* bits | Code
6. | N/A | Repeat positions 3 - 5 for all *a* symbols (excluding replacement symbol)
7. | *b* bytes | Replacement symbol
8. | 1 byte | Number of bits (*d*) in replacement symbol code
9. | *d* bits | Replacment symbol code
10. | 1 byte | Number of replacement values (*e*)
11. | *b* bytes | Replacement value
12. | N/A | Repeat position 11 for all *e - 1* replacement values (excluding the first value, which is already in the symbol table)
