#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Box2D/Box2D.h"
#include <QGraphicsRectItem>
#include <cstdlib>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    increment = 0;
    scene = new QGraphicsScene();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));

    for (int i = 0; i < 16; i++) {

        xpos[i] = (-8 + i)*30;
        ypos[i] = -250;
        xSize[i] = 15;
        ySize[i] = (rand() % 100)*2;
    }



    ui->graphicsView->setScene(scene);

    QBrush blackBrush(Qt::black);
    QBrush greenBrush(Qt::green);
    QPen blackpen(Qt::black);

    blackpen.setWidth(1);

    for (int i = 0; i < 16; i++) {
        barBoxes[i] = scene->addRect(xpos[i], ypos[i], xSize[i], ySize[i], blackpen, greenBrush);
    }

//    barBoxes[0] = scene->addRect(-100, -10, 200, 50, blackpen, greenBrush);

//    for (int i = 0; i < 16; i++) {
//        barBoxes[i] = scene->addRect(-100, -10, 200, 50, blackpen, greenBrush);
//    }

//    ellipse = scene->addEllipse(xpos,ypos,size,size,blackpen, greenBrush);

    ground = scene->addRect(-250,-10,550,50,blackpen,blackBrush);


    // Define the gravity vector.
    gravity = new b2Vec2(0.0f,-100.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    world = new b2World(*gravity);

    // Define the ground body.
    b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0.0f, 0.0f);

        // Call the body factory which allocates memory for the ground body
        // from a pool and creates the ground box shape (also from a pool).
        // The body is also added to the world.
        b2Body* groundBody = world->CreateBody(&groundBodyDef);

        // Define the ground box shape.
        b2PolygonShape groundBox;

        // The extents are the half-widths of the box.
        groundBox.SetAsBox(10000.0f, 10.0f);

        // Add the ground fixture to the ground body.
        groundBody->CreateFixture(&groundBox, 0.0f);

        // Define the dynamic body. We set its position and call the body factory.
        b2BodyDef bodyDef[16];
        for (int i = 0; i < 16; i++) {
            bodyDef[i].type = b2_dynamicBody;

            bodyDef[i].position.Set((-8 + i)*30, 300.0f);
            body[i] = world->CreateBody(&bodyDef[i]);

            dynamicBox[i].SetAsBox(xSize[i], ySize[i]);

            fixtureDef[i].shape = &dynamicBox[i];

            // Set the box density to be non-zero, so it will be dynamic.
            fixtureDef[i].density = 600.0f;

            // Override the default friction.
            fixtureDef[i].friction = 0.0f;

            fixtureDef[i].restitution = .6f;

            // Add the shape to the body.
            body[i]->CreateFixture(&fixtureDef[i]);


        }

        // Define another box shape for our dynamic body.



        // Define the dynamic body fixture.



        // Prepare for simulation. Typically we use a time step of 1/60 of a
        // second (60Hz) and 10 iterations. This provides a high quality simulation
        // in most game scenarios.
        timeStep = 1.0f / 60.0f;
        velocityIterations = 6;
        positionIterations = 2;


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    timer->start(4);


}

void MainWindow::update()
{
    increment += 1;
    world->Step(timeStep, velocityIterations, positionIterations);

    b2Vec2 position[16];

    // Now print the position and angle of the body.

    for (int i = 0; i < 16; i++) {
        position[i] = body[i]->GetPosition();
        xpos[i] = -(int)position[i].x;
        ypos[i] = -(int)position[i].y;
        barBoxes[i]->setRect(xpos[i], ypos[i], xSize[i], ySize[i]);
        barBoxes[i]->setRotation((double)body[i]->GetAngle());
    }

//    ellipse->setRect(xpos,ypos,size,size);
//    ellipse->setRotation((double)body->GetAngle());
//    barBoxes[0]->setRect(xpos[0], ypos[0], 10, 50);
//    barBoxes[0]->setRotation((double)body->GetAngle());
    if(increment >= 430){
        timer->stop();
        increment = 0;
    }
}
