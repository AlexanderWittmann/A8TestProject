#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Box2D/Box2D.h"
#include <QGraphicsRectItem>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    increment = 0;
    scene = new QGraphicsScene();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    xpos = 0;
    ypos = -300;
    size = 50;
    ui->graphicsView->setScene(scene);

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen blackpen(Qt::black);

    blackpen.setWidth(6);

    ellipse = scene->addEllipse(xpos,ypos,size,size,blackpen,blueBrush);
    //rect = scene->addRect(xpos,ypos,size,size,blackpen,blueBrush);
    ground = scene->addRect(-200,-10,400,50,blackpen,redBrush);


    // Define the gravity vector.
    gravity = new b2Vec2(0.0f,-10.0f);

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
        groundBox.SetAsBox(50.0f, 10.0f);

        // Add the ground fixture to the ground body.
        groundBody->CreateFixture(&groundBox, 0.0f);

        // Define the dynamic body. We set its position and call the body factory.
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(0.0f, 300.0f);
        body = world->CreateBody(&bodyDef);

        // Define another box shape for our dynamic body.

        dynamicBox.SetAsBox(50.0f, 50.0f);

        // Define the dynamic body fixture.

        fixtureDef.shape = &dynamicBox;

        // Set the box density to be non-zero, so it will be dynamic.
        fixtureDef.density = 50.0f;

        // Override the default friction.
        fixtureDef.friction = 0.3f;

        fixtureDef.restitution = 0.8f;

        // Add the shape to the body.
        body->CreateFixture(&fixtureDef);

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

    // Now print the position and angle of the body.
    b2Vec2 position = body->GetPosition();
    xpos = -(int)position.x;
    ypos = -(int)position.y;
    ellipse->setRect(xpos,ypos,size,size);
    ellipse->setRotation((double)body->GetAngle());
    if(increment >= 10000){
        timer->stop();
        increment = 0;
    }
}
