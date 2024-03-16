#include <MainWindow.h>

#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	mRenderWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New())
{
    ui->setupUi(this);

	// Set up the rendering
	// mRenderer = mView->GetRenderer();
	// mRenderer->Render();
	// mRenderWindow->AddRenderer(mRenderer);
	// ui->openGLWidget->setRenderWindow(mRenderWindow);

	// Set the UI connections
	// QObject::connect(ui->pushButton, &QPushButton::clicked,
	// 	this, &MainWindow::render);
}

MainWindow::~MainWindow() {
    delete ui;
}