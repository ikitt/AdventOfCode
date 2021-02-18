#ifndef Y20DAY12_H
#define Y20DAY12_H


#include <QVector>
#include <QString>

#include <cmath>


// {-5, 10} mean 5 West/10 North
typedef QPair<int, int> coordinate;

enum direction {
    NORTH,
    SOUTH,
    WEST,
    EST
};

enum instruction {
    N,
    S,
    E,
    W,
    L,
    R,
    F
};



class Ship
{
public:

    Ship(direction orientation, coordinate position);

    direction _direction = EST;
    coordinate _coordinate = {0,0};

    void move(instruction instruction, int power);
    static void moveWithWaypoint(instruction instruction, int power, Ship &ship, Ship &waypoint);

    void turnLeft();
    void turnRight();

    void rotateLeft();
    void rotateRight();

    void printPosition();


};


class Y20Day12
{
public:
    Y20Day12();

    static int computFirstResult();
    static int computSecondResult();

    static instruction instructionFromString(QString instru);
    static QString instructionToString(instruction instru);
    static QString directionToString(direction dir);

private:
    static const QVector<QString> _input;

    static const QVector<QPair<instruction /*orientation*/, int /*power*/>> _formatedInput;
};

#endif // Y20DAY12_H
