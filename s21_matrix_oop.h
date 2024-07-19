#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

class s21matrix{
    private:
      int rows_;
      int cols_;
      double **matrix_;
    public:
       S21Matrix();
       S21Matrix(int rows, int cols);
       S21Matrix(const S21Matrix& other);
       S21Matrix(S21Matrix&& other);
       ~S21Matrix();


       bool EqMatrix(const S21Matrix& other);
       void SumMatrix(const S21Matrix& other);
       void SubMatrix(const S21Matrix& other);
       void MulNumber(const double num);
       void MulMatrix(const S21Matrix& other);
       S21Matrix Transpose();
       S21Matrix CalcComplements();
       double Determinant();
       S21Matrix InverseMatrix();





}


#endif // S21_MATRIX_OOP_H