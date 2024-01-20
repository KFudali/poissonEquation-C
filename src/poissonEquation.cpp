#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include "../include/matrix.hpp"

int main(){

    // FEM method (a bit sketchy since its taken from a roject done in MATLAB :| //

    const double Ly = 1;
    const double Lx = 1;
    const int ny  = 4;
    const int nx  = 4;
    const int n_elements = (nx - 1) * (ny - 1);

    // create Element stiffness matrix and the element node map
    Matrix K_e(2./3., 4, 4);
    std::vector<double> element_stiffnes =  {2./3., -1./6., -1./3., -1./6.,
                                            -1./6., 2./3., -1./6., -1./3.,
                                            -1./3., -1./6., 2./3., -1./6.,
                                            -1./6., -1./3., -1./6., 2./3.};

    for(int i = 0; i < 4; i++)
    {
         for(int j = 0; j < 4; j++)
        {
            K_e.set(i,j,element_stiffnes[(i*4)+j]);
        }
    };

    Matrix element_nodes_ids(0, n_elements, 4);
    int first_node;
    std::vector<int> ids_vector;

    for(int i = 0; i < n_elements; i++)
    {
        first_node = i + (int)floor((double)i/((double)(nx-1)));

        ids_vector = {first_node, first_node + 1,  first_node + nx + 1, first_node + nx};
        element_nodes_ids.setRow(i, ids_vector);
    }

    
    // assemble global matrix
    Matrix K_g(0., nx*nx, ny*ny);
    double val;
    std::cout<<std::endl;
    for(int i = 0; i < n_elements; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                val = K_g(element_nodes_ids(i,k),element_nodes_ids(i,j));
                K_g.set(element_nodes_ids(i,k),element_nodes_ids(i,j), val + K_e(j,k));
            }
        }
    }


    // include boundary conditions
    std::vector<int> bottom_ids(nx, 0);
    std::vector<int> top_ids(nx, 0);
    std::vector<int> left_ids(ny, 0);
    std::vector<int> right_ids(ny, 0);
    std::vector<int> boudnary_ids;

    for(int i = 0; i < nx; i++)
    {
        bottom_ids[i] = i;
        top_ids[i] = (nx * (ny - 1)) + i;
        left_ids[i] = i*nx;
        right_ids[i] = (i+1)*nx - 1;
        boudnary_ids.push_back(bottom_ids[i]);
        boudnary_ids.push_back(top_ids[i]);
        boudnary_ids.push_back(left_ids[i]);
        boudnary_ids.push_back(right_ids[i]);
    };

    std::sort(boudnary_ids.begin(), boudnary_ids.end());
    boudnary_ids.erase(std::unique(boudnary_ids.begin(), boudnary_ids.end()), boudnary_ids.end());

    std::vector<double> u(nx*ny, 0.);
    std::vector<double> rhs(nx*ny, 0.);

    for(int i = 0; i < nx; i++)
    {
        u[top_ids[i]] = -1.;
    }

    rhs = K_g*u;

    // deleting elements from global stifness matrix - needed for dirichlet BC
    for(int i = (int)boudnary_ids.size() - 1; i >= 0 ; i--)
    {
        std::cout<<boudnary_ids[i]<<std::endl;
        K_g.removeRow(boudnary_ids[i]);
        K_g.removeCol(boudnary_ids[i]);
        rhs.erase(rhs.begin() + boudnary_ids[i]);
    };

    K_g.printMatrix();
    for_each( rhs.begin(),  rhs.end(), [](const auto& elem){std::cout<<elem<<std::endl;});

    // Solution of the u = Kg\rhs; Or K_g * u = rhs (Ax = b) system to be implemented



    // Visualize the results (now that's gonna be hard:/ )
} 