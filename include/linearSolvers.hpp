#pragma once
#include "../include/matrix.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

Matrix<double> conjugateGradient(Matrix<double> A, Matrix<double> b);
