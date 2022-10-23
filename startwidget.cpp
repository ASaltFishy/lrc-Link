#include "startwidget.h"
#include "ui_startwidget.h"

#define minMapWidth 7
#define minMapHeight 7
#define maxMapWidth 18
#define maxMapHeight 10

//构造函数，设置界面中各个元素的属性
StartWidget::StartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWidget)
{
    ui->setupUi(this);
    ui->MapHeight->setMinimum(minMapHeight);
    ui->MapWidth->setMinimum(minMapWidth);
    ui->MapHeight->setMaximum(maxMapHeight);
    ui->MapWidth->setMaximum(maxMapWidth);
    ui->MapHeight->setValue(7);
    ui->MapWidth->setValue(7);
}

StartWidget::~StartWidget()
{
    delete ui;
    delete window;
}

//跳转界面的函数，为信号槽函数
void StartWidget::jumpTo(int width,int height,bool singleMode)
{
    window = new MainWidget(height,width,singleMode);
    connect(window,SIGNAL(showStart()),this,SLOT(showStartSlot()));
    window ->show();
    this->hide();
}

//显示开始窗口
void StartWidget::showStartSlot()
{
    qDebug()<<"startWidget收到信号,跳转窗口"<<Qt::endl;
    this->show();
}

//“开始游戏”按钮点击事件槽函数
void StartWidget::on_StartGame_clicked()
{
    int width = ui->MapWidth->value();
    int height = ui->MapHeight->value();
    qDebug()<<"height:"<<height<<"width:"<<width<<Qt::endl;
    //游戏模式，isSingleMood为true是表示单人模式
    bool isSingleMode = ui->SinglePlayer->isChecked();
    jumpTo(width,height,isSingleMode);
}

//“退出游戏”按钮点击事件槽函数
void StartWidget::on_QuitGame_clicked()
{
    this->close();
}

//“加载游戏”按钮点击事件槽函数
void StartWidget::on_LoadGame_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Failed to open file: " + file.errorString());
        return;
    }
    QByteArray saveData = file.readAll();
    loadDoc = new QJsonDocument(QJsonDocument::fromJson(saveData));
    window = new MainWidget(loadDoc->object());
    connect(window,SIGNAL(showStart()),this,SLOT(showStartSlot()));
    window ->show();
    this->hide();
}

