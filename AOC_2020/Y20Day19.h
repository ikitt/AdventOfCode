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
    static int computSecondResult();


private:
    static const QVector<QString> _input;
    static QMap<int /*rules id*/, QString /*equivalent*/> _baseRules;
    static QMap<int /*rules id*/, QString /*equivalent*/> _completedRules;
    static QStringList _msg;

    static void readInput();
    static void computeRules();
    static void checkAndAddRule(QPair<int, QString> ruleToCheck);
    static QString replaceInRules(QString ruleToModif, int ruleId, QString ruleToInsert);
    static int countMsgMatching(int ruleId);

    static void readInput2();
    static void computeRules2();
    static void checkAndAddRule2(QPair<int, QString> ruleToCheck);
    static QString replaceInRules2(QString ruleToModif, int ruleId, QString ruleToInsert);
    static int countMsgMatching2(int ruleId);
};

#endif // Y20DAY19_H
