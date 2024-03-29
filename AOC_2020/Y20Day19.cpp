#include "Y20Day19.h"

Y20Day19::Y20Day19()
{

}


int Y20Day19::computFirstResult()
{
    readInput();
    fprintf(stdout, "Input read finished.\r\n");
    fflush(stdout);
    computeRules();

    fprintf(stdout, "All the %i rules completed.\r\n", _completedRules.size());
    fflush(stdout);

    for(int idx : _completedRules.keys())
    {
//        fprintf(stdout, "Rule %i give \"%s\".\r\n", idx, _completedRules[idx].toStdString().c_str());
//        fflush(stdout);
    }

    fprintf(stdout, "There is %i message matching rule 0.\r\n", countMsgMatching(0));
    fflush(stdout);

    //Read
        //Get rules // crash if two rules with same id
        //Get messages
    //While loop over rules
        //found each occurence of each complete rules found on last turn
        // quit if all rules are complete, crash if no more rules complete this turn and still incomplete rules
    return 12;
}


int Y20Day19::computSecondResult()
{
    return computFirstResult(); //change 2 line in input to switch from day 1 to day 2.
}

void Y20Day19::readInput()
{
    bool inRules = true;
    for(QString line : _input)
    {
        line = line.simplified();

        if(line.isEmpty())
        {
            inRules = false;
            continue;
        }

        if(inRules)
        {
            int ruleId = line.split(":")[0].toInt();
            QString rule = line.split(":")[1].simplified();
            rule.append(" ");
            rule.prepend(" ");

            if(_baseRules.keys().contains(ruleId))
                throw std::runtime_error("Multiple definition for rules " + std::to_string(ruleId));
            else
                _baseRules[ruleId] = rule;
        }
        else
        {
            _msg << line.simplified();
            _maxMsgSize = std::max(_maxMsgSize, line.simplified().size());
            _minMsgSize = std::min(_minMsgSize, line.simplified().size());
        }
    }
}


void Y20Day19::computeRules()
{
    int completedRulesLastTurn = -1;

    int lastPrintCount = 0;

    for(int ruleId : _baseRules.keys())
    {
        checkAndAddRule({ruleId, _baseRules[ruleId] });
    }

    while (_completedRules.size() < _baseRules.size())
    {
        for(int ruleId : _baseRules.keys())
        {
            //Pass already completed rules
            if(_completedRules.keys().contains(ruleId))
                continue;

            for(QString atomicRule : _baseRules[ruleId].split(" "))
            {
                bool okConv;
                if(_completedRules.keys().contains(atomicRule.toInt(&okConv)) && okConv)
                {
                    _baseRules[ruleId] = replaceInRules(_baseRules[ruleId], atomicRule.toInt(), _completedRules[atomicRule.toInt()]);
                }
            }

            checkAndAddRule({ruleId, _baseRules[ruleId]});
        }

        if(_completedRules.size() == completedRulesLastTurn)
        {
            fprintf(stdout, "Start looping rules.\r\n");
            fflush(stdout);
            completeLoopRule();
        }

        completedRulesLastTurn = _completedRules.size();

        if((_completedRules.size() - lastPrintCount) > 5)
        {
            lastPrintCount = _completedRules.size();
            fprintf(stdout, "Got %i completed rules.\r\n", lastPrintCount);
            fflush(stdout);
        }
    }

    for(int ruleId : _completedRules.keys())
    {
        _completedRules[ruleId] = _completedRules[ruleId].remove(' ');
    }
}


void Y20Day19::checkAndAddRule(QPair<int, QString> ruleToCheck)
{
    bool ruleComplete = !ruleToCheck.second.contains(QRegularExpression("\\d"));


//    fprintf(stdout, "Check rule %s: %s which is", std::to_string(ruleToCheck.first).c_str(), ruleToCheck.second.toStdString().c_str());
//    fflush(stdout);

    if(ruleComplete)
    {
//        QString rule = ruleToCheck.second.remove(' ').replace('|', ' ');
//        _completedRules[ruleToCheck.first] = rule;
        _completedRules[ruleToCheck.first] = ruleToCheck.second;


//        fprintf(stdout, " complete.\r\n");
//        fflush(stdout);
    }
    else
    {

//        fprintf(stdout, " incomplete.\r\n");
//        fflush(stdout);
    }
}


QString Y20Day19::replaceInRules(QString ruleToModif, int ruleId, QString ruleToInsert)
{
    QStringList splitted = ruleToModif.split('|');

//    fprintf(stdout, "Insert %s in %s.\r\n", ruleToInsert.toStdString().c_str(), ruleToModif.toStdString().c_str());
//    fflush(stdout);

    for(int idx = 0 ; idx < splitted.size() ; idx ++)
    {
//        bool okConv;
        QString stringId = " " + QString::number(ruleId) + " ";
        if(splitted[idx].contains(stringId))
        {
            for(QString ored : ruleToInsert.split('|'))
            {
                QString base = splitted[idx];
                base.replace(stringId, ored);
                splitted.insert(idx + 1, base);
            }
            splitted.removeAt(idx);
        }
    }

//    fprintf(stdout, "Which return %s.\r\n", splitted.join('|').toStdString().c_str());
//    fflush(stdout);

    return splitted.join('|');
}

//V1 moisi
//void Y20Day19::completeLoopRule()
//{
//    QMap<int /*rules id*/, QString /*equivalent*/> loopingRules;

//    for(int ruleId : _baseRules.keys())
//    {
//        //Pass already completed rules
//        if(!_completedRules.keys().contains(ruleId))
//        {
//            loopingRules[ruleId] = _baseRules[ruleId];
//            //            /*C'est de la merde ça prend 5 plombe*/ fprintf(stdout, "Looping rule %i = %s\r\n", ruleId, _baseRules[ruleId].toStdString().c_str());
//            //            fflush(stdout);
//        }

//    }

//    while (!loopingRules.isEmpty())
//    {
//        fprintf(stdout, "LoopR:%i ;MaxS:%i; ", loopingRules.size(), _maxMsgSize);
//        for(int ruleId : loopingRules.keys())
//        {
//            fprintf(stdout, "IdR:%i ;S:%i; \r\n", ruleId, loopingRules[ruleId].size());
//        }
//        fflush(stdout);
//        for(int ruleId : loopingRules.keys())
//        {
//            if(loopingRulesMaxed(loopingRules[ruleId]))
//            {
//                fprintf(stdout, "Plic\r\n");
//                fflush(stdout);
//                _completedRules[ruleId] = loopingRules[ruleId];
//                loopingRules.remove(ruleId);
//                continue;
//            }
//            for(QString atomicRule : loopingRules[ruleId].split(" "))
//            {
//                bool okConv;
//                if(loopingRules.keys().contains(atomicRule.toInt(&okConv)) && okConv)
//                {
//                    loopingRules[ruleId] = replaceInRules(_baseRules[ruleId], atomicRule.toInt(), _completedRules[atomicRule.toInt()]);
//                }
//            }
//        }
//    }

//    for(int ruleId : _completedRules.keys())
//    {
//        loopingRules[ruleId] = _completedRules[ruleId];
//        /*C'est de la merde ça prend 5 plombe*/ fprintf(stdout, "Complete rule %i = %s\r\n", ruleId, _completedRules[ruleId].toStdString().c_str());
//        fflush(stdout);
//    }
//}



void Y20Day19::completeLoopRule()
{
    throw std::runtime_error("En cours mais nul, à refaire depuis le début pour le jour 2avec des struct");
    QMap<int /*rules id*/, QString /*equivalent*/> loopingRules;

    for(int ruleId : _baseRules.keys())
    {
        //Pass already completed rules
        if(!_completedRules.keys().contains(ruleId))
        {
            loopingRules[ruleId] = _baseRules[ruleId];
        }

    }

    loopingRules.remove(0); // Triche pour simlifier, 0 n'est pas une loop directe mais une composition de loop.

    for(int ruleId : loopingRules.keys())
    {
        bool loopComplete = false;

        QStringList fullRule = loopingRules[ruleId].split(" ");
        QStringList toCompleteAtoRule;
        for (QString atomicRule : fullRule )
        {
            if(atomicRule.contains(QRegularExpression("\\d")))
            {
                toCompleteAtoRule << atomicRule;
            }
        }

        while(!loopComplete)
        {
            QStringList nextToCompleteAtoRule;
            for(QString atomicRule : toCompleteAtoRule)
            {
                for(QString atomicComplRule : fullRule)
                {
                    if(atomicComplRule.size() < _maxMsgSize)
                    {
                        QString atomicRuleCp = replaceInRules(atomicRule, ruleId, atomicComplRule);
                        if(atomicRuleCp.contains(QRegularExpression("\\d")))
                        {
                            nextToCompleteAtoRule << atomicRuleCp;
                        }
                        fullRule << atomicRuleCp;
                    }
                }
            }
            toCompleteAtoRule = nextToCompleteAtoRule;
            loopComplete = (toCompleteAtoRule.size() == 0);
        }

    }


    fprintf(stdout, "End with loop");
    fflush(stdout);

    //Opti for sujet
    //    "0: 8 11
    for(QString atomic8 : loopingRules[8])
    {
        // ET ENSUITE ?
    }



    for(int ruleId : _completedRules.keys())
    {
        loopingRules[ruleId] = _completedRules[ruleId];
        /*C'est de la merde ça prend 5 plombe*/ fprintf(stdout, "Complete rule %i = %s\r\n", ruleId, _completedRules[ruleId].toStdString().c_str());
        fflush(stdout);
    }
}

bool Y20Day19::loopingRulesMaxed(QString rule)
{
    bool res = true;
    for(QString ored: rule.split('|'))
    {
        //TRVD
//        for(QString part : ored.split(' '))
//        {
//            fprintf(stdout, "shitty = \"%s\"\r\n",part.toStdString().c_str());
//            fflush(stdout);
//        }


        if( (ored.split(' ',QString::SkipEmptyParts).size() < _maxMsgSize) && (ored.contains(QRegularExpression("\\d"))) )
        {
            res = false;
            return res;
        }
        else
        {
//            fprintf(stdout, "Ored = \"%s\", size=%i and contain digit ? %i\r\n",ored.toStdString().c_str() ,ored.split(' ', QString::SkipEmptyParts).size() ,ored.contains(QRegularExpression("\\d")) );
//            fflush(stdout);
        }
    }
    return res;
}


int Y20Day19::countMsgMatching(int ruleId)
{
    int multipleDefinition = 0;
    int emptyDefinition = 0;
    int lastIdx = 0;
    int cpt = 0;

    fprintf(stdout, "There is %i atomic rule in rule %i. _maxMsgSize = %i ; _minMsgSize = %i\r\n", _completedRules[ruleId].split('|').size(), ruleId, _maxMsgSize, _minMsgSize);
    fflush(stdout);

    QMap<int /*size*/, QVector<QString> /*rule by size*/> ruleBySize = {};
    QStringList eachRule = _completedRules[ruleId].remove(' ').split('|');
    QStringList eachRuleShrinked;

    for(QString atomicRule : eachRule)
    {
        if( (atomicRule.size() <= _maxMsgSize) && (atomicRule.size() >= _minMsgSize) )
        {
            eachRuleShrinked << atomicRule;
        }
    }
//    eachRuleShrinked = eachRule;


    for(QString atomicRule : eachRuleShrinked)
    {
        if(ruleBySize.keys().contains(atomicRule.size()))
        {
            ruleBySize[atomicRule.size()][++lastIdx] = atomicRule;
        }
        else
        {
            ruleBySize[atomicRule.size()] = QVector<QString>(eachRule.size());
            ruleBySize[atomicRule.size()][0] = atomicRule;
        }

        cpt++;
        if(cpt%100000 == 0)
        {
            fprintf(stdout, "Parse %i atomic rule.\r\n",cpt);
            fflush(stdout);
        }
    }

    cpt = 0;
    for(int idxG : ruleBySize.keys())
    {
        fprintf(stdout, "Start sorting.\r\n");
        fflush(stdout);
        std::sort(ruleBySize[idxG].begin(), ruleBySize[idxG].end());
        fprintf(stdout, "End sorting.\r\n");
        fflush(stdout);
        for(int idx = 0 ; idx < (ruleBySize[idxG].size() - 1) ; idx++)
        {
            if(ruleBySize[idxG][idx].isEmpty())
            {
                emptyDefinition++;
                ruleBySize[idxG].remove(idx);
                idx--;
            }
            else if(ruleBySize[idxG][idx] == ruleBySize[idxG][idx+1])
            {
                ruleBySize[idxG].remove(idx+1);
                multipleDefinition++;
                idx--;
            }
            cpt++;
            if(cpt%100000 == 0)
            {
                fprintf(stdout, "Filter %i atomic rule.\r\n",cpt);
                fflush(stdout);
            }
        }
    }

    fprintf(stdout, "Find %i multiple definition.\r\n",multipleDefinition);
    fflush(stdout);

    for(int idx : ruleBySize.keys())
    {
        fprintf(stdout, "Find %i rules of size %i.\r\n",ruleBySize[idx].size(), idx);
        fflush(stdout);
    }

    QMap<int, QVector<int>> idxOfFirstB; //Position of first B by size by idx
    for(int sizeIdx : ruleBySize.keys())
    {
        idxOfFirstB[sizeIdx] = QVector<int>(sizeIdx);
    }
    for(int sizeIdx : ruleBySize.keys())
    {
        for(int idx = 0 ; idx <= sizeIdx ; idx++)
        {
            for(int ruleIdx = 0 ; ruleIdx < ruleBySize[sizeIdx].size() ; ruleIdx++)
            {
                if(ruleBySize[sizeIdx][ruleIdx][idx] == "b")
                {
                    idxOfFirstB[sizeIdx][idx] = ruleIdx;
                    break;
                }
            }
        }
    }


    fprintf(stdout, "Finish getting first b.\r\n");
    fflush(stdout);

    int matcheCount = 0;
    /*QMap<int,int>*/ int ruleMatchingIdx = {};
    int lastSize = 0;

    fprintf(stdout, "Start sorting _msg.\r\n");
    fflush(stdout);
    std::sort(_msg.begin(),_msg.end());
    fprintf(stdout, "End sorting _msg.\r\n");
    fflush(stdout);

    for(int msgIdx = 0 ; msgIdx < _msg.size() ; msgIdx++)
    {
        QString msg = _msg[msgIdx];
        if(lastSize != msg.size())
        {
            lastSize = msg.size();
            ruleMatchingIdx = 0;
        }
        if(!ruleBySize.keys().contains(msg.size()))
        {
            continue;
        }

//        int msgFirstB = msg.indexOf('b');
        for(int idx = ruleMatchingIdx ; idx < ruleBySize[msg.size()].size() ; idx++)
        {
            QString atomicRule = ruleBySize[msg.size()][idx];
            if(atomicRule == msg)
            {
                matcheCount++;
                ruleMatchingIdx = idx;
                break;
            }
        }
    }

//    int matcheCount = 0;
//    for(QString msg : _msg)
//    {
//        if(!ruleBySize.keys().contains(msg.size()))
//        {
//            continue;
//        }

//        int msgFirstB = msg.indexOf('b');
//        for(int idx = idxOfFirstB[msg.size()][msgFirstB] ; idx < ruleBySize[msg.size()].size() ; idx++)
//        {
//            QString atomicRule = ruleBySize[msg.size()][idx];
//            if(atomicRule == msg)
//            {
//                matcheCount++;
//                break;
//            }
//        }
//    }
    return matcheCount;
}


QMap<int /*rules id*/, QString /*equivalent*/> Y20Day19::_baseRules = {};
QMap<int /*rules id*/, QString /*equivalent*/> Y20Day19::_completedRules = {};
QStringList Y20Day19::_msg = {};
int Y20Day19::_maxMsgSize = 0;
int Y20Day19::_minMsgSize = std::numeric_limits<int>::max();

 /* Test
const QVector<QString> Y20Day19::_input =
{
"0: 4 1 5    ",        // => aaaabb, aaabab, abbabb, abbbab, aabaab, aabbbb, abaaab, or ababbb
"1: 2 3 | 3 2",        // => aaab, aaba, bbab, bbba, abaa, abbb, baaa, or babb
"2: 4 4 | 5 5",        // => aa or bb
"3: 4 5 | 5 4",        // => ab or ba
"4: a        ",      // => a
"5: b        ",      // => b
"            ",
"ababbb      ",        // => OK
"bababa      ",        // => KO
"abbbab      ",        // => OK
"aaabbb      ",        // => KO
"aaaabbb     "         // => KO
};
// */


/* Test loop
const QVector<QString> Y20Day19::_input =
{
"0: 1 2    ",        // => aaaabb, aaabab, abbabb, abbbab, aabaab, aabbbb, abaaab, or ababbb
"1: 4 | 1 4 ",        // => aaab, aaba, bbab, bbba, abaa, abbb, baaa, or babb
"2: 3 | 3 2 ",        // => aa or bb
"3: 4 5 | 5 4",        // => ab or ba
"4: a        ",      // => a
"5: b        ",      // => b
"            ",
"aaaa      ",        // =>OK
"ba      ",        // =>OK
"ab      ",        // => OK
"abba      ",        // =>OK
"abbb      ",        // => KO
"bbbb     "         // => KO
};
// */


// /*
const QVector<QString> Y20Day19::_input =
{
//"11: 42 31 ", //for part 1
//"8: 42 ", //for part 1
"11: 42 31 | 42 11 31 ", //for part 2
"8: 42 | 42 8 ", //for part 2
"58: 127 99 | 105 36                                                                                                                                                   ",
"56: 71 99 | 102 36                                                                                                                                                    ",
"116: 36 | 99                                                                                                                                                          ",
"42: 19 36 | 68 99                                                                                                                                                     ",
"67: 36 71 | 99 73                                                                                                                                                     ",
"117: 81 99 | 80 36                                                                                                                                                    ",
"77: 99 37 | 36 83                                                                                                                                                     ",
"106: 27 99 | 32 36                                                                                                                                                    ",
"73: 36 99 | 99 99                                                                                                                                                     ",
"126: 15 36 | 73 99                                                                                                                                                    ",
"133: 99 99 | 36 116                                                                                                                                                   ",
"92: 99 51 | 36 14                                                                                                                                                     ",
"61: 99 21 | 36 6                                                                                                                                                      ",
"6: 54 116                                                                                                                                                             ",
"33: 36 103 | 99 9                                                                                                                                                     ",
"131: 54 99 | 15 36                                                                                                                                                    ",
"81: 36 38 | 99 78                                                                                                                                                     ",
"93: 99 100 | 36 87                                                                                                                                                    ",
"1: 113 99 | 129 36                                                                                                                                                    ",
"36: b                                                                                                                                                            ",
"70: 99 130 | 36 122                                                                                                                                                   ",
"76: 99 4 | 36 44                                                                                                                                                      ",
"79: 65 99 | 48 36                                                                                                                                                     ",
"99: a                                                                                                                                                             ",
"108: 118 99 | 96 36                                                                                                                                                   ",
"15: 36 36                                                                                                                                                             ",
"2: 99 102 | 36 27                                                                                                                                                     ",
"103: 109 99 | 136 36                                                                                                                                                  ",
"9: 23 99 | 63 36                                                                                                                                                      ",
"12: 15 99 | 123 36                                                                                                                                                    ",
"137: 36 54 | 99 20                                                                                                                                                    ",
"13: 36 30 | 99 70                                                                                                                                                     ",
"7: 99 32 | 36 102                                                                                                                                                     ",
"94: 18 36 | 59 99                                                                                                                                                     ",
"71: 36 99                                                                                                                                                             ",
"3: 99 104 | 36 62                                                                                                                                                     ",
"4: 72 99 | 114 36                                                                                                                                                     ",
"32: 36 36 | 99 36                                                                                                                                                     ",
"21: 27 99 | 122 36                                                                                                                                                    ",
"52: 99 20 | 36 73                                                                                                                                                     ",
"135: 99 116 | 36 99                                                                                                                                                   ",
"31: 95 99 | 89 36                                                                                                                                                     ",
"24: 99 107 | 36 125                                                                                                                                                   ",
"19: 36 77 | 99 28                                                                                                                                                     ",
"112: 15 36 | 15 99                                                                                                                                                    ",
"89: 99 50 | 36 111                                                                                                                                                    ",
"23: 99 34 | 36 73                                                                                                                                                     ",
"69: 36 54 | 99 73                                                                                                                                                     ",
"85: 12 99 | 25 36                                                                                                                                                     ",
"53: 36 54                                                                                                                                                             ",
"95: 36 76 | 99 117                                                                                                                                                    ",
"124: 106 99 | 22 36                                                                                                                                                   ",
"10: 102 99 | 122 36                                                                                                                                                   ",
"107: 99 133 | 36 34                                                                                                                                                   ",
"129: 54 99 | 71 36                                                                                                                                                    ",
"16: 36 130 | 99 27                                                                                                                                                    ",
"86: 36 122 | 99 102                                                                                                                                                   ",
"45: 97 36 | 41 99                                                                                                                                                     ",
"102: 99 99 | 116 36                                                                                                                                                   ",
"25: 32 36 | 133 99                                                                                                                                                    ",
"87: 99 52 | 36 115                                                                                                                                                    ",
"119: 91 99 | 101 36                                                                                                                                                   ",
"34: 99 99                                                                                                                                                             ",
"121: 36 91 | 99 52                                                                                                                                                    ",
"29: 102 36 | 27 99                                                                                                                                                    ",
"20: 116 116                                                                                                                                                           ",
"47: 36 36 | 99 99                                                                                                                                                     ",
"49: 123 99                                                                                                                                                            ",
"38: 99 98 | 36 86                                                                                                                                                     ",
"123: 36 36 | 36 99                                                                                                                                                    ",
"48: 36 123 | 99 54                                                                                                                                                    ",
"51: 36 54 | 99 102                                                                                                                                                    ",
"98: 73 99 | 47 36                                                                                                                                                     ",
"26: 20 99 | 34 36                                                                                                                                                     ",
"68: 36 88 | 99 108                                                                                                                                                    ",
"111: 75 36 | 5 99                                                                                                                                                     ",
"54: 99 36 | 99 99                                                                                                                                                     ",
"109: 47 36 | 20 99                                                                                                                                                    ",
"0: 8 11                                                                                                                                                               ",
"17: 36 57 | 99 120                                                                                                                                                    ",
"66: 99 132 | 36 35                                                                                                                                                    ",
"62: 36 130 | 99 32                                                                                                                                                    ",
"59: 36 130 | 99 122                                                                                                                                                   ",
"44: 99 60 | 36 92                                                                                                                                                     ",
"122: 99 36                                                                                                                                                            ",
"74: 126 99 | 16 36                                                                                                                                                    ",
"37: 82 99 | 85 36                                                                                                                                                     ",
"65: 130 36 | 27 99                                                                                                                                                    ",
"80: 58 36 | 43 99                                                                                                                                                     ",
"55: 99 130 | 36 20                                                                                                                                                    ",
"118: 66 36 | 3 99                                                                                                                                                     ",
"5: 24 36 | 124 99                                                                                                                                                     ",
"14: 36 54 | 99 71                                                                                                                                                     ",
"96: 40 99 | 61 36                                                                                                                                                     ",
"22: 36 34 | 99 135                                                                                                                                                    ",
"97: 36 27 | 99 20                                                                                                                                                     ",
"43: 99 128 | 36 29                                                                                                                                                    ",
"101: 73 36 | 133 99                                                                                                                                                   ",
"91: 133 36 | 54 99                                                                                                                                                    ",
"114: 36 112 | 99 52                                                                                                                                                   ",
"83: 79 99 | 74 36                                                                                                                                                     ",
"28: 134 99 | 39 36                                                                                                                                                    ",
"72: 99 26 | 36 49                                                                                                                                                     ",
"78: 36 25 | 99 90                                                                                                                                                     ",
"30: 102 99 | 133 36                                                                                                                                                   ",
"27: 99 36 | 36 99                                                                                                                                                     ",
"35: 99 27 | 36 15                                                                                                                                                     ",
"84: 2 36 | 64 99                                                                                                                                                      ",
"75: 1 36 | 119 99                                                                                                                                                     ",
"115: 130 36 | 71 99                                                                                                                                                   ",
"39: 99 84 | 36 121                                                                                                                                                    ",
"40: 99 69 | 36 110                                                                                                                                                    ",
"63: 36 32                                                                                                                                                             ",
"88: 17 99 | 93 36                                                                                                                                                     ",
"120: 53 99 | 55 36                                                                                                                                                    ",
"105: 99 133 | 36 123                                                                                                                                                  ",
"127: 36 123 | 99 47                                                                                                                                                   ",
"134: 99 46 | 36 45                                                                                                                                                    ",
"50: 36 33 | 99 138                                                                                                                                                    ",
"82: 131 99 | 59 36                                                                                                                                                    ",
"104: 122 99 | 27 36                                                                                                                                                   ",
"113: 34 36 | 123 99                                                                                                                                                   ",
"125: 99 123 | 36 54                                                                                                                                                   ",
"64: 54 36                                                                                                                                                             ",
"46: 36 10 | 99 107                                                                                                                                                    ",
"130: 99 36 | 36 116                                                                                                                                                   ",
"18: 36 54 | 99 34                                                                                                                                                     ",
"110: 99 34 | 36 27                                                                                                                                                    ",
"136: 99 15 | 36 73                                                                                                                                                    ",
"132: 122 36 | 133 99                                                                                                                                                  ",
"128: 15 99 | 102 36                                                                                                                                                   ",
"57: 36 56 | 99 67                                                                                                                                                     ",
"100: 99 63 | 36 137                                                                                                                                                   ",
"60: 7 99 | 63 36                                                                                                                                                      ",
"90: 36 122 | 99 133                                                                                                                                                   ",
"41: 34 36                                                                                                                                                             ",
"138: 99 94 | 36 13                                                                                                                                                    ",
"                                                                                                                                                                      ",
"babbbbababbbababaabaabab                                                                                                                                              ",
"aaababbaababbabbaababbabbaaabaab                                                                                                                                      ",
"abaaaabbaabaaabaababbbbaabbaaaba                                                                                                                                      ",
"abbaabbbbbaaaaaabaaaaaaa                                                                                                                                              ",
"aabaaaababababababaaababbabbbaaa                                                                                                                                      ",
"aaabaaabbbabbaaabbaababb                                                                                                                                              ",
"aaabbabbabbbaababbbabbab                                                                                                                                              ",
"bbbabbbbaaabbabbbaabbaab                                                                                                                                              ",
"babbbaabbaaabbaaaabaaaabaabbbaabaabbbaaaaabbbbbb                                                                                                                      ",
"abbaaabbabbabaaaaaaaaabb                                                                                                                                              ",
"bbbabbaaabaabbbbaaabbabbaabbbbbbbaababab                                                                                                                              ",
"ababbbabbabbababbaabbbbbbbbabaabaabbbbbb                                                                                                                              ",
"bbbbbbbbaabababababbbbba                                                                                                                                              ",
"aaabbbbbabbababbabbaaaaa                                                                                                                                              ",
"aaabbabbbaabbbaabaababbabbbbbbabaabaaabaababaaba                                                                                                                      ",
"abaaaabaabaaababaabbbbbb                                                                                                                                              ",
"bbbbbabbaababbbbaabbaaba                                                                                                                                              ",
"bbbaabaabaabbbbaabbabaaabababaaaaabbbabaababaababbbbabaa                                                                                                              ",
"abaaaabbbbaabbbabaababab                                                                                                                                              ",
"abababbabbaabaaaabbbbaba                                                                                                                                              ",
"babbbabbbbabbabaaaababbb                                                                                                                                              ",
"aabbaabaaabbbaaabbabaaaa                                                                                                                                              ",
"abbabaaababbbbababbbbaaabbabbbaa                                                                                                                                      ",
"babababaabbaabbbbabbbbabbaaabaabbbabbbaa                                                                                                                              ",
"abababababbbbbbbaaabaabb                                                                                                                                              ",
"bbbbbbaabaababaabbbaabba                                                                                                                                              ",
"bbabaababbababbbbaabbaba                                                                                                                                              ",
"aaaabaabaaababbbabaabbabbaaaaaaaaaaaabba                                                                                                                              ",
"babaabaaabbababbaabbbbaa                                                                                                                                              ",
"aababbbbabaabbabbbbabbbaababbbababbaaaabbabaaaab                                                                                                                      ",
"babaabbbbababababbababab                                                                                                                                              ",
"babababbbababbaaabbbaabaaaaabbbbaaaabaabaaabaaabaabaabbbbaaaaaaabaababab                                                                                              ",
"ababbababbbbaaabbabababbabaaaabbbbaabbbbaaaaabbabbaaaabbbbbbbbbabbbaaabbaababbbaaaabbaaaabbabbba                                                                      ",
"aaabaaabaabababaabbababaabbbaabaaaabaabb                                                                                                                              ",
"bbbbbbaabbaaabbabbaaababaaaababbbaaabbba                                                                                                                              ",
"bbbbbaaaaabaabbaabbabaabaabbbbbababbaababaaabbabaabbabab                                                                                                              ",
"bbaaabbbbaabbbabbbbaaaabbabbbabaaaaaabaabbaabbbbbbbabbab                                                                                                              ",
"baabaaabbbbabbbabbbaaabbaabbbbbb                                                                                                                                      ",
"bbbbaabaaabbbaababbbbaaaabbbbbab                                                                                                                                      ",
"bbbabbbabbbaaabbbbbaabbb                                                                                                                                              ",
"abbbaababaababaabaaaaaaa                                                                                                                                              ",
"bbbbbabbbabbaabaabaababa                                                                                                                                              ",
"aababaaabababbabbabbbaaa                                                                                                                                              ",
"aabbabbbbbaaaabbbbaabbbbababbbbabbbaaaaa                                                                                                                              ",
"bbabaaabbabbbbbbbbbbaabb                                                                                                                                              ",
"babbababaaabbabbbaaabbbb                                                                                                                                              ",
"abaaabbaabaaabbaaabbbbba                                                                                                                                              ",
"baababbbabbabbaabbababbbbaabaabaabababaabaabbaba                                                                                                                      ",
"bbaabbbabaaabbaabaababab                                                                                                                                              ",
"bbbbbabbabbababbbbaabbbb                                                                                                                                              ",
"bbbbaaaaabbababaababbbaa                                                                                                                                              ",
"bababababaababaabaababbaabaaaaaa                                                                                                                                      ",
"bbbbaaaaaababaabbbbaaaaa                                                                                                                                              ",
"aababaabbaaaabbbabbabbbb                                                                                                                                              ",
"abbbababaaabbbbaabbbbbbbaabaaaaa                                                                                                                                      ",
"aaabaaaaaaabbbaabbbabbabbaaaabbbabbabbabaabbabaababaabba                                                                                                              ",
"bbaaabbababaaaaababaaabb                                                                                                                                              ",
"bbbabbbbbbaabbbbbabbbbbbbabbbaababaabbbbaabaaaaa                                                                                                                      ",
"bbbbabbbabababbaaaabbaab                                                                                                                                              ",
"abaabbabaababaabbaaaabba                                                                                                                                              ",
"ababababbbbbbabbaaaaabaaabbbbbbbbababbbbaaabbbab                                                                                                                      ",
"bbbbbbbabbbbbaabbbbabbaaaaaabbababbaabbbabbaaaab                                                                                                                      ",
"abbbaababbaabaaaaabbbbaa                                                                                                                                              ",
"bbaaaabaaaaaaabaabababbb                                                                                                                                              ",
"babbabbbbbbbbbbbaabbbaaa                                                                                                                                              ",
"abababbaaabaabbaaaabbabbaaabbbaabaaaabaa                                                                                                                              ",
"babaabaaabbabbabababbaab                                                                                                                                              ",
"abbababaabaaabbbaaabaaaaaaaaabbbbbbaabbb                                                                                                                              ",
"babbabbaabbababbbaabbaba                                                                                                                                              ",
"babbabababababaaabbbaababaabbbbbaababbabbbaaaabaaaaabaaaabbbaaab                                                                                                      ",
"babaaaaaaaabbaaaabaaaaaa                                                                                                                                              ",
"bababaaabbbbbbbabaaababa                                                                                                                                              ",
"bbaababaaaabbbbaaabaabaabbaaabaa                                                                                                                                      ",
"abaaabbaabbabbabaababbaa                                                                                                                                              ",
"abbaaabbbaabbbaabaabbbab                                                                                                                                              ",
"bbbaaaabbbabbaabaabaabab                                                                                                                                              ",
"babbbbaaabaaabbabaaabbaaabaaabaa                                                                                                                                      ",
"bbbbbbaaaabababaababbbbb                                                                                                                                              ",
"abaabbaaabbbbbbbbabbbbba                                                                                                                                              ",
"abaabbbbbabbabbbbbbabaaa                                                                                                                                              ",
"baaaabbbabbbbbbbaaaabbba                                                                                                                                              ",
"aabababaabaabaaaabbabbba                                                                                                                                              ",
"bbaaabbababbbbabbbbbaabaaaaabbabaaabbaaaabbbbabbabbbbaababaaaaab                                                                                                      ",
"abbbbaabababaaaabbbaaaabaababaabbbbabbbbaaaaaaaabaaababbaaababaa                                                                                                      ",
"aabbabaaaabaaababaabbbab                                                                                                                                              ",
"babbabbbbbaabaaaaaabaaaababbbbbbaabbabba                                                                                                                              ",
"abaaaabbaaabaabababbbaaa                                                                                                                                              ",
"aaaababbbbbaaaabaabbbaaa                                                                                                                                              ",
"bbbabaabbbbbabbaabaaabaa                                                                                                                                              ",
"ababbabbaababaaaabaaaabbbbaaabbbbabaabab                                                                                                                              ",
"babbbbabaaabaaabaaaaabaaaabbabab                                                                                                                                      ",
"aababbabbabaabbbbaaabaab                                                                                                                                              ",
"aabaaababbbabaababaabbbaaabaabbabaabaaba                                                                                                                              ",
"bbbbabbbbbaaaabaaaabbbbbbbbabababaaabaaa                                                                                                                              ",
"abaabbbbbabaaaaaaaaababa                                                                                                                                              ",
"abbbbaaaaaababbaabbbaaaaabbababaaabbbaaababaabab                                                                                                                      ",
"babaaabaabaababbaaabbaab                                                                                                                                              ",
"abaabbbbbbabbabaabbababbabaaabbabaaaaaaa                                                                                                                              ",
"bababbabbaabbbbbbbbbaaab                                                                                                                                              ",
"bbbaaaabbbaabaaabaaaaaaa                                                                                                                                              ",
"bbaabbbbbbbaaaababbbabaa                                                                                                                                              ",
"baabbbbabbbbbbbbbabaaaabbaabbbbbabbbaaaabaababbaaabbbabaaaabaaabbababbbbaaabbaba                                                                                      ",
"abaabbbaaabbabaabbbbaababbaaaabbaaabaabb                                                                                                                              ",
"abbbababababababbbbabaaa                                                                                                                                              ",
"bbbabbaaaaabaababaabbbaaabbaaabbabbbaaabbbaaabbb                                                                                                                      ",
"abbbaaaababababbaabbabbb                                                                                                                                              ",
"baabbbaaaaababbaaabaabab                                                                                                                                              ",
"aaabbbbbaaabaabaabaabaaaabaabaaaaabbaaba                                                                                                                              ",
"bababbbbbabbaaabaaabaabaaabbbabbaabaaababbababbbbbabbbaabbbabbbaababbbaabbbababb                                                                                      ",
"abbabaaaabaabaabbaaaabbbaabbbbbb                                                                                                                                      ",
"abbaabbbaaaaabbbbababbaaaabbbaba                                                                                                                                      ",
"babbabbbbabababbbaabaaba                                                                                                                                              ",
"babbabbabaababaaaabbbbab                                                                                                                                              ",
"aababaabbbbbabbbbbbbabbaabbaaabaababbaab                                                                                                                              ",
"bbbaabbaaabaaababbabbabaaaaabbaaabbbabbbaabbabbaabaaabab                                                                                                              ",
"ababababababaabbbaaaaaabbabbbbabbbbbbbababababababbbbaabaaababaaaabbbbbbaabababbbbbbbaba                                                                              ",
"aaabaaababbbaabaabaabaaabbabbbab                                                                                                                                      ",
"bbabbaabbbabbababbabbbbb                                                                                                                                              ",
"ababababaababaabbaaaabab                                                                                                                                              ",
"bababaaaaaababbabbbbbaba                                                                                                                                              ",
"babbbbabbbaaababbbbbabbbbabaabbaabaabaab                                                                                                                              ",
"ababaabbbbbbbbabbbbbbaba                                                                                                                                              ",
"abbbaaaababbaabbbabbaaab                                                                                                                                              ",
"bbbbabbaabbbaababbabaabb                                                                                                                                              ",
"bbbbbabbbbbbabbbababaaab                                                                                                                                              ",
"babbabbbbbbabaabbbbaaaba                                                                                                                                              ",
"baababaabbbbabbbbababaab                                                                                                                                              ",
"aaaabaabaaaabbbbaaabbaab                                                                                                                                              ",
"bbbaaaabbabbababababaaab                                                                                                                                              ",
"abaaaababbbbaaaaababbaba                                                                                                                                              ",
"bbbbaaaaaaabbaaaaabaabab                                                                                                                                              ",
"babababbbabbabaaaaababbb                                                                                                                                              ",
"babbbaabbbaaabababbbbaba                                                                                                                                              ",
"aaabbabaababbaaabaaaaababababbaaabaabaabaaabbbbaaaaaaabbbabbaaba                                                                                                      ",
"abaaaabbabaabbbabaaaabbababaaabaababaabbaaaaabbbbabaaaba                                                                                                              ",
"bbbbaaaaabbbbbbbbaaabaab                                                                                                                                              ",
"bbaabaaaabbaaabbabbbbbaa                                                                                                                                              ",
"abbbbbaabababababbbbbaba                                                                                                                                              ",
"bbbabbbaabaababbbbbbabaa                                                                                                                                              ",
"bbbaaaabababbabbbbabbbba                                                                                                                                              ",
"abaababbbababaaabaaaaabb                                                                                                                                              ",
"bbabaaabbbaabbbbbaabaaaa                                                                                                                                              ",
"bbbaabaabbbbbbbabaabbaab                                                                                                                                              ",
"aabbabbbbbbbbabbbbaabaab                                                                                                                                              ",
"aabbabbbaaaaabbbbbbabbbbbaababbababaaabaaaababbabbaababbbaabbaba                                                                                                      ",
"abbbbbbbbababaaabaababab                                                                                                                                              ",
"bbbbbbbababbbbbbaaabaabaabbbbbba                                                                                                                                      ",
"abaabbabbbbaaabbaaaaaaaa                                                                                                                                              ",
"bbaaabababaaababbbbabbbabbababba                                                                                                                                      ",
"abbababbbabbabbbabaabaabbaababaaabbbabba                                                                                                                              ",
"abbbbbbbbbbbbaabaabaabab                                                                                                                                              ",
"bababbabbbbbbaabbaabbbab                                                                                                                                              ",
"aaaaabaaaaaaaababaababbb                                                                                                                                              ",
"aabbabbbaabaabaaabaaabaa                                                                                                                                              ",
"abbabaaabbabaabaabbababaaaabbbaabaababbaabaaaaabaaaabababbbabbab                                                                                                      ",
"aaabbbbbbbabbaaaabaaaaab                                                                                                                                              ",
"aaaabbbbbbbbbaabbbabbbba                                                                                                                                              ",
"ababbabbabbbabbbbabaaabb                                                                                                                                              ",
"bbbaaabbaaababbbaababbbbabaabbabbbbbaaaaaaabababaaaabaabaaabbababaabababbabbbbabbbabaaba                                                                              ",
"ababababbaababaabbbaaaba                                                                                                                                              ",
"baaabbaabbbabbbaabbabbba                                                                                                                                              ",
"abaaabbbbbaaaabbabababbbbaaabaabbabaaabb                                                                                                                              ",
"abaaaabbababbbbabaababab                                                                                                                                              ",
"baaaabbbaaabbabbaaaabaaa                                                                                                                                              ",
"baabbbaaaabbabaababbbaaa                                                                                                                                              ",
"bbbbbbbbbaaaaaabaaababbabbbbabbbabababaaaaaaabbaabbbbbabaabaabbbaaaaababaaabbabaaaaababa                                                                              ",
"bababaaabbaaababbbbbbbbabbbbbbababbbabaa                                                                                                                              ",
"aababaaaabbabbabbababbabbaabaaba                                                                                                                                      ",
"bbbbabbabbbbababbababaaabbbbaabb                                                                                                                                      ",
"abbaaabbbaabbbbabbbabbab                                                                                                                                              ",
"baaaabbbbaababbabababbbb                                                                                                                                              ",
"aaaabbabbabbbbbbbbabbbaa                                                                                                                                              ",
"bababbababbbbbabbbbabbab                                                                                                                                              ",
"abbabbabbbbabbaaabbbabba                                                                                                                                              ",
"ababbabbbaabbbbbababaaab                                                                                                                                              ",
"abbabbabbbabaabaabbabbababaabbaabaaaaaaa                                                                                                                              ",
"abbbababbbaabbabaabbbaaa                                                                                                                                              ",
"aaaababbabbbbaaaabbabbaa                                                                                                                                              ",
"bbabbaaaabbbbbbbbbbabbbbbaaaaabbbbbbbaba                                                                                                                              ",
"baabbabbbbbaabbbaabbababbbababba                                                                                                                                      ",
"baabbbaaaaaabbbbaabbabba                                                                                                                                              ",
"aababaaabababaaabbaaabbabababbaaabbaabbbababaaab                                                                                                                      ",
"bbaabbbbaaaabaababbbababbbbabbbaaababaaaabbaaaba                                                                                                                      ",
"abaaaabaabababaaaabaabbb                                                                                                                                              ",
"aaabaabababbabbaababaaaa                                                                                                                                              ",
"babababbbbabaaababaaabbaaaaaaaaaaaaabbababbabaaabaaaabbabaaaaabbaaababbbaaaaabaaaaabbaab                                                                              ",
"ababaaaababbbaaababbbbaababbabaabaaaabaaabaabbaaabbbaababaaababbabbaabaa                                                                                              ",
"abbbbbbbbaaabbababbbbbab                                                                                                                                              ",
"abbbbaaababbabaaabbbbbba                                                                                                                                              ",
"aaabbaaaabbaabbbbaaaaaaa                                                                                                                                              ",
"aaaabaabbbbbbbabbbbbbbbbbbbbbabbbbbababa                                                                                                                              ",
"babbabaaababaabbbabbaabbaaababbb                                                                                                                                      ",
"baabbaaabaaababaabbabbbabababbaababaaabbbbbbaaaabbaabbbbabababababaabbbb                                                                                              ",
"abbababbbabaaabaaaabbbbbbbaabbbbaabababbbbbbbabaaabbaaaa                                                                                                              ",
"bbaabbbaabbaabbbabaaaabbaabbbbaa                                                                                                                                      ",
"aaabbbbbbababbbaabbaaaba                                                                                                                                              ",
"abbbbaaababababbaaaabbba                                                                                                                                              ",
"abbaaabbabbababaaaaaabba                                                                                                                                              ",
"abbbabbbabaaaabbbabaabbbbbabbbbaabbbaabb                                                                                                                              ",
"abbbababbabbbabbbbaaaabb                                                                                                                                              ",
"baabaaabbbbbabbbababbabbbbbababb                                                                                                                                      ",
"bbabaaabbbaabbabbbaabbbbbbbbabbbbbbbababbbaaabaa                                                                                                                      ",
"babbabaaaaababbbbaaababaaaaabbbbaabbbaababbaabaabbbaabab                                                                                                              ",
"bbbbababaabaaabaabaaaaabababbbbbbabbaaaaaabaabaa                                                                                                                      ",
"bbbabbbaaaabbbaabbaaaabaaabbaaba                                                                                                                                      ",
"bbabaabaabaabbbbaaabbaba                                                                                                                                              ",
"bbaababaaaaabbabbbabbbaa                                                                                                                                              ",
"bbbbbbbababababaaabbbbab                                                                                                                                              ",
"abaabaaaaaabbabbbaaababb                                                                                                                                              ",
"bbaaaabababaaaaabaaaaabb                                                                                                                                              ",
"bbbaabaaabaabaaabbbbbaabbbaaababaaaaabbbabbabbbaaababbaa                                                                                                              ",
"baabbbbbabbbaaaaaaaaabba                                                                                                                                              ",
"aaaaaabaaabaabbaabbabbaa                                                                                                                                              ",
"abaaabbaabbaabbbbbbabbbabbaaabababaabbaaabbbaaabbaabbbab                                                                                                              ",
"abaabbababbababbabbbbaaaababbabbabbabbabbaababbb                                                                                                                      ",
"abababbababbbaabbbbababa                                                                                                                                              ",
"babaabbbbbaabaaabaabaaba                                                                                                                                              ",
"bbaaabbbbbbababbaaabababaabbaaabaabaabbb                                                                                                                              ",
"abbaaabbbabbaabbabbaabaa                                                                                                                                              ",
"abababbaaabaabbaabbbbaba                                                                                                                                              ",
"abaabaaababaabbbbbbbbbaaaabbaaba                                                                                                                                      ",
"abaababbabbabaaaaabbaabb                                                                                                                                              ",
"baababaaabbabaaaabababaabbaaabababaababaaabbabab                                                                                                                      ",
"aaaaabaababbaababaabbaba                                                                                                                                              ",
"aaabbbbbbbbbbbaaabbbbabb                                                                                                                                              ",
"aaaabaabbbbbbabbbbbbbaba                                                                                                                                              ",
"bbbbbabbabbbbaaaababaaba                                                                                                                                              ",
"bbabbaabbabbaababbbaabbb                                                                                                                                              ",
"bbabaaabbabbabbbaabaabab                                                                                                                                              ",
"babbbaababaabbbbbabbbbbbbaaaababbbaaaaab                                                                                                                              ",
"babbabbbababababbbbabaaa                                                                                                                                              ",
"aaaaaabaaababaaababbaababababbaabaaaabbaabbbbaba                                                                                                                      ",
"aababaabbbabbababbbbabaa                                                                                                                                              ",
"babbaabbbabbabaaabbabbaa                                                                                                                                              ",
"babbbbabbbaabaabbaaababbbbbbbbbaabbbbbbbaaaabbbb                                                                                                                      ",
"aabbabaaaababbbbbabbaababbbabaaa                                                                                                                                      ",
"abaabbababababbababaabab                                                                                                                                              ",
"baababaaaaabbbbaaaabaabb                                                                                                                                              ",
"bbbabbaabbabaabaabaaabaa                                                                                                                                              ",
"bbbabbbbbbbbbbabbbbbaaab                                                                                                                                              ",
"baabbbbababaaabaaaabaaaabbbaabab                                                                                                                                      ",
"aabaaababbabaaabbaabbbab                                                                                                                                              ",
"aaabbabbbbabaaabbababaaababbbbaabbaaababbabbbbbbabbbabaabbaaaaab                                                                                                      ",
"abaababbbabaaabababaabba                                                                                                                                              ",
"bbabbbbbbbbabaaaabaabababaababbbaabbaaabbaaababbbbbabbba                                                                                                              ",
"baabbabbbabbbbababbabbababbabababbaabbabaaaaabaaababaabaabababab                                                                                                      ",
"baaaaaababaaabbbaababbaa                                                                                                                                              ",
"aaabbbbaabababaaaaababab                                                                                                                                              ",
"baaaabbbbabaabbbbaaaabba                                                                                                                                              ",
"abbbabababbbbaaabbabbabaaabaabbbbbababba                                                                                                                              ",
"bbaabbabbbbaaabbabababaababbbaabaabbbbaa                                                                                                                              ",
"bababbabaabbbaabbbbbbaba                                                                                                                                              ",
"aaaabbbbbbbbbbabaabbbaba                                                                                                                                              ",
"baaabaaabbabbaaabababbbbbbbbababbbabaaabaabaabbabbbbbbababbababb                                                                                                      ",
"baaabbaaabaababbaabababaaaaababbbaaabaab                                                                                                                              ",
"aababaabbbaaababbbbaabba                                                                                                                                              ",
"bbbabbbbbabbbaabbbbbbbabaaabbabaabbbbbba                                                                                                                              ",
"ababababaabbabbbbbaabbbbaabaabbb                                                                                                                                      ",
"aabaaabaaaaabaabbabaaabb                                                                                                                                              ",
"bbbbaaaaababababbabbbbbbbabaabbbabbaaaba                                                                                                                              ",
"bbaaaababbbabaabaababbba                                                                                                                                              ",
"bbaabbabbabaaaaabababbaababbbbbb                                                                                                                                      ",
"baaaaababaabababaaabaabbbabaabbbbabaabbbbbbbbaab                                                                                                                      ",
"abbabaaabbbbbabbbbbaaaba                                                                                                                                              ",
"babbbabbabaabbbaaaababbb                                                                                                                                              ",
"abababaabababbbaabbaabba                                                                                                                                              ",
"babbabbbabbbaaaabbaabbaa                                                                                                                                              ",
"babbbbabbaababbaababbaba                                                                                                                                              ",
"bbbbaaaabbbbabbbbbaaabaa                                                                                                                                              ",
"bbababbbbabbbbabaaaabaabaabbbbbbaaaabbaa                                                                                                                              ",
"bbbbbbabababbabbaaabbbaabbbaabbabaaaabab                                                                                                                              ",
"aaabaaaaabababbabaaabaaa                                                                                                                                              ",
"ababaabbaabaabbaababbbaa                                                                                                                                              ",
"babababaabaabbaabbaaabaa                                                                                                                                              ",
"bbaaaababaabbbaaaabbbaabaababbabbbbbbaababababababbabaab                                                                                                              ",
"bbababbbaabaabbabbaabbbbaaabbabbbabbbaaa                                                                                                                              ",
"aaaababbabbababbaababaaabbabbbab                                                                                                                                      ",
"bbabbaaaaabaaaabbbbabaaa                                                                                                                                              ",
"aaaaabaaaaabbbaaabbabbba                                                                                                                                              ",
"abbbaababbbbbbabbbaabababbbbaaab                                                                                                                                      ",
"babbabaaababbabbabbaaaab                                                                                                                                              ",
"babaaabaaaaaaabaabbabbbb                                                                                                                                              ",
"bababbaabbababbbaabaaababbaabbabaababbbbaabbbaabbbbababb                                                                                                              ",
"aaaaaaabbbbabbaaabbbabab                                                                                                                                              ",
"bbabaabaaabbabbbbaaababa                                                                                                                                              ",
"abbabbabbbbaabaaaaaababa                                                                                                                                              ",
"bbbabbbbabbbbaaabaaabbbb                                                                                                                                              ",
"babbbabbbbbbabbbaabbbbaa                                                                                                                                              ",
"baaaabbbaaababbaababaaaa                                                                                                                                              ",
"aaaaaabababbbbabbababaab                                                                                                                                              ",
"bbaabbbbabbababababbaabbbbbbabaa                                                                                                                                      ",
"baabaaabbbbaaabbaabbbbba                                                                                                                                              ",
"bbabaababbaabbbbbbbabbab                                                                                                                                              ",
"bababbabaababbabbaabbabb                                                                                                                                              ",
"aaabbabbaababaabababaaaa                                                                                                                                              ",
"baababbaabaabbbbabbbaababbababbbbaabbababbbababaabbaaaba                                                                                                              ",
"aababaaaaaabaaabaaaabaabaabaabbbbbbababa                                                                                                                              ",
"abbbbaaaaaabbbbaabaabbbababaaabbababaaaa                                                                                                                              ",
"abbbabbbaaaababbbbbbabaa                                                                                                                                              ",
"bbabbaaababaabaaaaabaabb                                                                                                                                              ",
"aabaaababbabbaaabbaabbbbaabaaaabbaaabbabbaaaaababaababbbbbaaabbb                                                                                                      ",
"aaabbbbabaaaabbbbbababba                                                                                                                                              ",
"aaaabbbababbabaaabbabbbbaaabbaaaabbababbbaabbbab                                                                                                                      ",
"aaabbbaaababbbbabbbbaaab                                                                                                                                              ",
"aaaababbaaabbabbaababbba                                                                                                                                              ",
"babbbbbbbaababaabbbbbaba                                                                                                                                              ",
"abbbaaaababbbabbbabbbaaa                                                                                                                                              ",
"aabbbaabababababbbbbbbaabbbbbabbbaabbabb                                                                                                                              ",
"aaabbbaabaaabbabaababbba                                                                                                                                              ",
"abbbaabaaaabbbbabbbbbbababbaaaba                                                                                                                                      ",
"bbbabaabbabbbabbbabababb                                                                                                                                              ",
"aaaaaaabbbababbbbbaaaaab                                                                                                                                              ",
"abbabbbbbaabbbbbaaababbbbabbbbabbaabbabb                                                                                                                              ",
"aabaabbabbbbaabaaaaaaaabbababababaaabbaabbaababbbbbbbaaabaaaabbabbbbbaba                                                                                              ",
"aaaabaababaaaaaabaaaabba                                                                                                                                              ",
"bbbaaabbababababbbbbbaaa                                                                                                                                              ",
"abbbabababaabbbabbbbaababbbaaabbbbbbbbbaaabaaabb                                                                                                                      ",
"bbaaaabaababaabbaaabaabb                                                                                                                                              ",
"aaaabbabaaabbabbbbbbabbaabababaaabaabbabbaabbaba                                                                                                                      ",
"bbababbbbaaaabbbababaaaa                                                                                                                                              ",
"bbababbbabaaaabababaabab                                                                                                                                              ",
"aababababaababbaabbaaaba                                                                                                                                              ",
"baabbbaaabaabbbbaabbabbbabaabbbaaaabbaab                                                                                                                              ",
"bbbbbaabbabbabbabbbabbbbabbbbbaaaaaaabba                                                                                                                              ",
"baaaabbbbbbabbaabbbaabab                                                                                                                                              ",
"abbbabbbbbbbbabbbabababaabbbbbbbbababaaababbaaab                                                                                                                      ",
"abbaabaaaabbabaabbbaaabaabbbbaabaabbaababbaababbbaaabaaaaabbaaaa                                                                                                      ",
"baaabbabababbbabbaabaaaa                                                                                                                                              ",
"aaabaabaaababbbbababbaba                                                                                                                                              ",
"bbaabbbaaaaababbababaaaa                                                                                                                                              ",
"abbbbaaabaaaaaabbbbaabab                                                                                                                                              ",
"abbbbbaaababbbababbaabaa                                                                                                                                              ",
"ababbabbbbbabbbbbbabbabb                                                                                                                                              ",
"bbbbbbaaaaaaaabaaaabbaab                                                                                                                                              ",
"aababbababaaababbbbbaaaabbbaabbaababbaba                                                                                                                              ",
"aaababbaabbabababbbababa                                                                                                                                              ",
"abbabbabaaaaaabaabababaababbbaabbbabbaab                                                                                                                              ",
"aabaaababbabaaabbaaabaab                                                                                                                                              ",
"aaabbbbaabbbbbaaabaaabaa                                                                                                                                              ",
"aaabaaaababbbaabaabbaaba                                                                                                                                              ",
"abaaaabaaabbbaabaabaabab                                                                                                                                              ",
"babaabbaabbbbbbbabbabaaababaaabbbbbababa                                                                                                                              ",
"babbaababbbaaaababbbabbbabbaaabaabbaabaa                                                                                                                              ",
"abaabbbabbbbaaaabbbbbbbbbbbabbaaabbaaabbaabaababbaabbbab                                                                                                              ",
"bbaaaaaaaabbabbbabaaaabbaaaabbaa                                                                                                                                      ",
"bbaabbbbbbaababbaaaaaaaabbbaaabaaaababbbbbbaaaababbbabbababaaaabbbbaabbaabaabbbaabbaaaaa                                                                              ",
"bbabaababbaabaaababbbaaa                                                                                                                                              ",
"aaaababbaaabaaabaaaabbba                                                                                                                                              ",
"aaaabaabbabbabbabbaabaaaabbaabbbaaaaabba                                                                                                                              ",
"bbaabbbbabaababbbabbaababbbbbbaabaabaaababaabababbbababb                                                                                                              ",
"aaaaabbbaabbabbbabaaabbaababbbbbaaabbbbbbbabaaabbabaaaabbbbbaabb                                                                                                      ",
"bbbbaababababbaaababbbabaaaabbaa                                                                                                                                      ",
"abbbbaaaaababbabbbababaaaaabbbabbbaabaabbaaabaab                                                                                                                      ",
"abaabaaaaabaabbaaaabbaaaabbbbabb                                                                                                                                      ",
"bbabaabaaaaaaaabbbbababa                                                                                                                                              ",
"bbbbbabbabababaaabbaaaab                                                                                                                                              ",
"aaabbbabbaabababbbabbbbaabbbaaaaaaabbbab                                                                                                                              ",
"abbababaabaabbbaaaaabaaa                                                                                                                                              ",
"bbbabbaaaabbbaabaaabaaabbbbbabaa                                                                                                                                      ",
"abbababaabaaababbbbaaaba                                                                                                                                              ",
"babaabbaabaaabbbbabbabbaaabbbaaa                                                                                                                                      ",
"aaabaabaabaaababbabbbbbbbaabbabbabbabbbbbbaabaaabbaababbaaaaaaaaaaaaaabbbbbabaaa                                                                                      ",
"babbbabbabbbaaaaabbaabbabbbabbabbbababbaaabaaaaa                                                                                                                      ",
"bbbbbbababbaaabbbaaaabab                                                                                                                                              ",
"aaaabbbbbbaabbabababbaba                                                                                                                                              ",
"abaababbbabbbbabbabbaaab                                                                                                                                              ",
"ababbaaaabbbbbaaaaabbabbbbaabbabbaababbb                                                                                                                              ",
"aaabbbbababaaababaaabaab                                                                                                                                              ",
"bbbbbbbabbaabaaabaaaabbbbabaabbbaaabaabbbabbaaab                                                                                                                      ",
"bbababbbbabbbaababaaaaab                                                                                                                                              ",
"baaaabbbbaabbbaabaaabbbb                                                                                                                                              ",
"abaaabbababaaaaabbababba                                                                                                                                              ",
"aaabbbaaabaabbbbbaabaaba                                                                                                                                              ",
"baabababbaababbbbaababbbaabbbbaa                                                                                                                                      ",
"aabababaaaaaaabaaaababab                                                                                                                                              ",
"aabbababaabbbbbaabbaabaabbbbbbbaaaabaababaabababbbbabaab                                                                                                              "
}; // */
