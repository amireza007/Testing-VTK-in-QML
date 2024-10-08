#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickVTKItem.h>
#include <QQuickVTKRenderWindow.h>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickVTKRenderItem.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkConeSource.h>

#include <vtkCamera.h>
#include <vtkChartXYZ.h>
#include <vtkContext3D.h>
#include <vtkContextScene.h>
#include <vtkContextView.h>
#include <vtkFloatArray.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPen.h>
#include <vtkPlotLine3D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTable.h>
#include <vtkVersion.h>

#if VTK_VERSION_NUMBER >= 90220220630ULL
#define VTK_HAS_SETCOLORF 1
#endif

// // Plot the solution to the Lorenz attractor.
// // http://en.wikipedia.org/wiki/Lorenz_system
// namespace {
// void lorenz(const float* varX, float* varXDerivative)
// {
//     const float sigma = 10.f;
//     const float rho = 28.f;
//     const float beta = 2.66666666666f;

//     varXDerivative[0] = sigma * (varX[1] - varX[0]);
//     varXDerivative[1] = varX[0] * (rho - varX[2]) - varX[1];
//     varXDerivative[2] = varX[0] * varX[1] - beta * varX[2];
// }
// } // namespace

// //----------------------------------------------------------------------------
// int main(int, char*[])
// {
//     vtkNew<vtkNamedColors> colors;

//     // Create the data.
//     vtkNew<vtkTable> varXSolution;

//     vtkNew<vtkFloatArray> arrX0;
//     arrX0->SetName("X");
//     varXSolution->AddColumn(arrX0);

//     vtkNew<vtkFloatArray> arrX1;
//     arrX1->SetName("Y");
//     varXSolution->AddColumn(arrX1);

//     vtkNew<vtkFloatArray> arrX2;
//     arrX2->SetName("Z");
//     varXSolution->AddColumn(arrX2);

//     const unsigned int numberOfTimePoints = 1000;
//     varXSolution->SetNumberOfRows(numberOfTimePoints);
//     float varX[3];
//     varX[0] = 0.0f;
//     varX[1] = 1.0f;
//     varX[2] = 1.05f;

//     float varXDerivative[3];
//     const float deltaT = 0.01f;
//     for (unsigned int ii = 0; ii < numberOfTimePoints; ++ii)
//     {
//         varXSolution->SetValue(ii, 0, varX[0]);
//         varXSolution->SetValue(ii, 1, varX[1]);
//         varXSolution->SetValue(ii, 2, varX[2]);
//         lorenz(varX, varXDerivative);
//         varX[0] += varXDerivative[0] * deltaT;
//         varX[1] += varXDerivative[1] * deltaT;
//         varX[2] += varXDerivative[2] * deltaT;
//     }

//     // Set up a 3D scene and add an XYZ chart to it.
//     vtkNew<vtkContextView> view;
//     view->GetRenderWindow()->SetSize(640, 480);
//     view->GetRenderWindow()->SetWindowName("PlotLine3D");
//     vtkNew<vtkChartXYZ> chart;
//     chart->SetGeometry(vtkRectf(5.0, 5.0, 635.0, 475.0));
//     view->GetScene()->AddItem(chart);

//     // Add a line plot.
//     vtkNew<vtkPlotLine3D> plot;
//     plot->SetInputData(varXSolution);
// #if VTK_HAS_SETCOLORF
//     plot->GetPen()->SetColorF(colors->GetColor3d("LightCoral").GetData());
// #else
//     plot->GetPen()->SetColor(colors->GetColor3d("LightCoral").GetData());
// #endif
//     view->GetRenderWindow()->SetMultiSamples(0);
//     plot->GetPen()->SetWidth(2.0);
//     chart->AddPlot(plot);

//     // Finally render the scene.
//     view->GetRenderer()->SetBackground(
//         colors->GetColor3d("DarkOliveGreen").GetData());
//     view->GetRenderWindow()->Render();
//     view->GetInteractor()->Initialize();
//     view->GetInteractor()->Start();

//     return EXIT_SUCCESS;
// }

int main(int argc, char* argv[])
{
    QQuickVTKItem::setGraphicsApi();
    //QQuickVTKRenderWindow::setupGraphicsBackend();
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("hii", "Main");
    QObject* topLevel = engine.rootObjects().value(0);
    QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);

    window->show();

    // Fetch the QQuick window using the standard object name set up in the constructor
    QQuickVTKRenderItem* qquickvtkItem = topLevel->findChild<QQuickVTKRenderItem*>("ConeView");

    // Create a cone pipeline and add it to the view
    vtkNew<vtkActor> actor;
    vtkNew<vtkPolyDataMapper> mapper;
    vtkNew<vtkConeSource> cone;
    mapper->SetInputConnection(cone->GetOutputPort());
    actor->SetMapper(mapper);
    qquickvtkItem->renderer()->AddActor(actor);
    qquickvtkItem->renderer()->ResetCamera();
    qquickvtkItem->renderer()->SetBackground(0.5, 0.5, 0.7);
    qquickvtkItem->renderer()->SetBackground2(0.7, 0.7, 0.7);
    qquickvtkItem->renderer()->SetGradientBackground(true);
    qquickvtkItem->update();

    return app.exec();
}
