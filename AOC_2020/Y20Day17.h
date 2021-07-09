#ifndef Y20DAY17_H
#define Y20DAY17_H

#include <QVector>
#include <QString>


class Grid17
{
//          ^  z
//           \
//            \
//             |--> y
//             |
//             V x
//
public:
    Grid17(int max_x, int max_y, int max_z);

    QVector<QVector<QVector<bool>>> _grid;

    int countActiveNeighbors(int x, int y, int z);

    void print();
private:

};


class HyperGrid17
{
//          ^  z
//           \
//            \
//             |--> y
//             |
//             V x
//
public:
    HyperGrid17(int max_x, int max_y, int max_z, int max_w);

    QVector<QVector<QVector<QVector<bool>>>> _grid;

    int countActiveNeighbors(int x, int y, int z, int w);

    void print();
private:

};


class Y20Day17
{
public:
    Y20Day17();

    static int computFirstResult();
    static int computSecondResult();


private:
    static const QVector<QString> _input;

    static Grid17 _previousGrid;
    static Grid17 _currentGrid;

    static HyperGrid17 _previousHyperGrid;
    static HyperGrid17 _currentHyperGrid;
};


#endif // Y20DAY17_H
