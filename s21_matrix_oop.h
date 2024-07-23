#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <stdexcept>
#include <algorithm>

class S21Matrix {
private:
    int rows_;
    int cols_;
    double **matrix_;

    void AllocateMemory();
    void DeallocateMemory();
    void CopyMatrix(const S21Matrix& other);
    void MoveMatrix(S21Matrix&& other);
    void CheckMatrixValidity() const;
    void CheckMatrixValidity(const S21Matrix& other) const;

public:
    int GetRows() const { return rows_; }
    int GetCols() const { return cols_; }
    void SetRows(int rows);
    void SetCols(int cols);

    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();

    bool EqMatrix(const S21Matrix& other) const;
    void SumMatrix(const S21Matrix& other);
    void SubMatrix(const S21Matrix& other);
    void MulNumber(double num);
    void MulMatrix(const S21Matrix& other);
    S21Matrix Transpose() const;
    S21Matrix CalcComplements() const;
    double Determinant() const;
    S21Matrix InverseMatrix() const;
    S21Matrix MinorMatrix(int row, int col) const;

    S21Matrix& operator+=(const S21Matrix& other);
    S21Matrix& operator-=(const S21Matrix& other);
    S21Matrix& operator*=(const S21Matrix& other);
    S21Matrix& operator*=(double num);

    S21Matrix operator+(const S21Matrix& other) const;
    S21Matrix operator-(const S21Matrix& other) const;
    S21Matrix operator*(const S21Matrix& other) const;
    S21Matrix operator*(double num) const;

    S21Matrix& operator=(const S21Matrix& other);
    bool operator==(const S21Matrix& other) const;

    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;
};

#endif // S21_MATRIX_OOP_H
