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
        std::unique_ptr<Matrix<double>> u_solved;       
        
        std::vector<double> interior_ids;
        std::vector<double> boundary_ids;

        std::vector<double> bottom_ids;
        std::vector<double> top_ids;
        std::vector<double> left_ids;
        std::vector<double> right_ids;
        double top_value;
        double bottom_value;
        double right_value;
        double left_value;
        
    public:
        Model(int nx, int ny);
        virtual ~Model();

    void imposeBCs(double top_value, double bottom_value,
                    double right_value, double left_value);

    void assembleGlobalMatrices();
    void assembleKg();
    void updateBoundaryIds();
    void calculateRhs();
    void calculateSolution();
};
