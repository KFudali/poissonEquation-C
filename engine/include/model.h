#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <array>

#include "matrix.h"
#include "linearSolvers.h"

class Model
{
    private:
        int nx;
        int ny;
        int n_elements;

        std::unique_ptr<Matrix<double>> K_e;
        std::unique_ptr<Matrix<double>> K_g;
        std::unique_ptr<Matrix<double>> rhs;
        std::unique_ptr<Matrix<double>> u_full;

        std::vector<int> interior_ids;
        std::vector<int> boundary_ids;

        std::vector<int> bottom_ids;
        std::vector<int> top_ids;
        std::vector<int> left_ids;
        std::vector<int> right_ids;
        double top_value;
        double bottom_value;
        double right_value;
        double left_value;


        void assembleKg();
        void updateBoundaryIds();
        void assembleRhs();
        
    public:
        Model(int nx, int ny);
        virtual ~Model();

        void assembleModel();
        void calculateSolution();

        void changeTopBC(double value);
        void changeBottomBC(double value);
        void changeLeftBC(double value);
        void changeRightBC(double value);
};
