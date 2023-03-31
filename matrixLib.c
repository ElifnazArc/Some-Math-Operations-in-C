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
#include <stdlib.h>
#include <math.h>
#include "matrixLib.h"

float *returnVector(int size)
{
    // dinamik olarak bellekten yer ayırıp o aralığı rastgele sayılarla
    // doldurarak tek boyutlu bir dizi oluşturuyor.
    // Eğer yeterli alan yoksa ya da alan sınırını aşıyorsa uyarı veriyor.

    float *vector;

    vector = (float *)malloc(size * sizeof(float));

    if (vector == NULL)
    {
        printf("Not enough space...");
    }

    return vector;
}

//************************************************************************************************************//

float *returnZeroVector(int size)
{

    // Burada returnVector metodunu calloc ile tanımlayarak
    // diğer fonksiyonlar içinde ayrı bir diziye ihtiyaç duyulduğunda
    // direkt olarak elemanları 0 (sıfır) olarak atanmış tek boyutlu dizi oluşturuyor.

    float *zeroVec = (float *)calloc(size, sizeof(float));

    if (zeroVec == NULL)
    {
        printf("Not enough space...");
    }

    return zeroVec;
}

//************************************************************************************************************//

float **returnMatrix(int row, int col)
{
    // Malloc yöntemini kullaranak öncelikle tek boyutlu bir dizi oluşturuyorum.
    // Oluşturduğum bu dizinin her bir elemanı için tekrar bir işaretçi (pointer) atayarak,
    // iki boyutlu bir dizi oluşturuyorum.

    float **matris = (float **)malloc(row * sizeof(float *));
    for (int i = 0; i < row; i++)
    {
        matris[i] = (float *)malloc(col * sizeof(float));
    }

    if (matris == NULL)
    {
        printf("Not enough space...");
    }

    return matris;
}

//************************************************************************************************************//

float **returnZeroMatrix(int row, int col)
{
    // Calloc yöntemini kullaranak öncelikle tek boyutlu bir dizi oluşturuyorum.
    // Oluşturduğum bu dizinin her bir elemanı için tekrar bir işaretçi (pointer) atayarak,
    // iki boyutlu bir dizi oluşturuyorum.
    // Bu iki buyutlu diziyi oluşturmaktaki amaç tüm elemanlarını 0 (sıfır) atamak.

    float **zeroMatris = (float **)calloc(row, sizeof(float *));
    for (int i = 0; i < row; i++)
    {
        zeroMatris[i] = (float *)calloc(col, sizeof(float));
    }

    if (zeroMatris == NULL)
    {
        printf("Not enough space...");
    }

    return zeroMatris;
}

//************************************************************************************************************//

void freeMatrix(float **mat, int row)
{

    // Malloc, Calloc gibi dinamik bellek ayırma yöntemlerini kullandıktan sonra
    // Kullanılan alanı geri iade edebilmek adına bu metodu çağırıyorum.

    for (int i = 0; i < row; i++)
    {
        free(mat[i]);
    }
    free(mat);

    printf("Deletion Completed...");
}

//************************************************************************************************************//

float mean(float *vec, int size)
{
    // Verilen bir tek boyutlu dizinin içindeki tüm elemanları toplayıp
    // geriye bu dizinin ortalamasını döndürüyor.

    float average = 0;

    for (int i = 0; i < size; i++)
    {
        average += vec[i];
    }

    average /= (float)size;
    printf("\nAverage of vector : %f ", average);
    printf("\n");
    return average;
}

//************************************************************************************************************//

float correlation(float *vec, float *vec2, int size)
{

    // Korelasyon = (kovaryans(x, y)/ (σx*σy)) şeklinde bir formüle sahip. Kovaryans kısmını
    // kendi yazdığım covariance metoduyla geriye kalan kısmı ise σx = √covariance(x,x) ve σy = √covariance(y,y)
    // şeklinde yine kovaryans formülünü kullanarak çıkarıyoruz.

    printf("\n");

    // kovaryans(x, y) kısmının hesaplanması
    float correlation = covariance(vec, vec2, size);

    // (σx*σy) kısmının hesaplanması
    float denominator = (sqrt(covariance(vec, vec, size)) * sqrt(covariance(vec2, vec2, size)));

    // Bölme işlemi ve sonuç kısmı
    correlation /= denominator;

    float sum = correlation;

    printf("\nCorrelation is %f", sum);
    printf("\n");
    return sum;
}

//************************************************************************************************************//

float covariance(float *vec1, float *vec2, int size)
{

    // Kovaryans işlemi genel olarak 4 adımdan oluşuyor. Verilen iki vektörün ortalamasının bulunması,
    // Dizilerin her elemanından ortalamalarının çıkarılması, aynı boyutlu iki vektörün birbirlerine
    // karşılık gelen elemanlarının çarpılması ve yeni bir diziye atılması, ve son olarak çarpımların
    // bulunduğu dizinin elemanlarının toplanıp boyutunun bir eksiğine (size - 1) bölünmesi.
    // Bu metodun içinde ayrıca ortalama değeri döndüren mean metodunu ve içine değerleri atmak için
    // yeni bir vektör oluşturan zeroVector metodunu da çağırdım.

    float sum = 0;

    // Ortalamaların hesaplanması
    float meanOfVec1 = mean(vec1, size);
    float meanOfVec2 = mean(vec2, size);

    // Yeni vektörlerin oluşturulması
    float *Vector1NewVariables = returnZeroVector(size);
    float *Vector2NewVariables = returnZeroVector(size);

    // Her vektördeki her elemandan o vektörün ortalamasının çıkarılması
    for (int i = 0; i < size; i++)
    {
        Vector1NewVariables[i] = ((vec1[i]) - meanOfVec1);
        Vector2NewVariables[i] = ((vec2[i]) - meanOfVec2);
    }

    for (int i = 0; i < size; i++)
    {
        Vector1NewVariables[i] *= Vector2NewVariables[i];
        sum += Vector1NewVariables[i];
    }

    sum /= (size - 1);

    printf("\nCovariance of Vectors : %f", sum);
    printf("\n");

    if (sum < 0)
    {
        printf("\nThese vectors are in the opposite directions...\n");
    }
    else
    {
        printf("\nThese vectors are in the same direction...\n");
    }

    return sum;
}

//************************************************************************************************************//

float **matrixMultiplication(float **mat1, float **mat2, int row1, int col1, int row2, int col2)
{

    // Öncelikle birinci matrix'in satır ve ikinci matrix'in sütun bilgileriyle
    // yeni bir matrix oluşturuyor.
    // Daha sonrasında lineer cebir kurallarını kullanarak çarpımlarını yapıyor.

    float **multyOfMatrix = returnZeroMatrix(row1, col2);
    int rowCount = 0, colCount;
    float sum;

    if (col1 == row2)
    {

        for (int i = 0; i < row1; i++)
        {
            colCount = 0;

            for (int k = 0; k < col2; k++)
            {

                sum = 0;

                for (int j = 0; j < col1; j++)
                {

                    sum += mat1[i][j] * mat2[j][k];
                }

                multyOfMatrix[rowCount][colCount] = sum;
                colCount++;
            }

            rowCount++;
        }
    }
    else
    {

        printf("");
    }

    return multyOfMatrix;
}

//************************************************************************************************************//

float **matrixTranspose(float **mat, int row, int col)
{

    float **transposeMatris = returnZeroMatrix(col, row);

    for (int a = 0; a < col; a++)
    {
        for (int b = 0; b < row; b++)
        {
            transposeMatris[a][b] = mat[b][a];
        }
    }

    return transposeMatris;
}

//************************************************************************************************************//

float *rowMeans(float **mat, int row, int col)
{

    // Parametre olarak aldığı matrixin her satırının ortalamasını bid diziye atıyor.

    // Her satırın ortalamasını tutacak vektör.
    float *averageRow = returnZeroVector(row);

    int count = 0;

    // Her satırın elemanlarını toplayıp en sonunda sütunun toplam elemanına bölüyor.
    for (int a = 0; a < row; a++)
    {
        for (int b = 0; b < col; b++)
        {
            averageRow[count] += mat[a][b];
        }
        averageRow[count] = (averageRow[count] / (float)row);
        printf("Average of %d. Row : %f", (count + 1), averageRow[count]);
        printf("\n");
        count++;
    }

    return averageRow;
}

//************************************************************************************************************//

float *columnMeans(float **mat, int row, int col)
{

    // Parametre olarak aldığı matrixin her sütununun ortalamasını bid diziye atıyor.

    // Her sütunun ortalamasını tutacak vektör.
    float *averageColumn = returnZeroVector(col);

    int count = 0;

    // Her sütunun elemanlarını toplayıp en sonunda sütunun toplam elemanına bölüyor.
    for (int a = 0; a < col; a++)
    {
        for (int b = 0; b < row; b++)
        {

            averageColumn[count] += mat[b][a];
        }

        averageColumn[count] = (averageColumn[count] / (float)row);
        printf("Average of %d. Column : %f", (count + 1), averageColumn[count]);
        printf("\n");
        count++;
    }
    return averageColumn;
}

//************************************************************************************************************//

float **covarianceMatrix(float **mat, int row, int col)
{

    // Kovaryans işlemini yapabilmek için formüldeki değerleri öncelikle elde etmemiz gerekiyor.
    // Bunun için daha öncesinde yazdığım transpose, multiplication, columnMeans ve boş matrix döndüren
    // zeroMatrix metodlarını da dahil ettiğim işlemler yapıyorum.
    // Bir matrixin kovaryansını bulabilmek için kullanılan formül S = ((X')*(X))/n şeklinde.
    // X bizim parametre olarak verdiğimiz matrix ve tersi işareti olan, X'in transpozu oluyor.
    // n sayısı ise yine parametre olarak aldığımız row(satır) değeri.
    // Önclelikle X matrixin tüm elemanlarından, bulunduğu column(sütun)'un ortalamasını çıkarıyoruz. Sonrasında
    // X in transpozunu alıp yeni bir matrix oluşturuyoruz. Daha öncesinde üzerinde işlem yaptığımız matrixle
    // Transpoz olarak oluşturduğumuz matrixi çarpıp row değerine bölüp döndürüyoruz.

    // Çarpma ve transpoz için yeni matrixler oluşturuyor.
    float **transMatrix = returnZeroMatrix(row, col);

    float **multyMatrix = returnZeroMatrix(row, col);

    // Column'ların ortalamalarını yeni bir dizinin içine kaydediyor.
    float *colMeans = columnMeans(mat, row, col); //!!!!!!

    // Matrixin her elemanından, bulunduğu sütunun ortalamasını çıkarıyor.
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            mat[j][i] -= colMeans[i];
        }
    }

    // Transpoz işlemi yapıyor.
    transMatrix = matrixTranspose(mat, row, col);

    // Çarpma işlemi yapıyor
    multyMatrix = matrixMultiplication(mat, transMatrix, row, col, row, col);

    // Çarpma işleminin ardından her elemanı row değerine bölüyor.
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            multyMatrix[i][j] /= (float)row;
        }
    }

    return multyMatrix;
}

//************************************************************************************************************//

float determinant(float **mat, int row)
{
    // Öncelikle parametre olarak aldığım 3x3 matrixi, realloc kullanarak 5x3 olacak şekilde
    // genişletiyorum. Eski girdileri kullanarak yeni oluşturduğum alanı dolduruyorum.
    // Daha sonrasında 3x3 matrixe özel çapraz çarpım yöntemini kullanarak bu matrixin determinantını
    // hesaplayıp döndürüyorum. Bunun için önce sağa ve aşağı doğru sonrasında sola ve aşağı
    // doğru değerleri çarpıp işaretleriyle toplamamız yeterli.

    float detOfMatrix = 0, sumOfRight = 0, sumOfLeft = 0;
    int y = 0, k = 0;

    // Yeniden boyutlandırıyorum...
    for (int i = 0; i < row; i++)
    {
        mat[i] = realloc(mat[i], sizeof(float) + 2);
    }

    // Önceki girdileri kullanarak elemanları yerleştiriyorum...
    for (int m = 0; m < row; m++)
    {
        int p = 0;
        for (int n = row; n < (row + 2); n++)
        {

            mat[m][n] = mat[m][p];
            p++;
        }
    }

    // Determinant işleminde kullanmak için sağa çarpımları yapıyorum...

    for (int j = 0; j < row; j++)
    {
        float sum = 1;

        for (int n = (row - 1); n >= 0; n--)
        {

            sum *= mat[n][y];

            y++;
        }
        sumOfRight += sum;

        y -= 2;
    }

    // Determinant işleminde kullanmak için sola çarpımları yapıyorum...

    for (int j = 0; j < row; j++)
    {
        float sum = 1;

        for (int n = 0; n < row; n++)
        {

            sum *= mat[n][k];

            k++;
        }
        sumOfLeft += sum;

        k -= 2;
    }

    detOfMatrix = (sumOfRight - sumOfLeft);
    printf("\n");
    printf("\nDeterminant of matrix is %f", detOfMatrix, "\n");
    printf("                     ");
    printf("                     \n");
    return detOfMatrix;
}

//************************************************************************************************************//

void printVector(float *vec, int N)
{
    // Girilen tek boyutlu dizi uzunluğunca dönüyor
    // ve her elemanını yazdırıyor.

    printf("\n -- VECTOR -- \n");

    for (int i = 0; i < N; i++)
    {

        printf("%f ", vec[i]);
    }
    printf("\n");
}

//************************************************************************************************************//

void printMatrix(float **mat, int row, int col)
{
    // Girilen iki boyutlu diziyi satır ve sütunu dolaşarak
    // uzunluğunca her elemanını yazdırıyor

    printf("\n -- MATRIX -- \n");

    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            printf("%f ", mat[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

//************************************************************************************************************//

void randomNumbersForVector(float *vec, int row, int seed)
{

    // Tek boyutlu dizinin içinde 1-9 arası rastgele değerler döndüren metod.

    srand(seed);
    for (int i = 0; i < row; i++)
    {
        vec[i] = (float)(1 + (rand() % 9));
    }
}

//************************************************************************************************************//

void randomNumbersForMatrix(float **mat, int row, int col, int seed)
{

    // İki boyutlu dizinin içinde 1-9 arası rastgele değerler döndüren metod.

    srand(seed);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            mat[i][j] = (float)(1 + (rand() % 9));
        }
    }
}
