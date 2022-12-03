#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pushButton_result_clicked();                        //нажатие кнопки результата

    void on_radioButton_plus_clicked();                         //выбор сложения

    void on_radioButton_minus_clicked();                        //выбор вычитания

    void on_radioButton_mult_clicked();                         //выбор умножения

    void on_radioButton_div_clicked();                          //выбор деления

    void on_pushButton_clear_clicked();                         //нажатие кнопки очистки

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
