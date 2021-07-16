#include "Y20Day18.h"

Y20Day18::Y20Day18()
{

}

// 5292518335 is too low
// 147573952594968931263 is too high;
QString Y20Day18::computFirstResult()
{
//    unsigned long long int res = 0;
//    unsigned long long int interRes = 0;
//    unsigned long long int prevRes = 0;

    QVector<QString> eachRes;

    for(QString line : _input)
    {
        eachRes << QString::number(computeLine(line.simplified().remove(' ')));
//        fprintf(stdout, (line + " = %llu\r\n").toStdString().c_str(), interRes);
//        fflush(stdout);

//        prevRes = res;

//        res += interRes;

//        if(prevRes > res)
//        {
//                    fprintf(stdout, "kaboum");
//                    fflush(stdout);
//        }
    }

    QString res = bigSumAsString(eachRes);

    return res;
}


// 16363257406750921342408355254725400159231128476453435 is to high
// 09086810703039989742207922433786259878598442304161377 is to high
QString Y20Day18::computSecondResult()
{
//    fprintf(stdout, "Test big time\r\n");
//    fprintf(stdout, "Tesst 123000 = %s\r\n", QString::number(123000).toStdString().c_str());
//    fprintf(stdout, "123 * 222 = %s\r\n", bigTimeAsString("123", "222").toStdString().c_str());
//    fprintf(stdout, "222 * 123 = %s\r\n", bigTimeAsString("222", "123").toStdString().c_str());
//    fprintf(stdout, "76 * 55 = %s\r\n", bigTimeAsString("76", "55").toStdString().c_str());
//    fprintf(stdout, "568746 * 743115 = %s\r\n", bigTimeAsString("568746", "743115").toStdString().c_str());
//    fprintf(stdout, "2 * 4 = %s\r\n", bigTimeAsString("2", "4").toStdString().c_str());
//    fprintf(stdout, "963258 * 222 = %s\r\n", bigTimeAsString("963258", "222").toStdString().c_str());
//    fflush(stdout);

    QVector<QString> eachRes;

    for(QString line : _input)
    {
        eachRes << computeLineSecond(line.simplified().remove(' '));
    }

    QString res = bigSumAsString(eachRes);

    return res;
}

unsigned long long int Y20Day18::computeLine(QString line, int idx)
{
    unsigned long long int left = 0;
    unsigned long long int right = 0;
    QChar oper = ' ';
    bool getLeft = false;

    unsigned long long int befLeft = 0;

    for(; idx < line.size() ; idx++)
    {
        befLeft = left;
//        fprintf(stdout, "pass in for ");
        if(line[idx] == '+' || line[idx] == '*')
        {
//            fprintf(stdout, "with oper\r\n");
//            fflush(stdout);
            oper = line[idx];
        }
        else if(line[idx] == '(')
        {
//            fprintf(stdout, "with (\r\n");
//            fflush(stdout);
            int nextIdx = getParenthesisEnd(line, idx);
            if(getLeft)
            {
                right = computeLine(line.mid(idx + 1, nextIdx - idx - 1));
                if(oper == '+')
                {
                    left = left + right;
                }
                else if(oper == '*')
                {
//                    fprintf(stdout, "    %llu * %llu = ", left, right);
                    left = left * right;
//                    fprintf(stdout, "%llu\r\n", left);
//                    fflush(stdout);
                }
            }
            else
            {
                left = computeLine(line.mid(idx + 1, nextIdx - idx - 1));
                getLeft = true;
//                fprintf(stdout, "left = %llu\r\n", left);
//                fflush(stdout);
            }
            idx = nextIdx;
        }
        else if(_digit.contains(line[idx]))
        {
//            fprintf(stdout, "with digit\r\n");
//            fflush(stdout);
            if(getLeft)
            {
                right = line[idx].digitValue();
                if(oper == '+')
                {
                    left = left + right;
                }
                else if(oper == '*')
                {
//                    fprintf(stdout, "    %llu * %llu = ", left, right);
                    left = left * right;
//                    fprintf(stdout, "%llu\r\n", left);
//                    fflush(stdout);
                }
            }
            else
            {
                left = line[idx].digitValue();
                getLeft = true;
//                fprintf(stdout, "left = %llu\r\n", left);
//                fflush(stdout);
            }
        }
        else
            throw "C'est d'la merde";

        if(befLeft > left)
        {
            fprintf(stdout, "kaboum left\r\n");
            fflush(stdout);
        }
    }

    return left;
}


QString Y20Day18::computeLineSecond(QString line, int baseIdx)
{
    //Compute parenthesis
    for(int idx = baseIdx; idx < line.size() ; idx++)
    {
        if(line[idx] == '(')
        {
            int idxEndParenthesis = getParenthesisEnd(line, idx);
            QString parenthesisRes = computeLineSecond(line.mid(idx + 1, idxEndParenthesis - idx - 1));
            line.replace(idx, idxEndParenthesis-idx+1, parenthesisRes);
        }
    }

    //Compute +
    for(int idx = baseIdx; idx < line.size() ; idx++)
    {
        if(line[idx] == '+')
        {
            int searchIdxBg = idx;
            int searchIdxEd = idx;
            QVector<QString> sumVect = {};
            while (line[searchIdxBg-1].isDigit()) {
                searchIdxBg--;
                if(searchIdxBg == 0)
                    break;
            }
            while (line[searchIdxEd+1].isDigit()) {
                searchIdxEd++;
                if(searchIdxBg == (line.size() - 1))
                    break;
            }
            sumVect << line.mid(searchIdxBg, idx - searchIdxBg);
            sumVect << line.mid(idx+1, searchIdxEd - idx);

            QString sumRes = bigSumAsString(sumVect);

            line.replace(searchIdxBg, searchIdxEd - searchIdxBg + 1, sumRes);
            idx = searchIdxBg;
        }
    }

    //Compute *
    for(int idx = baseIdx; idx < line.size() ; idx++)
    {
        if(line[idx] == '*')
        {
            int searchIdxBg = idx;
            int searchIdxEd = idx;
            QVector<QString> sumVect = {};
            while (line[searchIdxBg-1].isDigit()) {
                searchIdxBg--;
                if(searchIdxBg == 0)
                    break;
            }
            while (line[searchIdxEd+1].isDigit()) {
                searchIdxEd++;
                if(searchIdxEd == (line.size() - 1))
                    break;
            }

            QString left = line.mid(searchIdxBg, idx - searchIdxBg);
            QString right = line.mid(idx+1, searchIdxEd - idx);

            QString sumRes = bigTimeAsString(left, right);

            line.replace(searchIdxBg, searchIdxEd - searchIdxBg + 1, sumRes);
            idx = searchIdxBg;
        }
    }
    return line;
}


int Y20Day18::getParenthesisEnd(QString line, int idx)
{
    int parenthesisCpt = 1;
    do {
        idx++;
        if(line[idx] == '(')
            parenthesisCpt++;
        else if(line[idx] == ')')
            parenthesisCpt--;
    } while (parenthesisCpt != 0);
    return idx;
}


QString Y20Day18::bigSumAsString(QVector<QString> eachRes)
{
//    fprintf(stdout, "Sum this\r\n");
//    fflush(stdout);
//    for(QString line : eachRes)
//    {
//        fprintf(stdout, "%s\r\n", line.toStdString().c_str());
//        fflush(stdout);
//    }


    int doneCount = 0;
    int idx = 1;
    int hold = 0;
    int current;
    QString output = "";
    while ( (doneCount < eachRes.size()) || (hold > 0) ) {
        doneCount = 0;
        current = 0;
        for(QString res : eachRes)
        {
            if(idx > res.size())
                doneCount++;
            else
            {
//                fprintf(stdout, "digit is  %i for %s\r\n", res[res.size()-idx].digitValue(), QString(res[res.size()-idx]).toStdString().c_str());
//                fflush(stdout);
                current += res[res.size()-idx].digitValue();
            }
        }


        current += hold;

//        fprintf(stdout, "Get %i\r\n", current);
//        fflush(stdout);

        int digit = current % 10;

//        fprintf(stdout, "Digit is  %i\r\n", digit);
//        fflush(stdout);

        hold = (current-digit)/10;

//        if(digit != 0 || hold > 0)
            output.push_front(QString::number(digit));

        idx++;
    }


//    fprintf(stdout, "output is %i\r\n", output.toInt()/*.toStdString().c_str()*/);
//    fflush(stdout);

    while (output[0] == '0') {
        output.remove(0,1);

    }

    return output;
}


QString Y20Day18::bigTimeAsString(QString left, QString right)
{
    QVector<QString> intermediateRes;

    for(int idxL = 1; idxL <= left.size() ; idxL++)
    {
        int hold = 0;
        QString interLine;
        for(int idxZ = 1; idxZ < idxL ; idxZ++)
        {
            interLine.push_front('0');
        }
        for(int idxR = 1; idxR <= right.size() ; idxR++)
        {
            int current = left[left.size()-idxL].digitValue() * right[right.size()-idxR].digitValue();

            current += hold;
            int digit = current % 10;
//            fprintf(stdout, "%i * %i + %i = %i (%i + %i)\r\n", left[left.size()-idxL].digitValue(), right[right.size()-idxR].digitValue(), hold, current, digit, (current-digit)/10);
//            fflush(stdout);
            hold = (current-digit)/10;
            interLine.push_front(QString::number(digit));
        }
        if(hold > 0)
            interLine.push_front(QString::number(hold));
        intermediateRes << interLine;
    }

    return bigSumAsString(intermediateRes);
}


const QString Y20Day18::_digit = "0123456789";

/*
const QVector<QString> Y20Day18::_input = {
//    "4+4+4",
//    "4*2",
//    "4+(2*3) + 5",

    "2 * 3 + (4 * 5)", //=>  26.
    "5 + (8 * 3 + 9 + 3 * 4 * 3)", //=> 437.
    "5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))", //=> 12240.
    "((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2" //=> 13632.

    "4 * (7 + 5 + 7) + 9 + 2 * ((5 * 6) * 9 + 6 + 3) + 3                                                                                                                                                   ",
    "5 + (4 * (3 + 2 + 5 + 9 * 3))                                                                                                                                                                         ",
    "4 + 5 + 9 * 9 * (7 * (7 + 7 * 3) * (9 + 3) * 5 + (2 * 8 * 3)) * 4                                                                                                                                     ",
    "(6 * 6 * 3 * (7 * 3 * 3 * 5) * 5 + 7) * (2 * 3 * 3 + 2) + 2                                                                                                                                          "

}; // */

///*
const QVector<QString> Y20Day18::_input = {
    "4 * (7 + 5 + 7) + 9 + 2 * ((5 * 6) * 9 + 6 + 3) + 3                                                                                                                                                   ",
    "5 + (4 * (3 + 2 + 5 + 9 * 3))                                                                                                                                                                         ",
    "4 + 5 + 9 * 9 * (7 * (7 + 7 * 3) * (9 + 3) * 5 + (2 * 8 * 3)) * 4                                                                                                                                     ",
    "(6 * 6 * 3 * (7 * 3 * 3 * 5) * 5 + 7) * (2 * 3 * 3 + 2) + 2                                                                                                                                           ",
    "2 + 6 * 5 * 4 + ((3 * 3 * 6 * 5 + 2) * 2 * 2) + 9                                                                                                                                                     ",
    "(3 * 4 + 3 * 6 * 7) + ((6 * 8 * 8 * 2 + 9 * 8) + 5 + 5 * 4 * 5 + 9) + (8 + 4) * 5                                                                                                                     ",
    "3 + 7 + 4 + (4 + (9 + 2 + 4 + 7 + 4)) + 6                                                                                                                                                             ",
    "2 * 2 * (9 * 5 * (9 + 4 * 8 * 4 * 5 * 8) + 9) * 2                                                                                                                                                     ",
    "5 + (7 + (9 * 3 * 8) * 4 * 2) * (4 + 2 * 8 + 4) * 4 + 9                                                                                                                                               ",
    "(9 + 4 * 8 * 7 * 8) * ((3 * 5 * 4 + 2 * 6 + 7) * 7 * 3 + 2 + 3 * 6) + (7 * 7 * 6 * 8 * (9 + 9 * 9 * 9 + 9 + 8) + 3) + 4 * 9 + (6 + 9 * 5)                                                             ",
    "9 * (9 + 6 * 2) + 8                                                                                                                                                                                   ",
    "(7 * 9 * 6 + 9) + 6 * 6 + (8 + 4 * (9 * 9) * 4 * 3) + 6                                                                                                                                               ",
    "(4 + 2) * 7                                                                                                                                                                                           ",
    "(3 * 7 + 3) + 7 * 5 * (4 + 9 * 8) + 4 + 3                                                                                                                                                             ",
    "(7 + (9 * 6 + 7 * 8 + 6 * 3) + 8 * 3) + 8                                                                                                                                                             ",
    "(8 * 2 + 8) + (8 * 5 * 8 * 7 * 8 * (3 * 3 + 9)) + 6 + 9 * (4 * 7 + 3 + 2)                                                                                                                             ",
    "6 + 7 * (3 * 2 + (3 * 8 + 9) * (4 + 2 + 5 + 7) + 8) + 7 + 5 * (6 * (7 + 6 + 5) + 3 + 4 * (8 + 4 + 9 + 3))                                                                                             ",
    "3 + 5 + (5 * (9 * 8 * 4) * 7 + 2 * 8) * (4 + 6) + (3 * 7 + 7 * 9 + (6 + 6 * 8 + 7 * 5 * 6)) * 4                                                                                                       ",
    "5 * (6 * 7 * 3) + 3 + 2 * 7 + ((9 * 6 + 5 + 3 + 8) * 4 * 5 * 7 * 7)                                                                                                                                   ",
    "(2 * 4 + 6 + 5) + (6 + 3 + 4 + 6 * 9 + 4) + (6 * 7 * 5)                                                                                                                                               ",
    "2 + ((9 + 9 + 5 + 8) + 2 * 6) * 7 * 3 * 4 + 6                                                                                                                                                         ",
    "6 * 4 + 9 * (5 + 5) + ((8 * 5 * 3 * 4 * 2) * 8) * 7                                                                                                                                                   ",
    "3 + (9 * 6 + 2 + 5 + 3) * (3 + 7 * 7 * 6 * 5) * (4 + (2 * 6 * 3 + 4 * 3 * 5) + 5 * 8 * 4 + (5 * 2 * 4 + 5 + 7))                                                                                       ",
    "(8 * 4 + 7 + 9 + 5 + 2) + 3 * 9 + (3 + 7 + 3 * 6 + 3) + 7 * 9                                                                                                                                         ",
    "8 * 7 * (6 * 2) * 2 * 7                                                                                                                                                                               ",
    "(2 + 6 + 3 + 8 * 4) + (3 + 4) + 5 * 9                                                                                                                                                                 ",
    "(2 * 6 + (8 + 8 + 9) + 7 + 7) + 9 * ((7 * 9 * 9) + 5 * 3 * 8 + (5 * 4 + 4 * 7) * 9) + 8 + 8                                                                                                           ",
    "(4 + (6 + 6 + 4 * 6 + 5 * 8) * 4) * 3 + (7 + 9 * 8 + 6 * (8 * 6 + 3 + 7 * 2 * 8) + 8) * 7 + 7                                                                                                         ",
    "(6 * 2 + 5) * (2 * (6 + 2 + 2 + 5 * 7 * 9) + 8 * 4) * 7 + 6 + ((4 * 6 + 5 * 4 + 2) * (7 + 9 * 7 + 8) + 4 * (5 * 4 * 9 + 3 + 6 + 7) * 5) + 6                                                           ",
    "6 * ((3 * 5 * 3 + 4 + 7 + 8) * 7 + 6)                                                                                                                                                                 ",
    "2 + 8 + 8 * 6 + (8 * 2 + 8) + 7                                                                                                                                                                       ",
    "(7 * 6) * 3 + 7 + 2 + 6 + 9                                                                                                                                                                           ",
    "2 * 2 * 3 + (2 * 2 * 4) * 2 + 4                                                                                                                                                                       ",
    "3 * (3 + (4 * 8) + 8 + 2 + 3 + 6)                                                                                                                                                                     ",
    "(3 + 2 + 2) + 3 + (2 * 7 + (8 * 4) * 9 * 2) + 8 + 2                                                                                                                                                   ",
    "9 * ((8 + 6 * 4) * 7) * 8 + (9 + 6) * 6 * (2 * 7 * 6 + (4 * 5 * 4) + 4)                                                                                                                               ",
    "3 + 2 * 3 * 9                                                                                                                                                                                         ",
    "(9 + 9 + 6 * 9 + 7) * (7 * 2 * 8) + ((2 * 3 * 7) * 3 + 9 + 9 * 6) + (8 + 8 + (7 + 9 * 2) * 4)                                                                                                         ",
    "((8 + 8 * 5) + 6 * 4 + 9 + 4 + 5) + 7 + 7 + 6 + (5 + 8 + 9)                                                                                                                                           ",
    "(3 + 9 + 2 + 5 * 7 * 6) * 2                                                                                                                                                                           ",
    "3 + 3 * ((2 * 3) + 3 * 6 * (4 * 3)) + 4 * (3 + 5 * 2 + 9 * 3)                                                                                                                                         ",
    "4 * 2 * 7 * ((4 * 5 + 9 + 8 * 6) + 8 + 9) + 7                                                                                                                                                         ",
    "(5 * 2 + 3 * 9 * 5) + 5 + 8 * (9 + 3) + (4 * 4 * 5)                                                                                                                                                   ",
    "2 * 4 + 3 + 9 + 7 + (3 * 4 * 3 * 7 + 7 + 5)                                                                                                                                                           ",
    "((2 * 4) * 3 * 3 * 7) + 7 * 3 + 2                                                                                                                                                                     ",
    "9 * 4 * 4 * (6 + 5) + 9 * 5                                                                                                                                                                           ",
    "7 * 5 * (5 * 2 * 7 * 8 + 5) + (2 * 4 + 7 + 3 * 5) + 7                                                                                                                                                 ",
    "5 * 2 * (7 + (8 + 9 * 2 + 3) * 3 + 3)                                                                                                                                                                 ",
    "(5 + 6 * 9 * 8 * 8) * (7 + 4 * 4 + (9 + 9 * 7 + 2 * 8) * 4) * (5 * 6 + 9 + 8 * (8 * 2 + 2 * 7)) * 9                                                                                                   ",
    "8 + 6 + (8 * 6) + 7 * (4 * 6) + 8                                                                                                                                                                     ",
    "9 + (4 * 8 * 4 * 5 + 8) * 3                                                                                                                                                                           ",
    "5 + 5 * 7 + (6 * (8 + 6 * 4) + 4 + 8 + 5) + 3                                                                                                                                                         ",
    "3 * 7 + (5 + 8 * 2 * 4 + (8 + 5 + 6 * 4 * 9) * 9) * 6 * 3                                                                                                                                             ",
    "((6 * 5) + 8 * 4 * 2 + (3 * 5)) + (4 * 5 + 2 * (5 + 9 * 6 + 2) + (8 + 3 * 5 + 4) * 4) * (3 + 6)                                                                                                       ",
    "8 * 8 + 8 * (6 + 7 * 2 + 2 * 7 * (5 * 9 * 3)) + 4                                                                                                                                                     ",
    "(5 + 7 + 7) + 6 + 7 * (3 + (9 * 3)) + 7 * ((9 + 3 + 2 + 6 * 4 * 4) + 2 + 2 * 8 + 9 + 5)                                                                                                               ",
    "5 + 3 * 8 * 6 + (4 * 4 * 7 * 3 + 8 + 9)                                                                                                                                                               ",
    "(9 * (8 * 6 * 6 + 8) + 5) * 3 + 5 * 5 + 9 + 8                                                                                                                                                         ",
    "3 + (8 + (7 + 2 + 6 + 5 * 7 + 3) + 6 + (9 * 3) + 5) + ((2 * 6 * 2 + 7 + 6) + 9 + 8) + 5 + 8 + 6                                                                                                       ",
    "8 * 6 + (2 * 5 + 7) * (3 + 6)                                                                                                                                                                         ",
    "(8 * 4) + 5 + (4 * (8 + 9) * 3 + 8) * 5 * 8                                                                                                                                                           ",
    "4 * (3 + 9 * (8 * 5 + 8 + 9 * 7 * 5)) + 9                                                                                                                                                             ",
    "9 * 7 * 8 + (5 + 3) + (4 + 5 + 5 * 5 * 7) * 2                                                                                                                                                         ",
    "8 * (5 + 8 + 3 + 6 * (4 * 7 * 6 * 3 * 9)) + 4 * 6 * 6 + 6                                                                                                                                             ",
    "(9 * (8 + 4 * 2 + 9 + 6 * 5) + 8 + 3 * 7) + 5 * 2 * 6 + 4 * 4                                                                                                                                         ",
    "6 + 7 * 4 + (9 + 5 * 9 + 4 + 6) + 3                                                                                                                                                                   ",
    "7 * 2 + (6 * 9) + 5 * 5 + 3                                                                                                                                                                           ",
    "(5 * 2 + (5 + 3 + 4 * 4 * 8 + 5) * 2 * 3 * 7) * 9 * 2                                                                                                                                                 ",
    "2 + (3 * 2 + 5) + (9 * 9 + 6 * 8)                                                                                                                                                                     ",
    "(4 + 4 + 3 + 5 + 5 * 2) * 2 * 5 + 9 + (7 * 5 + 5 * 5 + 3) + 3                                                                                                                                         ",
    "9 * (8 + 4) + 7 + 5 + 7 * 9                                                                                                                                                                           ",
    "4 * (8 + 2 + 7)                                                                                                                                                                                       ",
    "9 + 3 * 6 * 4 + (2 * 6 + (7 * 8 * 7 * 8) + 6 * 3)                                                                                                                                                     ",
    "8 + ((3 * 7 * 7 + 8 * 2) * 5 * 8) * (9 + 3 + 7 + 6)                                                                                                                                                   ",
    "7 * 2 + 4 * (6 + 4 * 8 * (8 * 9 + 8 * 3 * 6 * 6) * (5 + 7 * 6 * 3 + 6) * 6)                                                                                                                           ",
    "2 * (7 + 2 + (3 * 6 + 5 + 3 + 7) * 8 + (4 * 2 + 9 + 9 + 4 + 2)) * 9                                                                                                                                   ",
    "8 + (8 * 6 * 6 + (4 * 4 * 4 + 4) + 7 + 7) * 8 * 5 + 5                                                                                                                                                 ",
    "(9 + 2) + 6 * (5 * 7 * 6 + 7)                                                                                                                                                                         ",
    "8 * 3 + (6 * 2 * (8 * 2) * 5 + 9 + 9) + 4                                                                                                                                                             ",
    "4 * 9 + (6 + 2 * 9 * 9 * 5 + 5) * 3 * 7 + 4                                                                                                                                                           ",
    "(5 + (2 * 2 * 2) * 6 + 3 * (9 * 5 * 5 + 8 + 6 + 9) + 9) + (5 + 8 * 2 * (7 * 4 + 6 * 5) * 3) + 2 * 5                                                                                                   ",
    "7 + 4 + 6 * 5 + 7 * (5 + 9 * 6)                                                                                                                                                                       ",
    "(2 + 7 * (4 * 8 + 8 + 9 + 6 + 9) * 2) + 8 + 2                                                                                                                                                         ",
    "(2 * (6 * 8) * 8 * 5 * (9 * 4 + 3 * 7)) + 4 + (8 + 5 * 6 * (5 + 9 * 3 * 7))                                                                                                                           ",
    "4 + (8 * (2 * 6) + 4 * 5 + (7 * 2 * 3 + 9 * 6 * 2) + 5) + 2 + 2 * 7                                                                                                                                   ",
    "9 * (7 * 4) + 7 * ((6 * 9 + 9 * 6 * 8) + 2 * 2 * 5)                                                                                                                                                   ",
    "9 + (3 + 9 * 3 * 9 * 9) + (8 * 2 + 9) * 7                                                                                                                                                             ",
    "(5 + 6 + 8 * 7 + (4 * 3)) * 6 + 6                                                                                                                                                                     ",
    "4 * 7 * 7 + (4 * 5 * 2)                                                                                                                                                                               ",
    "(3 * 8 * 8 + 6 * 9 + 3) * (5 * 6 * 4)                                                                                                                                                                 ",
    "(4 + 2) * 4 * (4 + 9 + 2 * 9 * 8 + 8) + (8 * (8 * 3 + 8 * 5) + 6 + 4) * 3                                                                                                                             ",
    "(3 + 8 * 5 * 5 + (2 * 4 + 3)) + 2 * 7                                                                                                                                                                 ",
    "5 + 4 * (6 + 6 * 4 * (5 * 8 + 9 + 6 * 8 * 7) + 4 + 5) * 8 + 8 + (8 + (3 * 5 * 4 + 4 + 8 * 3) * 6 + 4 + 2 * 2)                                                                                         ",
    "((5 * 6) + 3 + 4 * (6 + 5) + 6 + 6) * 2 + 9 + (4 + 3 + 5 * (6 + 3 * 8))                                                                                                                               ",
    "6 + (4 * 5 * 9 * (4 * 4 * 9 * 7)) + 6 * 2 + (6 + 6 + 2 * 2 + 8 + 3) * 5                                                                                                                               ",
    "8 + (2 + 6) * 7 + (3 + 6) * 6                                                                                                                                                                         ",
    "5 * (7 * 9 * 9 + 7 + 3) + (9 + 4 * 6 * 6 * 9)                                                                                                                                                         ",
    "6 + 5 + 2 + (2 + 2 * 3 * 5 * 9 + 6)                                                                                                                                                                   ",
    "8 + 9 * (7 + 9 * 6) * (6 + 7 * 6) + 2                                                                                                                                                                 ",
    "5 * 9 + 4 + ((9 + 8 * 4) * 7) + 4                                                                                                                                                                     ",
    "(7 + 6 * (2 + 8 + 6 * 3) + 4) + 5 * 9 + 9 * (2 * 6) * ((4 + 6 + 2) * 6 * (6 * 8 * 8 + 3) + (2 + 3 * 2 * 8 * 8 * 3) * 3)                                                                               ",
    "7 * 5 + 5 * ((4 * 4 + 4 * 3 + 6 * 9) * 9 + 7 + (2 * 4) + (8 * 8 * 6 * 6 * 9 * 4) * 5) * (7 * 2) + 4                                                                                                   ",
    "2 * 4 + (3 * 8 + 8) + (8 + 9 + (4 * 5) * 8 * 9) + (8 + (8 + 5 * 7 + 8) + (8 + 9 + 4) + 7)                                                                                                             ",
    "5 + 3 + 4 + 2 * 3                                                                                                                                                                                     ",
    "((4 + 2) * 3 + 3 * 2 + 4 * (7 + 3 * 7 + 6 + 8 * 5)) * 3 * 9                                                                                                                                           ",
    "8 + (8 * 8 * 6) + 4 * 7                                                                                                                                                                               ",
    "(4 * (8 + 4 + 4 + 9 * 4) + 4 + (6 * 9 * 4 * 6 * 4 + 5)) * 7 + 2 + 3                                                                                                                                   ",
    "(2 + 4) + 3 + 8 + (7 * 6 * (9 + 8 + 8 * 9 + 5)) + 7 * 9                                                                                                                                               ",
    "8 + 9 * 5 + 9 + 7 * 9                                                                                                                                                                                 ",
    "(9 * 7) + 2 + 7 + 9                                                                                                                                                                                   ",
    "6 * 5                                                                                                                                                                                                 ",
    "7 + 2 * (5 * 7 * (4 + 5 * 7 + 2)) * 6 * (6 + 7 * 5 * 5 * 5 + (9 + 4))                                                                                                                                 ",
    "5 + 7 * 6 * 8 * (3 * 5 + 9 * 4 * (7 + 4 + 7 * 3)) * 8                                                                                                                                                 ",
    "(7 + 4 * 8 * 2 * (5 + 2 + 2) + 5) * 7 * 7 * (7 * 9)                                                                                                                                                   ",
    "2 * ((4 + 2 + 9 * 5 * 4) + 9 * 7 + 2) + 4                                                                                                                                                             ",
    "(9 + 2 + 2 + 7 * 2) + 5 * 8 * 3                                                                                                                                                                       ",
    "(6 + 9 + 5 + 4 + 8) * 8 * (9 + 8) + 5                                                                                                                                                                 ",
    "((7 + 5 + 8 + 5 * 8 + 9) * 6 * 7 + 8 + (7 * 3)) + (3 + 2 * 7 + (4 * 7 * 4 + 7 + 4 + 5) * 9 * (9 + 2 * 2 * 2)) * 4 * (6 + (7 * 4) * 7) * 4 * 5                                                         ",
    "(9 + 8) * 2 + 5 * ((6 + 4 * 6 + 6 * 8 * 7) * (5 + 9 + 8 * 6 * 7 * 4) + 6) * 8 * 7                                                                                                                     ",
    "8 + 3 + 2 + ((6 * 7) * 6 + 5 * 4 + 9) * 2                                                                                                                                                             ",
    "2 + ((3 + 8 + 8) + 8) + 3 + 2                                                                                                                                                                         ",
    "6 + ((7 * 3 + 6 * 7) + 2 * 7 * 4)                                                                                                                                                                     ",
    "7 * 4 + 9 + 6 + (5 + 2 * (8 * 2 * 7 * 2 * 4) + 2 + 7 * 7)                                                                                                                                             ",
    "(4 * (9 + 2)) * 5 * 8                                                                                                                                                                                 ",
    "2 * ((4 * 5) * (8 * 4 * 8 + 6) * 6) * 6 + 7                                                                                                                                                           ",
    "4 + 7 * 3 + (8 + 7 * 2 + 8 * (8 * 9 + 5 + 4)) * 3                                                                                                                                                     ",
    "5 * 6 * 3 + 9 * 2 * 4                                                                                                                                                                                 ",
    "7 + (6 * (6 * 8 * 5 * 9) + (3 * 9 + 6 * 6 + 4) * (8 * 8 * 9 + 8) + (4 * 7 + 6)) * 5                                                                                                                   ",
    "9 + (8 * 4 + 5 + 6 + 2 + 4) * (5 + (8 * 8)) + 4 + 6                                                                                                                                                   ",
    "3 * (3 + 7 * 7) * 8 + (3 * 3 * (2 * 8 + 4 + 3 * 7 * 2)) * 3                                                                                                                                           ",
    "2 + (9 * (9 + 5) + 8) + (8 * 9 + 6 * 6) * (3 + 6 * 4 * 5 * 9 + 9) + 2 + (8 + 5 * 5 * 2 * (2 + 3 + 3 * 4) * 5)                                                                                         ",
    "7 * 2 * (3 * 2 + 4 * 9 * 3)                                                                                                                                                                           ",
    "(2 + 9 * (4 * 8 * 3 * 6) * 7 + (2 * 7 * 5 * 6 * 8 + 8)) + (5 + 9 + (6 + 8) + 8) * 5 * (2 + 3 + 2 + 6)                                                                                                 ",
    "2 + (4 * (2 * 6 * 4 * 8) * 5 * 3 * 8 + 7) + (8 + 8 * 3 + 6 + (5 * 7)) * 6 + 2 + 7                                                                                                                     ",
    "(7 * 6 + 4 * 3 + 8 + 5) + ((7 + 3) + 7 + 4 + (4 * 9 * 2 + 6 * 2 + 8) * 5)                                                                                                                             ",
    "4 * 5 + 5 + 8 + (8 + 3 + 6 * 2 * 3 * 8) * 9                                                                                                                                                           ",
    "6 + 7 + (3 * 8 + 3 + 5 * 5 + (4 * 8 * 6 + 9 * 7 + 8)) + 8                                                                                                                                             ",
    "((2 * 3 + 3 * 9 * 8 + 3) * (7 + 2 * 2 * 3 + 3 * 7) + 5 + (8 * 9 + 4 * 9 + 9) * 6) * 9                                                                                                                 ",
    "7 * 4 * 5 * 7 + ((4 + 5 + 3 + 3 * 5 * 7) * (8 + 7 + 9 + 9 + 2 + 4))                                                                                                                                   ",
    "(3 * 2 * 8 * 4 * 4) * 4 + (4 + 8 + 7 + 4 + (5 * 9 * 5)) + ((5 + 2 + 6 + 3 * 3 * 9) + 4) * 9 * 3                                                                                                       ",
    "6 + 8 * 8 + 4                                                                                                                                                                                         ",
    "8 * (4 * 4 * 4 + 8 * 3 + 4) * 4                                                                                                                                                                       ",
    "6 * 4 * 8                                                                                                                                                                                             ",
    "(2 + 7 + 9 * (5 + 6) * 6) * 8 + 8 + 6 + 7                                                                                                                                                             ",
    "7 + 8 + 5 + 6 + 6                                                                                                                                                                                     ",
    "(2 * 2 * 6) * (7 + 3) * 4 + 4 * 9 * 4                                                                                                                                                                 ",
    "3 + (6 * 6 + 5 + 5 + 7) * 7 * (5 + 3) + 5                                                                                                                                                             ",
    "(7 * 2 + (5 * 3 + 7 * 4 * 3) * 7 * 2) * 6 * 4 * 3 * 3 + 5                                                                                                                                             ",
    "5 * ((9 * 8 + 8 * 7 * 7) + 4 * 3 * 9) + (2 * 9 + 9) * 9 * (5 + 2 + (4 * 8 * 4 + 8 * 5 + 8) * 7) * 4                                                                                                   ",
    "((8 + 6 + 2 + 4 * 5) + 7 + 8 * 5) * 9 + 4 + 6 + 4 * 6                                                                                                                                                 ",
    "5 + (6 * 4 * (5 * 4 + 7 + 2) + 4) + (7 + 3 * 9 + 7) + ((8 * 3 + 8) + 5 * 4 * 7 + 7 * (8 + 4))                                                                                                         ",
    "((7 + 9) + 5 + 8 * 4) + 4 + 3                                                                                                                                                                         ",
    "9 + 6 * (3 * 9 + 2 * 2) * 8 * 6                                                                                                                                                                       ",
    "5 + ((7 + 5 + 3) * (9 + 5 * 6 * 7 + 4 + 2) + 9 * 2 * 7 + (4 + 7 + 7 + 8 + 5 + 9)) + 5 * 9                                                                                                             ",
    "6 + (4 * 8 * (6 * 9)) + 9                                                                                                                                                                             ",
    "9 + 6 + ((9 + 6 + 3 * 3 * 4 * 2) + 9 + 7 + 8 + 5) + ((3 + 7 * 7) * 9 * 9 + 9) + (4 + 6) * 3                                                                                                           ",
    "9 + (2 * 3 + (5 * 5 * 8 * 4 * 9 * 2) * 9 + (3 + 2 * 7 + 9) * 2) * 2                                                                                                                                   ",
    "3 + (2 + 3 * 4 + 4) * (5 + 6 + 9 * 3) + 3                                                                                                                                                             ",
    "(8 * 4 + 5) + 4                                                                                                                                                                                       ",
    "5 + ((3 + 3 * 7 * 3) + 7 * 2) + 4 + ((9 + 6 + 9 + 7 * 7 * 9) + 5 * 4 + 7 * (7 * 3) + (5 * 9 + 8 * 3 * 2))                                                                                             ",
    "4 + (3 * 8 * 7 * 5 + 2 + 8)                                                                                                                                                                           ",
    "2 * 8 + (5 * 9 * 9 * (9 * 9 + 6) * 9)                                                                                                                                                                 ",
    "(5 * 3 * (3 + 7 + 2 + 3 + 8)) + 9                                                                                                                                                                     ",
    "2 + 3 + 8 + (3 + 5 * 4 * 6 + 4)                                                                                                                                                                       ",
    "5 + 5 + (9 * (6 * 3 + 3 * 3 + 6 * 8))                                                                                                                                                                 ",
    "2 + 2 + 7 + (6 * 8 * (4 * 4 + 2) + 4)                                                                                                                                                                 ",
    "3 * 8 * (4 * 2) + (5 * (4 * 7 * 2 + 6))                                                                                                                                                               ",
    "((2 * 3 + 7 + 5) * 8 + 8 * 2 + 5 * 9) + 4 + 8 + 4 * 6                                                                                                                                                 ",
    "7 * 3 + 6 + (8 + 8 * 6 + 9) * 9                                                                                                                                                                       ",
    "3 + 7 + 8 * 7                                                                                                                                                                                         ",
    "2 * 6 + ((3 * 4) + 9 + 6) + 2                                                                                                                                                                         ",
    "(4 * 7 + 4) * (2 * (9 * 2 + 7 * 2) + 8 * 7) + 7 * 6 * 4                                                                                                                                               ",
    "2 * 8 + (9 + (4 * 6 + 4 + 8 * 7 * 5) * 2 * 4 + 5) * 9                                                                                                                                                 ",
    "8 + 6 + 3 * ((4 + 9) * 3 + 3 * 2 * 2) * 7 + 7                                                                                                                                                         ",
    "5 * 4 * ((7 + 2 + 6) * 5 + 6 + 2 + 9) * 5 + 7 * 3                                                                                                                                                     ",
    "7 * (9 * 9 * (3 + 3)) * 8 * 7                                                                                                                                                                         ",
    "7 * ((9 + 8 * 4 + 4) + 3 * (9 * 5 * 4)) * 6                                                                                                                                                           ",
    "(4 + 6) * (4 + 7 * 2) * 5 * 2 + 8                                                                                                                                                                     ",
    "6 + 8 * (3 + 8 * 3 + 4 + 9 + 8) + 3 + 2                                                                                                                                                               ",
    "5 + 2 * 5 * 7 * ((9 + 5) + 8 + 2)                                                                                                                                                                     ",
    "4 * (3 + 4) * (8 * 3) * 5 + 7 * ((5 * 5 * 4 + 5 + 2) + 4)                                                                                                                                             ",
    "(9 * (9 + 2) + 7 * 4 + (7 * 8 * 3) + (7 * 7 * 3)) + (2 + 5 * (9 * 9 + 6 + 3) + 6) + 2 * 4 + ((4 + 5 + 8 * 6 * 3) + (5 * 5 + 2 * 2 * 2) + 2 + 4 * 3 * 8) * 7                                           ",
    "6 + 2 + 6 + ((3 * 9 + 7 + 7) + 3 + 6 + (6 + 2 * 6 + 3) + 8) * 5                                                                                                                                       ",
    "(5 * (6 * 2 * 5 * 2 + 6 + 6)) * 3 * 8                                                                                                                                                                 ",
    "5 * (4 + 8 + 2 + (5 * 6 * 9) + (8 * 3)) * (8 * (6 + 3 + 6 * 2) + 9 + 8) + 2 + 6 + 3                                                                                                                   ",
    "2 + 3 + 6 + (3 * (2 + 2 * 8) * 7 + 4 * 8 * 7)                                                                                                                                                         ",
    "(4 * 8 + 8 + 8) * 5                                                                                                                                                                                   ",
    "8 * 4 * (5 + 8 * 8 * 2) + 4 * 8 * 5                                                                                                                                                                   ",
    "4 * (7 * (5 + 5 + 5 * 6 * 7) * 2) * ((8 * 9 * 6 * 2) + 7 + 9) * (3 * 6 + 5 * (8 + 9))                                                                                                                 ",
    "5 + 2 * 4 * 8 * 4 * 4                                                                                                                                                                                 ",
    "(6 + 5 * (2 + 7 * 5 * 5 + 4)) * 5 + ((6 + 2) + 7 * 6 * 3 * 8 + 5) + 6 * 2                                                                                                                             ",
    "(3 + 4 * 5 * 6) + 6 + (5 + (5 + 9 + 5 * 3 + 4) * 2 + (5 + 2 * 4 * 3 + 3 * 4) * 8) + 4 + (6 + 8)                                                                                                       ",
    "9 * 3 + 4 * 3 + (9 + 7)                                                                                                                                                                               ",
    "(7 * 4) + (4 * 8 * 2) * (6 + 5 * 7 * 7 * 2) * ((3 * 4 * 9 + 2) + 7 + 3 * 5 + 6 * 5) * 2                                                                                                               ",
    "3 + 3 * (9 * 2 + 4 + 6)                                                                                                                                                                               ",
    "(8 + 9 * 6 * 5) * (3 + 4 * (7 + 5 + 3) + 4) * 3 + 5                                                                                                                                                   ",
    "2 + 8 * 6 + 8 + (9 * 4 * 2 * 7) + 9                                                                                                                                                                   ",
    "3 + 4 * (3 * 5 * (4 * 7 * 9 + 8 * 2) * 9 + (6 * 3 + 4 + 6 * 5) * (2 + 8 + 2 + 2)) + (6 * 2 * 5 * 5 + 3 + 4) + 6 * 8                                                                                   ",
    "3 + 5 + 3 + 5 + 7                                                                                                                                                                                     ",
    "(8 * 4 * 6 + 3 * 6) + 6                                                                                                                                                                               ",
    "3 + (4 + 7 + 5 + 3)                                                                                                                                                                                   ",
    "(2 * 9 + 9 + 7 * 9) * (4 + 3 + 3 * 4) * 2 + (3 * 5 * 9 + 4 * 6) + 2                                                                                                                                   ",
    "(4 + 2) * 6 * ((2 * 6 + 2 * 3 * 5) * 6) + 9 * 2                                                                                                                                                       ",
    "5 * 3 + (4 + 5 * (7 * 2 + 9 + 3 + 3)) * 5 + 2                                                                                                                                                         ",
    "2 * 3 * 4 + 9 + (4 * 6) * 6                                                                                                                                                                           ",
    "7 + 2 * 9 * ((2 + 5 * 9 * 2) + 9 + 4 + 3) * 9                                                                                                                                                         ",
    "7 * (6 * (8 * 7) * 5 * 6 + (4 * 3 + 9 * 6 + 8 + 6) + 8) * 2                                                                                                                                           ",
    "3 + (8 * (2 + 2) * 3 + 6)                                                                                                                                                                             ",
    "3 + (8 * 6) * ((4 * 3 * 7 + 5 * 9) + 8 * 5) * (6 * 5)                                                                                                                                                 ",
    "6 + 2 + (4 + 6 + 3 * 7 * 8) + 5 + 4                                                                                                                                                                   ",
    "(9 * 3 * 5) * 9 + 7                                                                                                                                                                                   ",
    "(9 * 6) * 3 + ((2 + 9) * (7 + 3 + 9 + 7)) * 6 * 6                                                                                                                                                     ",
    "3 * 4 + 2                                                                                                                                                                                             ",
    "5 * 2 * (7 + (6 + 3 * 4) * (3 * 4 + 4 * 3 + 5) + 3) + 6                                                                                                                                               ",
    "(4 + 8 + 4 + (6 * 5 + 4 + 5) * 7) + 3 * 4 * 7                                                                                                                                                         ",
    "8 + (6 + 4) + 4                                                                                                                                                                                       ",
    "(4 + 2 + (4 * 4 * 8) * 5) + 7 * (7 * (3 + 6 * 3 * 9 + 9 * 5) + (9 + 8 + 6 * 5 + 3)) * 9 * 9 * 2                                                                                                       ",
    "8 + ((4 * 9 + 7 * 2) + 6 + (4 * 9 * 5 + 3 * 9 * 5) + 2 * 7 + 6) * (5 * 9) + 4                                                                                                                         ",
    "6 * (9 * 3 * 6 + 4 + (2 * 2 + 6 * 5 + 3)) + 5                                                                                                                                                         ",
    "(8 + 8 + 4 * 4 * 8 + 6) + 7 * 7 + (7 * 3 * 8 * 2)                                                                                                                                                     ",
    "5 + (4 * 4 * 7 + 5) + (3 * 7) * 4 + 3                                                                                                                                                                 ",
    "3 + (5 + 7 + 5 * (5 + 9 + 5 * 6 * 8) * 9 + 9) + 3                                                                                                                                                     ",
    "(3 + 5 + 6 * 2 * 8 + (9 * 2 + 8 * 5 + 3 * 6)) * 6 + 5                                                                                                                                                 ",
    "3 * (7 * 4 + 7 + (4 + 2 + 8) + (4 + 4 + 5 * 2) + 5) * 6                                                                                                                                               ",
    "4 + ((7 + 3 + 7 + 3) + (8 * 2 + 3 + 3)) * (8 + 2) + 3 + 9                                                                                                                                             ",
    "9 + 7 * (5 + 2 + (3 + 7 * 2 * 6 + 7 * 6) + (3 * 8 * 6 * 9) + 7 + (7 + 7 + 7)) * (7 * 2) * 4 * (8 + 5 * (5 * 7 + 7 * 3 * 6 + 4) * (8 + 2 * 6 + 3 * 2 + 8))                                             ",
    "5 + 2 * (5 + 9 + 5) + 5 * 8                                                                                                                                                                           ",
    "9 * 4 * (4 + (8 * 7 * 8 * 5 + 2 + 7) + 7 * 8) + 2                                                                                                                                                     ",
    "5 * (7 + 6 * 2 * 9 * (2 * 2 * 8 + 7)) * 3 * 3                                                                                                                                                         ",
    "6 + 6 * 9 + (2 + (4 * 3 * 8 * 3 * 9) + 5)                                                                                                                                                             ",
    "9 + 3 * 2 * 3 + (9 * 4 * (4 * 9 * 3) * 8 + 7)                                                                                                                                                         ",
    "(8 + (3 * 5 * 9 * 7 * 8) + 7 + 3) + 5                                                                                                                                                                 ",
    "(6 * 6 * 5 * 6 * 3) + 5 * 8 * 6 * 8 + 6                                                                                                                                                               ",
    "2 * (4 + (8 * 7) * 7) + 7 + 8                                                                                                                                                                         ",
    "2 + (2 + 5 + (3 + 8 + 4)) + 2                                                                                                                                                                         ",
    "(5 * 6) * 9 + 4 + 3 + (9 * 3 * 7 * 8) + (2 + 9)                                                                                                                                                       ",
    "8 + ((8 * 2 + 9 * 3 * 7 + 2) * 4 + (2 * 6 + 6 + 4)) + 4 + 5 + 8 + 3                                                                                                                                   ",
    "7 * 2 * 8 * 9 * ((2 + 7 * 2 * 4) * 6 + 4 + 9 + 2) + 5                                                                                                                                                 ",
    "7 * (5 + 3 + 2 + 6) + 4 * 3                                                                                                                                                                           ",
    "9 + ((7 * 6 + 4 * 7 + 6 + 9) * 5 + 4 * 8) + 2 * (6 * 8 + 6 + 4 + 8 + 3) * 7                                                                                                                           ",
    "8 * (8 * (8 * 5 * 8)) + 6                                                                                                                                                                             ",
    "2 + 2 * 9 + 6 * 4 * 6                                                                                                                                                                                 ",
    "4 * (5 + 9 * (8 * 4 + 9 + 9 + 7 * 2) * 4 * 2 * (5 * 9)) * 9 + 5 * 9 + 5                                                                                                                               ",
    "8 * (2 + 9) + 7 + 8 * (7 * 3 * 3) + 3                                                                                                                                                                 ",
    "8 * 3 * 5 * 8 + 5                                                                                                                                                                                     ",
    "9 + 3 * (4 * 6 * 7 * 4 + 6 + (2 * 3 * 9 * 9 + 7)) * (7 + 3 + 9) + 9 * 4                                                                                                                               ",
    "(3 * 5 + (9 * 4 + 8 + 7) + 9 + 2) + 4                                                                                                                                                                 ",
    "(6 * 3 * 6 + 6) * ((5 + 3 * 2 * 7 * 6 * 5) + (5 * 2 + 7 + 2) * 3 + 6) * 6                                                                                                                             ",
    "((3 + 9 * 2) * 2) * 2 + (3 + 6) + 9                                                                                                                                                                   ",
    "4 + 2 * 8 + 8 + (8 * 3) + ((3 + 9 * 3 + 2 * 5 * 2) * 3 + (9 * 5 + 9) * (6 * 3 + 4 * 7 + 3) * 3 * 5)                                                                                                   ",
    "5 + (4 * 7 * 4 * (2 + 2)) + 9 + 2 * 2                                                                                                                                                                 ",
    "5 + 4                                                                                                                                                                                                 ",
    "((9 + 3 + 3) + 6 + 2 * 4) * (3 + 6)                                                                                                                                                                   ",
    "(7 * 6 * 5 + 7) * 3 + (6 + 4) + 2                                                                                                                                                                     ",
    "7 * 7 * (9 * 4 * 8 + 4 * (2 + 8) * 4) + 6 * 8 * (6 * 7 + 8 + 6 * 7 + 8)                                                                                                                               ",
    "(8 + 4 + 9) + 7 * (5 + 9 * 7) * 4                                                                                                                                                                     ",
    "2 + 6 * (3 + 8) * 3                                                                                                                                                                                   ",
    "3 + ((8 * 6 + 2 * 4 + 9 + 4) * 8 * (3 + 3 + 2 * 7 * 8)) + (3 * 6 * 6 + 2) + 5                                                                                                                         ",
    "(2 + 9 * 3) * 2 * 6 * 7                                                                                                                                                                               ",
    "5 + 8 * (7 + 4 * (9 + 3 + 7 * 5 * 9 * 5) + 8 + (2 + 2)) * 3 + ((6 + 2 + 9 + 8 * 2 * 3) * 7 + (6 + 2 * 3 + 6 + 5) + 9 + 7 * 5) + 3                                                                     ",
    "((8 * 2 + 2) * 6 + 2 * (2 + 7)) + (7 + 2 + (2 * 8 + 8 + 9) + 8) * 5 * 7 * 5                                                                                                                           ",
    "6 + 7 * 8 + 3 * (2 * 8 * 9)                                                                                                                                                                           ",
    "8 * 8 + (3 + 8 + 3 + 6 * 9 + (8 * 7 * 4)) * 2 + 6 + (8 * 7 * (8 + 5 * 5) + 7 * (3 * 8 * 4 * 9 + 7) + 3)                                                                                               ",
    "4 * (3 * 8 + 9 * 4 + 5) + 2 * 8                                                                                                                                                                       ",
    "(7 * 5 + (3 + 6) * (3 * 3 * 2 + 2) + 7 + 3) * 7                                                                                                                                                       ",
    "7 + 2 * ((9 * 4 * 3) + (9 * 5 + 6 * 2) + (3 + 9 + 4) + (2 * 8) + 8 * (4 * 4 * 2 * 4 + 7)) + 7                                                                                                         ",
    "4 + 4 + (5 * (7 * 8 + 2) + 3 + 6) * 6 * 5                                                                                                                                                             ",
    "((9 * 4 * 2 * 7) + (9 + 5 * 6) * 7 * 8) * 2 * 2 * (7 + (4 + 6 * 7)) + 5 * 7                                                                                                                           ",
    "7 + 5 * 3                                                                                                                                                                                             ",
    "(6 + 8 + 9 * (6 * 3 + 3 + 8 * 6 + 8) + (7 + 7)) + 4 * 6                                                                                                                                               ",
    "6 + 8 + 5 * ((2 * 4 + 2 + 2 + 3 + 8) + (9 + 7 + 6 + 8 + 6))                                                                                                                                           ",
    "5 + 3 + 9 * 2 * 2 + (8 + 4 * (5 + 6 * 9 * 4) * 2)                                                                                                                                                     ",
    "(9 * 7 * 3 * 6 * 7 * (7 + 2 * 4 * 6 * 4 + 8)) * (9 + 6 + 4 + (4 + 2 + 4 * 3) + 9 + 9) + 3 + 7                                                                                                         ",
    "7 * 3 * 9 + (7 + 4 + (9 * 3 * 6 + 3 * 5) + (9 * 8) * 3 * (3 * 6 + 8))                                                                                                                                 ",
    "(2 * (4 * 3 * 3 + 3 * 2) + 4) + 2                                                                                                                                                                     ",
    "(6 * (2 + 5) * 4) * 8 + 3 + 5 * 2 + 3                                                                                                                                                                 ",
    "(9 + 7 * 9 * 2 + 2 * 9) + 3 * 5 * 6                                                                                                                                                                   ",
    "7 * 8 + (7 * 3 + (8 * 5 * 6))                                                                                                                                                                         ",
    "4 * (6 + 5 * 8 + 4 * 4 + 5) * 5 * 6                                                                                                                                                                   ",
    "4 + (4 * 4 + (9 * 4 * 7) * (7 + 8 + 9 + 8 + 4 * 7) * 9 * 2) + 4 + 7 * (9 * 8 * 4 + 2 * 9 + 3) * (9 + 5 * 3)                                                                                           ",
    "4 + 7 * (3 + 5 * 3 * 7) + 7                                                                                                                                                                           ",
    "5 + 4 + (6 + 5 + (7 + 3 + 5) + 7 * 5) * 3 + 7                                                                                                                                                         ",
    "2 * ((9 * 7 * 2 * 7) + (5 + 2 + 3 * 2)) * (7 + 8) * 8 * (9 * 2)                                                                                                                                       ",
    "2 * 5 * (5 * 3 * 2 * 7 + 4) + 3                                                                                                                                                                       ",
    "4 + 5 * 3 * (4 + 9 + 3 + 8 + 2 * 3) + 6                                                                                                                                                               ",
    "4 * 4 + ((2 + 8 * 2 * 6 + 2 * 2) + 7)                                                                                                                                                                 ",
    "3 + (2 + (7 * 9 + 3 + 6 * 8 + 9) + 5 * 4 + 7 * 7)                                                                                                                                                     ",
    "((4 * 8 + 3 * 8) * 9) * ((4 + 4 * 6 + 5 * 8 + 6) * (7 + 7) * 8) + 6 * 4 + 4 * 3                                                                                                                       ",
    "(3 * 9 * 8 + (5 + 9 * 8 * 2 * 5 * 7) + (4 * 3 + 2 + 9 + 2 * 8) * 6) * 5 * (7 + 2 + 2 * 2 + 5) + 8 * 5                                                                                                 ",
    "(3 * 3) * (2 + 6 * 7 * 9)                                                                                                                                                                             ",
    "(7 * 8 * 9 + (7 + 8) * 5) + 7 + 9 * 3 * 4 + 2                                                                                                                                                         ",
    "(3 * 3 + 7 * 7) * 6 + 2                                                                                                                                                                               ",
    "(4 + 2 + (6 + 6 * 6 + 9) + 8) + 7                                                                                                                                                                     ",
    "8 * 8 + 7 * (2 * (7 + 3) + 2 + (8 * 8 + 5 * 4 + 9) + 6 * 8) + (7 * 8 * 8)                                                                                                                             ",
    "9 * 2                                                                                                                                                                                                 ",
    "9 * 5 * 5 * 8                                                                                                                                                                                         ",
    "6 * 3 * 4 + ((6 * 6 * 4 * 2 * 2 * 5) + 2 * 6 + 5) + 3 * 2                                                                                                                                             ",
    "3 * 5 + 5 + (3 * (3 + 4 * 5 * 5 + 3 * 7))                                                                                                                                                             ",
    "(3 + 9) + 2 * 8                                                                                                                                                                                       ",
    "5 * (5 + (8 * 8 + 8 * 5 + 2)) * 6 * (3 * 6 * 2 * 6) * 2 + 9                                                                                                                                           ",
    "(9 + 5 * 9 + 3 + 3) * 9 + 3 + (2 * 8 * (4 + 4 * 4 * 6 * 6) + 4)                                                                                                                                       ",
    "8 + (2 + 9 + (4 + 5 + 7) * 2) + 3                                                                                                                                                                     ",
    "7 + 9 + 9 + 3 * 7                                                                                                                                                                                     ",
    "2 + (7 * 6 * 2 + 7 + 8 * 2) + 3 * 4 + 9 * 2                                                                                                                                                           ",
    "(3 * (8 * 9 * 2 + 9 + 6) * 5) * 9 + 6 * 6 + 8                                                                                                                                                         ",
    "3 * 6 + (5 + 4 * 6 * 6 + (7 + 7)) * 4                                                                                                                                                                 ",
    "4 + (8 + 9 + 9 + 3 + 6 + (5 + 5)) * 6 + 6 + 3                                                                                                                                                         ",
    "(7 * 5 * 7 + 2 + 2) * 5 + (3 * 8 * 7 * 8 * (3 * 6 + 9 + 8) * 4) + 8 + (7 + (7 * 7 + 5 + 6 + 7) + 2 + (8 + 3) * 7) + 9                                                                                 ",
    "(8 * 3) + 8 + 9 * 3 + 5                                                                                                                                                                               ",
    "(6 + 8 * 4 + 2) * 2 * (7 * (6 + 2 * 2 + 2 * 4 + 8) * 6 * 8 * 7) + 6 + 4 * 9                                                                                                                           ",
    "8 * ((6 + 6 * 7 + 9) + 3) + 6 + 4 + 2                                                                                                                                                                 ",
    "7 + 7 + 7 * 6 * 2 + (5 + (4 * 6 + 3 * 5 + 8 + 4))                                                                                                                                                     ",
    "5 + (5 + (5 + 7 * 7) + (8 + 6 + 2 + 4 * 9 * 6) + (9 + 5 + 2)) * 7 * 3                                                                                                                                 ",
    "3 + 4 + (3 * 6 + 6 + 4) + 9 * ((9 * 2 * 8) * 2) * 6                                                                                                                                                   ",
    "8 * 7 * (8 * 8 * 5)                                                                                                                                                                                   ",
    "(4 * (3 + 2) * 8 * 4 * 9) * 7 + 7 + 6 + 2                                                                                                                                                             ",
    "7 + 9 * (9 * 8 * 9) + 8 + (3 + 2 + 7 + 2 * 4 + 8)                                                                                                                                                     ",
    "(3 + 9 + 4 + 2 + 8 + 4) + (7 + 5 + (2 * 6 + 4 * 5 + 4)) * 9 * 3 + 4 + 8                                                                                                                               ",
    "7 * 3 * 8                                                                                                                                                                                             ",
    "((2 * 3) + 4 + 4 * (7 * 8) + (3 + 8)) + 2 * 4 + 5 + 5 + 7                                                                                                                                             ",
    "2 + (9 * 3 * (3 * 4 * 6 * 8 + 7 * 9) * 2 * 2) + (8 * (4 * 9 * 9) + (5 * 8) + 9 * 9 + 5)                                                                                                               ",
    "6 + 8 + (3 * 3 + (4 * 6 + 8 * 8))                                                                                                                                                                     ",
    "7 * 3 + 7                                                                                                                                                                                             ",
    "3 + 5 * 5 + 6 * 4 * (2 * (3 * 2 + 6 + 2) + (6 * 2 * 3 + 6 + 8 * 6))                                                                                                                                   ",
    "3 * 5 * 7 + ((4 * 8 + 2 * 6 * 8) * 5) * (6 * 6 + 3 + 5 + 8 + 7) + 3                                                                                                                                   ",
    "(4 + 2) * 9 + 5 * (8 + 5 + 8 + 5 * (9 + 3 * 8 * 9)) * 7 * (3 + 5 + (4 + 2 * 8 + 3 + 5 * 8) * 2 * (4 * 4 + 9 * 6 + 9) * 5)                                                                             ",
    "((4 * 7 * 4 * 5) + 3 + (9 + 8 + 7 * 2 * 2 + 6) * 6) * 5                                                                                                                                               ",
    "4 * (5 * 2 * 8 * 4 + 2) * 2 + (5 + 6 + (3 + 2 * 8 * 5 * 2))                                                                                                                                           ",
    "9 * ((2 + 6 + 6 * 6 * 7 + 2) * 5) * 2 * 3 + 7                                                                                                                                                         ",
    "((4 + 3 + 6 * 4) * 5 + 3 + 3 + 8 * (8 + 2 * 6 * 6)) + (5 + (8 + 7) * 2 * 2 + (9 * 3 + 9 + 3 * 3) * 5) + 2 + 6 * ((4 * 3) + 5 * 3 * 2 + (4 + 2 * 6 + 8 + 5)) + 7                                       ",
    "(4 * 8) * 7 * 3 * 2 + (3 * 4 * 7 + 4)                                                                                                                                                                 ",
    "(8 + 7) * 9 + 7 + 9 + (6 + 3)                                                                                                                                                                         ",
    "7 * 4 + (7 * (5 * 6 + 7 * 9 + 3 + 4)) * 8                                                                                                                                                             ",
    "2 * (4 * (7 * 3 * 7 * 9) + 9 + 8 + 9 * 6) * 3 + 9 * 6                                                                                                                                                 ",
    "2 + (9 + 3 + 2 + 7 + (7 * 7 * 4 + 2) + 8) * 5 + 3 * 4 * 4                                                                                                                                             ",
    "6 + 5 * 7 + 5 + (4 * 8 + 6) * (4 + 3 * 3)                                                                                                                                                             ",
    "8 + (7 + 4 * 7 * 3) * 2 * 7 * 3                                                                                                                                                                       ",
    "2 * (9 + 3 + 2 * 6) + 6 + 6 * (4 * 6 + 7 + 9 * 9 + (2 * 6 + 5 * 3 + 4))                                                                                                                               ",
    "3 + 8 + (5 + 6 * 4 + (6 * 9) + 2)                                                                                                                                                                     ",
    "(4 + 5 * 4 * 9) * 7 * (9 + 3) * 7 * 4 + 7                                                                                                                                                             ",
    "(6 * 6 + 8 + 5 * 3) * (3 + 3 + 5 + 8 * 2 * 6)                                                                                                                                                         ",
    "(5 + (8 * 5 + 6) * (6 + 4 * 4 * 7) + 4) + (7 * 3 + 8) * 4 * (3 + 6 * (9 * 3)) + 6 * 9                                                                                                                 ",
    "6 + (6 * 7 * 2 * (2 + 9 + 2)) + 3 + (6 * 4 + 6 * 8 * 4) + 3 * 2                                                                                                                                       ",
    "((8 * 3) + 2 + 4 * 7 + 7 + 6) + 4 + (8 * 4 * 5 + (9 * 2) * (7 + 6)) * 7                                                                                                                               ",
    "(3 * 8 + (9 + 4 + 2 + 7)) + 7                                                                                                                                                                         ",
    "4 * 4 * (7 + 2 + 3 * 4 + 2 + (7 + 5 * 6 + 7 * 6 * 4)) * 2 * 4                                                                                                                                         ",
    "7 + (2 + 7 + 5 + 8 * 8 * 8) + 5 + 9 + 2                                                                                                                                                               ",
    "(8 + 9 * 9) + (5 + (9 + 4 + 2) * 8) * 7 * 4 * 4 * 3                                                                                                                                                   ",
    "(3 * 3 * (9 + 7 + 4 + 8 * 8) + 2 + 6) + 2 * 4                                                                                                                                                         ",
    "7 * ((6 + 3 + 2 * 9 + 7) + 5 + 6 + 3 * 4 + 2)                                                                                                                                                         ",
    "7 + (7 + 9 + 6 + 8) * 3 * (2 * 5 + 2 + 3 * 8) * (8 + 4 + (8 + 5) * 4) + 6                                                                                                                             ",
    "6 + (9 + 7 + (9 * 3 * 3 + 7 + 7)) * (2 * 3 * 2 * 2 * 2) * ((7 * 5 * 7 * 2 * 6 * 7) * 5 * 6 + (4 * 7)) * 9 + 8                                                                                         ",
    "(3 * 4 + 7 + 7) + 6 + 9 * 2 + ((2 * 3) * 2 + 7 + (6 * 9 + 5 + 2) + 6) + 2                                                                                                                             ",
    "8 + 5 * 5 * 2 + 9 * 2                                                                                                                                                                                 ",
    "(6 * (7 + 7 * 9 * 9 * 3) + 3) * 5 * (6 + 7 * 7 * (2 + 9 + 2)) + 5 + 4 * 5                                                                                                                             ",
    "4 * 4 + 7 + (7 * 3) + 2                                                                                                                                                                               ",
    "4 + 6 + 2 + (7 * 5 * 5 * (3 * 5 * 3 * 6 * 9 * 2) * 4 * (6 + 7 * 6 + 7)) * 6 * 9                                                                                                                       ",
    "9 * 6                                                                                                                                                                                                 ",
    "((5 + 9 * 6 + 9 * 2) + (2 * 5 + 3 * 6 + 3) + (7 * 7)) + (9 * 8 * 6) * 3 + 2 + (6 + (6 + 6 * 4) + 7) * 5                                                                                               ",
    "(3 + 9 + 7 + 6) + 3 * 9 * 9 + 9                                                                                                                                                                       ",
    "5 * 8 * 2 + 9                                                                                                                                                                                         ",
    "9 * (4 * (7 * 5 * 4) + 6 * 8 + 5) * (7 + (3 + 9) + (5 + 2 * 7 * 4 * 9 + 7) * 4 + 8 + 2) * 3                                                                                                           ",
    "4 + (3 * 8 * 4 + (5 + 8) * 7)                                                                                                                                                                         ",
    "9 * 3 + (5 + 7 + 8) + 2 + (7 + 4 * 6) * (8 + (4 * 2 + 8) * 9 * 8)                                                                                                                                     ",
    "5 * (4 * 3 * 4 * 2) + 8                                                                                                                                                                               ",
    "3 * ((8 + 4) * (2 * 5 + 2) + 4 * 6 * 6 + (6 * 5 * 9 + 3)) + 9 * 2 * 3                                                                                                                                 ",
    "3 * 8 + (8 * 6 + 6 * 9 * 8 * 7)                                                                                                                                                                       ",
    "5 * (5 * 7) * 5 * 8 + 2                                                                                                                                                                               ",
    "((5 * 4 * 5 + 2 * 3) * (3 * 5 * 5 + 2 + 7 * 6)) + 8 + 7 + 4 * 9 + 5                                                                                                                                   ",
    "8 + (5 * 6 + 5 * 6 + 2) + 9 * 4 + 8 * 3                                                                                                                                                               ",
    "8 * 9 + (6 + 3 * 3 + 9 + 4) * 2 + ((5 * 3 + 5 + 7 * 6) + 7) * 4                                                                                                                                       ",
    "7 * 4 * (2 + 9)                                                                                                                                                                                       ",
    "7 + 7                                                                                                                                                                                                 "
}; //*/

