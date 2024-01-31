#include "linearSolvers.hpp"

Matrix<double> conjugateGradient(Matrix<double> A, Matrix<double> b)
{
    Matrix x(0., b.col, 1);
    
    double alfa;
    double beta;
    Matrix<double> r;
    Matrix<double> r0;
    Matrix<double> p;
    Matrix<double> rt;
    Matrix<double> r0t;
    Matrix<double> pt; 


    Matrix<double> up;
    Matrix<double> down;

    Matrix<double> tmp;

    Matrix bt = b.transpose();

    r = (A*x);
    r = r - bt;

    p = r;
    double norm_r = 1.;
    int iter = 1;

    for(int i = 0; i<101; i++)
    {
        rt = r.transpose();
        pt = p.transpose();
        
        up = rt * r;
        down = pt*A;
        down = down*p;
        alfa = up(0,0) / down(0,0);

        tmp = p*alfa;
        x = x +tmp;

        tmp = A*p;
        tmp = tmp*alfa;
        r0 = r;
        r = r - tmp;
        norm_r = 0.;
        for(int i = 0; i < r.row; i++)
        {
            norm_r = norm_r + r(i,0)*r(i,0);
        }
        norm_r = sqrt(norm_r);
        if (norm_r < 1e-6)
        {
            std::cout<<"CG converged after iter = "<< iter << " with norm r = "<< norm_r << std::endl;
            break;
        }
        rt = r.transpose();
        up = rt*r;

        r0t = r0.transpose();
        down = r0t*r0;

        beta = up(0,0) / down(0,0);

        tmp = p*beta;

        p = r + tmp;
        if (iter > 100)
        {
            std::cout<<"CG did not converge after 100 iters, norm r = "<< norm_r << std::endl;
            break;
        }
        iter++;
    }


    // r.printMatrix();
    // Matrix rt = r.transopose();
    // r.printMatrix();
    // rt.printMatrix();
    // r = r - b;

    return x;
}