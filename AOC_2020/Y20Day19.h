#ifndef Y20DAY19_H
#define Y20DAY19_H

#include <QVector>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QRegularExpression>

class Y20Day19
{
public:
    Y20Day19();

    static int computFirstResult();
    static QString computSecondResult();


private:
    static const QVector<QString> _input;
    static QMap<int /*rules id*/, QStringList /*equivalent*/> _baseRules;
    static QMap<int /*rules id*/, QStringList /*equivalent*/> _completedRules;
    static QStringList _msg;

    static void readInput();
    static void computeRules();
    static void checkAndAddRule(QPair<int, QStringList> ruleToCheck);
};

#endif // Y20DAY19_H
