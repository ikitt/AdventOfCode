#ifndef Y20DAY04_H
#define Y20DAY04_H


#include <QString>
#include <QStringList>
#include <QList>
#include <QRegularExpression>

class Y20Day04
{
public:
    Y20Day04();

    typedef struct{
        bool isOk = false;
        QString completeStr = "";
        QString byr = ""; // (Birth Year)
        QString iyr = ""; // (Issue Year)
        QString eyr = ""; // (Expiration Year)
        QString hgt = ""; // (Height)
        QString hcl = ""; // (Hair Color)
        QString ecl = ""; // (Eye Color)
        QString pid = ""; // (Passport ID)
        QString cid = ""; // (Country ID)
    } Passport;

    static int computFirstResult();
    static int computSecondResult();

private:
    static const QStringList _input;

    static Passport fillPassport(QList<Passport>& list, QString passStr);
    static bool passIsValid_partial(QString pass);
    static bool passIsValid(Passport& pass);
    static bool containString(QString input, QString shouldBeIn);

    static bool validate_byr(Passport pass);
    static bool validate_iyr(Passport pass);
    static bool validate_eyr(Passport pass);
    static bool validate_hgt(Passport pass);
    static bool validate_hcl(Passport pass);
    static bool validate_ecl(Passport pass);
    static bool validate_pid(Passport pass);
};

#endif // Y20DAY04_H
