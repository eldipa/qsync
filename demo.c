#include <stdio.h>
#include <stdlib.h>

#include "lib/rolling-hash.h"


void calculate_checksums(FILE *f, int bsize) {
    char buf[bsize];

    while (1) {
        fread(buf, 1, bsize, f);
        if (feof(f)) {
            break;
        }

        printf("%08x\n", checksum(buf, bsize));
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage %s <file> <block-size>\n", argv[0]);
        return 1;
    }

    int bsize = atoi(argv[2]);
    if (bsize <= 0)
        return 1;

    FILE *file = fopen(argv[1], "rb");
    if (!file)
        return 1;

    calculate_checksums(file, bsize);

    fclose(file);
    return 0;
}
