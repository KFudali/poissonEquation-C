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
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> mRenderWindow;
	// std::unique_ptr<Model> model;


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
	void render();
};

#endif // MAINWINDOW_H
