## LZW

LZW data compression implementation in C compatible with [ncompress](https://vapier.github.io/ncompress/).

This is a hobby project under development

### How to use

To build from source you can run

```bash
make
```

then run the executable to compress `input.txt` and write the compressed data to `compressed.Z`:

```bash
cat ./input.txt | ./lzw > ./compressed.Z
```

`compressed.Z` can now be decompressed using both [ncompress](https://vapier.github.io/ncompress/) and the program itself. For example:

```bash
cat compressed.Z | compress -d
# or
cat compressed.Z | ./lzw -d
```

### Tests

To run unit tests you can run

```bash
make unit-test
```
