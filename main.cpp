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
int main(int argc, char *argv[])
{
    QQuickVTKRenderWindow::setupGraphicsBackend();
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.loadFromModule("hii","Main");

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
    app.exec();
}
