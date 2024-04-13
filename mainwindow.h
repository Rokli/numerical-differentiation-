#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Models/Sorting.h>
#include <QMainWindow>
#include <QTableWidget>
#include <QVector>
#include <Models/nuton.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_CalculationDerivatives_clicked();

    void on_CreateTable_clicked();

    void on_CreateGraph_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<float> xs, ys;
    QVector<double> x, y;
    Nuton nuton;
    float xBegin, xEnd,h;
};
#endif // MAINWINDOW_H
