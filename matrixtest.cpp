#include <vector>
#include <exception>
#include <fstream>
#include <climits>

#include "matrix.h"

#undef throw

inline bool equals(double x, double y) {
    return x - y < 1e-6 && x - y > -1e-6;
}

const size_t bigPrime = 1493;

void testMatrix() {
    // Now let's test matrices.
    using std::vector;
    
    
    const Matrix<4,5,Residue<17>> am = {{8,-4,-5,5,9},
                            {1,-3,-5,0,-7},
                            {7,-5,1,4,1},
                            {3,-1,3,2,5}};
    const Matrix<5,4,Residue<17>> bm = {{4,0,3,2},
                            {1,-7,4,5},
                            {7,1,5,3},
                            {-5,-3,-3,-1},
                            {1,-5,2,3}};

    if (am.rank() != 4 || bm.rank() != 3)
        throw std::runtime_error("rank() method failed.");
    const SquareMatrix<4, Residue<17>> ab = {{-23, -37, -14, 3},
                             {-41, 51, -48, -49},
                             {11, 19, -4, -9},
                             {27, -21, 24, 23}};

    const auto abm = am*bm;
    if (abm != SquareMatrix<4,Residue<17>>(ab))
        throw std::runtime_error("matrix multiplication or constructors failed.");

    const auto aminusb = am - bm.transposed();
    const Matrix<4,5,Residue<17>> diff = {{4, -5, -12, 10, 8},
                                {1, 4, -6, 3, -2},
                                {4, -9, -4, 7, -1},
                                {1, -6, 0, 3, 2}};
    if (aminusb != diff)
        throw std::runtime_error("Addition or subtraction failed.");

    auto newMatrix = Residue<17>(2) * aminusb * bm;
    newMatrix[2][2] = Residue<17>(1);

    if (newMatrix.det() != Residue<17>(14420160))
        throw std::runtime_error("Determinant is wrong.");

    if (newMatrix.trace() != Residue<17>(-345))
        throw std::runtime_error("Trace is wrong.");

    Matrix<4,4,Residue<17>> finiteUnity;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            finiteUnity[i][j] = Residue<17>(i == j);
        }
    }
    if (newMatrix.inverted() * newMatrix != finiteUnity)
        throw std::runtime_error("A*A^(-1) must be equal to unity matrix.");

    std::cerr << "Tests over the finite field passed!\n";

    // std::ifstream in("matr.txt");
    // SquareMatrix<20> bigMatrix;
    // for (int i = 0; i < 20; ++i)
    //     for (int j = 0; j < 20; ++j)
    //         in >> bigMatrix[i][j];

    // vector<vector<double>> bigInvertedMatrix(20, vector<double>(20));
    // for (int i = 0; i < 20; ++i)
    //     for (int j = 0; j < 20; ++j)
    //         in >> bigInvertedMatrix[i][j];

    // auto anotherMatrix = bigMatrix;
    //bigMatrix.inverted();
    // bigMatrix.invert();
    // std::cerr << "Big matrix inverted!\n";
    // for (int i = 0; i < 20; ++i) {
    //     auto row = bigMatrix.getRow(i);
    //     auto anotherRow = bigInvertedMatrix[i];
    //     for (int j = 0; j < 20; ++j) {
    //         if (!equals(static_cast<double>(row[j]), anotherRow[j])) {
    //             throw std::runtime_error("Inverted matrix is incorrect!");
    //         }
    //     }
    // }
    // std::cerr << "Inverted matrix is correct!\n";
    // bigMatrix *= anotherMatrix;
    // std::cerr << "Matrix multiplied by its inverted matrix!\n";
    // SquareMatrix<20> unity = SquareMatrix<20>();
    // for (int i = 0; i < 20; ++i) {
    //     for (int j = 0; j < 20; ++j) {
    //         unity[i][j] = (i == j);
    //     }
    // }

    // for (int j  = 0; j < 20; ++j) {
    //     auto column = bigMatrix.getColumn(j);
    //     auto unityColumn = unity.getColumn(j);
    //     for (int i = 0; i < 20; ++i) {
    //         if (column[i] != unityColumn[i]) {
    //             throw std::runtime_error("Product of A and A^(-1) must be equal to unity matrix.");
    //         }
    //     }
    // }

    // std::cerr << "Result of A*A^(-1) is correct!\n";

    // auto det = anotherMatrix.det();
    // std::cerr << "Determinant is computed!\n";
    // //det /= 20;
    // for (int i = 0; i < 20; ++i)
    //     anotherMatrix[0][i] /= det;
    // // now anotherMatrix is orthogonal matrix
    // if (anotherMatrix.det() != 1)
    //     throw std::runtime_error("Dividing a row by det must make the determinant equal to 1.");

    // auto transposedMatrix = anotherMatrix.transposed();
    // if ((anotherMatrix *= transposedMatrix).det() != 1)
    //     throw std::runtime_error("Product of two matrices with det=1 must give the matrix with same determinant.");

}
int main(){
    testMatrix();
}
