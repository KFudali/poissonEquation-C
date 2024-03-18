#include <MainWindow.h>

#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	solutionWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()),
	residualWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New())
{
    ui->setupUi(this);
	ui->openGLWidget_solution->setRenderWindow(solutionWindow);
	ui->openGLWidget_residual->setRenderWindow(residualWindow);

	// ui->openGLWidget->setRenderWindow(mRenderWindow);
	// Set up the rendering
	// mRenderWindow->AddRenderer(mRenderer);

	// Set the UI connections
	// QObject::connect(ui->pushButton, &QPushButton::clicked,
	// 	this, &MainWindow::render);
};


void MainWindow::setConnections(){
	

};



MainWindow::~MainWindow() {
    delete ui;
};