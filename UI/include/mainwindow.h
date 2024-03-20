#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVTKInteractor.h>
#include <QDoubleValidator>
#include <QPointer>
#include <QWidget>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkInteractorStyle.h>
#include <vtkNew.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkNamedColors.h>
#include <vtkCamera.h>
#include "model.h"
#include "./ui_mainwindow.h"



#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
	Ui::MainWindow *ui;
	QVTKOpenGLNativeWidget* solutionWidget;
	vtkSmartPointer<vtkRenderer> solutionRenderer;
	vtkSmartPointer<vtkRenderWindow> solutionWindow;
	vtkSmartPointer<vtkRenderWindowInteractor> solutionInteractor;

	QPointer<QDoubleValidator> validator_top;
	QPointer<QDoubleValidator> validator_bottom;
	QPointer<QDoubleValidator> validator_right;
	QPointer<QDoubleValidator> validator_left;

	std::unique_ptr<Model> model;
	void setConnections();
	void setValidators();
	void setActions();

	void plotSolution();
	void plotResiduals();
	

public:
    explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();
private slots:

	void assembleModel();
	void solveModel();
	
	void onTopChanged(const QString &text);
    void onBottomChanged(const QString &text);
    void onRightChanged(const QString &text);
    void onLeftChanged(const QString &text);
};

#endif // MAINWINDOW_H
