#include "s21_matrix_oop.hpp"

#include <cmath>

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols){
    if(rows>0 and cols>0){
        AllocateMemory();
    }
}
// сделать проверку
S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    AllocateMemory();
    CopyMatrix(other);
}

// сделать проверку
S21Matrix::S21Matrix(S21Matrix&& other) : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
    other.matrix_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
    DeallocateMemory();
}

void S21Matrix::AllocateMemory() {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        matrix_[i] = new double[cols_]();
    }
}


void S21Matrix::DeallocateMemory() {
    if(matrix_){
        for(int i=0;i<rows_;i++){
            delete[] matrix_[i];
        }
        delete[] matrix_;
        matrix_ = nullptr;
    }
}

void S21Matrix::MoveMatrix(S21Matrix&& other)  {
    DeallocateMemory();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.matrix_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
}

void S21Matrix::CopyMatrix(const S21Matrix& other) {
    for (int i = 0; i < rows_; ++i) {
        std::copy(other.matrix_[i], other.matrix_[i] + cols_, matrix_[i]);
    }
}

void S21Matrix::SetRows(int rows){
    if(rows!=rows_ and rows>0){
        matrix_ = new double*[rows_];
        for (int i = 0; i < rows_; ++i) {
            matrix_[i] = new double[cols_]();
            if (i<rows_){
                    std::copy(matrix_[i], matrix_[i] + cols_, new_matrix[i]);
            }
        })
        DeallocateMemory();
        rows_ = rows;
        matrix_ = new_matrix;

    }
}

void S21Matrix::SetColumns(int cols) {
    if(cols!=cols_ and cols>0){
        for (int i = 0; i < rows_; ++i) {
            double* new_row = new double[cols]();
            std::copy(matrix_[i], matrix_[i] + std::min(cols_, cols), new_row);
            delete[] matrix_[i];
            matrix_[i] = new_row;
        }
        cols_ = cols;
    }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
    bool res = true;
    if (other.rows_ != rows_ || other.cols_ != cols_) {
        result = false;
    } else {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                if (fabs(other.matrix_[i][j] - matrix_[i][j]) > 1e-7) {
                    res = false;
                }
            }
        }
        return res;
    }
}

void S21Matrix::SumMatrix(const S21Matrix& other){
    if (other.rows_ != rows_ ||  other.cols_ != cols_) {
        // вывести ошибку
        }
    for (int i = 0; i <rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] += other.matrix_[i][j];
        }
    }
}

void S21Matrix::SubMatrix(const S21Matrix& other){
    if (other.rows_ != rows_ ||  other.cols_ != cols_) {
        // вывести ошибку
    }
    for (int i = 0; i <rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] -= other.matrix_[i][j];
        }
    }
}

void S21Matrix::MulNumber(const double num){
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] *= num;
        }
    }
}

void S21Matrix::MulMatrix(const S21Matrix& other){
    if(cols_!=other.rows_){
        //вывести ошибку
    }
    S21Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            result.matrix_[i][j] = 0;
            for (int q = 0; q < cols_; q++) {
                result.matrix_[i][j] += matrix_[i][q] * other.matrix_[q][j];
            }
        }
    }
    *this = result;
}

S21Matrix S21Matrix::Transpose(){
    S21Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            result.matrix_[j][i] = matrix_[i][j];
        }
    }
    return result;
}

S21Matrix S21Matrix::CalcComplements() {
    if (rows_ != cols_) {
        // вывести ошибку
    }
    S21Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            S21Matrix minor_matrix = MinorMatrix(i, j);
            result.matrix_[i][j] = pow(-1, i + j) * minor_matrix.Determinant();
        }
    }
    return result;
}

double S21Matrix::Determinant() {
    if (rows_ != cols_) {
        // вывести ошибку
        }
    if (rows_ == 1) {
        return matrix_[0][0];
    } else if (rows_ == 2) {
        return matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];}
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

S21Matrix S21Matrix::InverseMatrix(){
    double det = Determinant();
    if (fabs(det) < 1e-7){
        // вывести ошибку
    }
    S21Matrix complements = CalcComplements();
    S21Matrix transpose = complements.Transpose();
    transpose.MulNumber(1.0 / det);
    return transpose;
}

// операторы

bool S21Matrix::operator==(const S21Matrix& other){
    return EqMatrix(other);
}
S21Matrix& S21Matrix::operator+=(const S21Matrix& other){
    SumMatrix(other);
    return *this;
}
S21Matrix& S21Matrix::operator-=(const S21Matrix& other){
    SubMatrix(other);
    return *this;
}
S21Matrix& S21Matrix::operator*=(const S21Matrix& other){
    MulMatrix(other);
    return *this;
}
S21Matrix& S21Matrix::operator*=(const double num){
    MulNumber(num);
    return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other){
    S21Matrix new_matrix = *this;
    new_matrix += other;
    return new_matrix;
}
S21Matrix S21Matrix::operator-(const S21Matrix& other){
    S21Matrix new_matrix = *this;
    new_matrix -= other;
    return new_matrix;
}
S21Matrix S21Matrix::operator*(const S21Matrix& other){
    S21Matrix new_matrix = *this;
    new_matrix *= other;
    return new_matrix;
}
S21Matrix S21Matrix::operator*(const double num){
    S21Matrix new_matrix = *this;
    new_matrix += num;
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
        //вывести ошибку
    }
    return matrix_[i][j];
}

double S21Matrix::operator()(int i, int j) const {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        //вывести ошибку
    }
    return matrix_[i][j];
}

