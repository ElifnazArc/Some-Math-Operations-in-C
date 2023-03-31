/**
 * @file Dosya adı
 *
 * Matris ve vektörleri kullanarak çeşitli işlemleri yapma ve kütüphane
 * kullanarak onları ana sınıf içinde deneme
 *
 * BLM204 BILGISAYAR PROGRAMLAMA III - Birinci Proje
 *
 * 03.12.2022 - 11.12.2022
 *
 * Elifnaz Arıcı - elifnaz.arici@stu.fsm.edu.tr
 */


float *returnVector(int);

float *returnZeroVector(int);

float **returnMatrix(int, int);

float **returnZeroMatrix(int, int);

void freeMatrix(float **, int);

float mean(float *, int);

float correlation(float *, float *, int);

float covariance(float *, float *, int);

float **matrixMultiplication(float **, float **, int, int, int, int);

float **matrixTranspose(float **, int, int);

float *rowMeans(float **, int, int);

float *columnMeans(float **, int, int);

float **covarianceMatrix(float **, int, int);

float determinant(float **, int);

void printVector(float *, int);

void printMatrix(float **, int, int);

void randomNumbersForVector(float *, int, int);

void randomNumbersForMatrix(float **, int, int, int);