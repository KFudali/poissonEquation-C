#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

#include "matrix.h"
#include "linearSolvers.h"
#include "plotContour.h"
#include "mainwindow.h"
#include "model.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[]){
    
    // FEM method (a bit sketchy since its taken from a project done in MATLAB :| )//
    std::cout<<"Model creation!";
    Model model(4,4);
    // std::cout<<"Model created!";
    model.imposeBCs(1, 0, 0, 0);
    model.assembleGlobalMatrices();
    model.calculateSolution();
    // model.calculate();

	// QApplication application(argc, argv);
    // MainWindow window;
    // window.showNormal();
	// // window.showMaximized();
	// return application.exec();
} 