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
    int period;
    int position;
    quint64 current;
    int dutyCycle;
    quint64 firstValidCoef;
} busSchedule;

class Y20Day13
{
public:
    Y20Day13();

    static int computFirstResult();
    static int computSecondResult(const quint64 & start = 0, const uint & id = 0);
    static int computSecondResultBrain();
    static int computSecondResultBrutThread(const quint64 & start = 0, const quint64 & stop = 0,const uint & id = 0);

    static QMap<int /*id*/,int /*schedule*/> _firstAvailableSchedule;

    static quint64 closestFollowingTime(const quint64 & ref, const quint64 & period, const quint64 & start = 0, const int &position = 0); // >=

private:
    static  QVector<busSchedule> _timeSheet;
    static const QVector<QString> _input;
};

#endif // Y20DAY13_H
