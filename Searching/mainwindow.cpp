#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox_row->setMaximum(MAX_MAS_SIZE);
    ui->spinBox_row->setMinimum(MIN_MAS_SIZE);
    ui->label_max->setVisible(false);
    ui->label_min->setVisible(false);
    ui->label_srednee->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)//проверка вводимых в таблицу значений
{
    bool fl;
    ui->tableWidget->item(row,column)->text().toDouble(&fl);
    if(fl&&!((qIsNaN(ui->tableWidget->item(row,column)->text().toDouble(&fl)))||(qIsInf(ui->tableWidget->item(row,column)->text().toDouble(&fl)))))
        ui->tableWidget->item(row,column)->setBackground(Qt::white); // setBackground
    else
        ui->tableWidget->item(row,column)->setBackground(Qt::red); // setBackground
    ui->tableWidget_2->clearContents();//очистка таблицы
}

void MainWindow::on_spinBox_row_valueChanged(int row)//спинбокс
{
    ui->tableWidget->setRowCount(row);
    ui->tableWidget_2->clearContents();
}


void MainWindow::on_pushButton_clear_clicked()//очистка
{
    ui->tableWidget->clearContents();//очистка таблицы
    ui->label_max->clear();//очистка мах
    ui->label_min->clear();//очистка мин
    ui->label_srednee->clear();//очистка сред
    ui->tableWidget_2->clearContents();//очистка таблицы
}


void MainWindow::on_pushButton_rand_clicked()//автозаполнение
{
    int row=ui->tableWidget->rowCount();
    ui->label_max->clear();//очистка мин
    ui->label_min->clear();
    ui->label_srednee->clear();
    ui->tableWidget_2->clearContents();//очистка таблицы

    double val;
    for (int i=0;i<row;i++)//идем по таблице
    {
        if (ui->tableWidget->item(i,0)==nullptr)//ячейка пустая
        {
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,0,ti); //помещаем ячейку в таблицу
        }
        ui->tableWidget->item(i,0)->setBackground(Qt::white);
        val=0.1*(rand()%2001-1000); // от -100 до 100
        mas_table1[i]=val;//присваиваем элементу рандомное значение
        ui->tableWidget->item(i,0)->setText(QString::number(val));//выводим рандомное значение
    }
}


void MainWindow::quick_sort(double *mas_table1,int row)//быстрая сортировка
{
    double razdel = mas_table1[row/2];//центральное значение
    int up=0;//начало
    int down=row-1;//конец
    do{
        while(mas_table1[up]<razdel)//пропускаем значения, если они в нужной половине
        {
            up++;
        }
        while(mas_table1[down]>razdel)//пропускаем значения, если они в нужной половине
        {
            down--;
        }
        if(up<=down)//если границы не совместились
        {
            double b = mas_table1[up]; // создали дополнительную переменную
            mas_table1[up] = mas_table1[down]; // меняем местами
            mas_table1[down] = b;
            up++;
            down--;
        }
    }
    while(up<=down);//пока границы не совместились

    if(down>0)//нижняя границыа больше нуля
        quick_sort(mas_table1, down+1);//рекурсия в верней половине
    if(up<row)//верхняя границыа меньше размера
        quick_sort(&mas_table1[up], row-up);//рекурсия в нижней половине
}



void MainWindow::rascheska(int row)//расческа сортировка
{
        int step=row;//задаем шаг
        int i;
        bool priznak_perest=true;//флаг перестановки
        while(step>1||priznak_perest)
        {
            if(step>1)
            {
                step= static_cast<int>(step/1.247);//
            }
            priznak_perest=false;
            i=0;
            while(i+step<row)
            {
                if(mas_table1[i]>mas_table1[i+step])//сравниваем  значения
                {
                    double b = mas_table1[i]; // создали дополнительную переменную
                    mas_table1[i] = mas_table1[i+step]; // меняем местами
                    mas_table1[i+step] = b;
                    priznak_perest=true;
                }
                i+=1;
            }
        }
    //}
}

void MainWindow::buble(int row)//пузырьковая сортировка
{
//    if(sorted(mas_table1,row))
//        QMessageBox::information(this,"Зачем?","Массив уже отсортирован");
//    else{
        int i=0;//первый элемент
        while (i<row-1) //пока первое число меньше размера
        {
            int j=i+1;
            while(j<row)//пока второе число меньше размера и не совместились в конце
            {
                if (mas_table1[i] > mas_table1[j])//сравниваем соседние значения
                {
                    double b = mas_table1[i]; // создали дополнительную переменную
                    mas_table1[i] = mas_table1[j]; // меняем местами
                    mas_table1[j] = b;
                }
                j=j+1;
            }
            i=i+1;
        }
    //}

}

void MainWindow::gnom(int row)//гномья сортировка
{
//    if(sorted(mas_table1,row))
//        QMessageBox::information(this,"Зачем?","Массив уже отсортирован");
//    else{
        int i=0;//первый элемент
        while(i<row)
        {
            if(i==0||mas_table1[i-1]<=mas_table1[i])//сравниваем соседние значения
                i+=1;
            else//если сверху больше чем снизу
            {
                int j=i-1;
                double b = mas_table1[i]; // создали переменную
                mas_table1[i] = mas_table1[j]; // меняем местами
                mas_table1[j] = b;
                i=j;
            }
        }
    //}

}

void MainWindow::monkey(int row)//обезьянья сортировка
{
    if(row<11&&!sorted(mas_table1,row))
    {
        int limit = 1000000;
        for(int i=1;i<limit;i++)//попытка отсортировать за limit раз
        {
            for(int j=0;j<row-1;j++)//проходим по таблице
            {
                int r=rand()%row;
                double b = mas_table1[j]; // создали дополнительную переменную
                mas_table1[j] = mas_table1[r]; // меняем местами
                mas_table1[r] = b;
            }
            if(sorted(mas_table1,row))
                break;
            else if (limit-1==i&&!sorted(mas_table1,row)) {
                QMessageBox::information(this,"Ошибка","Не получилось отсортивать массив за 100000 попыток");
            }
        }
    }
}

void MainWindow::on_pushButton_min_clicked()//поиск минимального
{
    int row=ui->tableWidget->rowCount();
    bool fl;//флаг успешной конвертации ячейки
    bool gl_fl=true;//фалг успешного создания массива
    for (int i=0;i<row;i++)//формирование массива
    {
        if (ui->tableWidget->item(i,0)==nullptr)//пустая ячейка
        {
            gl_fl=false;
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,0,ti); //помещаем ячейку в таблицу;
        }
        else
        {
            mas_table1[i]=ui->tableWidget->item(i,0)->text().toDouble(&fl);//конвертируем
            if(fl&&!((qIsNaN(mas_table1[i]))||(qIsInf(mas_table1[i]))))//если сконвертировано
            {
                ui->tableWidget->item(i,0)->setBackground(Qt::white);//красим ячейку в белый
            }

            else {

                gl_fl=false;
            }

        }
    }
    if(gl_fl)//cформировали правильно
    {
        double min=mas_table1[0];//делаем первое число минимумом
        int i=1;
        while (i<row)
        {
            if(min>mas_table1[i])
                min=mas_table1[i];//изменяем минимум, если он бошльше числа
            i++;
        }
        ui->label_min->setNum(min);
        ui->label_min->setVisible(true);
    }
    else {
        QMessageBox::information(this,"Ошибка","В таблице некоректное значение.");
        err_str();
        ui->label_max->clear();
        ui->label_min->clear();
        ui->label_srednee->clear();
    }
}

void MainWindow::on_pushButton_srednee_clicked()//поиск среднего
{
    int row=ui->tableWidget->rowCount();
    bool fl;//флаг успешной конвертации ячейки
    bool gl_fl=true;//фалг успешного создания массива
    for (int i=0;i<row;i++)//формирование массива
    {
        if (ui->tableWidget->item(i,0)==nullptr)//пустая ячейка
        {
            gl_fl=false;
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,0,ti); //помещаем ячейку в таблицу;
        }
        else
        {
            mas_table1[i]=ui->tableWidget->item(i,0)->text().toDouble(&fl);//конвертируем
            if(fl&&!((qIsNaN(mas_table1[i]))||(qIsInf(mas_table1[i]))))//если сконвертировано
            {
                ui->tableWidget->item(i,0)->setBackground(Qt::white);//красим ячейку в белый
            }

            else {

                gl_fl=false;

            }

        }
    }
    if(gl_fl)
    {
        double srednee=0;
        double sr;
        for (int i=0;i<row;i++)
        {
            srednee+=mas_table1[i];//считаем сумму всего массива
        }
        sr=srednee/row;//среднее арифметическое

        ui->label_srednee->setNum(sr);
        ui->label_srednee->setVisible(true);
    }
    else
    {
        QMessageBox::information(this,"Ошибка","В таблице некоректное значение.");
        err_str();
        ui->label_max->clear();
        ui->label_min->clear();
        ui->label_srednee->clear();
    }
}

void MainWindow::on_pushButton_max_clicked()
{
    int row=ui->tableWidget->rowCount();
    bool fl;//флаг успешной конвертации ячейки
    bool gl_fl=true;//фалг успешного создания массива
    for (int i=0;i<row;i++)//формирование массива
    {
        if (ui->tableWidget->item(i,0)==nullptr)//пустая ячейка
        {
            gl_fl=false;
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,0,ti); //помещаем ячейку в таблицу;
        }
        else
        {
            mas_table1[i]=ui->tableWidget->item(i,0)->text().toDouble(&fl);//конвертируем
            if(fl&&!((qIsNaN(mas_table1[i]))||(qIsInf(mas_table1[i]))))//если сконвертировано
            {
                ui->tableWidget->item(i,0)->setBackground(Qt::white);//красим ячейку в белый
            }

            else
            {

                gl_fl=false;
            }
        }
    }
    if(gl_fl)
    {
        double max=mas_table1[0];//делаем первое число максимумом
        int i=1;
        while (i<row)
        {
            if(max<mas_table1[i])
                max=mas_table1[i];//изменяем максимум, если он меньше числа
            i+=1;
        }
        ui->label_max->setNum(max);
        ui->label_max->setVisible(true);
    }
    else {
        QMessageBox::information(this,"Ошибка","В таблице некоректное значение.");
        err_str();
        ui->label_max->clear();
        ui->label_min->clear();
        ui->label_srednee->clear();
    }
}


void MainWindow::err_str()//подсветка строки с ошибкой
{
    int row=ui->tableWidget->rowCount();
    int err=row;
    bool fl=true;

    for (int i=row-1;i>-1;i--)//идем по таблице
    {
        if (ui->tableWidget->item(i,0)==nullptr)//пустая ячейка
            err=i;
        else {
            mas_table1[i]=ui->tableWidget->item(i,0)->text().toDouble(&fl);//преобразовали в число
            if(fl&&!((qIsNaN(mas_table1[i]))||(qIsInf(mas_table1[i]))))//если преобразовалось и не нан
            {
                err=row;//все хорошо
            }

            else {
                err=i;//записываем номер строки
                fl=false;
            }


        }
        if(err<row)//если были ошибочные строки
            ui->tableWidget->setCurrentCell(err,0);//подсветили строку с ошибкой
    }
}


bool MainWindow::sorted(double *mas_table1,int row)
{
    for (int i=0;i<row-1;i++)
    {
        if(mas_table1[i]>mas_table1[i+1])//проверяем порядок элементов
        {
            return false;
        }
    }
    return true;
}
void MainWindow::on_pushButton_sort_clicked()//выполнение сортировки
{
    int row=ui->tableWidget->rowCount();
    bool fl;//флаг успешной конвертации ячейки
    bool gl_fl=true;//фалг успешного создания массива
    for (int i=0;i<row;i++)//формирование массива
    {
        if (ui->tableWidget->item(i,0)==nullptr)//пустая ячейка
        {
            gl_fl=false;
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,0,ti); //помещаем ячейку в таблицу;
        }
        else
        {
            mas_table1[i]=ui->tableWidget->item(i,0)->text().toDouble(&fl);//конвертируем
            if(fl&&!((qIsNaN(mas_table1[i]))||(qIsInf(mas_table1[i]))))//если сконвертировано
            {
                ui->tableWidget->item(i,0)->setBackground(Qt::white);//красим ячейку в белый
            }

            else {

                gl_fl=false;
            }

        }
    }
    if(gl_fl&&row!=1)//if массив сформирован правильно
    {

        int sposob=ui->comboBox_sort->currentIndex();
        switch (sposob)
        {
        case 0:
        {
            quick_sort(mas_table1,row);
            break;
        }
        case 1:
        {
            rascheska(row);
            break;
        }
        case 2:
        {
            buble(row);
            break;
        }
        case 3:
        {
            gnom(row);
            break;
        }
        case 4:
        {
            monkey(row);
            break;
        }
        default:
        {
            quick_sort(mas_table1,row);
            break;
        }
        }
        for (int i=0;i<row;i++)//заполнение таблицы без проверки т.к. глфл=тру
            ui->tableWidget->item(i,0)->setText(QString::number(mas_table1[i]));
    }
    else if (gl_fl&&row==1) {
        QMessageBox::information(this,"Зачем?","Зачем сортировать одно число?!?!?");

    }
    else {
        QMessageBox::information(this,"Ошибка","В таблице некоректное значение.");
        err_str();
        ui->label_max->clear();//очистка мин
        ui->label_min->clear();
        ui->label_srednee->clear();
    }


}


void MainWindow::on_lineEdit_poisk_textChanged()//поиск
{
    QPalette pal=ui->lineEdit_poisk->palette();
    QColor red;
    QColor white;
    red.setRgb(227,38,54);
    white.setRgb(0,0,0);
    bool fl;
    double num=ui->lineEdit_poisk->text().toDouble(&fl);
    if(fl&!((qIsNaN(num))||(qIsInf(num))))
    {
        pal.setColor(QPalette::Text,white);
        ui->lineEdit_poisk->setPalette(pal);
    }
    else {
        pal.setColor(QPalette::Text,red);
        ui->lineEdit_poisk->setPalette(pal);
    }

}

void MainWindow::on_pushButton_addrow_clicked()//Добавиление строки
{
    ui->spinBox_row->setValue(ui->spinBox_row->value()+1);
}

void MainWindow::on_pushButton_delrow_clicked()//Удаление строки
{
    ui->spinBox_row->setValue(ui->spinBox_row->value()-1);
}

void MainWindow::on_pushButton_poisk_clicked()
{
    QPalette pal=ui->lineEdit_poisk->palette();
    QColor red;
    QColor white;
    red.setRgb(227,38,54);
    white.setRgb(0,0,0);
    int row=ui->tableWidget->rowCount();
    bool fl;//флаг успешной конвертации ячейки
    bool gl_fl=true;//фалг успешного создания массива
    for (int i=0;i<row;i++)//формирование массива
    {
        if (ui->tableWidget->item(i,0)==nullptr)//пустая ячейка
        {
            gl_fl=false;
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,0,ti); //помещаем ячейку в таблицу;
        }
        else
        {
            mas_table1[i]=ui->tableWidget->item(i,0)->text().toDouble(&fl);//конвертируем
            if(fl&&!((qIsNaN(mas_table1[i]))||(qIsInf(mas_table1[i]))))//если сконвертировано
            {
                ui->tableWidget->item(i,0)->setBackground(Qt::white);//красим ячейку в белый
            }

            else {

                gl_fl=false;
            }

        }
    }
    if(gl_fl)
    {
        bool flp;
        int n = 0;//колво подходящих элементов
        double num=ui->lineEdit_poisk->text().toDouble(&flp);//считали и преобразовываем искомое число
        if(flp&&!((qIsNaN(num))||(qIsInf(num))))//если вещественное число
        {
            if(!sorted(mas_table1,row))//если массив неотсортирован
            {
                int index[row];// массив для хранения индексов ячеек
                for (int i=0;i<row;i++)//идем по таблице
                {
                    if(fabs(mas_table1[i]-num)<1e-10)//и сравниваем каждое число с искомым
                    {
                        index[n++]=i;
                    }
                }
                if(n!=0)
                {
                    ui->tableWidget_2->setRowCount(n);
                    for(int i=0;i<n;i++)
                    {
                        // ui->label__index_ans->setText(int(index[i]).toString())
                        if (ui->tableWidget_2->item(i,0)==nullptr)//ячейка пустая
                        {
                            QTableWidgetItem * ti; //создали указатель
                            ti =  new QTableWidgetItem(); //выделяем память
                            ui->tableWidget_2->setItem(i,0,ti); //помещаем ячейку в таблицу
                        }
                        ui->tableWidget_2->item(i,0)->setBackground(Qt::white);
                        ui->tableWidget_2->item(i,0)->setText(QString::number(index[i] + 1));//выводим рандомное значение
                    }
                }
                else
                {
                    QMessageBox::information(this,"Ошибка","В массиве нет такого числа, введите другое число",QMessageBox::Ok);
                }
            }
            else {
                int n=0;//номер числа
                int index[row];
                int left=0;//левая граница
                int right=row;//правая граница
                while(right - left > 1)
                {
                    int mid = (right + left) / 2;
                    if(num-mas_table1[mid]>1e-10)
                        left=mid;
                    else
                        right=mid;

                }
                int i = (fabs(mas_table1[left] - num) < 1e-10) ? left : right;
                while (fabs(mas_table1[i] - num) < 1e-10) {
                    index[n++]=i;
                }
                if(n!=0)
                {
                    ui->tableWidget_2->setRowCount(n);
                    for(int i=0;i<n;i++)
                    {
                        // ui->label__index_ans->setText(int(index[i]).toString())
                        if (ui->tableWidget_2->item(i,0)==nullptr)//ячейка пустая
                        {
                            QTableWidgetItem * ti; //создали указатель
                            ti =  new QTableWidgetItem(); //выделяем память
                            ui->tableWidget_2->setItem(i,0,ti); //помещаем ячейку в таблицу
                        }
                        ui->tableWidget_2->item(i,0)->setBackground(Qt::white);
                        ui->tableWidget_2->item(i,0)->setText(QString::number(index[i]+1));//выводим рандомное значение
                    }
                }
                else {
                    QMessageBox::information(this,"Ошибка","В массиве нет такого числа, введите другое число",QMessageBox::Ok);
                }
            }
            on_lineEdit_poisk_textChanged();
        }

        else
        {
            QMessageBox::information(this,"Ошибка","Неверное значение искомого числа",QMessageBox::Ok);
            on_lineEdit_poisk_textChanged();

        }
    }
    else {
        QMessageBox::information(this,"Ошибка","В таблице некоректное значение.",QMessageBox::Ok);
        err_str();
        ui->label_max->clear();
        ui->label_min->clear();
        ui->label_srednee->clear();
        ui->label_poisk->clear();
        ui->label_kolvo_ans->clear();
        ui->tableWidget_2->clearContents();//очистка таблицы
    }

}
