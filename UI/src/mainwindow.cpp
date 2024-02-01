#include <MainWindow.hpp>

#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	mRenderer(vtkSmartPointer<vtkRenderer>::New()),
	mRenderWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()),
	mView(vtkSmartPointer<vtkContextView>::New())
{
    ui->setupUi(this);

	// Set up the rendering
	mRenderer = mView->GetRenderer();
	mRenderer->Render();
	mRenderWindow->AddRenderer(mRenderer);
	ui->openGLWidget->setRenderWindow(mRenderWindow);

	// Set the UI connections
	QObject::connect(ui->pushButton, &QPushButton::clicked,
		this, &MainWindow::render);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::addChart(vtkChartHistogram2D *chart)
{
	this->vtk_chart = chart;
}

void MainWindow::render()
{
	mView->GetScene()->AddItem(this->vtk_chart);
	mRenderWindow->Render();
}