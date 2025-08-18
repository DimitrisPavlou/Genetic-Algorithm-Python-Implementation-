#pragma once
#include <bits/stdc++.h>


class Matrix { 

    public: 
        Matrix(int rows, int cols); 
        Matrix(std::initializer_list<std::initializer_list<double>> init);
        ~Matrix() = default;
        // Copy constructor
        Matrix(const Matrix& other) = default;
        // Copy assignment
        Matrix& operator=(const Matrix& other) = default;
        // Move constructor
        Matrix(Matrix&& other) noexcept = default;
        // Move assignment
        Matrix& operator=(Matrix&& other) noexcept = default;
        
        double get(int i, int j); 
        void set(int i, int j, double val); 
        std::pair<int, int> size(); 
        Matrix transpose(); 
        Matrix operator+(const Matrix& A) const; 
        Matrix operator-(const Matrix& A) const; 
        Matrix operator/(const Matrix& A) const; 
        Matrix operator*(const Matrix& A) const; 
        Matrix operator*(const double& a) const; 
        // Access operators
        std::vector<double>& operator[](int i) { return array[i]; }
        const std::vector<double>& operator[](int i) const { return array[i]; }

        template <typename Func>
        Matrix applyFunction(Func func) const {
            Matrix result(array.size(), array[0].size());
            for (size_t i = 0; i < array.size(); ++i) {
                for (size_t j = 0; j < array[0].size(); ++j) {
                    result[i][j] = func(array[i][j]);
                }
            }
            return result;
        }

        // Overload for direct use with std:: functions (alternative)
        Matrix applyFunction(double (*func)(double)) const {
            return applyFunction([func](double x) { return func(x); });
        }

        Matrix get_row(int i); 
        Matrix get_column(int j);
        Matrix slice(int row_start, int row_end, int column_start, int column_end);

    private: 
        std::vector<std::vector<double>> array;  
        int rows, cols; 
}; 


void print_matrix(Matrix& A);
Matrix matmul(Matrix& A, Matrix& B);
Matrix random_init(int rows, int cols); 
Matrix ones(int rows, int cols); 
Matrix eye(int n); 
Matrix concatenate(Matrix& A, Matrix& B, int dim = 0); 

Matrix random_population_uniform_per_variable(int population_size, int num_variables,
                                              const std::vector<double>& lb_vec,
                                              const std::vector<double>& ub_vec,
                                              unsigned int seed = 0, bool use_seed = false); 