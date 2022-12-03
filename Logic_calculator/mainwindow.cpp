#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui -> comboBox_oper -> setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::my_func()                                      //тело функции
{
    bool op1, op2;
    bool res = true;                                            //объявление операнд
    int index;

    op1 = ui -> comboBox_op1 -> currentIndex() == 1;
    op2 = ui -> comboBox_op2 -> currentIndex() == 1;
    index = ui-> comboBox_oper -> currentIndex();

    QPalette pal;                                               //палитра
    pal = ui -> centralwidget -> palette();                     // текущая палитра
    ui -> comboBox_op2 -> setVisible(true);

    switch (index) {
    case 0:                                                     // дизъюнкция
        ui->comboBox_op2->show();                               // включаем 2 операнд
        res = op1 || op2;
        break;
    case 1:                                                     // конъюнкция
        ui->comboBox_op2->show();                               // включаем 2 операнд
        res = op1 && op2;
        break;
    case 2:                                                     // инверсия
        ui->comboBox_op2->hide();                               // скрываем 2 операнд
        res = !op1;
        break;
    case 3:                                                     // импликация
        ui->comboBox_op2->show();                               // включаем 2 операнд
        res = !op1 || op2;
        break;
    case 4:                                                     // эквивалентность
        ui->comboBox_op2->show();                               // включаем 2 операнд
        res = op1 == op2;
        break;
    case 5:                                                     // исключающее или
        ui->comboBox_op2->show();                               // включаем 2 операнд
        res = op1 != op2;
        break;
    }

    if(res)                                                     //красим фон в зависимости от результата
        pal.setColor(QPalette::Window, Qt::green);
    else
        pal.setColor(QPalette::Window, Qt::red);

    ui -> centralwidget -> setAutoFillBackground(true);
    ui -> centralwidget -> setPalette(pal);
}

void MainWindow::on_comboBox_oper_currentIndexChanged(int)      //Измение вида операции
{
    my_func();
}

void MainWindow::on_comboBox_op1_currentIndexChanged(int)       //Измение 1 оператора
{
    my_func();
}

void MainWindow::on_comboBox_op2_currentIndexChanged(int)       //Измение 2 оператора
{
    my_func();
}
