#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include "../include/matrix.hpp"

int main(){

    // FEM method (a bit sketchy since its taken from an old project done in MATLAB :| //

    const double Ly = 1;
    const double Lx = 1;
    const int ny  = 4;
    const int nx  = 4;
    const int n_elements = (nx - 1) * (ny - 1);

    Matrix K_e(2./3., 4, 4);

    std::vector<double> element_stiffnes =  {2./3., -1./6., -1./3., -1./6.,
                                            -1./6., 2./3., -1./6., -1./3.,
                                            -1./3., -1./6., 2./3., -1./6.,
                                            -1./6., -1./3., -1./6., 2./3.};

    // for_each(element_stiffnes.begin(), element_stiffnes.end(), [](const auto& elem){std::cout<<elem;});

    for(int i = 0; i < 4; i++)
    {
         for(int j = 0; j < 4; j++)
        {
            K_e.set(i,j,element_stiffnes[(i*4)+j]);
        }
    };

    // K_e.printMatrix();

    // for_each(row.begin(), row.end(), [](const auto& elem){std::cout<<elem;});

    Matrix element_nodes_ids(0, n_elements, 4);
    int first_node;
    std::vector<int> ids_vector;

    for(int i = 0; i < n_elements; i++)
    {
        first_node = i + (int)floor((double)i/((double)(nx-1)));

        ids_vector = {first_node, first_node + 1,  first_node + nx + 1, first_node + nx};
        element_nodes_ids.setRow(i, ids_vector);
    }

    Matrix K_g(0., nx*nx, ny*ny);
    // assemble global matrix
    double val;
    // K_e.printMatrix();
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
    // K_g.printMatrix();
    // std::cout<<std::endl;

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
    // std::cout<<"SIZE = "<<(int)boudnary_ids.size();
    // for_each(boudnary_ids.begin(), boudnary_ids.end(), [](const auto& elem){std::cout<<elem<<std::endl;});

    std::vector<double> u(nx*ny, 0.);
    std::vector<double> rhs(nx*ny, 0.);

    for(int i = 0; i < nx; i++)
    {
        u[top_ids[i]] = -1.;
    }

    rhs = K_g*u;

    // for_each( rhs.begin(),  rhs.end(), [](const auto& elem){std::cout<<elem<<std::endl;});

    // K_g.printMatrix();
    // std::cout<<std::endl;
    // std::cout<<std::endl;

    // // deleting elements from global stifness matrix - needed for dirichlet BC
    for(int i = (int)boudnary_ids.size() - 1; i >= 0 ; i--)
    {
        std::cout<<boudnary_ids[i]<<std::endl;
        K_g.removeRow(boudnary_ids[i]);
        K_g.removeCol(boudnary_ids[i]);
        rhs.erase(rhs.begin() + boudnary_ids[i]);
    };

    K_g.printMatrix();

    for_each( rhs.begin(),  rhs.end(), [](const auto& elem){std::cout<<elem<<std::endl;});

} 