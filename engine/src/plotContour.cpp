#include "../include/plotContour.hpp"


// Reference https://examples.vtk.org/site/Cxx/Plotting/Histogram2D/
void plotContour(Matrix<double> A, int nx, int ny)
{
// Define colors.
  vtkNew<vtkNamedColors> colors;
  vtkColor3d backgroundColor = colors->GetColor3d("White");
  vtkColor3d titleColor = colors->GetColor3d("Black");
  vtkColor3d axisTitleColor = colors->GetColor3d("Black");
  vtkColor3d axisLabelColor = colors->GetColor3d("Black");
  vtkColor4ub legendBackgroundColor = colors->GetColor4ub("White");

  // Set up a 2D scene, add an XY chart to it.
  int size = nx*ny;
  vtkNew<vtkContextView> view;
  view->GetRenderWindow()->SetSize(512, 512);
  view->GetRenderWindow()->SetWindowName("PoissonEquationSolution");

  view->GetRenderer()->SetBackground(backgroundColor.GetData());

  // Define a chart
  vtkNew<vtkChartHistogram2D> chart;

  // Chart Title.
  chart->SetTitle("Poisson Equation Solution");
  chart->GetTitleProperties()->SetFontSize(36);
  chart->GetTitleProperties()->SetColor(titleColor.GetData());

  // Chart Axes.
  chart->GetAxis(0)->GetTitleProperties()->SetFontSize(24);
  chart->GetAxis(0)->GetTitleProperties()->SetColor(axisTitleColor.GetData());
  chart->GetAxis(0)->GetLabelProperties()->SetColor(axisLabelColor.GetData());
  chart->GetAxis(0)->GetLabelProperties()->SetFontSize(18);

  chart->GetAxis(1)->GetTitleProperties()->SetFontSize(24);
  chart->GetAxis(1)->GetTitleProperties()->SetColor(
      axisLabelColor.GetData());
  chart->GetAxis(1)->GetLabelProperties()->SetColor(
      axisLabelColor.GetData());
  chart->GetAxis(1)->GetLabelProperties()->SetFontSize(18);

  // Chart Legend.
  dynamic_cast<vtkColorLegend*>(chart->GetLegend())->DrawBorderOff();
  chart->GetLegend()->GetBrush()->SetColor(legendBackgroundColor);

  // Add the chart to the view.
  view->GetScene()->AddItem(chart);

  vtkNew<vtkImageData> data;
  data->SetExtent(0, nx-1, 0, ny-1, 0, 0);
  data->AllocateScalars(VTK_DOUBLE, 1);

  data->SetOrigin(0, 0, 0.0);
  data->SetSpacing(1./nx, 1./ny, 1.0);

    // std::cout<<size;

  double* dPtr = static_cast<double*>(data->GetScalarPointer(0, 0, 0));
  for (int i = 0; i < nx; i++)
  {
    for (int j = 0; j < ny; j++)
    {
        std::cout<< -A.mat[i][j]<<std::endl;
        dPtr[i * ny + j] = -A.mat[i][j];
    }
  }
  chart->SetInputData(data);

  vtkNew<vtkColorTransferFunction> transferFunction;
  transferFunction->AddRGBSegment(0, 0.2, 1., 0.2, 1.0, 1., 0.2, 0.2);
  transferFunction->Build();
  chart->SetTransferFunction(transferFunction);

  view->GetRenderWindow()->Render();
  view->GetInteractor()->Start();

};
