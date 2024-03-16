#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

template<typename T> class Matrix
{
    private:

    public:
        int row;
        int col;
        std::vector<std::vector<T>> mat;
        Matrix(){};

        Matrix(T init_val, int r, int c) :  row(r), col(c)
        {
            std::vector<T> col_vec(col, init_val);
            std::vector<std::vector<T>> matrix(row, col_vec);
            this->mat = matrix;
        };
        Matrix(std::vector<std::vector<T>> init_matrix) : mat(init_matrix)
        {
            row = (int)mat.size();
            col = (int)mat[0].size();
        };
        Matrix(std::vector<T> init_vec)
        {
            row = 1;
            col = (int)init_vec.size();
            std::vector<std::vector<T>> matrix(1, init_vec);
            this->mat = matrix;
            mat[0] = init_vec;
        };

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
        Matrix transpose()
        {
            Matrix transposed_mat(this->mat[0][0], this->col, this->row);

            for(int i = 0; i < this->row; i++)
            {
                for(int j = 0; j < this->col; j++)
                {
                    transposed_mat.mat[j][i] = this->mat[i][j];
                }
            }
            return transposed_mat;
        }
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
                  result[i] = result[i] + this->mat[j][i]*vec[j];
                }
            }
            return result;
        }

        Matrix operator*(const Matrix matrix)
        {
            Matrix result(0., this->row, matrix.col);
            for(int i = 0; i < this->row; i++)
            {
                for(int j = 0; j < matrix.col; j++)
                {
                    for(int k = 0; k < this->col; k++)
                    {
                        result.mat[i][j] += this->mat[i][k]*matrix.mat[k][j];
                    }
                }
            }
            return result;
        }
        
        Matrix operator-(const double T)
        {
            Matrix result(this->mat);

            for(int i = 0; i < this->row; i++)
            {
                for(int j = 0; j < this->col; j++)
                {
                    result.set(i,j,this->mat[i][j] - T);
                }
            }
            return result;
        }
        Matrix operator-(const Matrix matrix)
        {
            Matrix result(this->mat);

            for(int i = 0; i < this->row; i++)
            {
                for(int j = 0; j < this->col; j++)
                {
                    result.mat[i][j] = this->mat[i][j] - matrix.mat[i][j];
                }
            }
            result.row = this->row;
            result.col = this->col;
            return result;
        }
        Matrix operator+(const double a)
        {
            Matrix result(this->mat);

            for(int i = 0; i < this->row; i++)
            {
                for(int j = 0; j < this->col; j++)
                {
                    result.set(i,j,this->mat[i][j] + a);
                }
            }
            result.row = this->row;
            result.col = this->col;
            return result;
        }
        Matrix operator*(const double a)
        {
            Matrix result(this->mat);

            for(int i = 0; i < this->row; i++)
            {
                for(int j = 0; j < this->col; j++)
                {
                    result.set(i,j,this->mat[i][j] * a);
                }
            }
            result.row = this->row;
            result.col = this->col;
            return result;
        }
        Matrix operator+(const Matrix matrix)
        {
            Matrix result(this->mat);

            for(int i = 0; i < this->row; i++)
            {
                for(int j = 0; j < this->col; j++)
                {
                    result.set(i,j,this->mat[i][j] + matrix.mat[i][j]);
                }
            }
            result.row = this->row;
            result.col = this->col;
            return result;
        }
        void removeRow(int row_id)
        {
            this->mat.erase(mat.begin() + row_id);
            this->row = this->row-1;
        }
        void removeCol(int col_id)
        {
            for_each(this->mat.begin(), this->mat.end(), [col_id](auto& vec)
            {
                vec.erase(vec.begin() + col_id);
            });
            this->col = this->col-1;
        }


};