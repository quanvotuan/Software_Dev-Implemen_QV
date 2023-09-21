#ifndef C_H
#define C_H

/* This ifdef allows the header to be used from both C and C++. */
#ifdef __cplusplus
extern "C" {
#endif
double computeSquare(double x);
int gcd(int y, int z);
int findSumPrimes(int x);
#ifdef __cplusplus
}
#endif

#endif