#ifndef Y20DAY14_H
#define Y20DAY14_H


#include <QVector>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QTimer>
#include <QTime>
#include <QRegularExpression>

#include <cmath>


class Y20Day14
{
public:
    Y20Day14();

    static unsigned long long int computFirstResult();
    static unsigned long long int computSecondResult();


private:
    static const QVector<QString> _input;

    static void readNextInput();
    static unsigned long long int getMaxMemIdx();
    static unsigned long long int applyMaskV1On(unsigned long long int value);
    static QString applyMaskV2On(unsigned long long int value);

    static unsigned long long int stringToInt(QString intput);
    static QString intToString(unsigned long long int intput);
    static QStringList possibleStrValue(QString input);

//    static void forEachPossibility(QString& idxStr, std::function<void(unsigned long long int)>(funLambda));
    static void forEachPossibility(QString& idxStr, std::function<void(unsigned long long int)>& (funLambda));

    static void myTest(std::function<void(unsigned long long int)>& marco);

    static void testLambda( void(*billy)(int));

    static unsigned long long int currentInputIdx;
    static QString currentMask;
    static QRegularExpression maskRegExp;
    static QRegularExpression memRegExp;
};

#endif // Y20DAY14_H


//"mem[23059] = 7959                          ",
//"mask = 0110X01X0110XX001X100010010X10110XX1",
