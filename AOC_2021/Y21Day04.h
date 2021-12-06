#ifndef Y21DAY04_H
#define Y21DAY04_H

#include <QString>
#include <QVector>

typedef struct Grid{
    QVector<QVector<int>> line;
    QVector<QVector<int>> column;
} Grid;


class Y21Day04
{
public:
    Y21Day04();

    static void computFirstResult();
    static void computSecondResult();
    static char mostCommonChar(const QVector<QString> & input, int idx);

    static void readInput();
    static void printGrids();

private:
    static QVector<int> _bNum;
    static QVector<Grid> _gridList;
    static const QVector<QString> _input;
};

#endif // Y21DAY04_H
