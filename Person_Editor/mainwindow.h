#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>// libra message

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
    void on_pushButton_clr_clicked();

    void on_pushButton_create_clicked();

    int function_gender(int kod_gender);

    void on_lineEdit_name_textChanged(const QString &arg1);

    void on_lineEdit_str_textChanged(const QString &arg1);

    void on_lineEdit_ag_textChanged(const QString &arg1);

    void on_lineEdit_iq_textChanged(const QString &arg1);

    void on_lineEdit_charm_textChanged(const QString &arg1);

    void on_lineEdit_luck_textChanged(const QString &arg1);

    void on_comboBox_race_currentIndexChanged();

    void calc_score_left(void);//функция расчета остатка очков

private:
    Ui::MainWindow *ui;
    int mas_str_value[4][2];        // сила для 4 рас - минимум и максимум
    int mas_dex_value[4][2];        // ловкость для 4 рас - минимум и максимум
    int mas_in_value[4][2];         // интелект для 4 рас - минимум и максимум
    int mas_luck_value[4][2];       // удача для 4 рас - минимум и максимум

    QString mas_gender[2][14];       // гендер
    QString mas_description[2][3];  // описание классов
};

#endif // MAINWINDOW_H
