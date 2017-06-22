#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    build(new Build)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #333; color: white");
    setupMenu();
    run();
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

void MainWindow::run()
{
    build->loadFile("101010");
    build->run();
    data = build->getOutput();
    ui->rFrame->setText(QString::number(data.back().frame));
    ui->rTime->setText(QString::number(data.back().frame*42.0/1000, 'f', 1));
    ui->rMineral->setText(QString::number(data.back().minerals));
    ui->rGas->setText(QString::number(data.back().gas));
    ui->rSupply->setText(QString::number(data.back().supply)+"/"+QString::number(data.back().supplymax));
    ui->rMiner->setText(QString::number(data.back().miners));
    ui->rGasMiner->setText(QString::number(data.back().gasminers));
}

void MainWindow::help()
{
    QMessageBox::about(this, tr("Help"), tr("This is the help menu I'll fill it out later"));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"), tr("This is the about display hello there amigos."));
}

