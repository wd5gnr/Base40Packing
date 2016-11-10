#ifndef __B40_H
#define __B40_H

#include <stdio.h>

char b40char[]=" ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,-";
extern const char *charset;
int encode(int ch, void (*out)(unsigned num));
const char *decode(unsigned word);

#endif
