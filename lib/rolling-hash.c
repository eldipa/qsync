#include "rolling-hash.h"
#define M 0x00010000

static
int lower_part(char *buf, int bsize) {
    int sum = 0;
    for (int i = 0; i < bsize; i++) {
        sum += buf[i];
    }

    return sum % M;
}

static
int higher_part(char *buf, int bsize) {
    int sum = 0;
    for (int i = 0; i < bsize; i++) {
        sum += (bsize-i) * buf[i];
    }
    return sum % M;
}

int checksum(char *buf, int bsize) {
    int lower = lower_part(buf, bsize);
    int higher = higher_part(buf, bsize);

    return lower + (higher << 16);
}

int advance_checksum(int sum, char moving_out, char moving_in, int bsize) {
    int lower  =  sum & 0x0000ffff;
    int higher = (sum & 0xffff0000) >> 16;

    lower  = (lower  - moving_out + moving_in) % M;
    higher = (higher - bsize * moving_out + lower) % M;

    return lower + (higher << 16);
}

