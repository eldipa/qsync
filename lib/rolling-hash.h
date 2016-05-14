#ifndef ROLLING_HASH_H_
#define ROLLING_HASH_H_

int checksum(char *buf, int bsize);
int advance_checksum(int sum, char moving_out, char moving_in, int bsize);

#endif
