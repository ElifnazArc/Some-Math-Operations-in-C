/**
 * @file Dosya adı
 *
 * Matris ve vektörleri kullanarak çeşitli işlemleri yapma ve kütüphane
 * kullanarak onlara ana sınıf içinde ulaşma
 *
 * BLM204 BILGISAYAR PROGRAMLAMA III - Birinci Proje
 *
 * 03.12.2022 - 10.12.2022
 *
 * Elifnaz Arıcı - elifnaz.arici@stu.fsm.edu.tr
 */

#include <stdio.h>
#include "matrixLib.h"
#include <stdlib.h>

int main(int argc, char *argcv[])
{
    int seed = atoi(argcv[3]);

    float *vec = returnVector(3);
    randomNumbersForVector(vec, 3, seed);
    printVector(vec, 3);

    float *vec2 = returnVector(3);
    randomNumbersForVector(vec2, 3, seed);
    printVector(vec2, 3);

    printf("\n--------------------------------------------------------------------------------------\n");

    mean(vec, 3);

    printf("\n--------------------------------------------------------------------------------------\n");

    float **matrix = returnMatrix(3, 3);
    randomNumbersForMatrix(matrix, 3, 3, seed);
    printMatrix(matrix, 3, 3);

    printf("\n--------------------------------------------------------------------------------------\n");

    float **matrix2 = returnMatrix(3, 3);
    randomNumbersForMatrix(matrix2, 3, 3, seed);
    printMatrix(matrix2, 3, 3);

    printf("\n--------------------------------------------------------------------------------------\n");

    rowMeans(matrix, 3, 3);

    printf("\n--------------------------------------------------------------------------------------\n");

    columnMeans(matrix, 3, 3);

    printf("\n--------------------------------------------------------------------------------------\n");

    correlation(vec, vec2, 3);

    printf("\n--------------------------------------------------------------------------------------\n");

    covariance(vec, vec2, 3);

    printf("\n--------------------------------------------------------------------------------------\n");

    determinant(matrix, 3);

    float **sum = covarianceMatrix(matrix, 3, 3);

    printMatrix(sum, 3, 3);

    printf("\n--------------------------------------------------------------------------------------\n");

    float **transpoz = matrixTranspose(matrix, 3, 3);

    printMatrix(transpoz, 3, 3);

    float **allMatrix = matrixMultiplication(matrix, matrix2, 3, 3, 3, 3);
    printMatrix(allMatrix, 3, 3);

    freeMatrix(matrix,3);
    freeMatrix(matrix2,3);
    free(vec);
    free(vec2);

}