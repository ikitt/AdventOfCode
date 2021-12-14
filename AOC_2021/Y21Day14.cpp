#include "Y21Day14.h"

#include <QPair>
#include <QList>

Y21Day14::Y21Day14()
{

}


void Y21Day14::computFirstResult()
{
    fprintf(stdout, "Start Day 14 second part\r\n");
    fflush(stdout);

    readInput2();
    for(int i = 0; i < 10; i++)
    {
        fprintf(stdout, "Turn %i\r\n",i);
        fflush(stdout);
        applyRules2();
//        displayCounter();

    }
    countPoint2();
}


void Y21Day14::computSecondResult()
{
    fprintf(stdout, "Start Day 14 second part\r\n");
    fflush(stdout);

    readInput2();
    for(int i = 0; i < 40; i++)
    {
        fprintf(stdout, "Turn %i\r\n",i);
        fflush(stdout);
        applyRules2();
//        displayCounter();

    }
    countPoint2();
}

void Y21Day14::readInput()
{
    bool inRules = false;
    _polymer = {};
    for(QString line : _input)
    {
        line = line.simplified();
        if(!inRules)
        {
            if(line.isEmpty())
                inRules = true;
            else
                for(QChar letter : line)
                    _polymer.push_back(letter.toLatin1());
        }
        else
        {
            QStringList splittedRule = line.split(" -> ", QString::SkipEmptyParts);
            std::string pair = "";
            pair.resize(2);
            pair[0] = splittedRule[0][0].toLatin1();
            pair[1] = splittedRule[0][1].toLatin1();
            _rules[pair] = splittedRule[1][0].toLatin1();
        }
    }
}


void Y21Day14::applyRules()
{
    char pair[2];
    std::vector<char> nextLine = {};
    unsigned long long int nextLineIdx = 0;
    int nonRulesPair = 0;
    nonRulesPair = _polymer.size()*2-1;
    nextLine.resize(_polymer.size()*2-1);
    nonRulesPair = 0;
    nonRulesPair = 0;
    nonRulesPair = 0;
    for(unsigned long long int  idx = 0 ; idx < (_polymer.size()-1); idx++)
    {
        pair[0] = _polymer[idx];
        pair[1] = _polymer[idx+1];
        nextLine[nextLineIdx++] = pair[0];
        if(_rules.keys().contains(pair))
        {
            nextLine[nextLineIdx++] = _rules[pair];
            nextLine[nextLineIdx++] = pair[1];

//            _polymer.insert(idx+1, _rules[pair]);
        }
        else
        {
            throw std::runtime_error("fuck");
        }
    }
    _polymer = nextLine;

//    QString pair="";
//    for(int idx = _polymer.size()-2 ; idx >= 0; idx--)
//    {
//        pair = _polymer.mid(idx,2);
//        if(_rules.keys().contains(pair))
//        {
//            _polymer.insert(idx+1, _rules[pair]);
//        }
//    }

//    for(int idx = 0 ; idx < _polymer.size()-1 ; idx++)
//    {
//        pairList.push_back(_polymer.mid(idx,2));
//    }
//    for(int idx = pairList.size()-1 ; idx >= 0; idx--)
//    {
//    }

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


void Y21Day14::readInput2()
{
    bool inRules = false;
    _polymer = {};
    _counter = {};
    _newCounter = {};
    for(QString line : _input)
    {
        line = line.simplified();
        if(!inRules)
        {
            if(line.isEmpty())
                inRules = true;
            else
                for(QChar letter : line)
                    _polymer.push_back(letter.toLatin1());
        }
        else
        {
            QStringList splittedRule = line.split(" -> ", QString::SkipEmptyParts);
            std::string pair = "";
            pair.resize(2);
            pair[0] = splittedRule[0][0].toLatin1();
            pair[1] = splittedRule[0][1].toLatin1();
            _rules[pair] = splittedRule[1][0].toLatin1();

            _counter[pair] = 0;
            _newCounter[pair] = 0;
        }
    }
//    displayCounter();

    std::string pair = "";
    pair.resize(2);

    for(unsigned long long int idx = 0 ; idx < (_polymer.size()-1); idx++)
    {
        pair[0] = _polymer[idx];
        pair[1] = _polymer[idx+1];
        _counter[pair] = _counter[pair] +1;
//        displayCounter();
    }
}


void Y21Day14::applyRules2()
{
    QMap<std::string, unsigned long long int>  nextCounter = _newCounter;
    for(std::string cpair : _counter.keys())
    {
        std::string pair_l = ""; std::string  pair_r = "";
        pair_l.resize(2);pair_r.resize(2);
        pair_l[0] = cpair[0];
        pair_l[1] = _rules[cpair];
        pair_r[0] = _rules[cpair];
        pair_r[1] = cpair[1];

//        fprintf(stdout, "From pair %s up %s and %s\r\n", cpair.c_str(), pair_l.c_str(), pair_r.c_str());
//        fflush(stdout);

        nextCounter[pair_l] = nextCounter[pair_l]+_counter[cpair];
        nextCounter[pair_r] = nextCounter[pair_r]+_counter[cpair];
    }
    _counter = nextCounter;
}

void Y21Day14::countPoint2()
{
    QMap<char,unsigned long long int> letterCounter = {};
    for(std::string key : _counter.keys())
    {
        char letter0 = key[0];
        char letter1 = key[1];

        if(letterCounter.keys().contains(letter0))
            letterCounter[letter0] = letterCounter[letter0]+_counter[key];
        else
            letterCounter[letter0] = _counter[key];

        if(letterCounter.keys().contains(letter1))
            letterCounter[letter1] = letterCounter[letter1]+_counter[key];
        else
            letterCounter[letter1] = _counter[key];

//        displayLetterCounter(letterCounter);

    }

    letterCounter[_polymer.front()] += 1;
    letterCounter[_polymer.back()] += 1;

//    displayLetterCounter(letterCounter);

    char highestLetter = 'N';
    char lowestLetter = 'N';
    for(char key : letterCounter.keys())
    {
        if(letterCounter[key] > letterCounter[highestLetter])
            highestLetter = key;

        if(letterCounter[key] < letterCounter[lowestLetter])
            lowestLetter = key;
    }


    fprintf(stdout, "Max char is %c(%llu) and lowest %c(%llu) so result is %llu\r\n", highestLetter, letterCounter[highestLetter]/2, lowestLetter, letterCounter[lowestLetter]/2, (letterCounter[highestLetter] - letterCounter[lowestLetter])/2);
    fflush(stdout);
}

void Y21Day14::displayCounter()
{
    fprintf(stdout, "####\r\n");
    for(std::string key: _counter.keys())
    {

        fprintf(stdout, "For pair %s got %llu occurences\r\n", key.c_str(), _counter[key]);
        fflush(stdout);
    }
}

void Y21Day14::displayLetterCounter(QMap<char,unsigned long long int>& letterCounter)
{
    fprintf(stdout, "#### letter counter\r\n");
    for(char key: letterCounter.keys())
    {

        fprintf(stdout, "For pair %c got %llu occurences\r\n", key, letterCounter[key]);
        fflush(stdout);
    }
}

std::vector<char> Y21Day14::_polymer = {};
QMap<std::string, char> Y21Day14::_rules = {};
QMap<std::string, unsigned long long int>  Y21Day14::_counter = {};
QMap<std::string, unsigned long long int>  Y21Day14::_newCounter = {};
//exemple input =>
/*Res first part =
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

// /*
// Res first part => 3406
// Res second  part => 3941782230241
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
