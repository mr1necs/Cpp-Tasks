#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>                                                                        // библиотека - "матиматика"
#include <QtMath>                                                                        // библиотека - "матиматика"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    no_auto_change=true;
    ui->spinBox->setMaximum(MAX_MAS_SIZE);
    ui->label_PArea->hide();
    ui->label_SArea->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBox_valueChanged(int arg1)                                          //изменили значение спинбокса
{
    ui->tableWidget->setRowCount(arg1);
}

void MainWindow::on_pushButton_res_clicked()                                                //проверки и расчет результата
{
    int row = ui->tableWidget->rowCount();                                                  //строки
    int colum = ui->tableWidget->columnCount();                                             //столбцы

    double PArea, SArea, side, x0, x, y0, y;
    bool flag1, flag2;                                                                      //флаг успешности

    SArea = 0;
    PArea = 0;
    x0 = 0;
    x = 0;
    y0 = 0;
    y = 0;
    flag2 = false;

    ui->label_err->hide();

    x = last_coordinate_X(x);                                                               //координата "x" последней вершины
    y = last_coordinate_Y(y);                                                               //координата "y" последней вершины

    for (int i=0; i<row; i++)                                                               //перемещение по строкам
    {
        for (int j=0; j<colum; j++)                                                         //перемещение по столбцам
        {
            if (ui->tableWidget->item(i,j)!=nullptr)                                        //проверка существования ячейки
            {
                if (j == 0)                                                                 //столбец "x"
                {
                    x0 = x;                                                                 //сохранение предыдущей координаты "x"
                    x = ui->tableWidget->item(i,j)->text().toDouble(&flag1);                //присваиваем
                    if (flag1 && (fabs(isinf(x)-0) < 1e-10) && (fabs(isnan(x)-0) < 1e-10))  //если в ячейке число
                    {
                        if (i==0)                                                           //сохраняем первую координату "x"
                        ui->tableWidget->item(i,j)->setBackground(Qt::white);               //окрашиваем в белый
                    }
                    else if ((fabs(isinf(x)-0) > 1e-10)||(fabs(isnan(x)-0) > 1e-10))        //в ячейке находится inf или nan
                    {
                        ui->tableWidget->item(i,j)->setBackground(Qt::red);                 //окрашиваем в красный
                        ui->label_PArea->clear();                                           //очистка периметра
                        ui->label_SArea->clear();                                           //очистка площади
                        ui->label_err->show();
                        ui->label_err->setText("Введены неверные данные");
                        flag2 = true;
                    }
                    else                                                                    //в ячейке мусор
                    {
                        ui->tableWidget->item(i,j)->setBackground(Qt::red);                 //окрашиваем в красный
                        ui->label_PArea->clear();                                           //очистка периметра
                        ui->label_SArea->clear();                                           //очистка площади
                        ui->label_err->show();
                        ui->label_err->setText("Введены неверные данные");
                        flag2 = true;
                    }
                }
                else                                                                        //если столбик "y"
                {
                    y0 = y;                                                                 //сохранение предыдущей координаты "y"
                    y = ui->tableWidget->item(i,j)->text().toDouble(&flag1);                //присваиваем
                    if (flag1 && (fabs(isinf(y)-0) < 1e-10) && (fabs(isnan(y)-0) < 1e-10))
                    {
                        if (i==0)                                                           //сохраняем первую координату "y"
                        ui->tableWidget->item(i,j)->setBackground(Qt::white);               //окрашиваем в белый
                    }
                    else if ((fabs(isinf(y)-0) > 1e-10)||(fabs(isnan(x)-0) > 1e-10))        //в ячейке находится inf или nan
                    {
                        ui->tableWidget->item(i,j)->setBackground(Qt::red);                 //окрашиваем в красный
                        ui->label_PArea->clear();                                           //очистка периметра
                        ui->label_SArea->clear();                                           //очистка площади
                        ui->label_err->show();
                        ui->label_err->setText("Введены неверные данные");
                        flag2 = true;
                    }
                    else                                                                    //в ячейке мусор
                    {
                        ui->tableWidget->item(i,j)->setBackground(Qt::red);                 //окрашиваем в красный
                        ui->label_PArea->clear();                                           //очистка периметра
                        ui->label_SArea->clear();                                           //очистка площади
                        ui->label_err->show();
                        ui->label_err->setText("Введены неверные данные");
                        flag2 = true;
                    }
                }
            }
            else                                                                            //не существует
            {
                                                                                            //создаем
                QTableWidgetItem * ti;                                                      //создаем указатель на ячейку
                ti = new QTableWidgetItem;                                                  //выделяем память
                ui->tableWidget->setItem(i,j,ti);                                           //помещаем ячейку в таблицу
                ui->tableWidget->item(i,j)->setBackground(Qt::red);
                ui->label_PArea->clear();                                                   //очистка периметра
                ui->label_SArea->clear();                                                   //очистка площади
                ui->label_err->show();
                ui->label_err->setText("Введены неверные данные");
                flag2 = true;
            }
        }
            side = sqrt((pow((x-x0),2) + pow((y-y0),2)));                                   //нахождение стороны
            PArea = PArea + side;                                                           //периметр
            SArea = SArea + ((x0 * y - x * y0)/2);                                          //площадь
    }
    if (flag2)
    {
        ui->label_PArea->hide();
        ui->label_SArea->hide();
    }
    else if((fabs(PArea-0) < 1e-10)||(fabs(SArea-0) < 1e-10))                               //многоугольник лежащий на одной прямой
    {
        ui->label_PArea->show();
        ui->label_SArea->hide();
        ui->label_err->show();
        ui->label_err->setText("Многоугольник самопересекающийся");
    }
    else
    {
        ui->label_PArea->show();
        ui->label_SArea->show();
    }
    ui->label_PArea->setNum(PArea);                                                         //вывод результата периметра
    ui->label_SArea->setNum(fabs(SArea));                                                   //вывод результата площади
    no_auto_change=true;

}

double MainWindow::last_coordinate_X(double x)                                              //координата "x" вершины
{
    int row = ui->tableWidget->rowCount();                                                  //строки
    bool flag;

    if (ui->tableWidget->item(row-1,0)!=nullptr)                                            //проверка на существование ячейки
    {
        x = ui->tableWidget->item(row-1,0)->text().toDouble(&flag);                         //достаем число из последней ячейки столбца "х"
        if (flag && (fabs(isinf(x)-0) < 1e-10))                                             //в ячейке число
            ui->tableWidget->item(row-1,0)->setBackground(Qt::white);
        else                                                                                //в ячейке мусор
        {
            ui->tableWidget->item(row-1,0)->setBackground(Qt::red);
            ui->label_PArea->clear();                                                       //очистка периметра
            ui->label_SArea->clear();                                                       //очистка площади
        }
    }
    else
    {
        QTableWidgetItem * ti;                                                              //создаем указатель на ячейку
        ti = new QTableWidgetItem;                                                          //выделяем память
        ui->tableWidget->setItem(row-1,0,ti);                                               //помещаем ячейку в таблицу
        ui->tableWidget->item(row-1,0)->setBackground(Qt::red);
        ui->label_PArea->clear();                                                           //очистка периметра
        ui->label_SArea->clear();                                                           //очистка площади
    }
    return x;
}

double MainWindow::last_coordinate_Y(double y)                                              //координата "y" вершины
{
    int row = ui->tableWidget->rowCount();                                                  //количество строк
    bool flag;

    if (ui->tableWidget->item(row-1,1)!=nullptr)                                            //проверка на существование ячейки
    {
        y = ui->tableWidget->item(row-1,1)->text().toDouble(&flag);                         //достаем число из последней ячейки столбца Y
        if (flag && (fabs(isinf(y)-0) < 1e-10))                                             //в ячейке число
            ui->tableWidget->item(row-1,1)->setBackground(Qt::white);
        else                                                                                //в ячейке мусор
        {
            ui->tableWidget->item(row-1,1)->setBackground(Qt::red);
            ui->label_PArea->clear();                                                       //очистка периметра
            ui->label_SArea->clear();                                                       //очистка площади
            ui->label_PArea->hide();
            ui->label_SArea->hide();
        }
    }
    else
    {
        QTableWidgetItem * ti;                                                              //создаем указатель на ячейку
        ti = new QTableWidgetItem;                                                          //выделяем память
        ui->tableWidget->setItem(row-1,1,ti);                                               //помещаем ячейку в таблицу
        QBrush br;
        br.setColor(Qt::red);
        br.setStyle(Qt::DiagCrossPattern);
        ui->tableWidget->item(row-1,1)->setBackground(Qt::red);
        ui->label_PArea->clear();                                                           //очистка периметра
        ui->label_SArea->clear();                                                           //очистка площади
    }
    return y;
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)                            //изменения ячейки
{
    if (no_auto_change)
    {
        bool flag;
        ui->tableWidget->item(row,column)->text().toInt(&flag);
        if (flag)
            ui->tableWidget->item(row,column)->setBackground(Qt::white);                    //окраска в белый
        else
        {
            QBrush br;
            br.setColor(Qt::red);
            br.setStyle(Qt::DiagCrossPattern);
            ui->tableWidget->item(row,column)->setBackground(Qt::red);
            ui->label_PArea->clear();                                                       //очистка периметра
            ui->label_SArea->clear();                                                       //очистка площади
        }
    }
    ui->label_err->hide();
}

void MainWindow::on_pushButton_clear_clicked()                                              //очистка
{
    ui->tableWidget->clearContents();                                                       //очистка таблицы
    ui->label_PArea->clear();                                                               //очистка периметра
    ui->label_SArea->clear();                                                               //очистка площади
    ui->label_err->hide();
}

void MainWindow::on_Random_clicked()
{
    no_auto_change=false;
    int row=ui->tableWidget->rowCount();
    int colum=ui->tableWidget->columnCount();

    int value;

    for (int i=0;i<row;i++)
        for (int j=0;j<colum;j++)
        {
            if (ui->tableWidget->item(i,j)==nullptr)
            {
                QTableWidgetItem * ti;                                                      //создали указатель
                ti =  new QTableWidgetItem();                                               //выделяем память
                ui->tableWidget->setItem(i,j,ti);                                           //помещаем ячейку в таблицу
            }
            QBrush br;
            br.setColor(Qt::white);
            br.setStyle(Qt::DiagCrossPattern);
            ui->tableWidget->item(i,j)->setBackground(Qt::white);

            value=rand()%201-100;                                                           // от -100 до 100
            ui->tableWidget->item(i,j)->setText(QString::number(value));
        }
    no_auto_change=true;
    ui->label_err->hide();
}

