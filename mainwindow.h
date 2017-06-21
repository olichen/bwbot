#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QIcon>
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
};

#endif // MAINWINDOW_H
