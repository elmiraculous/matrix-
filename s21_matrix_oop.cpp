#include "s21_matrix_oop.hpp"


S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {
}

//  сделать проверку на меньше 0
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols){
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
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        matrix_[i] = new double[cols_]();
    }
}

void S21Matrix::DeallocateMemory() {
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






