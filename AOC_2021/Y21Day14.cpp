#include "Y21Day14.h"

#include <QPair>
#include <QList>

Y21Day14::Y21Day14()
{

}


void Y21Day14::computFirstResult()
{
    fprintf(stdout, "Start Day 14 first part\r\n");
    fflush(stdout);

    readInput();
    for(int i = 0; i < 10; i++)
        applyRules();
    countPoint();
}


void Y21Day14::computSecondResult()
{
    fprintf(stdout, "Start Day 14 second part\r\n");
    fflush(stdout);

    readInput();
    for(int i = 0; i < 40; i++)
    {
        fprintf(stdout, "Turn %i \r\n", i);
        fflush(stdout);
        applyRules();
    }
    countPoint();
}

void Y21Day14::readInput()
{
    bool inRules = false;
    for(QString line : _input)
    {
        line = line.simplified();
        if(!inRules)
        {
            if(line.isEmpty())
                inRules = true;
            else
                _polymer = line;
        }
        else
        {
            QStringList splittedRule = line.split(" -> ", QString::SkipEmptyParts);
            _rules[splittedRule[0]] = splittedRule[1][0];
        }
    }
}

void Y21Day14::applyRules()
{
    QVector<QString> pairList = {};
    QString pair="";
    for(int idx = _polymer.size()-2 ; idx >= 0; idx--)
    {
        pair = _polymer.mid(idx,2);
        if(_rules.keys().contains(pair))
        {
            _polymer.insert(idx+1, _rules[pair]);
        }
    }/*
    for(int idx = 0 ; idx < _polymer.size()-1 ; idx++)
    {
        pairList.push_back(_polymer.mid(idx,2));
    }
    for(int idx = pairList.size()-1 ; idx >= 0; idx--)
    {
    }*/
//    fprintf(stdout, "After rules _polymer is %s\r\n", _polymer.toStdString().c_str());
//    fflush(stdout);
    //For each pair from end to begin insert if corresponding rules exist
}

void Y21Day14::countPoint()
{
    QMap<QChar,unsigned long long int> letterCounter = {};
    for(QChar letter : _polymer)
    {
        if(letterCounter.keys().contains(letter))
            letterCounter[letter] = letterCounter[letter]+1;
        else
            letterCounter[letter] = 1;
    }

    QChar highestLetter = 'N';
    QChar lowestLetter = 'N';
    for(QChar key : letterCounter.keys())
    {
        if(letterCounter[key] > letterCounter[highestLetter])
            highestLetter = key;

        if(letterCounter[key] < letterCounter[lowestLetter])
            lowestLetter = key;
    }


    fprintf(stdout, "Max char is %c(%llu) and lowest %c(%llu) so result is %llu\r\n", highestLetter.toLatin1(), letterCounter[highestLetter], lowestLetter.toLatin1(), letterCounter[lowestLetter], letterCounter[highestLetter] - letterCounter[lowestLetter]);
    fflush(stdout);
}


QString  Y21Day14::_polymer = {};
QMap<QString, QChar> Y21Day14::_rules = {};
//exemple input =>
///*Res first part =
///*Res second part =
const QVector<QString> Y21Day14::_input = {
    "NNCB   ",
    "       ",
    "CH -> B",
    "HH -> N",
    "CB -> H",
    "NH -> C",
    "HB -> C",
    "HC -> B",
    "HN -> C",
    "NN -> C",
    "BH -> H",
    "NC -> B",
    "NB -> B",
    "BN -> B",
    "BB -> N",
    "BC -> B",
    "CC -> N",
    "CN -> C"
};
// */

 /*
// Res first part => 3406
// Res second  part
const QVector<QString> Y21Day14::_input = {
    "KOKHCCHNKKFHBKVVHNPN",
    "       ",
    "BN -> C",
    "OS -> K",
    "BK -> C",
    "KO -> V",
    "HF -> K",
    "PS -> B",
    "OK -> C",
    "OC -> B",
    "FH -> K",
    "NV -> F",
    "HO -> H",
    "KK -> H",
    "CV -> P",
    "SC -> C",
    "FK -> N",
    "VV -> F",
    "FN -> F",
    "KP -> O",
    "SB -> O",
    "KF -> B",
    "CH -> K",
    "VF -> K",
    "BH -> H",
    "KV -> F",
    "CO -> N",
    "PK -> N",
    "NH -> P",
    "NN -> C",
    "PP -> H",
    "SH -> N",
    "VO -> O",
    "NC -> F",
    "BC -> B",
    "HC -> H",
    "FS -> C",
    "PN -> F",
    "CK -> K",
    "CN -> V",
    "HS -> S",
    "CB -> N",
    "OF -> B",
    "OV -> K",
    "SK -> S",
    "HP -> C",
    "SN -> P",
    "SP -> B",
    "BP -> C",
    "VP -> C",
    "BS -> K",
    "FV -> F",
    "PH -> P",
    "FF -> P",
    "VK -> F",
    "BV -> S",
    "VB -> S",
    "BF -> O",
    "BB -> H",
    "OB -> B",
    "VS -> P",
    "KB -> P",
    "SF -> N",
    "PF -> S",
    "HH -> P",
    "KN -> K",
    "PC -> B",
    "NB -> O",
    "VC -> P",
    "PV -> H",
    "KH -> O",
    "OP -> O",
    "NF -> K",
    "HN -> P",
    "FC -> H",
    "PO -> B",
    "OH -> C",
    "ON -> N",
    "VN -> B",
    "VH -> F",
    "FO -> B",
    "FP -> B",
    "BO -> H",
    "CC -> P",
    "CS -> K",
    "NO -> V",
    "CF -> N",
    "PB -> H",
    "KS -> P",
    "HK -> S",
    "HB -> K",
    "HV -> O",
    "SV -> H",
    "CP -> S",
    "NP -> N",
    "FB -> B",
    "KC -> V",
    "NS -> P",
    "OO -> V",
    "SO -> O",
    "NK -> K",
    "SS -> H"
};
// */
