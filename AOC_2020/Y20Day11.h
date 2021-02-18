#ifndef Y20DAY11_H
#define Y20DAY11_H

#include <QVector>
#include <QString>


class Map
{
public:
    Map();
    Map(const Map& copy);
    Map(const QVector<QString>);


    QVector<QString> getNeighbourg(int row, int column) const;
    QVector<QString> getVisible(int row, int column) const;

    int countEmpty() const;
    int countOccup() const;
    int countFloor() const;
    int countEmpty(int row, int column) const;
    int countOccup(int row, int column) const;
    int countFloor(int row, int column) const;

    static Map computeNext(const Map& initialState);
    static Map computeNextVisible(const Map& initialState);

    void print();

    inline bool operator==(const Map& other) {return (_map == other._map);};


    static const QString EMPTY;
    static const QString OCCUP;
    static const QString FLOOR;

    static const int OCCUP_TH;
    static const int EMPTY_TH;

private:
    QVector<QVector<QString>> _map;
    bool coorOk(QPair<int,int> dir) const;
};


class Y20Day11
{
public:
    Y20Day11();

    static int computFirstResult();
    static int computSecondResult();

private:
    static const QVector<QString> _input;

};

#endif // Y20DAY11_H
