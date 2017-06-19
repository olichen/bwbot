#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::help()
{
    QMessageBox::about(this, tr("Help"), tr("This is the help menu I'll fill it out later"));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"), tr("This is the about display hello there amigos."));
}

void MainWindow::setupMenu()
{
    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(help()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
}
