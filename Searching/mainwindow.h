#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <math.h>
#define MAX_MAS_SIZE 200
#define MIN_MAS_SIZE 1
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
    void on_tableWidget_cellChanged(int row, int column);

    void on_spinBox_row_valueChanged(int arg1);


    void on_pushButton_clear_clicked();//очистка

    void on_pushButton_rand_clicked();//рнадомное заполнение

    void on_pushButton_min_clicked();

    void on_pushButton_srednee_clicked();


    void quick_sort(double *mas_table1,int row);

    void rascheska(int row);

    void buble(int row);

    void gnom(int row);

    void monkey(int row);

    bool sorted(double *mas_table1,int row);

    void err_str();

    void on_pushButton_sort_clicked();

    void on_pushButton_max_clicked();

    void on_pushButton_poisk_clicked();

    void on_lineEdit_poisk_textChanged();

    void on_pushButton_addrow_clicked();

    void on_pushButton_delrow_clicked();

private:
    Ui::MainWindow *ui;


    double mas_table1[MAX_MAS_SIZE];
};

#endif // MAINWINDOW_H
