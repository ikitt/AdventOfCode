#ifndef Y21DAY10_H
#define Y21DAY10_H

#include <QString>
#include <QVector>
#include <QMap>

class Y21Day10
{
public:
    Y21Day10();

    static void computFirstResult();
    static void computSecondResult();



private:
    static const QVector<QString> _input;
    static const QString _openChunk;
    static const QString _closeChunk;
    static const QMap<char, int>_pointMap;
    static const QMap<char, int>_pointIncomplete;
    static const QMap<QChar,QChar>_closingMap;

};

#endif // Y21DAY10_H
