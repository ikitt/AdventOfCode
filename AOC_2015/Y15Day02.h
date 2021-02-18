#ifndef Y15DAY02_H
#define Y15DAY02_H


#include <QString>
#include <QStringList>
#include <QList>

class Y15Day02
{
public:
    Y15Day02();

typedef struct{
    int l;
    int h;
    int w;
} Dimension;

    static int computFirstResult();
    static int computSecondResult();
private:
    static const QStringList _input;
};

#endif // Y15DAY02_H
