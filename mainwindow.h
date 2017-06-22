#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QIcon>
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

private:
    Ui::MainWindow *ui;
    Build *build;
    void setupMenu();
    void run();
    vector<Frame> data;
};

#endif // MAINWINDOW_H
