#ifndef Y20DAY18_H
#define Y20DAY18_H

#include <QVector>
#include <QString>

class Y20Day18
{
public:
    Y20Day18();

    static QString computFirstResult();
    static QString computSecondResult();


private:
    static const QVector<QString> _input;

    static const QString _digit;

    static unsigned long long int computeLine(QString line, int idx = 0);
    static QString computeLineSecond(QString line, int idx = 0);
    static int getParenthesisEnd(QString line, int idx);
    static QString bigSumAsString(QVector<QString> eachRes);
    static QString bigTimeAsString(QString left, QString right);
};

#endif // Y20DAY18_H
