#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

using Matrix = vector<vector<int>>;

int getCellWidth(const Matrix &mat) {
    int maxVal = 0;
    for (const auto &row : mat)
        for (int val : row)
            if (abs(val) > maxVal)
                maxVal = abs(val);

    int width = 1;
    while (maxVal >= 10) {
        maxVal /= 10;
        width++;
    }
    return max(2, width + 1);
}

void printMatrix(const Matrix &mat) {
    if (mat.empty()) {
        cout << "(empty)\n\n";
        return;
    }

    int width = getCellWidth(mat);
    for (const auto &row : mat) {
        for (int val : row)
            cout << setw(width) << val;
        cout << '\n';
    }
    cout << '\n';
}

Matrix readMatrix(ifstream &file, int size) {
    Matrix mat(size, vector<int>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            file >> mat[i][j];
    return mat;
}

Matrix addMatrix(const Matrix &A, const Matrix &B) {
    int size = A.size();
    Matrix result(size, vector<int>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] + B[i][j];
    return result;
}

Matrix multiplyMatrix(const Matrix &A, const Matrix &B) {
    int size = A.size();
    Matrix result(size, vector<int>(size, 0));
    for (int i = 0; i < size; i++)
        for (int k = 0; k < size; k++)
            for (int j = 0; j < size; j++)
                result[i][j] += A[i][k] * B[k][j];
    return result;
}

pair<long long, long long> getDiagonalSums(const Matrix &mat) {
    int size = mat.size();
    long long mainSum = 0, secondarySum = 0;
    for (int i = 0; i < size; i++) {
        mainSum += mat[i][i];
        secondarySum += mat[i][size - 1 - i];
    }
    return {mainSum, secondarySum};
}

bool swapRows(Matrix &mat, int r1, int r2) {
    int size = mat.size();
    if (r1 < 0 || r2 < 0 || r1 >= size || r2 >= size)
        return false;
    swap(mat[r1], mat[r2]);
    return true;
}

bool swapCols(Matrix &mat, int c1, int c2) {
    int size = mat.size();
    if (c1 < 0 || c2 < 0 || c1 >= size || c2 >= size)
        return false;
    for (int i = 0; i < size; i++)
        swap(mat[i][c1], mat[i][c2]);
    return true;
}

bool updateCell(Matrix &mat, int r, int c, int value) {
    int size = mat.size();
    if (r < 0 || c < 0 || r >= size || c >= size)
        return false;
    mat[r][c] = value;
    return true;
}

int main() {
    string fileName;
    cout << "Enter the input file name: ";
    cin >> fileName;

    ifstream input(fileName);
    if (!input) {
        cout << "Error: Could not open the file.\n";
        return 1;
    }

    int n;
    input >> n;
    if (n <= 0) {
        cout << "Error: First value must be a positive integer N.\n";
        return 1;
    }

    Matrix A = readMatrix(input, n);
    Matrix B = readMatrix(input, n);

    cout << "Matrix A:\n";
    printMatrix(A);

    cout << "Matrix B:\n";
    printMatrix(B);

    cout << "A + B:\n";
    printMatrix(addMatrix(A, B));

    cout << "A * B:\n";
    printMatrix(multiplyMatrix(A, B));

    auto [sumA1, sumA2] = getDiagonalSums(A);
    cout << "diagonal sums of A main: " << sumA1 << ", secondary: " << sumA2 << "\n";

    auto [sumB1, sumB2] = getDiagonalSums(B);
    cout << "diagonal sums of B main: " << sumB1 << ", secondary: " << sumB2 << "\n\n";

    if (n >= 2) {
        Matrix ArowSwap = A;
        if (swapRows(ArowSwap, 0, 1)) {
            cout << "A after swapping rows 0 and 1:\n";
            printMatrix(ArowSwap);
        }

        Matrix AcolSwap = A;
        if (swapCols(AcolSwap, 0, 1)) {
            cout << "A after swapping cols 0 and 1:\n";
            printMatrix(AcolSwap);
        }
    } else {
        cout << "(Skipping row/col swaps: N < 2)\n\n";
    }

    Matrix Aupdated = A;
    if (updateCell(Aupdated, 0, 0, 999)) {
        cout << "A after updating A[0][0] = 999:\n";
        printMatrix(Aupdated);
    } else {
        cout << "(Skipping update: invalid indices)\n\n";
    }

    return 0;
}
