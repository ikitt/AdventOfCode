#ifndef Y20DAY1_H
#define Y20DAY1_H

#include <QString>
#include <QVector>
#include <QDateTime>

class Y20Day1
{
public:
    Y20Day1();

    static int answerPuzzle1();
    static int answerPuzzle2();
    static int answerPuzzle2NoOpti();

private:
    static const QVector<int> _input;
};

#endif // Y20DAY1_H
