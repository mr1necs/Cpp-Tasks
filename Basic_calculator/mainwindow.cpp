#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_error->setVisible(false);                                     //скрываем сообщение об ошибке
    ui->label_res->setVisible(false);                                       //скрываем окно с результатом
    ui->radioButton_plus->click();                                          //имитируем клик мышкой на радиокнопке сложения
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_result_clicked()                             //при нажатии на результат
{
    int op_1, op_2, res;
    QString str;                                                            //строка для конвертации
    bool fl1;                                                               //флаг успешности преобразования

    if (ui->radioButton_plus->isChecked())                                  //выбор сложения
    {
        str = ui->lineEdit_op_1->text();                                    //копируем в строку текст из поля 1
        op_1 = str.toInt(&fl1);                                             //пытаемся преобразовать 1 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
        if (fl1)                                                            //проверка успешности преобразования
        {
            str = ui->lineEdit_op_2->text();                                //копируем в строку текст из поля 2
            op_2 = str.toInt(&fl1);                                         //пытаемся преобразовать 2 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
            if (fl1)
            {
                res=op_1 + op_2;
                ui->label_error->setVisible(false);                         //скрываем сообщение об ошибке
                str.setNum(res);
                ui->label_res->setText(str);
                ui->label_res->setVisible(true);                            //показываем результат
            }
            else
            {
                ui->label_res->setVisible(false);                           //скрываем результат
                ui->label_error->setText("Ошибка в Cлагаемом 2");
                ui->label_error->setVisible(true);                          //показываем ошибку
            }
        }
        else
        {
            ui->label_res->setVisible(false);                               //скрываем результат
            ui->label_error->setText("Ошибка в Cлагаемом 1");
            ui->label_error->setVisible(true);                              //показываем ошибку
        }
    }

    if (ui->radioButton_minus->isChecked())                                 //выбор вычитание
    {
        str = ui->lineEdit_op_1->text();                                    //копируем в строку текст из поля 1
        op_1 = str.toInt(&fl1);                                             //пытаемся преобразовать 1 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
        if (fl1)                                                            //проверка успешности преобразования
        {
            str = ui->lineEdit_op_2->text();                                //копируем в строку текст из поля 2
            op_2 = str.toInt(&fl1);                                         //пытаемся преобразовать 2 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
            if (fl1)
            {
                res = op_1-op_2;
                ui->label_error->setVisible(false);                         //скрываем сообщение об ошибке
                ui->label_res->setNum(res);                                 //вывод результата
                ui->label_res->setVisible(true);                            //показываем результат
            }
            else
            {
                ui->label_res->setVisible(false);                           //скрываем результат
                ui->label_error->setText("Ошибка в Вычитаемом");
                ui->label_error->setVisible(true);                          //показываем ошибку
            }
        }
        else
        {
            ui->label_res->setVisible(false);                               //скрываем результат
            ui->label_error->setText("Ошибка в Уменьшаемом");
            ui->label_error->setVisible(true);                              //показываем ошибку
        }
    }

    if(ui->radioButton_mult->isChecked())                                   //выбор умножение
    {
        str = ui->lineEdit_op_1->text();                                    //копируем в строку текст из поля 1
        op_1 = str.toInt(&fl1);                                             //пытаемся преобразовать 1 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
        if (fl1)                                                            //проверка успешности преобразования
        {
            str = ui->lineEdit_op_2->text();                                //копируем в строку текст из поля 2
            op_2 = str.toInt(&fl1);                                         //пытаемся преобразовать 2 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
            if (fl1)
            {
                res=op_1*op_2;
                ui->label_error->setVisible(false);                         //скрываем сообщение об ошибке
                ui->label_res->setNum(res);                                 //вывод результата
                ui->label_res->setVisible(true);                            //показываем результат
            }

            else
            {
                ui->label_res->setVisible(false);                           //скрываем результат
                ui->label_error->setText("Ошибка в множителе 2");
                ui->label_error->setVisible(true);                          //показываем ошибку
            }
        }
        else
        {
            ui->label_res->setVisible(false);                               //скрываем результат
            ui->label_error->setText("Ошибка в множителе 1");
            ui->label_error->setVisible(true);                              //показываем ошибку
        }
    }

    if  (ui->radioButton_div->isChecked())                                  //выбор деление
    {
        str = ui->lineEdit_op_1->text();                                    //копируем в строку текст из поля 1
        op_1 = str.toInt(&fl1);                                             //пытаемся преобразовать 1 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
        if (fl1)                                                            //проверка успешности преобразования
        {
            str = ui->lineEdit_op_2->text();                                //копируем в строку текст из поля 2
            op_2 = str.toInt(&fl1);                                         //пытаемся преобразовать 2 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
            if(fl1)
            {
                if (op_2 != 0)                                              //проверка деления на 0
                {
                    res=op_1/op_2;
                    ui->label_error->setVisible(false);                     //скрываем сообщение об ошибке
                    ui->label_res->setNum(res);                             //вывод результата
                    ui->label_res->setVisible(true);                        //показываем результат
                }
                else
                {
                    ui->label_res->setVisible(false);                       //скрываем результат
                    ui->label_error->setText("На ноль делить нельзя!!!");
                    ui->label_error->setVisible(true);                      //показываем ошибку
                }

            }
            else
            {
                ui->label_res->setVisible(false);                           //скрываем результат
                ui->label_error->setText("Ошибка в Делителе");
                ui->label_error->setVisible(true);                          //показываем ошибку
            }
        }
        else
        {
            ui->label_res->setVisible(false);                               //скрываем результат
            ui->label_error->setText("Ошибка в Делимом");
            ui->label_error->setVisible(true);                              //показываем ошибку
        }

    }
}

void MainWindow::on_radioButton_plus_clicked()                              //Замена подписей у операторов при сложении
{
    ui->label_error->setVisible(false);
    ui->label_res->setVisible(false);
    ui->label_op_1->setText("Слагаемое 1");
    ui->label_op_2->setText("Слагаемое 2");
    ui->pushButton_result->setText("Сумма");
}

void MainWindow::on_radioButton_minus_clicked()                             //Замена подписей у операторов при вычитании
{
    ui->label_error->setVisible(false);
    ui->label_res->setVisible(false);
    ui->label_op_1->setText("Уменьшаемое");
    ui->label_op_2->setText("Вычитаемое");
    ui->pushButton_result->setText("Разность");
}

void MainWindow::on_radioButton_mult_clicked()                              //Замена подписей у операторов при умножении
{
    ui->label_error->setVisible(false);
    ui->label_res->setVisible(false);
    ui->label_op_1->setText("1-ый множитель");
    ui->label_op_2->setText("2-ой множитель");
    ui->pushButton_result->setText("Произведение");
}

void MainWindow::on_radioButton_div_clicked()                               //Замена подписей у операторов при делении
{
    ui->label_error->setVisible(false);
    ui->label_res->setVisible(false);
    ui->label_op_1->setText("Делимое");
    ui->label_op_2->setText("Делитель");
    ui->pushButton_result->setText("Частное");
}

void MainWindow::on_pushButton_clear_clicked()                              //очистка
{
    ui->lineEdit_op_1->clear();                                             //очистка op 1
    ui->lineEdit_op_2->clear();                                             //очистка op 2
    ui->label_res->clear();                                                 //очистка результата
    ui->label_error->clear();                                               //очистка ошибки
}
