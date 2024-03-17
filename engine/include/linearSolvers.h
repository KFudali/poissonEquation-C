#pragma once
#include "matrix.h"

#include <vector>
#include <iostream>
#include <algorithm>

Matrix<double> conjugateGradient(Matrix<double>& A,Matrix<double>& b);
