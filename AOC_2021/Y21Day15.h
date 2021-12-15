#ifndef Y21DAY15_H
#define Y21DAY15_H

#include <QString>
#include <QVector>

#include "utils/commonStruct.h"
#include "Y21Day09.h"


//class Map
//{
//public:
//    Map();
////    Map(const Map& copy);
//    Map(const QVector<QString>);


//    QVector<Point> getNeighbourg(int row, int column, bool withDiago = false) const;
//    QVector<QVector<int>> getVisible(int row, int column) const;

//    Point newPoint(int row, int column) const;

//    void print();

//    inline bool operator==(const Map& other) {return (_map == other._map);};

//    QVector<QVector<int>> _map;

//private:
//    bool coorOk(QPair<int,int> dir) const;
//};


class Y21Day15
{
public:
    Y21Day15();

    static void computFirstResult();
    static void computSecondResult();



private:
    static const QVector<QString> _input;

    static QVector<QVector<int>> _map;
    static void computePathMap(Map &riskMap, Map &pathMap);
};

#endif // Y21DAY15_H
