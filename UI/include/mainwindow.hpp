#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <QVTKInteractor.h>
#include <vtkInteractorStyle.h>
#include <vtkAxis.h>
#include <vtkBrush.h>
#include <vtkChartHistogram2D.h>
#include <vtkColorLegend.h>
#include <vtkColorTransferFunction.h>
#include <vtkContextView.h>
#include <vtkImageData.h>
#include <vtkMath.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTextProperty.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDataSetMapper.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
	Ui::MainWindow *ui;

	vtkSmartPointer<vtkRenderer> mRenderer;
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> mRenderWindow;
	vtkSmartPointer<vtkContextView> mView;
	vtkSmartPointer<vtkChartHistogram2D> vtk_chart;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
	void addChart(vtkChartHistogram2D *chart);

public slots:
	void render();
};

#endif // MAINWINDOW_H
