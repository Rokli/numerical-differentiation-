#include "mainwindow.h"
#include "Models/pointtopoint.h"
#include "ui_mainwindow.h"
#include <spline.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    h = 0.01;
    ui->graph->setInteraction(QCP::iRangeZoom, true);
    ui->graph->setInteraction(QCP::iRangeDrag, true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_CalculationDerivatives_clicked()
{
    ui->textEdit->clear();
    ui->textEdit->setPlainText("Значение производной:");

    double X = ui->pointGraph->text().toFloat();
    double prevTmp = 0;
    double tmp = PointToPoint::CalculationFormulaRigth(X, pow(10, -1));

    ui->textEdit->setPlainText(ui->textEdit->toPlainText() + "\n" + QString::number(tmp));
    int i = 2;
    do {
        prevTmp = tmp;
        tmp = PointToPoint::CalculationFormulaRigth(X, pow(10, -i));
        ui->textEdit->setPlainText(ui->textEdit->toPlainText() + "\n" + QString::number(tmp));
        i++;
    } while (prevTmp > tmp);

    ui->textEdit->setPlainText(ui->textEdit->toPlainText() + "\n" + "Оптимальный шаг:\t" + "10 в -"
                               + QString::number(i));
}

void MainWindow::on_CreateTable_clicked()
{
    ui->tablePoints->setRowCount(ui->NumberPoints->text().toInt());
}
void MainWindow::on_CreateGraph_clicked()
{
    for (int i = 0; i < ui->tablePoints->rowCount(); i++)
        xs.push_back(ui->tablePoints->item(i, 0)->text().toFloat());

    for (int i = 0; i < ui->tablePoints->rowCount(); i++)
        ys.push_back(ui->tablePoints->item(i, 1)->text().toFloat());
    PaintGraph paint(ui,xs,ys);
    paint.PaintSecondDiff();
}
