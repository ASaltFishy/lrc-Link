#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include <qdebug.h>
#include <QJsonArray>
#include <QJsonDocument>
#include "mainwidget.h"


namespace Ui {
class StartWidget;
}

class StartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = nullptr);
    ~StartWidget();


public slots:
    void jumpTo(int width,int height,bool singleMode);
    void showStartSlot();

private slots:
    void on_StartGame_clicked();
    void on_QuitGame_clicked();

    void on_LoadGame_clicked();

private:
    QJsonDocument *loadDoc;
    Ui::StartWidget *ui = nullptr;
    MainWidget *window = nullptr;
};


#endif // STARTWIDGET_H
