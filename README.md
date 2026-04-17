# Huffman Text File Compressor

A C implementation of Huffman coding for file compression. This utility analyzes character frequencies in a text file and generates optimal binary codes to reduce file size.

## Features

- **Huffman Encoding**: Builds an optimal prefix-free code using Huffman tree algorithm
- **Entropy Calculation**: Computes Shannon entropy to measure compression efficiency
- **Modular Design**: Organized into reusable components for compression, file I/O, and frequency analysis

## Project Structure

```
src/
├── main.c            # Entry point and CLI interface
├── compress.c/h      # Compression logic and file writing
├── huffman.c/h       # Huffman tree construction and encoding
├── frequency.c/h     # Character frequency analysis
├── file_utils.c/h    # File reading utilities
└── mem.c/h           # Memory management utilities
tests/                # Test directory (placeholder)
```

## Building

Compile with:
```bash
gcc src/*.c -o huffman
```

## Usage

Compress a file:
```bash
./huffman <filename>
```

Decompress a file (not yet implemented):
```bash
./huffman <filename> -decode
```

## Algorithm

1. Read input file and count character frequencies
2. Build a min-heap-based Huffman tree from frequencies
3. Generate optimal binary codes for each character
4. Write compressed file with encoding map and compressed data

## Notes

- Decompression feature is planned but not yet implemented
- Supports all 256 byte values (0-255)
