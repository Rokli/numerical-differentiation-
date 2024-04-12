#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pointtopoint.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // h = 0.1;
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
    ui->widget->setInteraction(QCP::iRangeZoom,true);
    ui->widget->setInteraction(QCP::iRangeDrag,true);
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x,y);
    ui->widget->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_CalculationDerivatives_clicked()
{
    ui->textEdit->clear();
    float X = ui->pointGraph->text().toFloat();
    QString textForm;
    for(int i = 1; i < 8; i++){
        textForm = ui->textEdit->toPlainText();
        ui->textEdit->setPlainText(textForm +"\n" +QString::number(PointToPoint::CalculationFormula(X,pow(10,-i))));
    }
}

