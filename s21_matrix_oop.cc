#include "s21_matrix_oop.h"
#include <cmath>
#include <stdexcept>

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be greater than 0.");
    }
    AllocateMemory();
}

S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    AllocateMemory();
    CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
    other.matrix_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
    DeallocateMemory();
}

void S21Matrix::AllocateMemory() {
    if (rows_ > 0 && cols_ > 0) {
        matrix_ = new double*[rows_];
        for (int i = 0; i < rows_; ++i) {
            matrix_[i] = new double[cols_]();
        }
    } else {
        matrix_ = nullptr;
    }
}

void S21Matrix::DeallocateMemory() {
    if (matrix_) {
        for (int i = 0; i < rows_; ++i) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
        matrix_ = nullptr;
    }
}

void S21Matrix::CopyMatrix(const S21Matrix& other) {
    for (int i = 0; i < rows_; ++i) {
        std::copy(other.matrix_[i], other.matrix_[i] + cols_, matrix_[i]);
    }
}

void S21Matrix::CheckMatrixValidity() const {
    if (rows_ <= 0 || cols_ <= 0 || matrix_ == nullptr) {
        throw std::runtime_error("Invalid matrix.");
    }
}

void S21Matrix::CheckMatrixValidity(const S21Matrix& other) const {
    other.CheckMatrixValidity();
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrix dimensions must match.");
    }
}

void S21Matrix::MoveMatrix(S21Matrix&& other) {
    DeallocateMemory();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.matrix_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
}

void S21Matrix::SetRows(int rows) {
    if (rows <= 0) {
        throw std::out_of_range("Number of rows must be greater than 0.");
    }
    if (rows != rows_) {
        double** new_matrix = new double*[rows];
        for (int i = 0; i < rows; ++i) {
            new_matrix[i] = new double[cols_]();
            if (i < rows_) {
                std::copy(matrix_[i], matrix_[i] + cols_, new_matrix[i]);
            }
        }
        DeallocateMemory();
        rows_ = rows;
        matrix_ = new_matrix;
    }
}

void S21Matrix::SetCols(int cols) {
    if (cols <= 0) {
        throw std::out_of_range("Number of columns must be greater than 0.");
    }
    if (cols != cols_) {
        for (int i = 0; i < rows_; ++i) {
            double* new_row = new double[cols]();
            std::copy(matrix_[i], matrix_[i] + std::min(cols_, cols), new_row);
            delete[] matrix_[i];
            matrix_[i] = new_row;
        }
        cols_ = cols;
    }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
    CheckMatrixValidity(other);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (fabs(other.matrix_[i][j] - matrix_[i][j]) > 1e-7) {
                return false;
            }
        }
    }
    return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
    CheckMatrixValidity(other);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] += other.matrix_[i][j];
        }
    }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
    CheckMatrixValidity(other);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] -= other.matrix_[i][j];
        }
    }
}

void S21Matrix::MulNumber(double num) {
    CheckMatrixValidity();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] *= num;
        }
    }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
    CheckMatrixValidity();
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Number of columns in the first matrix must match the number of rows in the second matrix.");
    }
    S21Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < other.cols_; ++j) {
            result.matrix_[i][j] = 0;
            for (int k = 0; k < cols_; ++k) {
                result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }
    *this = result;
}

S21Matrix S21Matrix::Transpose() const {
    CheckMatrixValidity();
    S21Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result.matrix_[j][i] = matrix_[i][j];
        }
    }
    return result;
}

S21Matrix S21Matrix::CalcComplements() const {
    CheckMatrixValidity();
    if (rows_ != cols_) {
        throw std::invalid_argument("Matrix must be square to calculate complements.");
    }
    S21Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            S21Matrix minor_matrix = MinorMatrix(i, j);
            result.matrix_[i][j] = pow(-1, i + j) * minor_matrix.Determinant();
        }
    }
    return result;
}

double S21Matrix::Determinant() const {
    CheckMatrixValidity();
    if (rows_ != cols_) {
        throw std::invalid_argument("Matrix must be square to calculate the determinant.");
    }
    if (rows_ == 1) {
        return matrix_[0][0];
    } else if (rows_ == 2) {
        return matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
    }
    double det = 0;
    int sign = 1;
    for (int i = 0; i < cols_; ++i) {
        S21Matrix minor_matrix = MinorMatrix(0, i);
        det += sign * matrix_[0][i] * minor_matrix.Determinant();
        sign *= -1;
    }
    return det;
}

S21Matrix S21Matrix::MinorMatrix(int row, int col) const {
    CheckMatrixValidity();
    S21Matrix result(rows_ - 1, cols_ - 1);
    for (int i = 0, minor_row = 0; i < rows_; ++i) {
        if (i == row) continue;
        for (int j = 0, minor_col = 0; j < cols_; ++j) {
            if (j == col) continue;
            result.matrix_[minor_row][minor_col] = matrix_[i][j];
            minor_col++;
        }
        minor_row++;
    }
    return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
    CheckMatrixValidity();
    double det = Determinant();
    if (fabs(det) < 1e-7) {
        throw std::runtime_error("Matrix is singular and cannot be inverted.");
    }
    S21Matrix complements = CalcComplements();
    S21Matrix transpose = complements.Transpose();
    transpose.MulNumber(1.0 / det);
    return transpose;
}

// Operators

bool S21Matrix::operator==(const S21Matrix& other) const {
    return EqMatrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
    SumMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
    SubMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
    MulMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
    MulNumber(num);
    return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
    S21Matrix new_matrix = *this;
    new_matrix += other;
    return new_matrix;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
    S21Matrix new_matrix = *this;
    new_matrix -= other;
    return new_matrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
    S21Matrix new_matrix = *this;
    new_matrix *= other;
    return new_matrix;
}

S21Matrix S21Matrix::operator*(double num) const {
    S21Matrix new_matrix = *this;
    new_matrix *= num;
    return new_matrix;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
    if (this != &other) {
        DeallocateMemory();
        rows_ = other.rows_;
        cols_ = other.cols_;
        AllocateMemory();
        CopyMatrix(other);
    }
    return *this;
}

double& S21Matrix::operator()(int i, int j) {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Matrix indices out of range.");
    }
    return matrix_[i][j];
}

const double& S21Matrix::operator()(int i, int j) const {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Matrix indices out of range.");
    }
    return matrix_[i][j];
}
