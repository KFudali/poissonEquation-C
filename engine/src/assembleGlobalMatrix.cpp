#include "assembleGlobalMatrix.h"
#iniclue "matrix.h"

void calculateRHS(Matrix<double> *rhs, Matrix<double> *K_g,
                    double top_value, double bottom_value,
                    double right_value, double left_value)
{
    int nx =  sqrt(K_g->row);
    int ny =  sqrt(K_g->col);

    // include boundary conditions
    std::vector<int> bottom_ids(nx, 0);
    std::vector<int> top_ids(nx, 0);
    std::vector<int> left_ids(ny, 0);
    std::vector<int> right_ids(ny, 0);
    std::vector<int> boundary_ids;
    std::vector<int> interior_ids;

    for(int i = 0; i < nx; i++)
    {
        bottom_ids[i] = i;
        top_ids[i] = (nx * (ny - 1)) + i;
        left_ids[i] = i*nx;
        right_ids[i] = (i+1)*nx - 1;
        boundary_ids.push_back(bottom_ids[i]);
        boundary_ids.push_back(top_ids[i]);
        boundary_ids.push_back(left_ids[i]);
        boundary_ids.push_back(right_ids[i]);
    };


    std::sort(boundary_ids.begin(), boundary_ids.end());
    boundary_ids.erase(std::unique(boundary_ids.begin(), boundary_ids.end()), boundary_ids.end());

    for(int i = 0; i <nx*ny; i++)
    {
        if(std::find(boundary_ids.begin(), boundary_ids.end(), i) == boundary_ids.end())
        {
            interior_ids.push_back(i);
        }
    };

    std::vector<double> u(nx*ny, 0.);
    std::vector<double> rhs_vec(nx*ny, 0.);

    for(int i = 0; i < nx; i++)
    {
        u[top_ids[i]] = -1.;
    }

    rhs_vec = K_g*u;

    // deleting elements from global stifness matrix - needed for dirichlet BC
    for(int i = (int)boundary_ids.size() - 1; i >= 0 ; i--)
    {
        K_g.removeRow(boundary_ids[i]);
        K_g.removeCol(boundary_ids[i]);
        rhs.erase(rhs.begin() + bounda  ry_ids[i]);
    };
}