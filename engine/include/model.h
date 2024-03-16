#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

#include "matrix.h"
#include "linearSolvers.h"

class Model
{
    private:
        int nx;
        int ny;
        Matrix<double> K_e;
        Matrix<double> K_g;
        Matrix<double> rhs;
        Matrix<double> u0;
        
        bool BCs_imposed = false;
        bool model_assembled = false;
        double top_value;
        double bottom_value;
        double right_value;
        double left_value;
        
    public:
        Model(int nx, int ny);
        virtual ~Model(){};

        // void imposeBCs(double top_value, double bottom_value,
        //                double right_value, double left_value);

        // void assemble();
        // void calculate();
};
