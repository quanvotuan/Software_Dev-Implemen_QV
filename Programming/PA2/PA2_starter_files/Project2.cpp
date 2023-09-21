// matrix-multiplication <Project2.cpp>
// ECE 312 Project 2 submission by
// <Your Name Here>
// <Your EID>
// Slip days used: <0>
// Fall 2023

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "MatrixMultiply.h"

void multiplyMatrices(
        double a[],
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],
        const uint32_t b_cols,
        double c[]) {

// M x N * N * K
        int i = 0;
        int j = 0;
    while(i < a_rows){
        while(j < b_cols){
            a[i][j] * b[i][j];
            j++
        }
        i++;

    )}


    // Note from Lecture:
//    int rows = 4;
//    int cols = 3;
//
//    // Create a ptr -> ptr named a (store in the a Stack)
//    double** a = (double**) malloc(rows*sizeof(double*));
//
//    for(int i = 0; i < rows; i++){
//        a[i] = (double*) malloc(cols*sizeof(double));
//    }
//
//    a[0][1] = 5;
//    printf("%f\n", a[0][1]);

    // https://en.wikipedia.org/wiki/Row-_and_column-major_order
}

double** multiplyMatricesPtr(
        double** a,
        const uint32_t a_rows,
        const uint32_t a_cols,
        double** b,
        const uint32_t b_cols) {
    return NULL;
}

// https://en.wikipedia.org/wiki/Matrix_(mathematics)#Submatrix
double** createSubMatrix(
         double** a,
         const uint32_t a_rows,
         const uint32_t a_cols,
		 const uint32_t row_x, 
		 const uint32_t col_y) {
    return NULL;
}
