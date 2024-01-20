#pragma once
#include <vector>
#include <algorithm>

template<typename T> class Matrix
{
    private:
        int row;
        int col;
        int vec_id;

    public:

        std::vector<std::vector<T>> mat;
        Matrix(T init_val, int c, int r) :  col(c), row(r)
        {
            std::vector<T> row_vec(row, init_val);
            std::vector<std::vector<T>> matrix(col, row_vec);
            this->mat = matrix;
        };
        Matrix(std::vector<std::vector<T>> init_matrix) : mat(init_matrix)
        {};

        ~Matrix() {};

        void printMatrix()
        {
            for_each(mat.begin(),
                     mat.end(),
                     [](const auto& column)
                    {                                
                        for_each(column.begin(),
                                 column.end(),
                                [](const auto& elem)
                                {
                                    std::cout << elem << " ";
                                });
                        std::cout<<std::endl;
                    });
        };
        const T operator()(int row_id, int col_id)
        {
            return this->mat[row_id][col_id];
        };
        Matrix operator+(const Matrix mat_2)
        {
            if(this->row != mat_2.col &&  this->col != mat_2.col)
            {
                std::cout<<"Matrices have different dimensions and cannot be added!" << std::endl;
                return *this;
            }
            else
            {
                for(int i = 0; i < this->row; i++)
                {
                    for(int j = 0; j < this->col; j++)
                    {
                        this->mat[i][j] += mat_2.mat[i][j];
                    }
                }
                return *this;
            }
        };
        void set(int row_id, int col_id, T value)
        {
            this->mat[row_id][col_id] = value;
        }
        void setColumn(int col_num, const std::vector<T> column)
        {
            for(int i = 0; i < this->row; i++)
            {
                this->mat[i][col_num] = column[i];
            }
        };

        void setRow(int row_num, const std::vector<T> row)
        {
           this->mat[row_num] = row;
        };

        std::vector<T> getColumn(int col_num)
        {
            std::vector<T> column(this->row);
            for(int i = 0; i < this->row; i++)
            {
                column[i] = this->mat[i][col_num];
            }
            return column;
        }
        std::vector<T> getRow(int row_num)
        {
            return this->mat[row_num];
        };
        std::vector<T> operator*(const std::vector<T> vec)
        {
            std::vector<T> result(this->row);
            for(int i = 0; i < this->row; i++)
            {
                for(int j = 0; j < this->col; j++)
                {
                  result[i] += this->mat[i][j]*vec[i];
                }
            }
            return result;
        }
        Matrix operator*(const Matrix mat)
        {
            return *this;
        }
        void removeRow(int row_id)
        {
            this->mat.erase(mat.begin() + row_id);
        }
        void removeCol(int col_id)
        {
            for_each(this->mat.begin(), this->mat.end(), [col_id](auto& vec)
            {
                vec.erase(vec.begin() + col_id);
            });
        }

};