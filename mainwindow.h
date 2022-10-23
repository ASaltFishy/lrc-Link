#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QLabel>
#include "mainwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int _height = 10,int _width = 10,bool _singleMode = true,QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MainWidget *widget;
    QHBoxLayout mainLayout;
    QLabel timeHint;
    QLabel timer;
    QLabel p1Hint;
    QLabel p1Score;
    QLabel *p2Hint;
    QLabel *p2Score;

    int singleMode;

signals:
    void showStart();
};

#endif // MAINWINDOW_H
