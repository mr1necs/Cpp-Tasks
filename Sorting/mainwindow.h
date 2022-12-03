#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <math.h>
#define MAX_MAS_SIZE 200                                    //Максимальный размер массива

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_addrow_clicked();

    void on_pushButton_delrow_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_random_clicked();

    void on_tableWidget_cellChanged(int row, int column);

    void on_pushButton_magik_clicked();

    void on_pushButton_max_clicked();

    void on_pushButton_min_clicked();

    void on_pushButton_mid_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::MainWindow *ui;
    bool no_auto_change;                                 // признак НЕ АВТОМАТИЧЕСКОЙ ПРОВЕРКИ (РУЧНОЙ ВВОД)
    double mas_table[MAX_MAS_SIZE];                      //В практической работе одномерный
    void fast_sort( int a,int b);                        //быстрая сортировка
    void check_input();                                  //проверка ввода
    void mas_peretasovka(double mas[MAX_MAS_SIZE]);
    bool gl_flag=true;
    int table_pos=-1;
};

#endif // MAINWINDOW_H
