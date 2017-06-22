#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    build(new Build)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: gray; color: white");
    setupMenu();
    build->loadFile("101010");
    build->run();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupMenu()
{
    ui->b1->setStyleSheet("background-image:url(images/c10.png)");
    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(help()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::help()
{
    QMessageBox::about(this, tr("Help"), tr("This is the help menu I'll fill it out later"));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"), tr("This is the about display hello there amigos."));
}

