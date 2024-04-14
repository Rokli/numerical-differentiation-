#ifndef PAINTGRAPH_H
#define PAINTGRAPH_H
#include "ui_mainwindow.h"
#include "Models/Sorting.h"
#include "Models/nuton.h"
#include <vector>
using namespace std;

class PaintGraph{
private:
    Ui::MainWindow *ui;
    float xBegin, xEnd,h = 0.1;
    vector<float> xs,ys;
    QCPItemTracer *tracer;
    QCPGraph *spl;
private:
    void SetBeginEndH()
    {
        xBegin = Sorting::VectorMinToFloat(xs);
        xEnd = Sorting::VectorMaxToFloat(xs);
    }
    void SettingSpl(){
        spl = ui->graph->addGraph();
        spl->setPen(QPen(Qt::blue));
    }
    void SettingTracer(){
        tracer = new QCPItemTracer(ui->graph);
        tracer->setGraph(spl);
        tracer->setInterpolating(true);
        tracer->setStyle(QCPItemTracer::tsCrosshair);
    }
public:
    PaintGraph(Ui::MainWindow *ui,vector<float> x, vector<float> y){
        xs = x;
        ys = y;
        this->ui = ui;
        SetBeginEndH();
        SettingSpl();
        SettingTracer();
    }
    void PaintNuton(){
        QVector<double> x, y;
        Nuton nuton;
        nuton.NewtonPolinominal(xs, ys);
        for(float X = xBegin; X <= xEnd; X += h){
            x.push_back(X);
            y.push_back(nuton.polynominal(X));
        }
        spl->setData(x, y);
        ui->graph->replot();
    }

};

#endif // PAINTGRAPH_H
