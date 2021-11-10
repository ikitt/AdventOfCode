#ifndef Y20DAY19BIS_H
#define Y20DAY19BIS_H

#include <QVector>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QRegularExpression>

#include <bitset>

class Y20Day19Bis
{
public:
    Y20Day19Bis();

    static int computFirstResult();
    static int computSecondResult();


private:
    static const QVector<QString> _input;

//    std::list<std::bitset> copain;

    static QMap<int /*rules id*/, QString /*equivalent*/> _baseRules;
    static QMap<int /*rules id*/, QString /*equivalent*/> _completedRules;
    static QStringList _msg;
    static int _maxMsgSize;
    static int _minMsgSize;

    static void readInput();
    static void computeRules();
    static void checkAndAddRule(QPair<int, QString> ruleToCheck);
    static QString replaceInRules(QString ruleToModif, int ruleId, QString ruleToInsert);
    static int countMsgMatching(int ruleId);

    static void completeLoopRule();
    static bool loopingRulesMaxed(QString rule);

    static void readInput2();
    static void computeRules2();
    static void checkAndAddRule2(QPair<int, QString> ruleToCheck);
    static QString replaceInRules2(QString ruleToModif, int ruleId, QString ruleToInsert);
    static int countMsgMatching2(int ruleId);
};

#endif // Y20DAY19BIS_H
