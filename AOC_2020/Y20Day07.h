#ifndef Y20DAY07_H
#define Y20DAY07_H


#include <QRegularExpression>
#include <QStringList>
#include <QMap>

class Y20Day07
{
public:
    Y20Day07();

    static int computFirstResult();
    static int computSecondResult();

private:
    static const QStringList _input;
    static QMap<QString, QMap<QString, unsigned int>> containedColor; // QMap<Outmost bag color, QMap<Inside bag color, number of bag>>
    static bool computeRules();
};





class Bag
{
public:
    Bag();
    Bag(QString color);

    const QString _color;
    QMap<QString, int> _directContent;
    QMap<QString, int> _indirectContent;

    void printDirectContent();
    void printIndirectContent();

    static void fillIndirectContent(QMap<QString, Bag*> bagsList);
    static void recursiveAdd(QString baseColor, QString curentColor, int factor, QMap<QString, Bag*> bagsList);
    void addToColor(QString color, int number);

private:
    static const QStringList _input;
    static QMap<QString, QMap<QString, unsigned int>> containedColor; // QMap<Outmost bag color, QMap<Inside bag color, number of bag>>
    static bool computeRules();
};

#endif // Y20DAY07_H
