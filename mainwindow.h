#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QIcon>
#include <QTimer>
#include <vector>
#include "src/frame.h"
#include "src/build.h"
#include "src/unittree.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void help();
    void about();
    void bpage(int page);
    void cslower();
    void cstop();
    void cpause();
    void cplay();
    void cfaster();
    void update();

private:
    Ui::MainWindow *ui;
    Build *pBuild;
    QTimer timer;
    int frame, index;
    float framems;
    char mRace, mPage;
    UnitTree cUnitTree;

    void init();
    void initMenu();
    void initRace(char race);
    void initControls();
    void initBuildOrder();
    void run();
    void render(int index);
    vector<Frame> data;
};

#endif // MAINWINDOW_H
