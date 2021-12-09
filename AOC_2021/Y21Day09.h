#ifndef Y21DAY09_H
#define Y21DAY09_H

#include <QString>
#include <QVector>

#include "utils/commonStruct.h"

typedef struct Bassin
{
    QVector<Point> points = {};
}Bassin;

class Map
{
public:
    Map();
//    Map(const Map& copy);
    Map(const QVector<QString>);


    QVector<Point> getNeighbourg(int row, int column, bool withDiago = false) const;
    QVector<QVector<int>> getVisible(int row, int column) const;

    bool isLowPoint(int row, int column);
    bool isLowPointOfStranger(const Point &pt, const Bassin& bass);
    bool isInBassin(Point pt, const Bassin &bas);

    void expandBassin(QVector<Point> lowPoints, Bassin &bass);

    Point newPoint(int row, int column) const;

    void print();

    inline bool operator==(const Map& other) {return (_map == other._map);};

    QVector<QVector<int>> _map;

private:
    bool coorOk(QPair<int,int> dir) const;
};


class Y21Day09
{
public:
    Y21Day09();

    static void computFirstResult();
    static void computSecondResult();



private:
    static const QVector<QString> _input;

    static QVector<QVector<int>> _map;
};

#endif // Y21DAY09_H
