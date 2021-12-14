#ifndef Y21DAY14_H
#define Y21DAY14_H

#include <QString>
#include <QChar>
#include <QVector>
#include <QMap>


class Y21Day14
{
public:
    Y21Day14();

    static void computFirstResult();
    static void computSecondResult();



private:
    static const QVector<QString> _input;
    static QString _polymer;
    static QMap<QString, QChar> _rules;

    static void readInput();
    static void applyRules();
    static void countPoint();
};

#endif // Y21DAY14_H
