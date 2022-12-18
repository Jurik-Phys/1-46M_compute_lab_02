// Начало файла lab_02.с++

#include "lab_02.h"

Matrix::Matrix() {
    // Debug
    // std::cout << "Matrix Constructor" << "\n";
}

Matrix::~Matrix() {
    // Debug
    // std::cout << "[~] Matrix Destructor" << "\n";
}

DensityMatrix::DensityMatrix(){
    // Debug
    std::cout << "DensityMatrix Constructor без параметров" << "\n";
}

DensityMatrix::DensityMatrix(const int& rows, const int& cols){
    // Debug
    // std::cout << "DensityMatrix Constructor" << "\n";
    m_rows = rows;
    m_cols = cols; 
    gsl_matrix *new_m = gsl_matrix_alloc (m_rows, m_cols);
    m = new_m;
}

DensityMatrix::DensityMatrix(gsl_matrix* new_m){
    // Debug
    // std::cout << "DensityMatrix Constructor" << "\n";
    
    m = new_m;
    m_rows = new_m->size1; 
    m_cols = new_m->size2; 
}

DensityMatrix::~DensityMatrix() { 
    // Debug
    // std::cout << "[~] DensityMatrix Destructor" << "\n";
}

void DensityMatrix::fill(const char& algo_type){
    if ( algo_type == 'A' ) { 
        // A(100×130) aij=4.1*(i-j)
        for ( int i = 0; i < m_rows; i++) {
            for ( int j = 0; j < m_cols; j++ ) {
                gsl_matrix_set (this->m, i, j, 4.1*(i-j));
            }
        }
    }

    if ( algo_type == 'B' ) {
        // B (130×100) bij=i*j*5.2.
        for ( int i = 0; i < m_rows; i++) {
            for ( int j = 0; j < m_cols; j++ ) {
                gsl_matrix_set (this->m, i, j, i*j*5.2);
            }
        }
    }

    if ( algo_type == 'X' ) { 
        // A(100×130) aij=4.1*(i-j)
        for ( int i = 0; i < m_rows; i++) {
            for ( int j = 0; j < m_cols; j++ ) {
                if (( i == 3 ) || ( i == 7 ) || ( j == 3 ) || ( j == 7 ) ){
                    gsl_matrix_set (this->m, i, j, 4.1*(i-j));
                }
                else{
                    gsl_matrix_set (this->m, i, j, 0 );
                }
            }
        }
    }

    if ( algo_type == 'Y' ) { 
        // B (130×100) bij=i*j*5.2.
        for ( int i = 0; i < m_rows; i++) {
            for ( int j = 0; j < m_cols; j++ ) {
                if (( i == 3 ) || ( i == 5 ) || ( i == 7 ) || ( j == 3 ) || ( j == 7 ) ){
                    gsl_matrix_set (this->m, i, j,  i*j*5.2);
                }
                else{
                    gsl_matrix_set (this->m, i, j, 0 );
                }
            }
        }
    }
}

void DensityMatrix::print(const std::string& m_name){
    std::cout << " ==>> Матрица " << m_name << " [" << m_rows << "x" << m_cols << "]\n" ;  
    if ( ( m_rows < 16 ) && ( m_cols < 16 ) ){
        for ( int i = 0; i < m_rows; i++) {
            std::cout << "\n";
            for ( int j = 0; j < m_cols; j++ ) {
                printf("%10.1f ", gsl_matrix_get (this->m, i, j));	
            }
        }
        std::cout << "\n\n";
    }else
        std::cout << "      Максимальный размер матрицы для вывода на экран 15x15 \n";
}

gsl_matrix* DensityMatrix::get(){
    return this->m;
}

int DensityMatrix::get_rows(){
    return m->size1;
}

int DensityMatrix::get_cols(){
    return m->size2;
}

SparseMatrix DensityMatrix::toSparseMatrix(){
    gsl_spmatrix *sp_matrix = gsl_spmatrix_alloc(this->get_rows(), this->get_cols()); 

    // https://www.gnu.org/software/gsl/doc/html/spmatrix.html#c.gsl_spmatrix_d2sp
    gsl_spmatrix_d2sp(sp_matrix, this->get());
       
    // for ( int i = 0; i < this->get_rows(); i++) {
    //     for ( int j = 0; j < this->get_cols(); j++ ) {
    //         gsl_spmatrix_set (sp_matrix, i, j, gsl_matrix_get (this->m, i, j));
    //     }    
    // }

    SparseMatrix out_matrix(sp_matrix);
    return out_matrix;
}

void DensityMatrix::transpose(){
    // https://www.gnu.org/software/gsl/doc/html/vectors.html?highlight=transpose#c.gsl_matrix_transpose
    gsl_matrix_transpose(m);
}

double DensityMatrix::get_value(const int& i, const int& j){
    return gsl_matrix_get (this->m, i, j);
}


SparseMatrix::SparseMatrix(const int& rows, const int& cols){
    // Debug
    // std::cout << "SparseMatrix Constructor" << "\n";
    m_rows = rows;
    m_cols = cols; 
    gsl_spmatrix *new_sp_m = gsl_spmatrix_alloc (m_rows, m_cols);
    // gsl_spmatrix *new_sp_m = gsl_spmatrix_alloc_nzmax(m_rows, m_cols, (int)m_ros*m_cols*0.1, GSL_SPMATRIX_CSC);
    sp_m = new_sp_m;
}

SparseMatrix::SparseMatrix(gsl_spmatrix* new_sp_m){
    // Debug
    // std::cout << "DensityMatrix Constructor" << "\n";
    
    sp_m = new_sp_m;
    m_rows = new_sp_m->size1; 
    m_cols = new_sp_m->size2; 
}

SparseMatrix::~SparseMatrix() { 
    // Debug
    // std::cout << "[~] SparseMatrix Destructor" << "\n";
}

void SparseMatrix::fill(const char& algo_type){
    if ( algo_type == 'A' ) { 
        // A(100×130) aij=4.1*(i-j)
        for ( int i = 0; i < m_rows; i++) {
            for ( int j = 0; j < m_cols; j++ ) {
                gsl_spmatrix_set (this->sp_m, i, j, 4.1*(i-j));
            }
        }
    }

    if ( algo_type == 'B' ) {
        // B (130×100) bij=i*j*5.2.
        for ( int i = 0; i < m_rows; i++) {
            for ( int j = 0; j < m_cols; j++ ) {
                gsl_spmatrix_set (this->sp_m, i, j, i*j*5.2);
            }
        }
    }
    
    if ( algo_type == 'X' ) { 
        // A(100×130) aij=4.1*(i-j)
        for ( int i = 0; i < m_rows; i++) {
            for ( int j = 0; j < m_cols; j++ ) {
                if (( i == 3 ) || ( i == 7 ) || ( j == 3 ) || ( j == 7 ) ){
                    gsl_spmatrix_set (this->sp_m, i, j, 4.1*(i-j));
                }
                else{
                    gsl_spmatrix_set (this->sp_m, i, j, 0 );
                }
            }
        }
    }

    if ( algo_type == 'Y' ) { 
        // B (130×100) bij=i*j*5.2.
        for ( int i = 0; i < m_rows; i++) {
            for ( int j = 0; j < m_cols; j++ ) {
                if (( i == 3 ) || ( i == 5 ) || ( i == 7 ) || ( j == 3 ) || ( j == 7 ) ){
                    gsl_spmatrix_set (this->sp_m, i, j,  i*j*5.2);
                }
                else{
                    gsl_spmatrix_set (this->sp_m, i, j, 0 );
                }
            }
        }
    }
}

void SparseMatrix::print(const std::string& m_name){
    std::cout << " ==>> Матрица " << m_name << " [" << m_rows << "x" << m_cols << "]\n" ;  
    if ( ( m_rows < 16 ) && ( m_cols < 16 ) ){
        for ( int i = 0; i < m_rows; i++) {
            std::cout << "\n";
            for ( int j = 0; j < m_cols; j++ ) {
                printf("%10.1f ", gsl_spmatrix_get (this->sp_m, i, j));	
            }
        }
        std::cout << "\n\n";
    }else
        std::cout << "      Максимальный размер матрицы для вывода на экран 15x15 \n";
}

gsl_spmatrix* SparseMatrix::get(){
    return this->sp_m;
}

int SparseMatrix::get_rows(){
    return sp_m->size1;
}

int SparseMatrix::get_cols(){
    return sp_m->size2;
}

DensityMatrix SparseMatrix::toDensityMatrix(){
    gsl_matrix *dens_matrix = gsl_matrix_alloc(this->get_rows(), this->get_cols()); 

    // https://www.gnu.org/software/gsl/doc/html/spmatrix.html#c.gsl_spmatrix_sp2d
    gsl_spmatrix_sp2d(dens_matrix, this->get() );

    // for ( int i = 0; i < this->get_rows(); i++) {
    //     for ( int j = 0; j < this->get_cols(); j++ ) {
    //         gsl_matrix_set (dens_matrix, i, j, gsl_spmatrix_get (this->sp_m, i, j));
    //     }    
    // }

    DensityMatrix out_matrix(dens_matrix);
    return out_matrix;
}

void SparseMatrix::transpose(){
    // https://www.gnu.org/software/gsl/doc/html/spmatrix.html?highlight=gsl_spmatrix_transpose#c.gsl_spmatrix_transpose
    gsl_spmatrix_transpose(sp_m);
}

double SparseMatrix::get_value(const int& i, const int& j){
    return gsl_spmatrix_get (this->sp_m, i, j);
}

// ==>> GSL MATRIX MULTIPLICATION << == //
 
GSLMatrixMultiplication::GSLMatrixMultiplication(){
    // Debug
    // std::cout << "GSLMatrixMultiplication Constructor" << "\n";
}
 
GSLMatrixMultiplication::~GSLMatrixMultiplication() {
    // Debug
    // std::cout << "[~] GSLMatrixMultiplication Destructor" << "\n";
}

DensityMatrix GSLMatrixMultiplication::density(DensityMatrix den_A, DensityMatrix den_B){

    gsl_matrix *A = den_A.get();
    gsl_matrix *B = den_B.get();

    // https://www.gnu.org/software/gsl/doc/html/blas.html#examples
    // https://www.gnu.org/software/gsl/doc/html/blas.html#level-3
    gsl_matrix *res_matrix = gsl_matrix_calloc(A->size1, B->size2);
 	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, A, B, 0.0, res_matrix );

    DensityMatrix dens_m(res_matrix);
    return dens_m; 
}

SparseMatrix GSLMatrixMultiplication::sparse(SparseMatrix sp_A, SparseMatrix sp_B) {
    // https://www.gnu.org/software/gsl/doc/html/spblas.html
    // CSC  (compressed sparse column format)
    
    int non_zero_values_A = sp_A.get_rows()* sp_A.get_cols() * 0.2;
    int non_zero_values_B = sp_B.get_rows()* sp_B.get_cols() * 0.2;
    int non_zero_values_R = sp_A.get_rows()* sp_B.get_cols() * 0.2;

    gsl_spmatrix* spA_compress        = gsl_spmatrix_alloc_nzmax(sp_A.get_rows(), sp_A.get_cols(), non_zero_values_A, GSL_SPMATRIX_CSC );
    gsl_spmatrix* spB_compress        = gsl_spmatrix_alloc_nzmax(sp_B.get_rows(), sp_B.get_cols(), non_zero_values_B, GSL_SPMATRIX_CSC );
    gsl_spmatrix* res_matrix_compress = gsl_spmatrix_alloc_nzmax(sp_A.get_rows(), sp_B.get_cols(), non_zero_values_R, GSL_SPMATRIX_CSC );

    gsl_spmatrix_csc(spA_compress, sp_A.get());
    gsl_spmatrix_csc(spB_compress, sp_B.get());
    
	gsl_spblas_dgemm(1.0, spA_compress, spB_compress, res_matrix_compress );
	
    SparseMatrix out_matrix(res_matrix_compress);
    return out_matrix;
}

