#include <bits/stdc++.h>
#include "Matrix.hpp"



static thread_local std::mt19937 rng(std::random_device{}());

void print_matrix(Matrix& A){

    for(int i=0; i<A.size().first; i++){
        for(int j=0; j<A.size().second; j++) 
            std::cout<<A[i][j]<<" ";
        std::cout << std::endl;    
    }
}

Matrix matmul(Matrix& A, Matrix& B){
    int rowsA=A.size().first, colsA=A.size().second; 
    int rowsB=B.size().first, colsB = B.size().second; 

    if(colsA != rowsB){
        std::cerr << "Matrix multiplication error: Dimensions of Matrices do not match\n";
        throw std::runtime_error("Dimensions of Matrices do not match");
    }

    double sum; 
    Matrix C(rowsA, colsB);
    for(int i=0; i<rowsA; i++){
        for(int j=0; j<colsB; j++){
            sum = 0; 
            for(int k=0; k<colsA; k++)
                sum += A[i][k] * B[k][j];
            C[i][j] = sum; 
        }
    } 
    return C; 
}

Matrix ones(int rows, int cols){
    Matrix mat(rows, cols); 
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            mat[i][j] = 1.0; 
        }
    }
    return mat; 
}


Matrix eye(int n){
    Matrix mat(n,n); 
    for(int i=0; i<n; i++){
        mat[i][i] = 1;
    }
    return mat; 
}

Matrix::Matrix(int rows, int cols): rows(rows), cols(cols), array(rows, std::vector<double>(cols, 0.0)){
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> init) {
    rows = init.size();
    cols = init.begin()->size();
    array.resize(rows);
    
    int i = 0;
    for(const auto& row : init) {
        if (row.size() != cols) 
            throw std::invalid_argument("All rows must have equal columns");
        array[i++] = row; // Copy each row
    }
}


double Matrix::get(int i, int j){
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    return array[i][j];
}

void Matrix::set(int i, int j, double val){ 
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    array[i][j] = val;
}


std::pair<int, int> Matrix::size() {
    return std::make_pair(rows, cols);  
}

Matrix Matrix::transpose(){ 

    Matrix mat(cols, rows);
    for(int i = 0; i<cols; i++){
        for(int j=0; j<rows; j++){
            mat[i][j] = array[j][i]; 
        }
    }
    return mat; 

}

Matrix Matrix::operator+(const Matrix& A) const{

    if (rows != A.rows || cols != A.cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }

    Matrix C(rows, cols); 
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            C[i][j] = array[i][j] + A[i][j];
        }
    }

    return C; 
}

Matrix Matrix::operator*(const Matrix& A) const{

    if (rows != A.rows || cols != A.cols) {
        std::cerr << "Matrix dimensions must match for element wise multiplication\n";
        throw std::runtime_error("Dimensions of Matrices do not match");
    }

    Matrix C(rows, cols); 
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            C[i][j] = array[i][j] * A[i][j];
        }
    }

    return C;
}



Matrix Matrix::operator*(const double& a) const{

    Matrix C(rows, cols); 
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            C[i][j] = array[i][j] * a;
        }
    }

    return C;
}



Matrix Matrix::operator-(const Matrix& A) const{

    if (rows != A.rows || cols != A.cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }

    Matrix C(rows, cols); 
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            C[i][j] = array[i][j] - A[i][j];
        }
    }

    return C; 
}


Matrix Matrix::operator/(const Matrix& A) const{

    if (rows != A.rows || cols != A.cols) {
        std::cerr << "Matrix dimensions must match for element wise multiplication\n";
        throw std::runtime_error("Dimensions of Matrices do not match");
    }

    for(int i=0; i<rows; i++){
        for(int j = 0; j<cols; j++){
            if(A[i][j]==0.0){
                std::cerr << "Matrix division not possible due to 0 values\n";
                throw std::runtime_error("Division by 0");
            }
        }
    }

    Matrix C(rows, cols); 
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            C[i][j] = array[i][j] / A[i][j];
        }
    }

    return C;
}


Matrix Matrix::get_row(int i){
    
    int columns = cols; 
    Matrix v(1, cols); 
    for(int j=0; j<columns; j++){
        v[0][j] = array[i][j];  
    } 
    return v;
}

Matrix Matrix::get_column(int j){
    
    int rows = rows; 
    Matrix v(rows, 1); 
    for(int i=0; i<rows; i++){
        v[i][0] = array[i][j];  
    } 
    return v;
}

Matrix Matrix::slice(
    int row_start = 0, 
    int row_end = -1,  // -1 means "all rows till the end"
    int column_start = 0, 
    int column_end = -1 // -1 means "all columns till the end"
) {
    // Handle default cases for row_end/column_end
    if (row_end == -1) row_end = rows - 1;
    if (column_end == -1) column_end = cols - 1;

    // Bounds checking
    if (row_start < 0 || row_end >= rows || column_start < 0 || column_end >= cols)
        throw std::out_of_range("Slice indices out of bounds");

    int new_rows = row_end - row_start + 1;
    int new_cols = column_end - column_start + 1;
    Matrix sub_matrix(new_rows, new_cols);

    for (int i = 0; i < new_rows; i++) {
        for (int j = 0; j < new_cols; j++) {
            sub_matrix[i][j] = array[row_start + i][column_start + j];
        }
    }

    return sub_matrix;
}


Matrix concatenate(Matrix& A, Matrix& B, int dim) {
    // Check if matrices are non-empty
    if (A.size().first == 0 || A.size().second == 0 || 
        B.size().first == 0 || B.size().second == 0) {
        throw std::invalid_argument("Cannot concatenate empty matrices");
    }

    // Get dimensions
    int rowsA = A.size().first, colsA = A.size().second;
    int rowsB = B.size().first, colsB = B.size().second;

    // Concatenate along rows (vertical stacking)
    if (dim == 0) {
        if (colsA != colsB) {
            throw std::invalid_argument(
                "Column count mismatch for row-wise concatenation: " + 
                std::to_string(colsA) + " vs " + std::to_string(colsB)
            );
        }

        Matrix result(rowsA + rowsB, colsA);
        for (int i = 0; i < rowsA; ++i) {
            for (int j = 0; j < colsA; ++j) {
                result[i][j] = A[i][j];
            }
        }
        for (int i = 0; i < rowsB; ++i) {
            for (int j = 0; j < colsB; ++j) {
                result[rowsA + i][j] = B[i][j];
            }
        }
        return result;
    }
    // Concatenate along columns (horizontal stacking)
    else if (dim == 1) {
        if (rowsA != rowsB) {
            throw std::invalid_argument(
                "Row count mismatch for column-wise concatenation: " + 
                std::to_string(rowsA) + " vs " + std::to_string(rowsB)
            );
        }

        Matrix result(rowsA, colsA + colsB);
        for (int i = 0; i < rowsA; ++i) {
            for (int j = 0; j < colsA; ++j) {
                result[i][j] = A[i][j];
            }
            for (int j = 0; j < colsB; ++j) {
                result[i][colsA + j] = B[i][j];
            }
        }
        return result;
    }
    else {
        throw std::invalid_argument(
            "Invalid dim value: " + std::to_string(dim) + 
            " (must be 0 for rows or 1 for columns)"
        );
    }
}

Matrix random_population_uniform_per_variable(int population_size, int num_variables,
                                              const std::vector<double>& lb_vec,
                                              const std::vector<double>& ub_vec,
                                              unsigned int seed, bool use_seed) {
    if (population_size <= 0 || num_variables <= 0)
        throw std::invalid_argument("bad dims");
    if ((int)lb_vec.size() != num_variables || (int)ub_vec.size() != num_variables)
        throw std::invalid_argument("lb_vec/ub_vec size mismatch");

    if (use_seed) rng.seed(seed);

    Matrix pop(population_size, num_variables);
    for (int j = 0; j < num_variables; ++j) {
        double lb = lb_vec[j];
        double ub = ub_vec[j];
        if (lb > ub) std::swap(lb, ub);
        std::uniform_real_distribution<double> dist(lb, ub);
        for (int i = 0; i < population_size; ++i) {
            pop[i][j] = dist(rng);
        }
    }
    return pop;
}




