#ifndef Y20DAY13_H
#define Y20DAY13_H


#include <QVector>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QTimer>
#include <QTime>

//#include <algorithm>

typedef  struct{
    qint64 period;
    qint64 position;
    qint64 current;
    int dutyCycle;
    qint64 firstValidCoef;
} busSchedule;

class Y20Day13
{
public:
    Y20Day13();

    static int computFirstResult();
    static int computSecondResult(const qint64 & start = 0, const uint & id = 0);
    static int computSecondResultBrain();
    static int computSecondResultBrainBis();
    static int computSecondResultBrutThread(const qint64 & start = 0, const qint64 & stop = 0,const uint & id = 0);

    static QMap<int /*id*/,int /*schedule*/> _firstAvailableSchedule;

    static qint64 closestFollowingTime(const qint64 & ref, const qint64 & period, const qint64 & start = 0, const int &position = 0); // >=

private:
    static  QVector<busSchedule> _timeSheet;
    static const QVector<QString> _input;

    static busSchedule mixBus(busSchedule busOne, busSchedule busTwo);
    static qint64 findFirstValid(busSchedule busOne, busSchedule busTwo);
    static qint64 positionAt0(busSchedule busOne, busSchedule busTwo);
};

#endif // Y20DAY13_H
