#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMath>                                                   // библиотека математики
#include <QMessageBox>                                              // библиотека сообщения
#define MAX_MAS_SIZE 100

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinBox_valueChanged(int arg1);                         //количества вершин

    void on_pushButton_clear_clicked();                             //очистка

    double last_coordinate_X(double x);                             //координата "x"

    double last_coordinate_Y(double y);                             //координата "y"

    void on_tableWidget_cellChanged(int row, int column);           // изменили ячейку

    void on_pushButton_res_clicked();                               // нахождение площади и периметра

    void on_Random_clicked();

private:
    Ui::MainWindow *ui;
    bool no_auto_change;                                            //признак НЕ автоматического (ручного) ввода
    int mas_table[MAX_MAS_SIZE][MAX_MAS_SIZE];
};
#endif // MAINWINDOW_H
