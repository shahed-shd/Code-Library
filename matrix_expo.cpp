// Algorithm        : Matrix expo calculation
// Language         : C++11


#include <cstdio>
#include <vector>
using namespace std;


typedef long long LL;


class Matrix {
public:
    vector<vector<LL>> mat;

    Matrix(int row, int col, LL value = 0) {
        mat.resize(row, vector<LL>(col, value));
    }

    inline int getRowCount() const { return mat.size(); }

    inline int getColumnCount() const { return mat[0].size(); }

    Matrix multiply(const Matrix& other) const {
        int prodRowCount = getRowCount();
        int prodColCount = other.getColumnCount();
        int eachElemLoopCount = getColumnCount();

        Matrix prod(prodRowCount, prodColCount, 0);

        for (int r = 0; r < prodRowCount; ++r) {
            for (int c = 0; c < prodColCount; ++c) {
                LL &ref = prod.mat[r][c] = 0;

                for (int i = 0; i < eachElemLoopCount; ++i) {
                    ref += mat[r][i] * other.mat[i][c];
                }
            }
        }

        return prod;
    }

    Matrix expo(const int& pw) const {
        int dim = getRowCount(); // Must be a square matrix
        Matrix res(dim, dim);

        if (pw == 1) {
            res.mat = mat;
            return res;
        }

        if (pw & 1) {
            Matrix tmp = expo(pw - 1);
            res = multiply(tmp);
        }
        else {
            Matrix tmp = expo(pw >> 1);
            res = tmp.multiply(tmp);
        }

        return res;
    }

    void print() const {
        for (auto &vec : mat) {
            for (auto &x : vec) {
                printf(" %lld", x);
            }
            printf("\n");
        }
    }
};


int main()
{
    Matrix matA(3, 3);
    matA.mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    printf("Matrix A:\n");
    matA.print();

    Matrix matB(3, 4, 7);
    printf("\nMatrix B:\n");
    matB.print();

    Matrix matProd = matA.multiply(matB);
    printf("\nA * B:\n");
    matProd.print();

    int pw = 9;
    Matrix matExpoRes = matA.expo(pw);
    printf("\nA raised to the power %d:\n", pw);
    matExpoRes.print();

    return 0;
}

/*
Output:

Matrix A:
 1 2 3
 4 5 6
 7 8 9

Matrix B:
 7 7 7 7
 7 7 7 7
 7 7 7 7

A * B:
 42 42 42 42
 105 105 105 105
 168 168 168 168

A raised to the power 9:
 8219725776 10099688472 11979651168
 18614436174 22871810025 27129183876
 29009146572 35643931578 42278716584
 
*/
