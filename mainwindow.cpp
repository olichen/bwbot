#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    build(new Build),
    frame(0), index(0), framems(21)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #222; color: white;");
    init();
    run();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    initMenu();
    initControls();
}

void MainWindow::initMenu()
{
    ui->b1->setStyleSheet("background-image:url(images/c10.png)");
    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(help()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::initRace(char race)
{
    if (race=='t')
    {
        //
    }
}

void MainWindow::initControls()
{
    ui->cslower->setStyleSheet("background-image:url(images/ucslower.png)");
    ui->cstop->setStyleSheet("background-image:url(images/ucstop.png)");
    ui->cpause->setStyleSheet("background-image:url(images/ucpause.png)");
    ui->cplay->setStyleSheet("background-image:url(images/ucplay.png)");
    ui->cfaster->setStyleSheet("background-image:url(images/ucfaster.png)");
    connect(ui->cslower, SIGNAL(clicked()), this, SLOT(cslower()));
    connect(ui->cstop, SIGNAL(clicked()), this, SLOT(cstop()));
    connect(ui->cpause, SIGNAL(clicked()), this, SLOT(cpause()));
    connect(ui->cplay, SIGNAL(clicked()), this, SLOT(cplay()));
    connect(ui->cfaster, SIGNAL(clicked()), this, SLOT(cfaster()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}
void MainWindow::cslower()
{
    framems*=2;
    timer.start(framems);
    ui->statusBar->showMessage("Playing ("+QString::number(42.0/framems)+"x).");
}
void MainWindow::cstop()
{
    timer.stop();
    frame=0;
    index=0;
    framems=42;
    ui->statusBar->showMessage(tr("Stopped."));
}
void MainWindow::cpause()
{
    timer.stop();
    ui->statusBar->showMessage(tr("Paused."));
}
void MainWindow::cplay()
{
    timer.start(framems);
    ui->statusBar->showMessage("Playing ("+QString::number(42.0/framems)+"x).");
}
void MainWindow::cfaster()
{
    framems/=2;
    timer.start(framems);
    ui->statusBar->showMessage("Playing ("+QString::number(42.0/framems)+"x).");
}

void MainWindow::update()
{
    ui->rFrame->setText(QString::number(frame));
    ui->rTime->setText(QString::number(frame*42.0/1000, 'f', 1));
    if (index < (int)data.size())
    {
        if(frame==data[index].frame)
        {
        while(frame==data[index].frame)
            {
                render(index);
                index++;
            }
        }
        frame++;
    }
    else
        cpause();
}

void MainWindow::render(int index)
{
    ui->rMineral->setText(QString::number(data[index].minerals));
    ui->rGas->setText(QString::number(data[index].gas));
    ui->rSupply->setText(QString::number(data[index].supply)+"/"+QString::number(data[index].supplymax));
    ui->rMiner->setText(QString::number(data[index].miners));
    ui->rGasMiner->setText(QString::number(data[index].gasminers));
}

void MainWindow::run()
{
    build->loadFile("101010");
    build->run();
    data = build->getOutput();
    ui->rFrame->setText(QString::number(20000));
    ui->rTime->setText(QString::number(data.back().frame*42.0/1000, 'f', 1));
    ui->rMineral->setText(QString::number(data.back().minerals));
    ui->rGas->setText(QString::number(data.back().gas));
    ui->rSupply->setText(QString::number(200)+"/"+QString::number(200));
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

