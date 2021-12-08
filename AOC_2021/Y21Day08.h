#ifndef Y21DAY08_H
#define Y21DAY08_H

#include <QString>
#include <QVector>

class Y21Day08
{
public:
    Y21Day08();

    static void computFirstResult();
    static void computSecondResult();



private:
    static const QVector<QString> _input;
    static const QVector<int> _nbrSegments;
    static QVector<QString> _digitEquivalent;

    static void get1478(QStringList& unknownDigit);
    static void get3(QStringList& unknownDigit);
    static void get9(QStringList& unknownDigit);
    static void get0(QStringList& unknownDigit);
    static void get6(QStringList& unknownDigit);
    static void get5(QStringList& unknownDigit);
    static void get2(QStringList& unknownDigit);

    static bool firstIncludeSecond(QString first, QString second);
    static bool isEquivalent(QString first, QString second);

    static void printKnown();
    static int getOutInteger(QStringList output);

};

#endif // Y21DAY08_H
