#pragma once
#include "matrix.h"
#include <vector>
#include <iostream>
#include <algorithm>
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

void plotContour(Matrix<double> A, int nx, int ny,
 vtkChartHistogram2D *chart);
