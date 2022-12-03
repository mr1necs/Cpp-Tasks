#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    no_auto_change = true;
    ui->spinBox_Row_valueChange->setMaximum(MAX_MAS_SIZE);
    on_pushButton_clicked();
    ui->tableWidget_2->setEditTriggers(QTableWidget::NoEditTriggers);
    mas_table = nullptr;
    mas_no_duplicates = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_Row_valueChange_valueChanged(int arg1) // выбок количества чисел
{
    ui->tableWidget->setRowCount(arg1);
}

void MainWindow::on_pushButton_Random_clicked() // автозаполнение
{
    delete [] mas_table;
    mas_table=nullptr;

    int row=ui->tableWidget->rowCount();
    int colum=ui->tableWidget->columnCount();
    int val;
    try
    {
        mas_table=new double[row];
    } catch (std::bad_alloc&)

    {
        QMessageBox::information(this,"Ошибка","Не возможно выделить память",QMessageBox::Ok);
    }

    if (row >= 300000) // предупреждение по поводу зависания, если обрабатывается много чисел
    {
        QMessageBox::information(this, "Оповещение", "Операции необходимо время.", QMessageBox::Ok);
    }

    for (int i = 0;i < row;i++)
        for (int j=0;j<colum;j++)
        {
            if (ui->tableWidget->item(i,j)==nullptr)
            {
                //создаем
                QTableWidgetItem * ti;// Создаем указатель на ячейку
                ti = new QTableWidgetItem;// Выделяем память
                ui->tableWidget->setItem(i,j,ti);// Помещаем ячейку в таблицу
            }
            //ui->tableWidget->item(i,j)->setBackgroundColor(Qt::white);

            val=rand()%201-100;// от -100 до 100
            ui->tableWidget->item(i,j)->setText(QString::number(val));
        }
    // no_auto_change=true;
    delete [] mas_table;
    mas_table=nullptr;
}

void MainWindow::on_tableWidget_cellChanged(int row) // изменили ячейку
{
    if(no_auto_change)
    {
        bool flag;
        double x = ui->tableWidget->item(row,0)->text().toDouble(&flag);

        if (flag && (fabs(isinf(x)-0) < 1e-7) && (fabs(isnan(x)-0) < 1e-7))
        {
            ui->tableWidget->item(row,0)->setBackground(Qt::white);
            ui->label_MIN_result->setVisible(false);
            ui->label_MAX_result->setVisible(false);
            ui->label_MEAN_result->setVisible(false);
            ui->tableWidget_2->clearContents();//очистка таблицы
            ui->tableWidget_2->setRowCount(0);
        }
        else
        {
            ui->tableWidget->item(row,0)->setBackground(Qt::red);
            ui->label_MIN_result->setVisible(false);
            ui->label_MAX_result->setVisible(false);
            ui->label_MEAN_result->setVisible(false);
            ui->tableWidget_2->clearContents();//очистка таблицы
            ui->tableWidget_2->setRowCount(0);
        }
    }
}

void MainWindow::on_pushButton_MIN_MAX_MEAN_clicked() // нахождение минимального, максимального и среднего значений
{
    no_auto_change = false;

    delete [] mas_table;
    mas_table=nullptr;

    int row = ui->tableWidget->rowCount();
    int rub = -1;
    double min = 0;
    double max = 0;
    double sum = 0;
    double mean = 0;
    double x = 0;
    bool flag, flag_not_that = false;

    if (row >= 500000) // предупреждение по поводу зависания, если обрабатывается много чисел
    {
        QMessageBox::information(this, "Оповещение", "Операции необходимо время.", QMessageBox::Ok);
    }

    if (row > 0)
    {
        if (ui->tableWidget->item(0,0)!=nullptr) // проверка на существование ячейки
        {    // существует
            min = max =  ui->tableWidget->item(0,0)->text().toDouble(&flag);  // присвоение начального значения
            if (flag && (fabs(isinf(min)-0) < 1e-7) && (fabs(isnan(min)-0) < 1e-7))
                ui->tableWidget->item(0,0)->setBackground(Qt::white);
            else
            {
                flag_not_that = true;
                ui->tableWidget->item(0,0)->setBackground(Qt::red);
                if (rub == -1)
                    rub = 0;
            }
        }
        else
        { // не существует
            // создаем
            QTableWidgetItem * ti; // создаем указатель на ячейку
            ti = new QTableWidgetItem; // выделяем память
            ui->tableWidget->setItem(0,0,ti); // помещаем ячейку в таблицу
            ui->tableWidget->item(0,0)->setBackground(Qt::red);
            if (rub == -1)
                rub = 0;
            flag_not_that = true;
        }
    }

    for (int i=1; i<row; i++)
        if (ui->tableWidget->item(i,0)!=nullptr) // проверка на существование ячейки
        {    // существует
            x = ui->tableWidget->item(i,0)->text().toDouble(&flag);
            if (flag && (fabs(isinf(x)-0) < 1e-7) && (fabs(isnan(x)-0) < 1e-7))
            {
                ui->tableWidget->item(i,0)->setBackground(Qt::white);
                if (min > x) // нахождение минимального числа
                    min = x;
                else if (max < x) // нахождение максимального числа
                    max = x;
            }
            else
            {
                flag_not_that = true;
                ui->tableWidget->item(i,0)->setBackground(Qt::red);
                if (rub == -1)
                    rub = i;
            }
            sum += ui->tableWidget->item(i,0)->text().toDouble(&flag);
        }
        else
        { // не существует
            // создаем
            QTableWidgetItem * ti; // создаем указатель на ячейку
            ti = new QTableWidgetItem; // выделяем память
            ui->tableWidget->setItem(i,0,ti); // помещаем ячейку в таблицу
            ui->tableWidget->item(i,0)->setBackground(Qt::red);
            if (rub == -1)
                rub = i;
            flag_not_that = true;
        }
    if (flag_not_that)
    {
        ui->label_MIN_result->setVisible(false);
        ui->label_MAX_result->setVisible(false);
        ui->label_MEAN_result->setVisible(false);
        QMessageBox::information(this, "Ошибка", "Таблица содержит ячейки с некорректным значением.", QMessageBox::Ok);
        ui->tableWidget->selectRow(rub);
        ui->tableWidget->setFocus();
    }
    else
    {
        mean = sum / row; // нахождение среднего числа
        ui->label_MIN_result->setVisible(true);
        ui->label_MAX_result->setVisible(true);
        ui->label_MEAN_result->setVisible(true);
        ui->label_MIN_result->setNum(min);
        ui->label_MAX_result->setNum(max);
        ui->label_MEAN_result->setNum(mean);
    }
    no_auto_change = true;

    delete [] mas_table;
    mas_table=nullptr;

}

void MainWindow::on_pushButton_bubble_clicked() // сортировка пузырьком
{
    no_auto_change = false;

    delete [] mas_table;
    mas_table=nullptr;

    int row = ui->tableWidget->rowCount();
    int rub = -1;
    bool flag; // признак успешной конвертации ячейки
    bool gl_flag = true; // признак успешного формирования массива из таблицы

    if (row >= 20000) // предупреждение по поводу зависания, если обрабатывается много чисел
    {
        QMessageBox::information(this, "Оповещение", "Операции необходимо время.", QMessageBox::Ok);
    }

    // проверка на наличие памяти для массива
    try
    {
        mas_table = new double[row];
    }
    catch (std::bad_alloc&)
    {
        QMessageBox::information(this,"Ошибка","Невозможно выделить память.",QMessageBox::Ok);
        //        return;
        gl_flag=false;
    }

    if (gl_flag)
    {
        // заполнение массива + проверка на число
        for (int i=0; i<row; i++)
            if (ui->tableWidget->item(i,0)==nullptr)
            {
                gl_flag=false; // нет ячейки
                QTableWidgetItem * ti; // создаем указатель на ячейку
                ti = new QTableWidgetItem; // выделяем память
                ui->tableWidget->setItem(i,0,ti); // помещаем ячейку в таблицу
                ui->tableWidget->item(i,0)->setBackground(Qt::red);
                if (rub == -1)
                    rub = i;
            }
            else
            {
                mas_table[i] = ui->tableWidget->item(i,0)->text().toDouble(&flag);
                if (flag && (fabs(isinf(mas_table[i])-0) < 1e-7) && (fabs(isnan(mas_table[i])-0) < 1e-7))
                    ui->tableWidget->item(i,0)->setBackground(Qt::white);
                else
                {
                    ui->tableWidget->item(i,0)->setBackground(Qt::red);
                    gl_flag=false; // есть ячейка с ошибкой
                    if (rub == -1)
                        rub = i;
                }
            }
    }

    if (gl_flag)
    { // массив сформированн корректно
        // проверка на отсортированность массива
        bool falg_sorting = true;
        for (int i = 1; i < row; i++)
        {
            if (mas_table[i-1] > mas_table[i])
                falg_sorting = false;
        }
        if(!falg_sorting)
        {
            // сортировка пузырьком
            int i = 0;
            int j = 0;
            double t = 0;

            while (i<(row-1))
            {
                j = i+1;
                while (j<row)
                {
                    if (mas_table[i]>mas_table[j])
                    {
                        t = mas_table[i];
                        mas_table[i] = mas_table[j];
                        mas_table[j] = t;
                    }
                    j += 1;
                }
                i+=1;
            }
            // вывод результатов в таблицу (без проверок, так как gl_flag = true)
            for (int i=0; i<row; i++)
                ui->tableWidget->item(i,0)->setText(QString::number(mas_table[i]));
        }
        else
            QMessageBox::information(this, "Оповещение", "Массив уже отсортирован", QMessageBox::Ok);
    }
    else
        QMessageBox::information(this, "Ошибка", "Таблица содержит ячейки с некорректным значением.", QMessageBox::Ok);

    ui->tableWidget->selectRow(rub);
    ui->tableWidget->setFocus();

    delete [] mas_table;
    mas_table=nullptr;

    no_auto_change = true;
}

void MainWindow::on_pushButton_gnome_clicked() // гномья сортировка
{
    no_auto_change = false;

    delete [] mas_table;
    mas_table=nullptr;

    int row = ui->tableWidget->rowCount();
    int rub = -1;
    bool flag; // признак успешной конвертации ячейки
    bool gl_flag = true; // признак успешного формирования массива из таблицы

    if (row >= 20000) // предупреждение по поводу зависания, если обрабатывается много чисел
    {
        QMessageBox::information(this, "Оповещение", "Операции необходимо время.", QMessageBox::Ok);
    }

    // проверка на наличие памяти для массива
    try
    {
        mas_table = new double[row];
    }
    catch (std::bad_alloc&)
    {
        QMessageBox::information(this,"Ошибка","Невозможно выделить память.",QMessageBox::Ok);
        //        return;
        gl_flag=false;
    }

    if (gl_flag)
    {
        // заполнение массива + проверка на число
        for (int i=0; i<row; i++)
            if (ui->tableWidget->item(i,0)==nullptr)
            {
                gl_flag=false; // нет ячейки
                QTableWidgetItem * ti; // создаем указатель на ячейку
                ti = new QTableWidgetItem; // выделяем память
                ui->tableWidget->setItem(i,0,ti); // помещаем ячейку в таблицу
                ui->tableWidget->item(i,0)->setBackground(Qt::red);
                if (rub == -1)
                    rub = i;
            }
            else
            {
                mas_table[i] = ui->tableWidget->item(i,0)->text().toDouble(&flag);
                if (flag && (fabs(isinf(mas_table[i])-0) < 1e-7) && (fabs(isnan(mas_table[i])-0) < 1e-7))
                    ui->tableWidget->item(i,0)->setBackground(Qt::white);
                else
                {
                    ui->tableWidget->item(i,0)->setBackground(Qt::red);
                    gl_flag=false; // есть ячейка с ошибкой
                    if (rub == -1)
                        rub = i;
                }
            }
    }

    if (gl_flag)
    { // массив сформированн корректно
        // проверка на отсортированность массива
        bool falg_sorting = true;
        for (int i = 1; i < row; i++)
        {
            if (mas_table[i-1] > mas_table[i])
                falg_sorting = false;
        }
        if(!falg_sorting)
        {
            // сортировка гномиком
            int i = 0;
            int j = 0;
            double t = 0;
            while (i < row)
                if ((i == 0)||(mas_table[i-1]<mas_table[i])||(fabs(mas_table[i-1]-mas_table[i])<1e-7))
                    i+=1;
                else
                {
                    j = i-1;
                    t = mas_table[i];
                    mas_table[i] = mas_table [j];
                    mas_table[j] = t;
                    i = j;
                }

            // вывод результатов в таблицу (без проверок, так как gl_flag = true)
            for (int i=0; i<row; i++)
                ui->tableWidget->item(i,0)->setText(QString::number(mas_table[i]));
            delete [] mas_table;
            mas_table=nullptr;
        }
        else
            QMessageBox::information(this, "Оповещение", "Массив уже отсортирован", QMessageBox::Ok);
    }
    else
        QMessageBox::information(this, "Ошибка", "Таблица содержит ячейки с некорректным значением.", QMessageBox::Ok);

    ui->tableWidget->selectRow(rub);
    ui->tableWidget->setFocus();

    delete [] mas_table;
    mas_table=nullptr;

    no_auto_change = true;
}

void MainWindow::on_pushButton_comb_clicked() // сортировка расческой
{
    no_auto_change = false;

    delete [] mas_table;
    mas_table=nullptr;

    int row = ui->tableWidget->rowCount();
    int rub = -1;
    bool flag; // признак успешной конвертации ячейки
    bool gl_flag = true; // признак успешного формирования массива из таблицы

    if (row >= 20000) // предупреждение по поводу зависания, если обрабатывается много чисел
    {
        QMessageBox::information(this, "Оповещение", "Операции необходимо время.", QMessageBox::Ok);
    }

    // проверка на наличие памяти для массива
    try
    {
        mas_table = new double[row];
    }
    catch (std::bad_alloc&)
    {
        QMessageBox::information(this,"Ошибка","Невозможно выделить память.",QMessageBox::Ok);
        //        return;
        gl_flag=false;
    }

    if (gl_flag)
    {
        // заполнение массива + проверка на число
        for (int i=0; i<row; i++)
            if (ui->tableWidget->item(i,0)==nullptr)
            {
                gl_flag=false; // нет ячейки
                QTableWidgetItem * ti; // создаем указатель на ячейку
                ti = new QTableWidgetItem; // выделяем память
                ui->tableWidget->setItem(i,0,ti); // помещаем ячейку в таблицу
                ui->tableWidget->item(i,0)->setBackground(Qt::red);
                if (rub == -1)
                    rub = i;
            }
            else
            {
                mas_table[i] = ui->tableWidget->item(i,0)->text().toDouble(&flag);
                if (flag && (fabs(isinf(mas_table[i])-0) < 1e-7) && (fabs(isnan(mas_table[i])-0) < 1e-7))
                    ui->tableWidget->item(i,0)->setBackground(Qt::white);
                else
                {
                    ui->tableWidget->item(i,0)->setBackground(Qt::red);
                    gl_flag=false; // есть ячейка с ошибкой
                    if (rub == -1)
                        rub = i;
                }
            }
    }

    if (gl_flag)
    { // массив сформированн корректно
        // проверка на отсортированность массива
        bool falg_sorting = true;
        for (int i = 1; i < row; i++)
        {
            if (mas_table[i-1] > mas_table[i])
                falg_sorting = false;
        }
        if(!falg_sorting)
        {
            // сортировка расчесткой
            int step = row;
            int i = 0;
            double t = 0;
            int factor = 2; // фактор уменьшения
            bool fl = true;
            while (step > 1 || fl)
            {
                if (step>1)
                    step = step/factor;
                fl = false;
                i = 0;
                while (i + step < row)
                {
                    if (mas_table[i]>mas_table[i+step])
                    {
                        t = mas_table[i];
                        mas_table[i] = mas_table[i+step];
                        mas_table[i+step] = t;
                        fl = true;
                    }
                    i+=1;
                }
            }
            // вывод результатов в таблицу (без проверок, так как gl_flag = true)
            for (int i=0; i<row; i++)
                ui->tableWidget->item(i,0)->setText(QString::number(mas_table[i]));
            delete [] mas_table;
            mas_table=nullptr;
        }
        else
            QMessageBox::information(this, "Оповещение", "Массив уже отсортирован", QMessageBox::Ok);
    }
    else
        QMessageBox::information(this, "Ошибка", "Таблица содержит ячейки с некорректным значением.", QMessageBox::Ok);

    ui->tableWidget->selectRow(rub);
    ui->tableWidget->setFocus();

    delete [] mas_table;
    mas_table=nullptr;

    no_auto_change = true;
}

void MainWindow::on_pushButton_quick_clicked() // быстрая сортировка
{
    no_auto_change = false;
    int row = ui->tableWidget->rowCount();
    int rub = -1;
    bool flag; // признак успешной конвертации ячейки
    bool gl_flag = true; // признак успешного формирования массива из таблицы

    if (row >= 300000) // предупреждение по поводу зависания, если обрабатывается много чисел
    {
        QMessageBox::information(this, "Оповещение", "Операции необходимо время.", QMessageBox::Ok);
    }

    //очищаем, что есть в mas_table
    if (mas_table!=nullptr)
    {
        delete [] mas_table;
        mas_table=nullptr;
    }

    // проверка на наличие памяти для массива
    try
    {
        mas_table = new double[row];
    }
    catch (std::bad_alloc&)
    {
        QMessageBox::information(this,"Ошибка","Невозможно выделить память.",QMessageBox::Ok);
        //        return;
        gl_flag=false;
    }

    if (gl_flag)
    {
        // заполнение массива + проверка на число
        for (int i=0; i<row; i++)
            if (ui->tableWidget->item(i,0)==nullptr)
            {
                gl_flag=false; // нет ячейки
                QTableWidgetItem * ti; // создаем указатель на ячейку
                ti = new QTableWidgetItem; // выделяем память
                ui->tableWidget->setItem(i,0,ti); // помещаем ячейку в таблицу
                ui->tableWidget->item(i,0)->setBackground(Qt::red);
                if (rub == -1)
                    rub = i;
            }
            else
            {
                mas_table[i] = ui->tableWidget->item(i,0)->text().toDouble(&flag);
                if (flag && (fabs(isinf(mas_table[i])-0) < 1e-7) && (fabs(isnan(mas_table[i])-0) < 1e-7))
                    ui->tableWidget->item(i,0)->setBackground(Qt::white);
                else
                {
                    ui->tableWidget->item(i,0)->setBackground(Qt::red);
                    gl_flag=false; // есть ячейка с ошибкой
                    if (rub == -1)
                        rub = i;
                }
            }

        // проверка на отсортированность массива
        bool falg_sorting = true;

        for (int i = 1; i < row; i++)
        {
            if (mas_table[i-1] > mas_table[i])
                falg_sorting = false;
        }

        if (!falg_sorting)
        {
            int b = 0;
            int e = row-1;
            quick_sort (gl_flag, b, e);
            for (int i=0; i<row; i++)
                ui->tableWidget->item(i,0)->setText(QString::number(mas_table[i]));

            delete [] mas_table;
            mas_table=nullptr;
        }
        else
            QMessageBox::information(this, "Оповещение", "Массив уже отсортирован", QMessageBox::Ok);
    }

    ui->tableWidget->selectRow(rub);
    ui->tableWidget->setFocus();

    ui->tableWidget_2->clearContents(); // очистка таблицы
    ui->tableWidget_2->setRowCount(0);

    delete [] mas_table;
    mas_table=nullptr;

    no_auto_change = true;
}

void MainWindow::quick_sort(bool gl_flag, int b, int e) // функция быстрой сортировки
{
    no_auto_change = false;

    if (gl_flag)
    { // массив сформированн корректно
        // быстрая сортировка
        int left = b;
        int right = e;
        double pivot = mas_table[(left+right)/2];
        double t = 0;

        while (left <= right)
        {
            while (mas_table[left] < pivot)
                left += 1;
            while (mas_table[right] > pivot)
                right -= 1;
            if (left <= right)
            {
                t = mas_table[right];
                mas_table[right] = mas_table[left];
                mas_table[left] = t;
                left+=1;
                right-=1;
            }
        }
        if (b < right)
            quick_sort(gl_flag, b, right);
        if (e > left)
            quick_sort(gl_flag, left, e);
    }
    else
    {
        QMessageBox::information(this, "Ошибка", "Таблица содержит ячейки с некорректным значением.", QMessageBox::Ok);
    }

    no_auto_change = true;
}

void MainWindow::on_pushButton_monkey_clicked() // обезьянья сортировка
{
    no_auto_change = false;

    delete [] mas_table;
    mas_table=nullptr;

    int row = ui->tableWidget->rowCount();
    int rub = -1;
    bool flag; // признак успешной конвертации ячейки
    bool gl_flag = true; // признак успешного формирования массива из таблицы

    if (row >= 100000) // предупреждение по поводу зависания, если обрабатывается много чисел
    {
        QMessageBox::information(this, "Оповещение", "Операции необходимо время.", QMessageBox::Ok);
    }

    // проверка на наличие памяти для массива
    try
    {
        mas_table = new double[row];
    }
    catch (std::bad_alloc&)
    {
        QMessageBox::information(this,"Ошибка","Невозможно выделить память.",QMessageBox::Ok);
        //        return;
        gl_flag=false;
    }

    if (gl_flag)
    {
        // заполнение массива + проверка на число
        for (int i=0; i<row; i++)
            if (ui->tableWidget->item(i,0)==nullptr)
            {
                gl_flag=false; // нет ячейки
                QTableWidgetItem * ti; // создаем указатель на ячейку
                ti = new QTableWidgetItem; // выделяем память
                ui->tableWidget->setItem(i,0,ti); // помещаем ячейку в таблицу
                ui->tableWidget->item(i,0)->setBackground(Qt::red);
                if (rub == -1)
                    rub = i;
            }
            else
            {
                mas_table[i] = ui->tableWidget->item(i,0)->text().toDouble(&flag);
                if (flag && (fabs(isinf(mas_table[i])-0) < 1e-7) && (fabs(isnan(mas_table[i])-0) < 1e-7))
                    ui->tableWidget->item(i,0)->setBackground(Qt::white);
                else
                {
                    ui->tableWidget->item(i,0)->setBackground(Qt::red);
                    gl_flag=false; // есть ячейка с ошибкой
                    if (rub == -1)
                        rub = i;
                }
            }
    }

    if (gl_flag)
    { // массив сформирован корректно
        bool falg_sorting = true;
        double t = 0;
        //        int val = rand()%1000+1; // от 1 до 1000 - рандомное число
//        int val = 5000;
//        int counter = 0;

        // проверка на отсортированность массива
        for (int i = 1; i < row; i++)
        {
            if (mas_table[i-1] > mas_table[i])
                falg_sorting = false;
        }
        if (falg_sorting)
            QMessageBox::information(this, "Оповещение", "Массив уже отсортирован", QMessageBox::Ok);
        else
            while(!falg_sorting)
            {
                for (int i = 1; i < row; i++)
                {// проверка на отсортированность массива
                    if (mas_table[i-1] < mas_table[i])
                        falg_sorting = true;
                    else {
                        int val_1 = rand()%row;
                        t = mas_table[val_1];
                        mas_table[val_1] = mas_table[i];
                        mas_table[i] = t;
                    }
                }

                for (int i = 1; i < row; i++)
                {
                    if (mas_table[i-1] > mas_table[i])
                        falg_sorting = false;
                }

//                if (falg_sorting)
//                    QMessageBox::information(this, "Оповещение", "Обезьянья сортировка прошла успешно.", QMessageBox::Ok);
//                else {
//                    if (counter == val){
//                        QMessageBox::information(this, "Ошибка", "Обезьянья сортировка не удалась.", QMessageBox::Ok);
//                        break;
//                    }
//                    else
//                        counter ++;
//                }
            }
    }
    else
        QMessageBox::information(this, "Ошибка", "Таблица содержит ячейки с некорректным значением.", QMessageBox::Ok);

    if (gl_flag)
        for (int i=0; i<row; i++)
            ui->tableWidget->item(i,0)->setText(QString::number(mas_table[i]));

    ui->tableWidget->selectRow(rub);
    ui->tableWidget->setFocus();

    delete [] mas_table;
    mas_table=nullptr;

    no_auto_change = true;
}

void MainWindow::on_pushButton_clicked() // очистка
{
    ui->tableWidget->clearContents(); // очистка таблицы
    ui->label_MIN_result->setVisible(false);
    ui->label_MAX_result->setVisible(false);
    ui->label_MEAN_result->setVisible(false);
}

void MainWindow::on_pushButton_search_clicked() // поиск заданного значения
{
    no_auto_change = false;

    delete [] mas_table;
    mas_table=nullptr;

    int row = ui->tableWidget->rowCount();
    int rub = -1;
    bool flag; // признак успешной конвертации ячейки
    bool gl_flag = true; // признак успешного формирования массива из таблицы

    if (row >= 500000) // предупреждение по поводу зависания, если обрабатывается много чисел
    {
        QMessageBox::information(this, "Оповещение", "Операции необходимо время.", QMessageBox::Ok);
    }

    // проверка на наличие памяти для массива
    try
    {
        mas_table = new double[row];
    }
    catch (std::bad_alloc&)
    {
        QMessageBox::information(this,"Ошибка","Невозможно выделить память.",QMessageBox::Ok);
        //        return;
        gl_flag=false;
    }

    if (gl_flag)
    {
        // заполнение массива + проверка на число
        for (int i=0; i<row; i++)
            if (ui->tableWidget->item(i,0)==nullptr)
            {
                gl_flag=false; // нет ячейки
                QTableWidgetItem * ti; // создаем указатель на ячейку
                ti = new QTableWidgetItem; // выделяем память
                ui->tableWidget->setItem(i,0,ti); // помещаем ячейку в таблицу
                ui->tableWidget->item(i,0)->setBackground(Qt::red);
                if (rub == -1)
                    rub = i;
            }
            else
            {
                mas_table[i] = ui->tableWidget->item(i,0)->text().toDouble(&flag);
                if (flag && (fabs(isinf(mas_table[i])-0) < 1e-7) && (fabs(isnan(mas_table[i])-0) < 1e-7))
                    ui->tableWidget->item(i,0)->setBackground(Qt::white);
                else
                {
                    ui->tableWidget->item(i,0)->setBackground(Qt::red);
                    gl_flag=false; // есть ячейка с ошибкой
                    if (rub == -1)
                        rub = i;
                }
            }
    }

    if (gl_flag)
    { // массив сформирован корректно
        bool falg_sorting = true;
        double required_number = ui->lineEdit->text().toDouble(&flag);
        double counter = 0;

        if (flag && (fabs(isinf(required_number)-0) < 1e-7) && (fabs(isnan(required_number)-0) < 1e-7))
        {
            // проверка на отсортированность массива
            for (int i = 1; i < row; i++)
            {
                if (mas_table[i-1] > mas_table[i])
                    falg_sorting = false;
            }

            if (falg_sorting)
            {// если массив отсортирован
                for (int i = 0; i < row; i++)
                {
                    if (fabs(mas_table[i] - required_number) < 1e-7)
                    {
                        ui->tableWidget_2->setRowCount(counter+1);
                        QTableWidgetItem * ti; // создаем указатель на ячейку
                        ti = new QTableWidgetItem; // выделяем память
                        ui->tableWidget_2->setItem(counter,0,ti); // помещаем ячейку в таблицу
                        ui->tableWidget_2->item(counter,0)->setText(QString::number(i+1)); // записываем число в таблицу
                        counter++;
                    }
                    else if (required_number < mas_table[i])
                        break;
                }
            }
            else
            {// если массив не отсортирован
                for (int i = 0; i < row; i++)
                {
                    if (fabs(mas_table[i] - required_number) < 1e-7)
                    {
                        ui->tableWidget_2->setRowCount(counter+1);
                        QTableWidgetItem * ti; // создаем указатель на ячейку
                        ti = new QTableWidgetItem; // выделяем память
                        ui->tableWidget_2->setItem(counter,0,ti); // помещаем ячейку в таблицу
                        ui->tableWidget_2->item(counter,0)->setText(QString::number(i+1)); // записываем число в таблицу
                        counter++;
                    }
                }
            }
            if (counter == 0)
            {
                ui->tableWidget_2->clearContents(); // очистка таблицы
                ui->tableWidget_2->setRowCount(0);
                QMessageBox::information(this, "Оповещение", "В массиве нет данного числа.", QMessageBox::Ok);
            }
        }
        else
        {
            ui->tableWidget_2->clearContents(); // очистка таблицы
            ui->tableWidget_2->setRowCount(0);
            QMessageBox::information(this, "Ошибка", "Некорректно написано поисковое значение.", QMessageBox::Ok);
        }
    }
    else
    {
        ui->tableWidget_2->clearContents(); // очистка таблицы
        ui->tableWidget_2->setRowCount(0);
        QMessageBox::information(this, "Ошибка", "Таблица содержит ячейки с некорректным значением.", QMessageBox::Ok);
    }

    // позиционирование на первую ошибку в массиве
    ui->tableWidget->selectRow(rub);
    ui->tableWidget->setFocus();

    delete [] mas_table;
    mas_table=nullptr;

    no_auto_change = true;
}


void MainWindow::on_pushButton_copletition_clicked() // заполнение таблицы одним заданным числом
{
    no_auto_change = false;

    delete [] mas_table;
    mas_table=nullptr;

    int row = ui->tableWidget->rowCount();
    bool flag;
    double number = ui->lineEdit_completion->text().toDouble(&flag);

    if (row >= 500000) // предупреждение по поводу зависания, если обрабатывается много чисел
    {
        QMessageBox::information(this, "Оповещение", "Операции необходимо время.", QMessageBox::Ok);
    }

    if (flag && (fabs(isinf(number)-0) < 1e-7) && (fabs(isnan(number)-0) < 1e-7))
    {
        for (int i=0; i<row; i++)
        {
            if (ui->tableWidget->item(i,0)==nullptr) // проверка на существование ячейки
            {    // существует
                QTableWidgetItem * ti; // создаем указатель на ячейку
                ti = new QTableWidgetItem; // выделяем память
                ui->tableWidget->setItem(i,0,ti); // помещаем ячейку в таблицу
            }
            ui->tableWidget->item(i,0)->setBackground(Qt::white);
            ui->tableWidget->item(i,0)->setText(QString::number(number)); // вывод результата в таблицу
        }
        ui->label_MIN_result->setVisible(false);
        ui->label_MAX_result->setVisible(false);
        ui->label_MEAN_result->setVisible(false);
    }
    else
        QMessageBox::information(this, "Ошибка", "Некорректно написано число.", QMessageBox::Ok);

    delete [] mas_table;
    mas_table=nullptr;

    no_auto_change = true;
}


void MainWindow::on_pushButton_duplicates_clicked() // удаление дубликатов
{
    no_auto_change = false;

    delete [] mas_table;
    mas_table=nullptr;

    int row = ui->tableWidget->rowCount();
    int rub = -1;
    bool flag; // признак успешной конвертации ячейки
    bool gl_flag = true; // признак успешного формирования массива из таблицы

    if (row >= 500000) // предупреждение по поводу зависания, если обрабатывается много чисел
    {
        QMessageBox::information(this, "Оповещение", "Операции необходимо время.", QMessageBox::Ok);
    }

    // проверка на наличие памяти для массива mas_table
    try
    {
        mas_table = new double [row];
    }
    catch (std::bad_alloc&)
    {
        QMessageBox::information(this,"Ошибка","Невозможно выделить память для массива.",QMessageBox::Ok);
        //        return;
        gl_flag=false;
    }

    if (gl_flag)
    {
        // проверка на наличие памяти для массива mas_no_duplicates
        try
        {
            mas_no_duplicates = new double [row];
        }
        catch (std::bad_alloc&)
        {
            QMessageBox::information(this,"Ошибка","Невозможно выделить память для массива дубликатов.",QMessageBox::Ok);
            //            return;
            gl_flag=false;
        }
    }

    if (gl_flag)
    {
        // заполнение массива + проверка на число
        for (int i=0; i<row; i++)
            if (ui->tableWidget->item(i,0)==nullptr)
            {
                gl_flag=false; // нет ячейки
                QTableWidgetItem * ti; // создаем указатель на ячейку
                ti = new QTableWidgetItem; // выделяем память
                ui->tableWidget->setItem(i,0,ti); // помещаем ячейку в таблицу
                ui->tableWidget->item(i,0)->setBackground(Qt::red);
                if (rub == -1)
                    rub = i;
            }
            else
            {
                mas_table[i] = ui->tableWidget->item(i,0)->text().toDouble(&flag);
                if (flag && (fabs(isinf(mas_table[i])-0) < 1e-7) && (fabs(isnan(mas_table[i])-0) < 1e-7))
                    ui->tableWidget->item(i,0)->setBackground(Qt::white);
                else
                {
                    ui->tableWidget->item(i,0)->setBackground(Qt::red);
                    gl_flag=false; // есть ячейка с ошибкой
                    if (rub == -1)
                        rub = i;
                }
            }
    }

    if (gl_flag)
    { // массив сформирован корректно
        // проверка на отсортированность массива
        bool falg_sorting = true;
        for (int i = 1; i < row; i++)
        {
            if (mas_table[i-1] > mas_table[i])
            {
                falg_sorting = false;
                break;
            }
        }

        if (!falg_sorting)
        {// если массив не отсортирован, то отсортируем его
            int b = 0, e = row-1;
            quick_sort (gl_flag, b, e);
//            on_pushButton_comb_clicked();
        }

        // удаление дубликатов
        int index = 0;
        for (int i = 0; i < row; ++i)
        {
            if (i == 0 || (fabs(mas_table[i] - mas_table[i-1])>1e-7))
            {
                mas_no_duplicates[index++] = mas_table[i];
            }
        }
        delete [] mas_table;
        mas_table = mas_no_duplicates;
        ui->tableWidget->setRowCount(index);
        for (int i=0; i<index; i++)
            ui->tableWidget->item(i,0)->setText(QString::number(mas_table[i]));
        delete [] mas_table;
        mas_table=nullptr;
        QMessageBox::information(this,"Оповещение","Дубликатов удалены.",QMessageBox::Ok);
    }
    else
    {
        ui->tableWidget_2->clearContents(); // очистка таблицы
        ui->tableWidget_2->setRowCount(0);
        delete [] mas_table;
        mas_table=nullptr;
        QMessageBox::information(this, "Ошибка", "Таблица содержит ячейки с некорректным значением.", QMessageBox::Ok);
    }

    // позиционирование на первую ошибку в массиве
    ui->tableWidget->selectRow(rub);
    ui->tableWidget->setFocus();

    delete [] mas_table;
    mas_table=nullptr;

    no_auto_change = true;
}

void MainWindow::on_pushButton_addrow_clicked()//Добавиление строки
{
    ui->spinBox_Row_valueChange->setValue(ui->spinBox_Row_valueChange->value()+1);
}

void MainWindow::on_pushButton_delrow_clicked()//Удаление строки
{
    ui->spinBox_Row_valueChange->setValue(ui->spinBox_Row_valueChange->value()-1);
}


