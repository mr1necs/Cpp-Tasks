#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_error->setVisible(false);                                     //скрываем сообщение об ошибке
    ui->label_res->setVisible(false);                                       //скрываем окно с результатом
    ui->radioButton_plus->click();                                          //иммитация нажатия на кнопку
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_result_clicked()                             //при нажатии на результат
{
    double op_1, op_2;
    double res;
    QString str;                                                            //строка для конвертации
    bool fl1;                                                               //флаг на успешность преобразования
    bool fl2;                                                               //флаг на успешность преобразования

    if (ui->radioButton_plus->isChecked())                                  //выбор сложения
    {
        str = ui->lineEdit_op_1->text();                                    //копируем в строку текст из поля 1
        op_1 = str.toDouble(&fl1);                                             //пытаемся преобразовать 1 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
        if (fl1)                                                            //проверка успешности преобразования
        {
            str = ui->lineEdit_op_2->text();                                //копируем в строку текст из поля 2
            op_2 = str.toDouble(&fl2);                                         //пытаемся преобразовать 2 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
            if (fl2)
            {
                res=op_1 + op_2;
                if (qIsInf(res)||qIsNaN(res))
                {
                    ui->label_res->setVisible(false);                           //скрываем результат
                    ui->label_error->setText("Невозможно!");
                    ui->label_error->setVisible(true);                          //показываем ошибку
                }
                else
                {

                    ui->label_error->setVisible(false);                         //скрываем сообщение об ошибке
                    str.setNum(res, 'e', 10);
                    ui->label_res->setText(str);
                    ui->label_res->setVisible(true);                            //показываем результат
                }
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
        op_1 = str.toDouble(&fl1);                                             //пытаемся преобразовать 1 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
        if (fl1)                                                            //проверка успешности преобразования
        {
            str = ui->lineEdit_op_2->text();                                //копируем в строку текст из поля 2
            op_2 = str.toDouble(&fl2);                                         //пытаемся преобразовать 2 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
            if (fl2)
            {
                res = op_1-op_2;
                if (qIsInf(res)||qIsNaN(res))
                {
                    ui->label_res->setVisible(false);                           //скрываем результат
                    ui->label_error->setText("Невозможно!");
                    ui->label_error->setVisible(true);                          //показываем ошибку
                }
                else
                {

                    ui->label_error->setVisible(false);                         //скрываем сообщение об ошибке
                    str.setNum(res);
                    ui->label_res->setText(str);
                    ui->label_res->setVisible(true);                            //показываем результат
                }
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
        op_1 = str.toDouble(&fl1);                                             //пытаемся преобразовать 1 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
        if (fl1)                                                            //проверка успешности преобразования
        {
            str = ui->lineEdit_op_2->text();                                //копируем в строку текст из поля 2
            op_2 = str.toDouble(&fl2);                                         //пытаемся преобразовать 2 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
            if (fl2)
            {
                res=op_1*op_2;
                if (qIsInf(res)||qIsNaN(res))
                {
                    ui->label_res->setVisible(false);                           //скрываем результат
                    ui->label_error->setText("Невозможно!");
                    ui->label_error->setVisible(true);                          //показываем ошибку
                }
                else
                {

                    ui->label_error->setVisible(false);                         //скрываем сообщение об ошибке
                    str.setNum(res);
                    ui->label_res->setText(str);
                    ui->label_res->setVisible(true);                            //показываем результат
                }                         //показываем результат
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
        op_1 = str.toDouble(&fl1);                                             //пытаемся преобразовать 1 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
        if (fl1)                                                            //проверка успешности преобразования
        {
            str = ui->lineEdit_op_2->text();                                //копируем в строку текст из поля 2
            op_2 = str.toDouble(&fl2);                                         //пытаемся преобразовать 2 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
            if(fl2)
            {
                if (op_2 != 0)                                              //проверка деления на 0
                {
                    res=op_1/op_2;
                    if (qIsInf(res)||qIsNaN(res))
                    {
                        ui->label_res->setVisible(false);                           //скрываем результат
                        ui->label_error->setText("Невозможно!");
                        ui->label_error->setVisible(true);                          //показываем ошибку
                    }
                    else
                    {

                        ui->label_error->setVisible(false);                         //скрываем сообщение об ошибке
                        str.setNum(res);
                        ui->label_res->setText(str);
                        ui->label_res->setVisible(true);                            //показываем результат
                    }
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

    if(ui->radioButton_sqrt->isChecked())                                   //выбор корня
    {
        double res1 = 0;
        str=ui->lineEdit_op_1->text();                                      //копируем в строку текст из поля 1
        op_1=str.toDouble(&fl1);                                            //пытаемся преобразовать 1 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
        if(fl1)
        {
            res1 = sqrt(op_1);
            if(qIsNaN(res1))
            {
                ui->label_res->setVisible(false);                           //скрываем результат
                ui->label_error->setText("Ошибка! Число меньше 0");
                ui->label_error->setVisible(true);                          //показываем ошибку
            }
            else
            {
                ui->label_error->setVisible(false);                         //скрываем сообщение об ошибке
                ui->label_res->setNum(res1);                                //вывод результата
                ui->label_res->setVisible(true);                            //показываем результат
            }
        }
        else
        {
            ui->label_res->setVisible(false);                               //скрываем результат
            ui->label_error->setText("Ошибка в подкоренном числе");
            ui->label_error->setVisible(true);                              //показываем ошибку
        }
    }

    if(ui->radioButton_sin->isChecked())                                    //Выбор sin
    {
        double res1 = 0;
        str=ui->lineEdit_op_1->text();                                      //копируем в строку текст из поля 1
        op_1=str.toDouble(&fl1);                                            //пытаемся преобразовать 1 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
        if(fl1)
        {
            res1=sin(op_1);
            ui->label_error->setVisible(false);                             //скрываем сообщение об ошибке
            ui->label_res->setNum(res1);                                    //вывод результата
            ui->label_res->setVisible(true);                                //показываем результат
        }

        else
        {
            ui->label_res->setVisible(false);                               //скрываем результат
            ui->label_error->setText("Ошибка в аргументе");
            ui->label_error->setVisible(true);                              //показываем ошибку
        }

    }

    if(ui->radioButton_cos->isChecked())                                    //выбор cos
    {
        double res1 = 0;
        str=ui->lineEdit_op_1->text();                                      //копируем в строку текст из поля 1
        op_1=str.toDouble(&fl1);                                            //пытаемся преобразовать 1 операнд в целостной тип данных и присваиваем число к соответствуещей переменной
        if(fl1)
        {
            res1=cos(op_1);
            ui->label_error->setVisible(false);                             //скрываем сообщение об ошибке
            ui->label_res->setNum(res1);                                    //вывод результата
            ui->label_res->setVisible(true);                                //показываем результат
        }

        else
        {
            ui->label_res->setVisible(false);                               //скрываем результат
            ui->label_error->setText("Ошибка в аргументе");
            ui->label_error->setVisible(true);                              //показываем ошибку
        }

    }

    if(ui->radioButton_asin->isChecked())                                   //выбор arsin
    {
        double res1 = 0;
        str=ui->lineEdit_op_1->text();                                      //копируем в строку текст из поля 1
        op_1=str.toDouble(&fl1);                                            //пытаемся преобразовать 1 операнд в целостной тип данных и присваиваем число к соответствуещей переменной

        if(fl1)
        {
            res1=asin(op_1);
            if(qIsNaN(res1))
            {
                ui->label_res->setVisible(false);                          //скрываем результат
                ui->label_error->setText("Ошибка! Число должно быть больше -1 и меньше 1.");
                ui->label_error->setVisible(true);                          //показываем ошибку
            }
            else
            {
                ui->label_error->setVisible(false);                         //скрываем сообщение об ошибке
                ui->label_res->setNum(res1);                                //вывод результата
                ui->label_res->setVisible(true);                            //показываем результат
            }
        }
        else
        {
            ui->label_res->setVisible(false);                               //скрываем результат
            ui->label_error->setText("Ошибка в аргументе");
            ui->label_error->setVisible(true);                              //показываем ошибку
        }
    }

    if(ui->radioButton_acos->isChecked())                                   //выбор arcos
    {
        double res1 = 0;
        str=ui->lineEdit_op_1->text();                                      //копируем в строку текст из поля 1
        op_1=str.toDouble(&fl1);                                            //пытаемся преобразовать 1 операнд в целостной тип данных и присваиваем число к соответствуещей переменной

        if(fl1)
        {
            res1=acos(op_1);
            if(qIsNaN(res1))
            {
                ui->label_res->setVisible(false);                           //скрываем результат
                ui->label_error->setText("Ошибка! Число должно быть больше -1 и меньше 1.");
                ui->label_error->setVisible(true);                          //показываем ошибку
            }
            else
            {
                ui->label_error->setVisible(false);                         //скрываем сообщение об ошибке
                ui->label_res->setNum(res1);                                //вывод результата
                ui->label_res->setVisible(true);                            //показываем результат
            }
        }
        else
        {
            ui->label_res->setVisible(false);                               //скрываем результат
            ui->label_error->setText("Ошибка в аргументе");
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
    ui->pushButton_result->setText("Cумма");
    ui->lineEdit_op_2->setVisible(true);
    ui->label_op_2->setVisible(true);
    ui->label_off->hide();
}

void MainWindow::on_radioButton_minus_clicked()                             //Замена подписей у операторов при вычитании
{
    ui->label_error->setVisible(false);
    ui->label_res->setVisible(false);
    ui->label_op_1->setText("Уменьшаемое");
    ui->label_op_2->setText("Вычитаемое");
    ui->pushButton_result->setText("Разность");
    ui->lineEdit_op_2->setVisible(true);
    ui->label_op_2->setVisible(true);
    ui->label_off->hide();
}

void MainWindow::on_radioButton_mult_clicked()                              //Замена подписей у операторов при умножении
{
    ui->label_error->setVisible(false);
    ui->label_res->setVisible(false);
    ui->label_op_1->setText("1-ый множитель");
    ui->label_op_2->setText("2-ой множитель");
    ui->pushButton_result->setText("Произведение");
    ui->lineEdit_op_2->setVisible(true);
    ui->label_op_2->setVisible(true);
    ui->label_off->hide();
}

void MainWindow::on_radioButton_div_clicked()                               //Замена подписей у операторов при делении
{
    ui->label_error->setVisible(false);
    ui->label_res->setVisible(false);
    ui->label_op_1->setText("Делимое");
    ui->label_op_2->setText("Делитель");
    ui->pushButton_result->setText("Частное");
    ui->lineEdit_op_2->setVisible(true);
    ui->label_op_2->setVisible(true);
    ui->label_off->hide();
}

void MainWindow::on_pushButton_clear_clicked()                              //очистка
{
    ui->lineEdit_op_1->clear();                                             //очистка op 1
    ui->lineEdit_op_2->clear();                                             //очистка op 2
    ui->label_res->clear();                                                 //очистка результата
    ui->label_error->clear();                                               //очистка ошибки
}

void MainWindow::on_radioButton_sqrt_clicked()                              //Замена подписей у операторов при корне
{
    ui->label_error->setVisible(false);
    ui->label_res->setVisible(false);
    ui->lineEdit_op_2->setVisible(false);
    ui->label_op_2->setVisible(false);
    ui->label_op_1->setText("Аргумент");
    ui->pushButton_result->setText("Результат");
}

void MainWindow::on_radioButton_sin_clicked()                              //Замена подписей у операторов при синусе
{
    ui->label_error->setVisible(false);
    ui->label_res->setVisible(false);
    ui->lineEdit_op_2->setVisible(false);
    ui->label_op_2->setVisible(false);
    ui->label_op_1->setText("Аргумент в рад");
    ui->pushButton_result->setText("Результат");
    ui->label_off->hide();
}

void MainWindow::on_radioButton_cos_clicked()                              //Замена подписей у операторов при косинусе
{
    ui->label_error->setVisible(false);
    ui->label_res->setVisible(false);
    ui->lineEdit_op_2->setVisible(false);
    ui->label_op_2->setVisible(false);
    ui->label_op_1->setText("Аргумент в рад");
    ui->pushButton_result->setText("Результат");
    ui->label_off->hide();
}

void MainWindow::on_radioButton_asin_clicked()                              //Замена подписей у операторов при обратном синусе
{
    ui->label_error->setVisible(false);
    ui->label_res->setVisible(false);
    ui->lineEdit_op_2->setVisible(false);
    ui->label_op_2->setVisible(false);
    ui->label_op_1->setText("Аргумент");
    ui->pushButton_result->setText("Результат");
    ui->label_off->show();
}

void MainWindow::on_radioButton_acos_clicked()                              //Замена подписей у операторов при обратном косинусе
{
    ui->label_error->setVisible(false);
    ui->label_res->setVisible(false);
    ui->lineEdit_op_2->setVisible(false);
    ui->label_op_2->setVisible(false);
    ui->label_op_1->setText("Аргумент");
    ui->pushButton_result->setText("Результат");
    ui->label_off->show();
}

