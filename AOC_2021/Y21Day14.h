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
    static std::vector<char> _polymer;
    static QMap<std::string, char>  _rules;
    static QMap<std::string, unsigned long long int>  _counter;
    static QMap<std::string, unsigned long long int>  _newCounter;

    static void readInput();
    static void applyRules();
    static void countPoint();

    static void readInput2();
    static void applyRules2();
    static void countPoint2();
    static void displayCounter();
    static void displayLetterCounter(QMap<char, unsigned long long> &letterCounter);
};

#endif // Y21DAY14_H
