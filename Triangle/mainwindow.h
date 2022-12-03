#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMath>                                                   // библиотека математики
#include <QMessageBox>

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

    void on_pushButton_clear_clicked();                             //очистка

    void on_pushButton_res_clicked();                               //нахождение площади и периметра

    void on_Random_clicked();                                       //рандом

    double checkCoord(QString str);                                 //проверка ввода

private:
    Ui::MainWindow *ui;
    bool no_auto_change;
};
#endif // MAINWINDOW_H
