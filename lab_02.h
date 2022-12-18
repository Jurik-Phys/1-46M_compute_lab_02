// Начало файла lab_02.h
#ifndef LAB_02_H // 
#define LAB_02_H 1

#include <cmath>
#include <ctime>
#include <iostream>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_spblas.h>

// using namespace std;

class Matrix {
    protected:
        int m_rows, m_cols;

    public:
        Matrix();
        virtual ~Matrix() = 0; 
};

class SparseMatrix;

class DensityMatrix : public Matrix {
    private:
        gsl_matrix *m;

    public:
        DensityMatrix();
        ~DensityMatrix(); 
        DensityMatrix(const int&, const int&);
        DensityMatrix(gsl_matrix*);
        void fill(const char&);
        void print(const std::string&);
        gsl_matrix* get();
        SparseMatrix toSparseMatrix();
        void transpose();
        int get_rows();
        int get_cols();
        double get_value(const int&, const int&);
};

class SparseMatrix : public Matrix {
    private:
        gsl_spmatrix *sp_m;

    public:
        SparseMatrix();
        ~SparseMatrix(); 
        SparseMatrix(const int&, const int&);
        SparseMatrix(gsl_spmatrix*);
        void fill(const char&);
        void print(const std::string&);
        gsl_spmatrix* get();
        DensityMatrix toDensityMatrix();
        void transpose();
        int get_rows();
        int get_cols();
        double get_value(const int&, const int&);
};

class GSLMatrixMultiplication  {
    public:
        GSLMatrixMultiplication();
        ~GSLMatrixMultiplication();

        DensityMatrix density(DensityMatrix, DensityMatrix);
        // DensityMatrix density(SparseMatrix, DensityMatrix);
        // DensityMatrix density(DensityMatrix, SparseMatrix);
        // DensityMatrix density(SparseMatrix, SparseMatrix);

        SparseMatrix sparse(SparseMatrix, SparseMatrix);
};

#endif
