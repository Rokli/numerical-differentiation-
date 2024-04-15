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
    float xBegin, xEnd,h = 0.01;
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
        QVector<double> x, y;
        Spline spline;
        spline.CreateSpline(xs,ys);
        for(float X = xBegin; X <= xEnd; X += h){
            x.push_back(X);
            y.push_back(spline.Interpolat(X));
        }
        matrix = spline.GetMatrix();
        spl->setData(x, y);
        ui->graph->replot();
    }
    void PaintFirstDiff(){
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
        spl->setData(x, y);
        ui->graph->replot();
    }
    void PaintSecondDiff(){
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
        spl->setData(x, y);
        ui->graph->replot();
    }
    void PaintMatrix(){
        ui->forMatrix->clear();
        // ui->forMatrix->setPlainText("Matrix:" + "\n");
        for(int i = 0; i < (int)matrix.size(); i++){
            for(int j = 0; j < (int) matrix.size();j++){
                ui->forMatrix->setPlainText(ui->forMatrix->toPlainText() + "\t" + QString::number(matrix[i][j]));
            }
            ui->forMatrix->setPlainText(ui->forMatrix->toPlainText() + "\n");
        }
    }
};

#endif // PAINTGRAPH_H
