#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include  <spline.h>
#include <QMainWindow>
#include <QVector>
#include <QTableWidget>
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

private:
    Ui::MainWindow *ui;
    double XBegin,Xend,h,X;
    int n;
    QVector<double> x,y;
};
#endif // MAINWINDOW_H
