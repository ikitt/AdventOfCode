#ifndef Y21DAY18_H
#define Y21DAY18_H

#include <QString>
#include <QVector>


//class SnailPair
//{
//public:
//    SnailPair();

//    SnailPair operator+ (const SnailPair & first) const;

//    void print();
//    void reduce();

//    unsigned long long int magnitude();

//    bool isPair;

//private:
//    void explode();

//};

class Y21Day18
{
public:
    Y21Day18();

    static void computFirstResult();
    static void computSecondResult();



private:
    static const QVector<QString> _input;

    static QString addPair(QString left, QString right);
    static void reducePair(QString& pair);
    static bool explodev0(QString& pair, int depth=0);
    static bool explode(QString& pair);
    static void propagateRightFrom(QString& pair, int toProp, int from);
    static void propagateLeftFrom(QString& pair, int toProp, int from);
    static bool split(QString& pair);
    static unsigned long long int getMagnitude(const QString& pair);
    static QPair<QString, QString> getLeftRight(const QString& pair);
    static bool isPair(const QString& str);
    static QString makePair(const QString& left, const QString& right);
    static QString getPairFromSplit(const QString& highIntStr);

    void quickAndDirtyPointerTest(QString * pstr);
    void bisQuickAndDirtyPointerTest(QString * pstr);
};

#endif // Y21DAY18_H
