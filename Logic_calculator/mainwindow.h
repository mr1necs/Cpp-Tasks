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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_oper_currentIndexChanged(int index);

    void on_comboBox_op1_currentIndexChanged(int index);

    void on_comboBox_op2_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    void my_func(void);                                             //объявление нашей функции
};
#endif // MAINWINDOW_H
