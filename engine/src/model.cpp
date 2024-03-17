#include "model.h"
// #include "assembleGlobalMatrix.h"

Model::Model(int _nx, int _ny) : nx(_nx), ny(_ny){

    this->n_elements = (nx - 1) * (ny - 1);

    this->K_g = std::make_unique<Matrix<double>>(0., nx*nx, ny*ny);
    this->rhs = std::make_unique<Matrix<double>>(0., 1, nx*ny);
    this->u_solved = std::make_unique<Matrix<double>>(0., nx, ny);
    this->u_full = std::make_unique<Matrix<double>>(0., nx, ny);

    std::vector<std::vector<double>> K_e_vec = {
        {2./3., -1./6., -1./3., -1./6.},
        {-1./6., 2./3., -1./6., -1./3.},
        {-1./3., -1./6., 2./3., -1./6.},
        {-1./6., -1./3., -1./6., 2./3.}
    };
    this->K_e = std::make_unique<Matrix<double>>(K_e_vec);
    updateBoundaryIds();
}

Model::~Model(){}

void Model::imposeBCs(double top_value, double bottom_value,
                       double right_value, double left_value)
                       {
                            this->top_value = top_value;
                            this->bottom_value = bottom_value;
                            this->right_value = right_value;
                            this->left_value = left_value;
                       };

void Model::assembleKg(){

    Matrix<int> element_nodes_ids(0, n_elements, 4);
    int first_node;
    std::vector<int> ids_vector;

    for(int i = 0; i < n_elements; i++)
    {
        first_node = i + (int)floor((double)i/((double)(nx-1)));
        ids_vector = {first_node, first_node + 1,  first_node + nx + 1, first_node + nx};
        element_nodes_ids.setRow(i, ids_vector);
    }

    double val;
    for(int i = 0; i < n_elements; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                val = this->K_g->mat[element_nodes_ids(i,k)][element_nodes_ids(i,j)];
                this->K_g->set(element_nodes_ids(i,k),element_nodes_ids(i,j), val + this->K_e->mat[j][k]);
            }
        }
    }

}

void Model::assembleGlobalMatrices()
{
    assembleKg();
}

void Model::updateBoundaryIds(){
    bottom_ids.reserve(nx);
    top_ids.reserve(nx);
    left_ids.reserve(ny);
    right_ids.reserve(ny);
    boundary_ids.reserve(nx + ny + nx + ny);
    interior_ids.reserve(nx*ny);

    for (int i = 0; i < nx; i++) {
        bottom_ids[i] = i;
        top_ids[i] = (nx * (ny - 1)) + i;
    }

    for (int i = 0; i < ny; i++) {
        left_ids[i] = i * nx;
        right_ids[i] = (i + 1) * nx - 1;
    }

    boundary_ids.insert(boundary_ids.end(), bottom_ids.begin(), bottom_ids.end());
    boundary_ids.insert(boundary_ids.end(), top_ids.begin(), top_ids.end());
    boundary_ids.insert(boundary_ids.end(), left_ids.begin(), left_ids.end());
    boundary_ids.insert(boundary_ids.end(), right_ids.begin(), right_ids.end());

    std::sort(boundary_ids.begin(), boundary_ids.end());
    boundary_ids.erase(std::unique(boundary_ids.begin(), boundary_ids.end()), boundary_ids.end());
   
    std::iota(interior_ids.begin(), interior_ids.end(), 1);
    interior_ids.erase(std::remove_if(interior_ids.begin(), interior_ids.end(),
[&](int id){return std::binary_search(boundary_ids.begin(), boundary_ids.end(), id);}),
     interior_ids.end());
}

void Model::calculateRhs(){

    std::vector<double> u(nx*ny, 0.);
    std::vector<double> rhs_vec(nx*ny, 0.);

    for(int i = 0; i < nx; i++){
        u[top_ids[i]] = top_value;
        u[bottom_ids[i]] = bottom_value;
    }
    for(int i = 0; i < ny; i++){
        u[right_ids[i]] = right_value;
        u[left_ids[i]] = right_value;
    }

    rhs_vec = *this->K_g*u;

    for (auto it = boundary_ids.rbegin(); it != boundary_ids.rend(); ++it) {
        this->K_g->removeRow(*it);
        this->K_g->removeCol(*it);
        rhs_vec.erase(rhs_vec.begin() + *it);
    }
    this->rhs = std::make_unique<Matrix<double>>(rhs_vec);
};


void Model::calculateSolution(){
    this->u_solved = conjugateGradient(*K_g, *rhs);
    
    int id;
    // fill the full solution with solved domain
    for(int i = 0; i < (int)interior_ids.size(); i++)
    {
        id = interior_ids[i];
        u[id] = u_solved(i,0);
    }

    Matrix u_domain(0., nx,ny);
    //Reshape matrix
    for(int i = 0; i<nx; i++)
    {
        for(int j = 0; j<nx; j++)
        {       
            u_domain.set(i,j, u[i*ny + j]);
        }
    }
    u_domain.printMatrix();
}
