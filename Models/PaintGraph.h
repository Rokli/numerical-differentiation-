#ifndef PAINTGRAPH_H
#define PAINTGRAPH_H
#include "ui_mainwindow.h"
#include "Models/Sorting.h"
#include "Models/nuton.h"
#include "Models/WorkingWithDerivatives.h"
#include "spline.h"
#include <vector>
using namespace std;

class PaintGraph{
private:
    Ui::MainWindow *ui;
    float xBegin, xEnd,h = 0.1;
    vector<float> xs,ys;
    QCPItemTracer *tracer;
    QCPGraph *spl;
    vector<vector<float>> matrix;
private:
    void SetBeginEndH()
    {
        xBegin = Sorting::VectorMinToFloat(xs);
        xEnd = Sorting::VectorMaxToFloat(xs);
    }
    void SettingGraph(){
        ui->graph->xAxis->setTicks(true);
        ui->graph->yAxis->setTicks(true);
    }
    QCPGraph* SettingSpl(){
        QCPGraph *graph = ui->graph->addGraph();
        return graph;
    }
    void SettingTracer(QCPGraph* graph){
        tracer = new QCPItemTracer(ui->graph);
        tracer->setGraph(graph);
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
        // SettingTracer();
        SettingGraph();
    }
    void PaintNuton(){
        QVector<double> x, y;
        Nuton nuton;
        nuton.NewtonPolinominal(xs, ys);
        for(float X = xBegin; X <= xEnd; X += h){
            x.push_back(X);
            y.push_back(nuton.Polynominal(X));
        }
        spl->setData(x, y);
        ui->graph->replot();
    }
    void PaintSpline(){
        QCPGraph *graph = SettingSpl();
        graph->setPen(QPen(Qt::red));
        QVector<double> x, y;
        Spline spline;
        spline.CreateSpline(xs,ys);
        for(float X = xBegin; X <= xEnd; X += h){
            x.push_back(X);
            y.push_back(spline.Interpolat(X));
        }
        matrix = spline.GetMatrix();
        graph->setData(x, y);
        ui->graph->replot();
    }
    void PaintFirstDiff(){
        QCPGraph *graph = SettingSpl();
        graph->setPen(QPen(Qt::green));
        QVector<double> x, y;
        vector<float> splineValuesY,splineValuesX;
        Spline spline;
        spline.CreateSpline(xs,ys);
        for(float X = xBegin; X <= xEnd; X += h){
            splineValuesX.push_back(X);
            splineValuesY.push_back(spline.Interpolat(X));
        }
        int i = 1;
        for(float X = xBegin + h; X <= xEnd; X += h){
            x.push_back(X);
            y.push_back(WorkingWithDerivatives::FirstDerivatives(splineValuesY[i-1],splineValuesY[i],h));
            i++;
        }
        graph->setData(x, y);
        ui->graph->replot();
    }
    void PaintSecondDiff(){
        QCPGraph *graph = SettingSpl();
        graph->setPen(QPen(Qt::blue));
        QVector<double> x, y;
        vector<float> splineValuesY,splineValuesX;
        Spline spline;
        spline.CreateSpline(xs,ys);
        for(float X = xBegin; X <= xEnd; X += h){
            splineValuesX.push_back(X);
            splineValuesY.push_back(spline.Interpolat(X));
        }
        int i = 2;
        for(float X = xBegin + h; X <= xEnd; X += h){
            x.push_back(X);
            y.push_back(WorkingWithDerivatives::SecondDerivatives(splineValuesY[i-2],splineValuesY[i+2],splineValuesY[i],h));
            i++;
        }
        graph->setData(x, y);
        ui->graph->replot();
    }
    void PaintMatrix(){
        ui->forMatrix->clear();
        for(int i = 0; i < (int)matrix.size(); i++){
            for(int j = 0; j < (int) matrix.size();j++){
                ui->forMatrix->setPlainText(ui->forMatrix->toPlainText() + "\t" + QString::number(matrix[i][j]));
            }
            ui->forMatrix->setPlainText(ui->forMatrix->toPlainText() + "\n");
        }
    }
};

#endif // PAINTGRAPH_H
