#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <math.h>

namespace Ui { class MainWindow; }


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_result_clicked();                        //нажатие кнопки результата

    void on_radioButton_plus_clicked();                         //выбор операции сложения

    void on_radioButton_minus_clicked();                        //выбор операции вычитания

    void on_radioButton_mult_clicked();                         //выбор операции умножения

    void on_radioButton_div_clicked();                          //выбор операции деления

    void on_pushButton_clear_clicked();                         //нажатие кнопки очистки

    void on_radioButton_sqrt_clicked();                         //выбор операции корнь

    void on_radioButton_sin_clicked();                          //выбор операции sin

    void on_radioButton_cos_clicked();                          //выбор операции cos

    void on_radioButton_asin_clicked();                         //выбор операции arcsin

    void on_radioButton_acos_clicked();                         //выбор операции arccos

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
