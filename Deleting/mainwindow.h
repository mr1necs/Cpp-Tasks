#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#define MAX_MAS_SIZE 1000000 // максимальный размер массива

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

    void on_spinBox_Row_valueChange_valueChanged(int arg1); // выбор количества чисел

    void on_pushButton_Random_clicked(); // рандомное заполнение таблицы

    void on_tableWidget_cellChanged(int row); // проверка данных при их изменении в таблице

    void on_pushButton_MIN_MAX_MEAN_clicked(); // нахождение макс, мин, ср. знач

    void on_pushButton_bubble_clicked(); // сортировка пузырьком

    void on_pushButton_gnome_clicked(); // гномья сортировка

    void on_pushButton_comb_clicked(); // сортировка расческой

    void on_pushButton_quick_clicked(); // быстрая сортировка

    void quick_sort(bool gl_flag, int b, int e); // функция быстрой сортировки

    void on_pushButton_monkey_clicked(); // обезьянья сортировка

    void on_pushButton_clicked(); // очистка

    void on_pushButton_search_clicked(); // поиск заданного значения

    void on_pushButton_copletition_clicked(); // заполнение таблицы заданным числом

    void on_pushButton_duplicates_clicked(); // удаление дубликатов

    void on_pushButton_addrow_clicked();

    void on_pushButton_delrow_clicked();

private:
    Ui::MainWindow *ui;
    bool no_auto_change; // признак НЕ автоматической проверки (ручной ввод)
    double * mas_table; // У нас в практике будет одномерный массив
    double * mas_no_duplicates; // массив для удаления дубликатов
};
#endif // MAINWINDOW_H
