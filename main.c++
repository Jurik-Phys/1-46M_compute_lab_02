// Начало файла main.c++

#include <cstdlib>
#include <ctime>
#include "lab_02.h"

int main(int argc, char** argv){
    // Умножьте матрицу A(100×130) aij=4.1*(i-j) на матрицу B (130×100) bij=i*j*5.2.
    // Результирующую матрицу транспонируйте.

    int row, col;
    GSLMatrixMultiplication multiplication;

    clock_t timer_start, timer_stop; 

    std::cout << "[*] Задание \n";
    std::cout << "    Умножьте матрицу A (100×130) aij=4.1*(i-j) \n";
    std::cout << "          на матрицу B (130×100) bij=i*j*5.2   \n"; 
    std::cout << "    Результирующую матрицу транспонируйте.   \n\n"; 

    std::cout << "Введите размерность матрицы A \n";
    std::cout << " - число строк (100): ";
    std::cin  >> row;
    std::cout << " - число столбцов (130): ";
    std::cin  >> col;
    
    // Создание плотной и разреженной матриц A
    DensityMatrix dens_A(row, col);
    SparseMatrix sp_A(row, col);
    DensityMatrix dens_AX(row, col);
    SparseMatrix sp_AX(row, col);

    std::cout << "\nВведите размерность матрицы B \n";
    std::cout << " - число строк (130): ";
    std::cin  >> row;
    std::cout << " - число столбцов (100): ";
    std::cin  >> col;
    
    // Создание плотной и разреженной матриц B
    DensityMatrix dens_B(row, col);
    SparseMatrix sp_B(row, col);
    DensityMatrix dens_BY(row, col);
    SparseMatrix sp_BY(row, col);

    // Заполнение данными 
    dens_A.fill('A');
    sp_A.fill('A');
    
    dens_B.fill('B');
    sp_B.fill('B');
    
    // Вывод матриц размером менее 15x15 на экран
    dens_A.print("A (density)");
    sp_A.print("A (sparse)");

    dens_B.print("B (density)");
    sp_B.print("B (sparse)");

    // Произведение плотных матриц 
    timer_start = clock();
        DensityMatrix dens_result = multiplication.density(dens_A, dens_B);
    timer_stop = clock();
    dens_result.print("Multiplication Result (density)");
    std::cout << "      Длительность " << 1000*( timer_stop - timer_start ) / (double) CLOCKS_PER_SEC << " (мc) \n";

    // Произведение разреженных матриц
    timer_start = clock();
        SparseMatrix sp_result = multiplication.sparse(sp_A, sp_B);
    timer_stop = clock();
    sp_result.print("Multiplication Result (sparse)");
    std::cout << "      Длительность " << 1000*( timer_stop - timer_start ) / (double) CLOCKS_PER_SEC << " (мс) \n";

    // Транспонирование результата произведения матриц
    dens_result.transpose();
    dens_result.print("Transpose Multiplication Result (density)");
    
    sp_result.transpose();
    sp_result.print("Transpose Multiplication Result (sparse)");

    // Преобразование разреженной матрицы в плотную
    DensityMatrix dens_from_sparse_A = sp_A.toDensityMatrix();
    dens_from_sparse_A.print("A (density from sparse)");

    // Преобразование плотной матрицы в разреженную 
    SparseMatrix sparse_from_dens_A = dens_A.toSparseMatrix();
    sparse_from_dens_A.print("A (sparse from density)");

    dens_AX.fill('X');
    sp_AX.fill('X');
    
    dens_BY.fill('Y');
    sp_BY.fill('Y');
    
    // Вывод матриц размером менее 15x15 на экран
    dens_AX.print("X (density)");
    sp_AX.print("X (sparse)");

    dens_BY.print("Y (density)");
    sp_BY.print("Y (sparse)");
    
    // Произведение плотных матриц 
    timer_start = clock();
        DensityMatrix dens_result_xy = multiplication.density(dens_AX, dens_BY);
    timer_stop = clock();
    dens_result_xy.print("Multiplication Result (density)");
    std::cout << "      Длительность " << 1000*( timer_stop - timer_start ) / (double) CLOCKS_PER_SEC << " (мс) \n";

    // Произведение разреженных матриц
    timer_start = clock();
        SparseMatrix sp_result_xy = multiplication.sparse(sp_AX, sp_BY);
    timer_stop = clock();
    sp_result_xy.print("Multiplication Result (sparse)");
    std::cout << "      Длительность " << 1000*( timer_stop - timer_start ) / (double) CLOCKS_PER_SEC << " (мс) \n";

    return EXIT_SUCCESS;
}
