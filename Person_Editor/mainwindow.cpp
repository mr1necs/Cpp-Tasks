#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui -> pushButton_clr -> click();
    ui -> lineEdit_scr_lft -> setReadOnly(true);                        //запрещаем пользователю изменять максимальное колличество очков

                                            //Ограничения по характеристике "Сила" для рас
    mas_str_value[0][0] = 2;                // люди
    mas_str_value[0][1] = 10;               // люди
    mas_str_value[1][0] = 1;                // хоббиты
    mas_str_value[1][1] = 8;                // хоббиты
    mas_str_value[2][0] = 1;                // гномы
    mas_str_value[2][1] = 6;                // гномы
    mas_str_value[3][0] = 5;                // орки
    mas_str_value[3][1] = 15;               // орки

                                            //Ограничение по характеристике "Ловкость" для рас
    mas_dex_value[0][0] = 1;                // люди
    mas_dex_value[0][1] = 10;               // люди
    mas_dex_value[1][0] = 1;                // хоббиты
    mas_dex_value[1][1] = 12;               // хоббиты
    mas_dex_value[2][0] = 1;                // гномы
    mas_dex_value[2][1] = 8;                // гномы
    mas_dex_value[3][0] = 1;                // орки
    mas_dex_value[3][1] = 8;                // орки

                                            //Ограничение по характеристике "Интелект" для рас
    mas_in_value[0][0] = 1;                 // люди
    mas_in_value[0][1] = 10;                // люди
    mas_in_value[1][0] = 1;                 // хоббиты
    mas_in_value[1][1] = 10;                // хоббиты
    mas_in_value[2][0] = 5;                 // гномы
    mas_in_value[2][1] = 15;                // гномы
    mas_in_value[3][0] = 1;                 // орки
    mas_in_value[3][1] = 5;                 // орки

                                            //Ограничение по характеристике "Удача" для рас
    mas_luck_value[0][0] = 3;               // люди
    mas_luck_value[0][1] = 15;              // люди
    mas_luck_value[1][0] = 1;               // хоббиты
    mas_luck_value[1][1] = 10;              // хоббиты
    mas_luck_value[2][0] = 3;               // гномы
    mas_luck_value[2][1] = 12;              // гномы
    mas_luck_value[3][0] = 1;               // орки
    mas_luck_value[3][1] = 5;               // орки

    mas_gender[0][0]="Красавец";
    mas_gender[0][1]="Лазутчик";
    mas_gender[0][2]="Чернокнижник";
    mas_gender[0][3]="Удачливый парнишка";
    mas_gender[0][4]="Воин";
    mas_gender[0][5]="Наемник";
    mas_gender[0][6]="Боевой маг";
    mas_gender[0][7]="Проворный маг";
    mas_gender[0][8]="Вор";
    mas_gender[0][9]="Плут";
    mas_gender[0][10]="Алхимик";
    mas_gender[0][11]="Мудрец";
    mas_gender[0][12]="Обаятельный везунчик";
    mas_gender[0][13]="Обыкновенный работяга";

    mas_gender[1][0]="Красавица";
    mas_gender[1][1]="Лазутчица";
    mas_gender[1][2]="Чернокнижница";
    mas_gender[1][3]="Удачливая девица";
    mas_gender[1][4]="Воительница";
    mas_gender[1][5]="Наемница";
    mas_gender[1][6]="Боевая ведьма";
    mas_gender[1][7]="Проворная чародейка";
    mas_gender[1][8]="Воровка";
    mas_gender[1][9]="Плутовка";
    mas_gender[1][10]="Женщина-алхимик";
    mas_gender[1][11]="Ведунья";
    mas_gender[1][12]="Везучая красотка";
    mas_gender[1][13]="Обыкновенная работяга";

    ui -> lineEdit_name -> setMaxLength(20);              // макс длина вводимого текста в name
    ui -> lineEdit_str -> setMaxLength(2);                // макс длина вводимого текста в "Сила"
    ui -> lineEdit_ag -> setMaxLength(2);                 // макс длина вводимого текста в "Ловкость"
    ui -> lineEdit_iq -> setMaxLength(2);                 // макс длина вводимого текста в "Интелект"
    ui -> lineEdit_charm -> setMaxLength(2);              // макс длина вводимого текста в "Харизма"
    ui -> lineEdit_luck -> setMaxLength(2);               // макс длина вводимого текста в "Удача"
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clr_clicked()              // очистка введеных данных
{
    ui -> lineEdit_name -> clear();
    ui -> lineEdit_ag -> clear();
    ui -> lineEdit_str -> clear();
    ui -> lineEdit_iq -> clear();
    ui -> lineEdit_luck -> clear();
    ui -> lineEdit_charm -> clear();

    ui -> lineEdit_scr_lft -> setText("25");

    ui -> label_hp_val -> clear();
    ui -> label_mp_val -> clear();
    ui -> label_atk_val -> clear();
    ui -> label_def_val -> clear();
    ui -> label_class_val -> clear();
    ui -> label_priv_val ->  clear();
    ui -> radioButton_sex_m -> setChecked(true);

}

void MainWindow::on_pushButton_create_clicked()             //характеристики
{
    int str, dex, in, luck, har;                            // характеристики
    QString name;                                           // имя персанажа
    int dlina;                                              // длина имени
    bool fl;                                                // признак успешной генерации
    int kod_race = ui -> comboBox_race -> currentIndex();


    name = ui ->lineEdit_name -> text();
    dlina = name.length();                                  //длина строки
    if((dlina < 3)||(dlina > 20))
    {
        fl = false;
        QMessageBox::information(this,"Ошибка","Имя должно быть длиной от 3 до 25.",QMessageBox::Ok);
    }
    else
        fl = true;


    str = 0;
    dex = 0;
    in = 0;
    luck = 0;

    if(fl)                                                  // проверка параметра "Сила"
    {
        str = ui -> lineEdit_str -> text().toInt(&fl);
        if(fl)                                              // вместо вложенных if
        {
            if((str < mas_str_value[kod_race][0]) || (str > mas_str_value[kod_race][1]))
            {
                fl = false;
                QMessageBox::information(this,"Ошибка","Параметр \"Сила\" должен быть от " + QString::number(mas_str_value[kod_race][0]) + " до " + QString::number(mas_str_value[kod_race][1]) + ".", QMessageBox::Ok);
            }
        }
        else
            QMessageBox::information(this,"Ошибка","Неверное значение параметра \"Сила\"",QMessageBox::Ok);
    }
    if(fl)
    {                                                       // проверка параметра "Ловкость"
        dex = ui -> lineEdit_ag -> text().toInt(&fl);
        if(fl)                                              //вместо вложенных if
        {
            if((dex < mas_dex_value[kod_race][0]) || (dex > mas_dex_value[kod_race][1]))
            {
                fl = false;
                QMessageBox::information(this,"Ошибка","Параметр \"Ловкость\" должен быть от " + QString::number(mas_dex_value[kod_race][0]) + " до " + QString::number(mas_dex_value[kod_race][1]) + ".", QMessageBox::Ok);
            }
        }
        else
            QMessageBox::information(this,"Ошибка","Неверное значение параметра \"Ловкость\".",QMessageBox::Ok);
    }
    if(fl)
    {
                                                            // проверка параметра "Интелект"
        in = ui -> lineEdit_iq -> text().toInt(&fl);
        if(fl)                                              //вместо вложенных if
        {
            if((in < mas_in_value[kod_race][0]) || (in > mas_in_value[kod_race][1]))
            {
                fl = false;
                QMessageBox::information(this,"Ошибка","Параметр \"Интелект\" должен быть от " + QString::number(mas_in_value[kod_race][0]) + " до " + QString::number(mas_in_value[kod_race][1]) + ".", QMessageBox::Ok);
            }
        }
        else
            QMessageBox::information(this,"Ошибка","Неверное значение параметра \"Интелект\".",QMessageBox::Ok);
    }

    if(fl)
    {
                                                            // проверка параметра "Харизма"
        har = ui -> lineEdit_charm -> text().toInt(&fl);
        if(fl)                                              //вместо вложенных if
        {
            if((har < 0) || (har > 11))
            {
                fl = false;
                QMessageBox::information(this,"Ошибка","Параметр \"Харизма\" должен быть от 1 до 10.", QMessageBox::Ok);
            }
        }
        else
            QMessageBox::information(this,"Ошибка","Неверное значение параметра \"Харизма\".",QMessageBox::Ok);
    }

    if(fl)
    {
                                                            // проверка параметра "Удача"
        luck = ui -> lineEdit_luck -> text().toInt(&fl);
        if(fl)                                              //вместо вложенных if
        {
            if((luck < mas_luck_value[kod_race][0]) || (luck > mas_luck_value[kod_race][1]))
            {
                fl = false;
                QMessageBox::information(this,"Ошибка","Параметр \"Удача\" должен быть от " + QString::number(mas_luck_value[kod_race][0]) + " до " + QString::number(mas_luck_value[kod_race][1]) + ".", QMessageBox::Ok);
            }
        }
        else
            QMessageBox::information(this,"Ошибка","Неверное значение параметра \"Удача\".",QMessageBox::Ok);
    }

    if(fl)                                                  //счетчик
    {
        int scr_lft = 25 - str - dex - in - luck - har;
        ui -> lineEdit_scr_lft -> setText(QString::number(scr_lft));
        if(scr_lft < 0)
        {
            fl = false;
            QMessageBox::information(this,"Ошибка","Нельзя потратить больше 25 очков",QMessageBox::Ok);
        }

        else
        {
            if(scr_lft > 0)
            {
                fl = false;
                QMessageBox::information(this,"Ошибка","Нужно потратить все очки",QMessageBox::Ok);
            }
        }
    }
    if(fl)                                                  // вывод получившихся характеристик
    {
        int hp, mp, def, atk, priv, kod_gender = 0;
        def = 6 * str + 2 * dex + 2 * luck;                 // защита
        atk = 7 * dex + 3 * luck + 2 * str;                 // атака
        hp = 8 * str + 2 * def;                             // здоровье
        mp = 8 * in + dex + luck;                           // мана
        priv = 3 * str + dex + 3 * in + 2 * luck + 3 * har; // привлекательность


        ui -> label_hp_val -> setNum(hp);
        ui -> label_mp_val -> setNum(mp);
        ui -> label_def_val -> setNum(def);
        ui -> label_atk_val -> setNum(atk);
        ui -> label_priv_val -> setNum(priv);

        if((str>7&&dex<8&&in<8&&luck<8&&har<8)||(str>7&&luck>7&&in<8&&dex<8&&har<8))
            ui->label_class_val->setText(mas_gender[function_gender(kod_gender)][0]);           //воин

        if(dex>7&&str<8&&in<8&&luck<8&&har<8)
            ui->label_class_val->setText(mas_gender[function_gender(kod_gender)][1]);           //Лазутчик

        if(in>7&&dex<8&&str<8&&luck<8&&har<8)
            ui->label_class_val->setText(mas_gender[function_gender(kod_gender)][2]);           //Чернокнижник

        if(luck>7&&dex<8&&in<8&&str<8&&har<8)
            ui->label_class_val->setText(mas_gender[function_gender(kod_gender)][3]);           //Удачливый хлопец

        if((har>7&&dex<8&&in<8&&luck<8&&str<8)||(str>7&&har>7&&in<8&&luck<8&&dex<8))
            ui->label_class_val->setText(mas_gender[function_gender(kod_gender)][4]);           //Красавец

        if(str>7&&dex>7&&in<8&&luck<8&&har<8)
            ui->label_class_val->setText(mas_gender[function_gender(kod_gender)][5]);           //Наемник

        if(str>7&&in>7&&dex<8&&luck<8&&har<8)
            ui->label_class_val->setText(mas_gender[function_gender(kod_gender)][6]);           //Боевой-маг

        if(dex>7&&in>7&&str<8&&luck<8&&har<8)
            ui->label_class_val->setText(mas_gender[function_gender(kod_gender)][7]);           //Проворный  маг

        if(dex>7&&luck>7&&in<8&&str<8&&har<8)
            ui->label_class_val->setText(mas_gender[function_gender(kod_gender)][8]);           //Вор

        if(dex>7&&har>7&&in<8&&str<8&&luck<8)
            ui->label_class_val->setText(mas_gender[function_gender(kod_gender)][9]);           //Плут

        if(in>7&&luck>7&&str<8&&dex<8&&har<8)
            ui->label_class_val->setText(mas_gender[function_gender(kod_gender)][10]);          //Алхимик

        if(in>7&&har>7&&str<8&&dex<8&&luck<8)
            ui->label_class_val->setText(mas_gender[function_gender(kod_gender)][11]);          //Мудрец

        if(luck>7&&har>7&&str<8&&dex<8&&in<8)
            ui->label_class_val->setText(mas_gender[function_gender(kod_gender)][12]);          //Обаятельный везунчик

        if(in<8&&dex<8&&str<8&&luck<8&&har<8)
            ui->label_class_val->setText(mas_gender[function_gender(kod_gender)][13]);          //Работяга
    }
    else                                                    //очистка
    {
        ui -> label_hp_val -> clear();
        ui -> label_mp_val -> clear();
        ui -> label_atk_val -> clear();
        ui -> label_def_val -> clear();
        ui->label_priv_val->clear();
        ui -> label_class_val -> clear();
    }
}

int MainWindow::function_gender(int kod_gender)             //Гендер
{
    if (ui->radioButton_sex_w->isChecked())
        kod_gender = 1;
    else
        kod_gender = 0;
    return kod_gender;
}



void MainWindow::on_lineEdit_name_textChanged(const QString &)              //Окраска Имени
{
    int dlina=ui->lineEdit_name->text().length();

    QPalette pal=ui->lineEdit_name->palette();                              //Окраска имени в красный, если имя меньше 3 и больше 20

    if((dlina < 3)||(dlina > 20))
    {
        pal.setColor(QPalette::Text,Qt::red);                               //Окраска в красный
    }
    else
    {
        pal.setColor(QPalette::Text,Qt::green);                             //Окраска в зеленый
    }
    ui->lineEdit_name->setPalette(pal);
}

void MainWindow::on_lineEdit_str_textChanged(const QString &                )//Окраска характеристики Сила
{
    int val = ui->lineEdit_str->text().toInt();
    int race_index = ui->comboBox_race->currentIndex();
    //Палитра цветов
    QPalette pal_line = ui->lineEdit_str->palette();
    QPalette pal_lable = ui->label_str->palette();
    QColor col_green, col_orange, col_black;
    col_green.setRgb(34, 139, 34);//RGB цвет
    col_orange.setRgb(255, 140, 0);//RGB цвет
    col_black.setRgb(0, 0, 0);//RGB цвет
    //Окраска
    if((val < mas_str_value[race_index][0])||(val > mas_str_value[race_index][1]))
        pal_lable.setColor(QPalette::WindowText, col_black);
    else if ((val >= 0)&&(val < 4))
        pal_lable.setColor(QPalette::WindowText,Qt::red);
    else if ((val >= 4)&&(val < 8))
        pal_lable.setColor(QPalette::WindowText,col_orange);
    else
        pal_lable.setColor(QPalette::WindowText,col_green);
    ui->label_str->setPalette(pal_lable);

    if(val < mas_str_value[race_index][0])
        pal_line.setColor(QPalette::Text,Qt::red);
    else if (val > mas_str_value[race_index][1])
        pal_line.setColor(QPalette::Text, Qt::red);
    else
        pal_line.setColor(QPalette::Text,col_green);
    ui->lineEdit_str->setPalette(pal_line);
    calc_score_left();
}

void MainWindow::on_lineEdit_ag_textChanged(const QString &)//Окраска характеристики Ловкость
{
    int val = ui->lineEdit_ag->text().toInt();
    int race_index = ui->comboBox_race->currentIndex();
    //Палитра цветов
    QPalette pal_line = ui->lineEdit_ag->palette();
    QPalette pal_lable = ui->label_dex->palette();
    QColor col_green, col_orange, col_black;
    col_green.setRgb(34, 139, 34);
    col_orange.setRgb(255, 140, 0);
    col_black.setRgb(0, 0, 0);
    //Окраска
    if((val < mas_dex_value[race_index][0])||(val > mas_dex_value[race_index][1]))
        pal_lable.setColor(QPalette::WindowText, col_black);
    else if ((val >= 0)&&(val < 4))
        pal_lable.setColor(QPalette::WindowText,Qt::red);
    else if ((val >= 4)&&(val < 8))
        pal_lable.setColor(QPalette::WindowText,col_orange);
    else
        pal_lable.setColor(QPalette::WindowText,col_green);
    ui->label_dex->setPalette(pal_lable);

    if((val < mas_dex_value[race_index][0])||(val > mas_dex_value[race_index][1]))
        pal_line.setColor(QPalette::Text,Qt::red);
    else
        pal_line.setColor(QPalette::Text,col_green);
    ui->lineEdit_ag->setPalette(pal_line);
    calc_score_left();
}

void MainWindow::on_lineEdit_iq_textChanged(const QString &)//Окраска характеристики Интелект
{
    int val = ui->lineEdit_iq->text().toInt();
    int race_index = ui->comboBox_race->currentIndex();
    //Палитра цветов
    QPalette pal_line = ui->lineEdit_iq->palette();
    QPalette pal_lable = ui->label_in->palette();
    QColor col_green, col_orange, col_black;
    col_green.setRgb(34, 139, 34);
    col_orange.setRgb(255, 140, 0);
    col_black.setRgb(0, 0, 0);
    //Окраска
    if((val < mas_in_value[race_index][0])||(val > mas_in_value[race_index][1]))
        pal_lable.setColor(QPalette::WindowText, col_black);
    else if ((val >= 0)&&(val < 4))
        pal_lable.setColor(QPalette::WindowText,Qt::red);
    else if ((val >= 4)&&(val < 8))
        pal_lable.setColor(QPalette::WindowText,col_orange);
    else
        pal_lable.setColor(QPalette::WindowText,col_green);
    ui->label_in->setPalette(pal_lable);

    if((val < mas_in_value[race_index][0])||(val > mas_in_value[race_index][1]))
        pal_line.setColor(QPalette::Text,Qt::red);
    else
        pal_line.setColor(QPalette::Text,col_green);
    ui->lineEdit_iq->setPalette(pal_line);
    calc_score_left();
}

void MainWindow::on_lineEdit_charm_textChanged(const QString &)//Окраска характеристики Харизма
{
    int val = ui->lineEdit_charm ->text().toInt();

    QPalette pal = ui->lineEdit_charm ->palette();
    QPalette pal_lable = ui->label_har->palette();
    QColor col_green, col_orange;
    col_green.setRgb(9,171,63);
    col_orange.setRgb(228,160,16);

    if((val <= 0)||(val > 10))       // введенное значение не удовлетворяет параметрам
        pal_lable.setColor(QPalette::WindowText,Qt::black);
    else if ((val >= 1)&&(val < 4))  // светфор - цвет красный, низкий показатель
        pal_lable.setColor(QPalette::WindowText,Qt::red);
    else if ((val >= 4)&&(val < 8)) // светфор - цвет оранжевый, хороший показатель
        pal_lable.setColor(QPalette::WindowText,col_orange);
    else if((val >= 8)&&(val <= 10))// светфор - цвет зеленый, высокий показатель
        pal_lable.setColor(QPalette::WindowText,col_green);
    ui->label_har->setPalette(pal_lable);

    if((val <= 0)||(val > 10)) // введенное значение не удовлетворяет параметрам
        pal.setColor(QPalette::Text,Qt::red);
    else                    // введенное значение удовлетворяет параметрам
        pal.setColor(QPalette::Text,col_green);
    ui->lineEdit_charm ->setPalette(pal);

    calc_score_left();
}

void MainWindow::on_lineEdit_luck_textChanged(const QString &)//Окраска характеристики Удача
{
    int val = ui->lineEdit_luck->text().toInt();
    int race_index = ui->comboBox_race->currentIndex();
    //Палитра цветов
    QPalette pal_line = ui->lineEdit_luck->palette();
    QPalette pal_lable = ui->label_luck->palette();
    QColor col_green, col_orange, col_black;
    col_green.setRgb(34, 139, 34);
    col_orange.setRgb(255, 140, 0);
    col_black.setRgb(0, 0, 0);
    //Окраска
    if((val < mas_luck_value[race_index][0])||(val > mas_luck_value[race_index][1]))
        pal_lable.setColor(QPalette::WindowText, col_black);
    else if ((val >= 0)&&(val < 4))
        pal_lable.setColor(QPalette::WindowText,Qt::red);
    else if ((val >= 4)&&(val < 8))
        pal_lable.setColor(QPalette::WindowText,col_orange);
    else
        pal_lable.setColor(QPalette::WindowText,col_green);
    ui->label_luck->setPalette(pal_lable);

    if((val < mas_luck_value[race_index][0])||(val > mas_luck_value[race_index][1]))
        pal_line.setColor(QPalette::Text,Qt::red);
    else
        pal_line.setColor(QPalette::Text,col_green);
    ui->lineEdit_luck->setPalette(pal_line);
    calc_score_left();
}

void MainWindow::on_comboBox_race_currentIndexChanged()//Вызывает функции характеристик после изменения расы
{
    const QString arg1;
    on_lineEdit_luck_textChanged(arg1);
    on_lineEdit_str_textChanged(arg1);
    on_lineEdit_ag_textChanged(arg1);
    on_lineEdit_iq_textChanged(arg1);
    on_lineEdit_charm_textChanged(arg1);
}

void MainWindow::calc_score_left() //функция расчета остатков очков
{
    int str, dex, in, luck, scr_lft, har;

    str = ui -> lineEdit_str -> text().toInt();
    dex = ui -> lineEdit_ag -> text().toInt();
    in = ui -> lineEdit_iq -> text().toInt();
    luck = ui -> lineEdit_luck -> text().toInt();
    har = ui -> lineEdit_charm -> text().toInt();

    scr_lft = 25 - str - dex - in - luck - har;

    QPalette pal = ui->lineEdit_str->palette();
    QColor col;
    col.setRgb(34, 139, 34);

    if(scr_lft != 0)
        pal.setColor(QPalette::Text,Qt::red);
    else
        pal.setColor(QPalette::Text,col);
    ui->lineEdit_scr_lft->setPalette(pal);
    ui->lineEdit_scr_lft->setText(QString::number(scr_lft));
}


