#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>                                                                        // библиотека - "матиматика"
#include <QtMath>                                                                        // библиотека - "матиматика"
bool err;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    no_auto_change=true;
    ui->label_PArea->hide();
    ui->label_SArea->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_res_clicked()                                               //проверки и расчет результата
{
    double PArea, SArea, x1, x2, x3, y1, y2, y3;
    QString str;

    ui->label_PArea->clear();
    ui->label_SArea->clear();
    ui->label_Error->hide();
    ui->label_PArea->hide();
    ui->label_SArea->hide();

    err = false;
    x1 = checkCoord(ui->lineEdit_x1->text());
    x2 = checkCoord(ui->lineEdit_x2->text());
    x3 = checkCoord(ui->lineEdit_x3->text());
    y1 = checkCoord(ui->lineEdit_y1->text());
    y2 = checkCoord(ui->lineEdit_y2->text());
    y3 = checkCoord(ui->lineEdit_y3->text());

    if (!err)                                                                               //проверка на наличие ошибок данных
    {
        PArea = sqrt((x2-x1) * (x2-x1) + (y2-y1) * (y2-y1)) + sqrt((x3-x2) * (x3-x2) + (y3-y2) * (y3-y2)) + sqrt((x1-x3) * (x1-x3) + (y1-y3) * (y1-y3));
        SArea = abs((x2-x1) * (y3-y1) - (x3-x1) * (y2-y1)) / 2;
        if (SArea != 0)                                                                     //проверка треуголька на одной линии
        {
            ui->label_SArea->show();
            str.setNum(SArea);
            ui->label_SArea->setText(str);
        }
        else
        {
            ui->label_Error->show();
            ui->label_Error->setText("Треугольник на одной прямой");
        }
        ui->label_PArea->show();
        str.setNum(PArea);
        ui->label_PArea->setText(str);
    }
}

void MainWindow::on_pushButton_clear_clicked()                                              //очистка
{
    ui->lineEdit_x1->clear();
    ui->lineEdit_x2->clear();
    ui->lineEdit_x3->clear();
    ui->lineEdit_y1->clear();
    ui->lineEdit_y2->clear();
    ui->lineEdit_y3->clear();
    ui->label_PArea->clear();
    ui->label_SArea->clear();
    ui->label_Error->hide();
    ui->label_PArea->hide();
    ui->label_SArea->hide();
    err = false;
}

void MainWindow::on_Random_clicked()                                                        //рандомное заполнение
{
    no_auto_change = false;
    ui->lineEdit_x1->setText(QString::number(rand()%201-100));
    ui->lineEdit_x2->setText(QString::number(rand()%201-100));
    ui->lineEdit_x3->setText(QString::number(rand()%201-100));
    ui->lineEdit_y1->setText(QString::number(rand()%201-100));
    ui->lineEdit_y2->setText(QString::number(rand()%201-100));
    ui->lineEdit_y3->setText(QString::number(rand()%201-100));
    no_auto_change = true;
    ui->label_Error->hide();
    ui->label_PArea->hide();
    ui->label_SArea->hide();
}

double MainWindow::checkCoord(QString str)                                                  //проверка введенных данных
{
    bool fl;
    double a;

    a = str.toDouble(&fl);
    if (!fl || err || qIsInf(a) || qIsNaN(a))
    {
        err = true;
        ui->label_Error->show();
        ui->label_Error->setText("Введен не верный параметр");
    }
    else
    {
        err = false;
    }
    return a;
}
