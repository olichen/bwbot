#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    build(new Build),
    frame(0), index(0), framems(21),
    mRace('t'), mPage('1')
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
    initRace(mRace);
}

void MainWindow::initMenu()
{
    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(help()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::initRace(char race)
{
    mRace = race;
    QString pixmapfolder("images/");
    ui->rMinerP->setPixmap(QPixmap(pixmapfolder+mRace+"211.png"));
    ui->rGasMinerP->setPixmap(QPixmap(pixmapfolder+mRace+"113.png"));
    ui->rSupplyP->setPixmap(QPixmap(pixmapfolder+mRace+"111.png"));
    QString imgfolder("background-image:url(images/");
    ui->b1->setStyleSheet(imgfolder+mRace+"1.png)");
    ui->b2->setStyleSheet(imgfolder+mRace+"2.png)");
    ui->b3->setStyleSheet(imgfolder+mRace+"3.png)");
    ui->b4->setStyleSheet(imgfolder+mRace+"4.png)");
    bpage(1);
}

void MainWindow::bpage(int page)
{
    mPage = '0'+page;
    QString imgfolder("background-image:url(images/");
    ui->bq->setStyleSheet(imgfolder+mRace+mPage+"11.png)");
    ui->bw->setStyleSheet(imgfolder+mRace+mPage+"12.png)");
    ui->be->setStyleSheet(imgfolder+mRace+mPage+"13.png)");
    ui->br->setStyleSheet(imgfolder+mRace+mPage+"14.png)");
    ui->bt->setStyleSheet(imgfolder+mRace+mPage+"15.png)");
    ui->by->setStyleSheet(imgfolder+mRace+mPage+"16.png)");
    ui->bu->setStyleSheet(imgfolder+mRace+mPage+"17.png)");
    ui->ba->setStyleSheet(imgfolder+mRace+mPage+"21.png)");
    ui->bs->setStyleSheet(imgfolder+mRace+mPage+"22.png)");
    ui->bd->setStyleSheet(imgfolder+mRace+mPage+"23.png)");
    ui->bf->setStyleSheet(imgfolder+mRace+mPage+"24.png)");
    ui->bg->setStyleSheet(imgfolder+mRace+mPage+"25.png)");
    ui->bh->setStyleSheet(imgfolder+mRace+mPage+"26.png)");
    ui->bj->setStyleSheet(imgfolder+mRace+mPage+"27.png)");
    ui->bz->setStyleSheet(imgfolder+mRace+mPage+"31.png)");
    ui->bx->setStyleSheet(imgfolder+mRace+mPage+"32.png)");
    ui->bc->setStyleSheet(imgfolder+mRace+mPage+"33.png)");
    ui->bv->setStyleSheet(imgfolder+mRace+mPage+"34.png)");
    ui->bb->setStyleSheet(imgfolder+mRace+mPage+"35.png)");
    ui->bn->setStyleSheet(imgfolder+mRace+mPage+"36.png)");
    ui->bm->setStyleSheet(imgfolder+mRace+mPage+"37.png)");
}

void MainWindow::initControls()
{
    connect(ui->b1, &QPushButton::clicked, this, [=](){this->bpage(1);});
    connect(ui->b2, &QPushButton::clicked, this, [=](){this->bpage(2);});
    connect(ui->b3, &QPushButton::clicked, this, [=](){this->bpage(3);});
    connect(ui->b4, &QPushButton::clicked, this, [=](){this->bpage(4);});
    //connect(ui->b2, SIGNAL(clicked()), this, SLOT(bpage(2)));
    //connect(ui->b3, SIGNAL(clicked()), this, SLOT(bpage(3)));
    //connect(ui->b4, SIGNAL(clicked()), this, SLOT(bpage(4)));

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

