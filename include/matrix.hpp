#pragma once
#include <vector>
#include <algorithm>

template<typename T> class Matrix
{
    private:
        int row;
        int col;
        int vec_id;
        std::vector<std::vector<T>> mat;
    public:
        Matrix(T init_val, int r, int c) : row(r), col(c)
        {
            std::vector<T> row_vec(row, init_val);
            std::vector<std::vector<T>> matrix(col, row_vec);
            this->mat = matrix;
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

        T operator()(int row_id, int col_id)
        {
            return this->mat[row_id][col_id];
        };
};