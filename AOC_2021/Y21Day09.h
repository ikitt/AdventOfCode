#ifndef Y21DAY09_H
#define Y21DAY09_H

#include <QString>
#include <QVector>


class Map
{
public:
    Map();
//    Map(const Map& copy);
    Map(const QVector<QString>);


    QVector<int> getNeighbourg(int row, int column) const;
    QVector<QVector<int>> getVisible(int row, int column) const;

    bool isLowPoint(int row, int column);
//    int countEmpty() const;
//    int countOccup() const;
//    int countFloor() const;
//    int countEmpty(int row, int column) const;
//    int countOccup(int row, int column) const;
//    int countFloor(int row, int column) const;

//    static Map computeNext(const Map& initialState);
//    static Map computeNextVisible(const Map& initialState);

    void print();

    inline bool operator==(const Map& other) {return (_map == other._map);};


//    static const QString EMPTY;
//    static const QString OCCUP;
//    static const QString FLOOR;

//    static const int OCCUP_TH;
//    static const int EMPTY_TH;
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
