#ifndef Y21DAY05_H
#define Y21DAY05_H

#include <QString>
#include <QVector>
#include <QPair>

#include "utils/commonStruct.h"


class Y21Day05
{
public:
    Y21Day05();

    static void computFirstResult();
    static void computSecondResult();

private:
    static QVector<Line> _lines;
    static QVector<QVector<int>> _map;
    static int _max_x;
    static int _max_y;
    static int _twoPlusCounter;
    static const QVector<QString> _input;

    static void fileLines();
    static void makeMap(bool withDiag  = false);
    static QVector<Point> getPointList(const Line & line, bool withDiag = false);
    static void printMap();

};

#endif // Y21DAY05_H
