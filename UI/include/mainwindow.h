#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVTKInteractor.h>

#include <vtkInteractorStyle.h>
#include <vtkNew.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkSmartPointer.h>

#include "model.h"
#include "./ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
	Ui::MainWindow *ui;
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> solutionWindow;
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> residualWindow;
	std::unique_ptr<Model> model;

	void setConnections();



public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
	void createNewModel();
	void assembleModel();
	void calculateModel();
	void plotSolution();
	void plotResiduals();
};

#endif // MAINWINDOW_H
