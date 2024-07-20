#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

class S21Matrix{
    private:
      int rows_;
      int cols_;
      double **matrix_;

      AllocateMemory();
      DeallocateMemory();
      CopyMatrix();
      MoveMatrix();

    public:

        int getRows() { return rows_; }
        int getCols() { return cols_; }
        double** getMatrix() { return matrix_; }
        void SetRows(int rows);
        void SetColumns(int cols);



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

        S21Matrix operator+=(const S21Matrix& other);
        S21Matrix operator-=(const S21Matrix& other);
        S21Matrix operator*=(const S21Matrix& other);
        S21Matrix operator*=(const double num);

        S21Matrix operator+(const S21Matrix& other);
        S21Matrix operator-(const S21Matrix& other);
        S21Matrix operator*(const S21Matrix& other);
        S21Matrix operator*(const double num);

        S21Matrix& operator=(const S21Matrix& other);
        bool operator==(const S21Matrix& other);

        double& operator()(int i, int j);
        double& operator()(int i, int j) const;




}


#endif // S21_MATRIX_OOP_H