#include "koch.h"
#include <QObject>





Koch::Koch(QObject *parent)
    : QObject(parent)
{

}

Koch::~Koch()
{

}
Koch::Koch()
{

}

void Koch::generateKoch(QPointF qa, QPointF qb){


    double ax = qa.x(), ay = qa.y(), bx = qb.x(), by = qb.y();
    //qDebug() << (ax - bx)*(ax - bx) + (ay - by) *(ay - by);
    if (k == 0){
        curvePoints1.push_back(qa);
        curvePoints1.push_back(qb);
        starL = sqrt((ax - bx)*(ax - bx) + (ay - by) *(ay - by));
    }
    if ((ax - bx)*(ax - bx) + (ay - by) *(ay - by) > 120 ){
        //if ((ax - bx) ^ 2 + (ay - by) ^ 2 > 100  && 3*k+2<pow(4,KochK)+1){
        QPointF qc, qd, qe;
        double cx, cy, dx, dy, ex, ey, l, alpha;
        double diff3x = (bx - ax) / 3;
        double diff3y = (by - ay) / 3;
        cx = ax + diff3x; cy = ay + diff3y;
        ex = bx - diff3x; ey = by - diff3y;
        l = sqrt((ax - bx)*(ax - bx) + (ay - by) *(ay - by)) / 3;
        alpha = atan((ey - cy) / (ex - cx));
        if (((alpha >= 0) && (ex - cx) < 0) ||
            ((alpha <= 0) && (ex - cx < 0))) {
            alpha = alpha + 3.1415;
        }
        dx = cx + cos(alpha - 3.1415 / 3)*l;
        dy = cy + sin(alpha - 3.1415 / 3)*l;
        //dx = cx + 0.5*ex - 1.732*0.5*ey;
        //dy = cy + 0.5*ey + 1.732*0.5*ex;
        qc.setX(cx); qc.setY(cy); qd.setX(dx); qd.setY(dy); qe.setX(ex); qe.setY(ey);
        //curvePoints1.insert(1, qc);
        //curvePoints1.insert(2, qd);
        //curvePoints1.insert(3, qe);
        k++;
        //qDebug() << k;
        //qDebug() << pow(4, KochK) + 1;
        //qDebug() << curvePoints1.size();
        Koch::generateKoch(qa, qc);
        Koch::generateKoch(qc, qd);
        Koch::generateKoch(qd, qe);
        Koch::generateKoch(qe, qb);
    }
    else{
        QLineF tmp1(qa,qb);
        curveLine.push_back(tmp1);
    }
}


