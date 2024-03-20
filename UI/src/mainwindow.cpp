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

	this->setValidators();
	this->setConnections();
	this->setActions();

	this->model = std::make_unique<Model>(20,20);

	this->solutionRenderer = vtkSmartPointer<vtkRenderer>::New();
	this->solutionWindow->AddRenderer(solutionRenderer);
	this->solutionRenderer->SetRenderWindow(solutionWindow);



	vtkNew<vtkNamedColors> colors;
	solutionRenderer->SetBackground(colors->GetColor3d("SlateGray").GetData());

	// vtkNew<vtkRenderWindowInteractor> interactor;
	// interactor->SetRenderWindow(solutionWindow);

};

void MainWindow::solveModel(){
	this->model->solveModel();
    vtkSmartPointer<vtkActor> solutionActor = this->model->getSolutionActor();
	this->solutionRenderer->AddActor2D(std::move(solutionActor));
	this->solutionRenderer->Render();
}

void Model::updateSolutionActor(){

    this->solutionGrid = vtkSmartPointer<vtkStructuredGrid>::New();

    vtkNew<vtkDoubleArray> pointValues;
    vtkNew<vtkPoints> points;

    pointValues->SetNumberOfComponents(1);
    pointValues->SetNumberOfTuples(nx*ny);

    double x = 0;
    double y = 0;
    double dx = 1./(nx-1);
    double dy = 1./(ny-1);
    for(int i = 0; i < this->nx; ++i){
        y = 0;
        for(int j = 0; j < this->ny; ++j){
            points->InsertNextPoint(x, y, 0.);
            pointValues->InsertNextValue(this->u_full->mat[i][j]);
            std::cout<< x << " " << y << std::endl;
            y += dy;
        }
        x += dx;
    }

    this->solutionGrid->SetPoints(points);
    this->solutionGrid->GetPointData()->SetScalars(pointValues);

    vtkSmartPointer<vtkDataSetMapper> mapper =
        vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputData(this->solutionGrid);

    this->solutionActor =
        vtkSmartPointer<vtkActor>::New();
    this->solutionActor->SetMapper(mapper);
};

vtkSmartPointer<vtkActor> Model::getSolutionActor(){
    return this->solutionActor;
};

void MainWindow::assembleModel(){
	this->model->assembleModel();
	this->ui->pushButton_solve->setEnabled(true);
}

void MainWindow::setActions(){
	this->ui->pushButton_assemble->setEnabled(true);
	this->ui->pushButton_solve->setEnabled(false);
}

void MainWindow::setValidators(){
	QPointer<QDoubleValidator> validator_top = new QDoubleValidator(-999999.0, 999999.0, 2, this);
	QPointer<QDoubleValidator> validator_bottom = new QDoubleValidator(-999999.0, 999999.0, 2, this);
	QPointer<QDoubleValidator> validator_right = new QDoubleValidator(-999999.0, 999999.0, 2, this);
	QPointer<QDoubleValidator> validator_left = new QDoubleValidator(-999999.0, 999999.0, 2, this);
	ui->lineEdit_top->setValidator(validator_top);
	ui->lineEdit_bottom->setValidator(validator_bottom);
	ui->lineEdit_right->setValidator(validator_right);
	ui->lineEdit_left->setValidator(validator_left);
	ui->lineEdit_top->setText("0.");
	ui->lineEdit_bottom->setText("0.");
	ui->lineEdit_right->setText("0.");
	ui->lineEdit_left->setText("0.");
};

void MainWindow::setConnections(){
	connect(ui->lineEdit_top, &QLineEdit::textChanged, this, &MainWindow::onTopChanged);
	connect(ui->lineEdit_bottom, &QLineEdit::textChanged, this, &MainWindow::onBottomChanged);
	connect(ui->lineEdit_right, &QLineEdit::textChanged, this, &MainWindow::onRightChanged);
	connect(ui->lineEdit_left, &QLineEdit::textChanged, this, &MainWindow::onLeftChanged);

	connect(ui->pushButton_assemble, &QPushButton::clicked, this, &MainWindow::assembleModel);
	connect(ui->pushButton_solve, &QPushButton::clicked, this, &MainWindow::solveModel);
};

void MainWindow::onTopChanged(const QString &text) {
    double value = text.toDouble();
    this->model->changeTopBC(value);
}
void MainWindow::onBottomChanged(const QString &text) {
    double value = text.toDouble();
   	this->model->changeBottomBC(value);
}
void MainWindow::onRightChanged(const QString &text) {
    double value = text.toDouble();
  	this->model->changeRightBC(value);
}
void MainWindow::onLeftChanged(const QString &text) {
    double value = text.toDouble();
	this->model->changeLeftBC(value);
}


MainWindow::~MainWindow() {
    delete ui;
};