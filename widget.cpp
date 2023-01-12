#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //第一次修改
    QString s="6";

}

Widget::~Widget()
{
    delete ui;
}

