// ECE 312 PA0
// Quan Vo
// qtv73
// Slip days used: 0
// Fall 2023
#include "pa0.h"
#include <stdio.h>

double computeSquare(double x) {
	x = x * x;
    // How to print out the result -> Check
        // printf("Here is the result: %f", x);
	return x;
}

int gcd(int y, int z) {
//    for(int i=1; i<y; i++) {
//        if(i < 6 && i > 2) {
//            printf("%d ", i);
//        }
//        else if (i % 2 == 0) {
//            printf("a ");
//        }
//    }

	//TODO: Your code here
    int a = 0; // Bigger #
    int b = 0; // Smaller #
    int q = 0; // Divider #
    // int r = 1; // Remainder #
    int result = 0; // result

// Check for Negative
    if(y < 0){
        y = y * (-1);
    }
    if (z < 0){
        z = z * (-1);
    }

// Check the bigger number
    if (y == z){
        return y;
    }
    else if(y > z){
        a = y;
        b = z;
    }
    else if (y < z){
        a = z;
        b = y;
    }

    for (int i = 0; i < a; ++i) {
        q = a/b;
        int r = a-(b*q);
        if (r == 0){
            result = b;
            break;
        }
        a = b;
        b = r;
        result = r;
    }
    return result;
}

//Given function to be used in findSumPrimes
//Returns 1 if num is prime and 0 if num is not prime
int isPrime(int num) {

    if (num <= 1) return 0;
    if (num % 2 == 0 && num > 2) return 0;
    for(int i = 3; i< num / 2; i+= 2)
    {
        if( num % i == 0 ){
            return 0;
        }
    }
    return 1;
}

int findSumPrimes(int x) {
    int sum = 0;
    for (int i = 0; i <= x; ++i) {
        if (isPrime(i) == 1){
            sum += i;
        }
    }
	return sum;
}

