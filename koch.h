#ifndef KOCH_H
#define KOCH_H

#include <QPoint>

#include <QObject>
#include <math.h>
#include <QDebug>
#include <QLine>
#include <QVector>
#include <QObject>
#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QPaintEvent>
#include <cmath>
#include <QCursor>
//#include "ui_palette.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QtGui>
#include <QWidget>
#include <QPainter>
#include <QtWidgets/QMainWindow>
#include<iostream>
#include <stdio.h>
//#include <tchar.h>
//#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <iostream>
//#include <DLNADeviceInterfaceIds.h>
#include "math.h"
#include "stdlib.h"
#include <QLabel>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QPushButton>
#include <qglobal.h>
class Koch : public QObject
{
    Q_OBJECT

public:
    Koch(QObject *parent);
    ~Koch();
    Koch();
    int KochK=3;
    int k = 0;
    QVector<QPointF> ctrlPoints;  // 控制点
    QVector<QPointF> curvePoints; // 所有曲线上的点
    QVector<QPointF> curvePoints1; // 两个控制点间的曲线点
    QVector<QLineF> curveLine; // 两个点间的曲线
    void generateKoch(QPointF qa, QPointF qb);
private:
    double starL;
};


#endif // KOCH_H
