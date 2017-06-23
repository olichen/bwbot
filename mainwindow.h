#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QIcon>
#include <QTimer>
#include <vector>
#include "src/frame.h"
#include "src/build.h"

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
    Build *build;
    QTimer timer;
    int frame, index;
    float framems;
    char mRace, mPage;

    void init();
    void initMenu();
    void initRace(char race);
    void initControls();
    void run();
    void render(int index);
    vector<Frame> data;
};

#endif // MAINWINDOW_H
