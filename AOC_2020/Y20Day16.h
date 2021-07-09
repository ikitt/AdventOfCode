#ifndef Y20DAY16_H
#define Y20DAY16_H

#include <QVector>
#include <QString>
#include <QStringList>
#include <QRegularExpression>

class Y20Day16
{
public:
    Y20Day16();

    static int computFirstResult();
    static unsigned long long int computSecondResult();


private:
    static const QVector<QString> _input;

    static QVector<int> _myTicket;
    static QVector<QVector<int>> _allTickets;
    static QVector<bool> _validValue;
    static QMap<QString, QVector<bool>> _fields;

    static int _tsre;

    static QVector<QList<QString>> _possibleFieldsByIndex;


    static void fillFields();
    static void addPossibleFields(QString line);
    static void removeImpossibleTickets();
    static void shrinkPossibleFiels();
    static void loopToRemoveKnownFields();
};

#endif // Y20DAY16_H
