#include "mainwindow.h"
#include "Models/pointtopoint.h"
#include "ui_mainwindow.h"
#include <spline.h>
#include <algorithm>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    h = 0.1;
    // XBegin = -3;
    // Xend = 3 + h;
    // ui->widget->xAxis->setRange(-4,4);
    // ui->widget->yAxis->setRange(0,9);

    // X = XBegin;
    // n = (Xend - XBegin) /h + 2;
    // for(X = XBegin ; X <= Xend;X += h){
    //         x.push_back(X);
    //         y.push_back(X*X);
    // }
    ui->graph->setInteraction(QCP::iRangeZoom, true);
    ui->graph->setInteraction(QCP::iRangeDrag, true);
    // ui->widget->addGraph();
    // ui->widget->graph(0)->addData(x,y);
    // ui->widget->replot();
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
void PaintGraph(){

}
void MainWindow::on_CreateGraph_clicked()
{
    for (int i = 0; i < ui->tablePoints->rowCount(); i++)
        xs.push_back(ui->tablePoints->item(i, 0)->text().toFloat());

    for (int i = 0; i < ui->tablePoints->rowCount(); i++)
        ys.push_back(ui->tablePoints->item(i, 1)->text().toFloat());
    nuton.NewtonPolinominal(xs, ys);
    xBegin = Sorting::VectorMinToFloat(xs);
    xEnd = Sorting::VectorMaxToFloat(xs);
    int i = 0;
    for(float X = xBegin; X <= xEnd; X += h){
        x.push_back(xs[i]);
        y.push_back(nuton.polynominal(xs[i]));
        i++;
    }
    // for (int i = 0; i < ui->tablePoints->rowCount(); i++)
    //     x.push_back(xs[i]);
    // for (int i = 0; i < ui->tablePoints->rowCount(); i++)
    //     y.push_back(nuton.polynominal(xs[i]));

    QCPGraph *spl = ui->graph->addGraph();
    spl->setPen(QPen(Qt::blue));
    QCPItemTracer *tracer = new QCPItemTracer(ui->graph);
    tracer->setGraph(spl);
    tracer->setInterpolating(true);

    // spl->setLineStyle(QCPGraph::);
    spl->setData(x, y);

    //  ui->graph->xAxis->setRange(-0.5,0.5);
    // ui->graph->yAxis->setRange(-0.5,0.5);
    ui->graph->replot();
    // ui->graph->addGraph();
    // ui->graph->graph(0)->addData(x,y);
    // ui->graph->replot();
}
