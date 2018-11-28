#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "Box2D/Box2D.h"
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rect;
    QGraphicsRectItem *barBoxes[16];
    QGraphicsRectItem *ground;
    int xpos[16];
    int ypos[16];
    int size;

    int ySize[16];
    int xSize[16];
    float32 timeStep;
    int32 velocityIterations;
    int32 positionIterations;
    b2FixtureDef fixtureDef[16];
    b2PolygonShape dynamicBox[16];
    b2Body* body[16];
    b2World *world;
    QTimer *timer;
    int increment;
    b2Vec2 *gravity;



private slots:
    void on_pushButton_clicked();
    void update();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
