#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    no_auto_change=true;
    ui->spinBox->setMaximum(MAX_MAS_SIZE);
    ui->radioButton_puz->click();
    ui->label_max->clear();
    ui->label_mid->clear();
    ui->label_min->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::fast_sort(int a, int b)                //Быстрая сортировка
{
    int l =a;
    int r =b;
    double mid=mas_table[(r+l)/2];
    double t=0;
    while (l<=r)
    {
        while (mas_table[l]>mid)
            l++;
        while(mas_table[r]<mid)
            r--;
        if(l<=r)
        {
            t=mas_table[l];
            mas_table[l]=mas_table[r];
            mas_table[r]=t;
            l++;
            r--;
        }
    }
    if(a<r)
        fast_sort(a,r);
    if(b>l)
        fast_sort(l,b);

}
void MainWindow::check_input()                          //Проверка данных на вводе

{
    gl_flag=true;
    no_auto_change=false;
    bool flag;

    int row=ui->tableWidget->rowCount();
    for( int i=0;i<row;i++)
    {
        if (ui->tableWidget->item(i,0)==nullptr)
        {
            QTableWidgetItem * ti;                      //Создаем указатель на ячейку
            ti = new QTableWidgetItem;                  //Выделяем память
            ui->tableWidget->setItem(i,0,ti);           //Помещаем ячейку в таблицу
            QBrush br;
            br.setColor(Qt::white);
            br.setStyle(Qt::DiagCrossPattern);
            ui->tableWidget->item(i,0)->setBackground(Qt::red);
            if(gl_flag)
                table_pos=i;
            gl_flag=false;
        }
        else
        {
            mas_table[i]=ui->tableWidget->item(i,0)->text().toDouble(&flag);
            if (!flag||qIsInf(mas_table[i])||qIsNaN(mas_table[i]))
            {
                QBrush br;
                br.setColor(Qt::white);
                br.setStyle(Qt::DiagCrossPattern);
                ui->tableWidget->item(i,0)->setBackground(Qt::red);
                if(gl_flag)
                    table_pos=i;
                gl_flag=false;
            }
            else
            {
                QBrush br;
                br.setColor(Qt::white);
                br.setStyle(Qt::DiagCrossPattern);
                ui->tableWidget->item(i,0)->setBackground(Qt::white);
            }
        }
    }
}

void MainWindow::mas_peretasovka(double mas[MAX_MAS_SIZE])      //Случайная перестановка элементов в массиве
{
    int row=ui->tableWidget->rowCount();
    int index;
    double t;
    for(int i=0;i<row;i++)
    {
        index=rand()%row;
        t=mas[i];
        mas[i]=mas[index];
        mas[index]=t;
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)              //Изменение спинбокса
{
    ui->tableWidget->setRowCount(arg1);
    ui->label_max->clear();
    ui->label_mid->clear();
    ui->label_min->clear();
}

void MainWindow::on_pushButton_random_clicked()                 //Автозаполнение
{
    int row=ui->tableWidget->rowCount();
    int colum=ui->tableWidget->columnCount();
    int val;

    for (int i = 0;i < row;i++)
        for (int j=0;j<colum;j++)
        {
            if (ui->tableWidget->item(i,j)==nullptr)
            {
                QTableWidgetItem * ti;                          //Создаем указатель на ячейку
                ti = new QTableWidgetItem;                      //Выделяем память
                ui->tableWidget->setItem(i,j,ti);               //Помещаем ячейку в таблицу
            }
            QBrush br;
            br.setColor(Qt::white);
            br.setStyle(Qt::DiagCrossPattern);
            ui->tableWidget->item(i,j)->setBackground(Qt::white);

            val=rand()%201-100;                                 // от -100 до 100
            ui->tableWidget->item(i,j)->setText(QString::number(val));
        }
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)//Изменение ячейки
{

    if (no_auto_change)
    {
        ui->label_max->clear();
        ui->label_mid->clear();
        ui->label_min->clear();

        bool flag;
        double a=ui->tableWidget->item(row,column)->text().toDouble(&flag);
        if (!flag||qIsInf(a)||qIsNaN(a))
        {
            QBrush br;
            br.setColor(Qt::white);
            br.setStyle(Qt::DiagCrossPattern);
            ui->tableWidget->item(row,column)->setBackground(Qt::red);
            gl_flag=false;
        }
        else
        {
            QBrush br;
            br.setColor(Qt::white);
            br.setStyle(Qt::DiagCrossPattern);
            ui->tableWidget->item(row,column)->setBackground(Qt::white);
            gl_flag=true;
        }
    }
}

void MainWindow::on_pushButton_magik_clicked()                  //Кнопка сортировки
{
    no_auto_change=false;
    int row=ui->tableWidget->rowCount();
    bool fl_sort=true;
    check_input();

    if(gl_flag)
    {
        if (ui->radioButton_puz->isChecked())                   //Пузырьком
        {
            for(int i=0;i<row;i++)
            {
                for (int j=0;j<row-1;j++)
                    if (mas_table[j+1]>mas_table[j])
                    {
                        double  t=mas_table[j];
                        mas_table[j]=mas_table[j+1];
                        mas_table[j+1]=t;
                    }
            }
        }
        if(ui->radioButton_gnom->isChecked())                   //Гномья
        {
            int i=0;
            while (i<row)
            {
                if(i==0||mas_table[i-1]>=mas_table[i])
                    i++;
                else
                {
                    double t=mas_table[i];
                    mas_table[i]=mas_table[i-1];
                    mas_table[i-1]=t;
                    i--;
                }
            }
        }
        if(ui->radioButton_saru->isChecked())                   //Обезьянья

        {     int n=0;
            double mas[MAX_MAS_SIZE];

            for(int i=0;i<row;i++)
                mas[i]=mas_table[i];
            fast_sort(0,row-1);

            for(int i=0;i<row;i++)
                if(abs(mas[i]-mas_table[i])>1e-5)
                    fl_sort=false;

            while(n<10000&&!fl_sort)
            {
                fl_sort=true;
                for(int i=0;i<row;i++)
                    if(abs(mas[i]-mas_table[i])>1e-5)
                        fl_sort=false;
                if(!fl_sort)
                    mas_peretasovka(mas);
                else {
                    break;
                }

                n++;
            }
            if(!fl_sort)
                QMessageBox::information(this,"Ошибка","Слишком большой Массив",QMessageBox::Ok);
        }
        if(ui->radioButton_rasch->isChecked())              //Расчёска
        {
            double t;
            int n=row;
            bool fl_peres=true;
            while (n>1||fl_peres)
            {
                if(n>1)
                    n=int (n/1.247);
                fl_peres=false;
                int i=0;
                while(i+n<row)
                {
                    if(mas_table[i]<mas_table[i+n])
                    {
                        t=mas_table[i];
                        mas_table[i]=mas_table[i+n];
                        mas_table[i+n]=t;
                        fl_peres=true;
                    }
                    i++;
                }
            }
        }
        if(ui->radioButton_fast->isChecked())
        {
            fast_sort(0,row-1);
        }
        for (int i = 0;i < row&&fl_sort;i++)            //Вывод в таблицу

            ui->tableWidget->item(i,0)->setText(QString::number(mas_table[i]));
    }
    else
    {
        QMessageBox::information(this,"Ошибка","В таблице некоректное значение.",QMessageBox::Ok);
        ui->tableWidget->selectRow(table_pos);
        ui->tableWidget->setFocus();
    }
    no_auto_change=true;
}

void MainWindow::on_pushButton_max_clicked()            //максимальное значение
{
    no_auto_change=false;
    int row=ui->tableWidget->rowCount();
    check_input();
    double max=mas_table[0];
    if(gl_flag)                                         //ошибки ввода нет
    {
        for(int i=1;i<row;i++)
        {
            if(mas_table[i]>max)
                max=mas_table[i];
        }
        ui->label_max->setNum(max);
    }
    else
    {
        ui->tableWidget->selectRow(table_pos);
        ui->tableWidget->setFocus();
        QMessageBox::information(this,"Ошибка","В таблице некоректное значение.",QMessageBox::Ok);
    }
    no_auto_change=true;
}

void MainWindow::on_pushButton_mid_clicked()            //среднее значения
{
    int row=ui->tableWidget->rowCount();
    check_input();
    double mid=0;
    if(gl_flag)                                         //ошибки ввода нет
    {
        for (int i=0;i<row;i++)
        {mid+=mas_table[i];

        }
        mid=mid/row;
        ui->label_mid->setNum(mid);
    }
    else
    {
        ui->tableWidget->selectRow(table_pos);
        ui->tableWidget->setFocus();
        QMessageBox::information(this,"Ошибка","В таблице некоректное значение.",QMessageBox::Ok);
    }
}

void MainWindow::on_pushButton_min_clicked()//минимальное значение
{
    no_auto_change=false;
    int row=ui->tableWidget->rowCount();
    check_input();
    double min=mas_table[0];
    if(gl_flag)//ошибки ввода нет
    {
        for(int i=1;i<row;i++)
        {
            if(mas_table[i]<min)
                min=mas_table[i];
        }
        ui->label_min->setNum(min);
    }
    else
    {
        ui->tableWidget->selectRow(table_pos);
        ui->tableWidget->setFocus();
        QMessageBox::information(this,"Ошибка","В таблице некоректное значение.",QMessageBox::Ok);
    }
    no_auto_change=true;
}

void MainWindow::on_pushButton_clear_clicked()//Очистка
{
    no_auto_change=false;
    ui->label_max->clear();
    ui->label_mid->clear();
    ui->label_min->clear();
    int row=ui->tableWidget->rowCount();

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setRowCount(row);

    no_auto_change=true;
}

void MainWindow::on_pushButton_addrow_clicked()//Добавиление строки
{
    ui->spinBox->setValue(ui->spinBox->value()+1);
}

void MainWindow::on_pushButton_delrow_clicked()//Удаление строки
{
    ui->spinBox->setValue(ui->spinBox->value()-1);
}
