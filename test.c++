#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include <cstdlib>
#include <ctime>
#include "lab_02.h"

TEST_CASE("General density matrix test"){
    GSLMatrixMultiplication multiplication;
    // Создание плотной матрицы
    DensityMatrix dens_A(5, 7);
    DensityMatrix dens_B(7, 5);
    
    // Заполнение данными 
    dens_A.fill('A');
    dens_B.fill('B');

    DensityMatrix dens_result = multiplication.density(dens_A, dens_B);

    CHECK( abs(dens_result.get_value(1,1) + 1492.4 ) < 0.0001 );
}

TEST_CASE("General sparse matrix test"){
    GSLMatrixMultiplication multiplication;
    // Создание разреженой матрицы
    SparseMatrix sp_A(5, 7);
    SparseMatrix sp_B(7, 5);
    
    // Заполнение данными 
    sp_A.fill('A');
    sp_B.fill('B');

    SparseMatrix sp_result = multiplication.sparse(sp_A, sp_B);

    CHECK( abs(sp_result.get_value(1,1) + 1492.4 ) < 0.0001 );
}

TEST_CASE("General transpose matrix test"){
    // Создание разреженой матрицы
    SparseMatrix sp_A(5, 7);
    
    // Заполнение данными 
    sp_A.fill('A');

    double ff_sp_A = sp_A.get_value(4,2);
    sp_A.transpose();

    CHECK( sp_A.get_value(2,4) == ff_sp_A );
}
