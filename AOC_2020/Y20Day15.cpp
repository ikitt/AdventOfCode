#include "Y20Day15.h"

Y20Day15::Y20Day15()
{

}

int Y20Day15::computFirstResult()
{
    QMap<int /*value*/, int /*last spoken*/> valueHistory;
    int currentTurn;
    int lastSpoken;
    int speaking;
    const int turnLimit = 2020;
    bool initListDone = false;

    for(currentTurn = 1; currentTurn <= turnLimit ; currentTurn++)
    {
        if(!initListDone)
        {
            valueHistory[_input[currentTurn - 1]] = currentTurn;
            lastSpoken = _input[currentTurn - 1];

            if(currentTurn == _input.size())
                initListDone = true;
        }
        else
        {

            if(valueHistory.keys().contains(lastSpoken))
                speaking = (currentTurn - 1) - valueHistory[lastSpoken];
            else
                speaking = 0;
            valueHistory[lastSpoken] = (currentTurn-1);
            lastSpoken = speaking;
        }

        fprintf(stdout, "Spoken at turn %i is %i.\r\n", currentTurn, lastSpoken);
        fflush(stdout);
    }

    return lastSpoken;
}

unsigned long long Y20Day15::computSecondResult()
{
    const unsigned int turnLimit = 30000000;
    std::vector<unsigned int> valHito(turnLimit, 0);
    unsigned int currentTurn = 1;
    unsigned int lastSpoken;
    unsigned int speaking;

    qint64 start = QDateTime::currentSecsSinceEpoch();

    for(; currentTurn <= (unsigned int)_input.size() ; currentTurn++)
    {
        valHito[_input[currentTurn - 1]] = currentTurn;
        lastSpoken = _input[currentTurn - 1];
        fprintf(stdout, "Spoken at turn %i is %i (%llu).\r\n", currentTurn, lastSpoken, (QDateTime::currentSecsSinceEpoch() - start));
        fflush(stdout);
    }

    for( ; currentTurn <= turnLimit ; currentTurn++)
    {
        if(valHito[lastSpoken] != 0)
            speaking = (currentTurn - 1) - valHito[lastSpoken];
        else
            speaking = 0;
        valHito[lastSpoken] = (currentTurn-1);
        lastSpoken = speaking;


        if((currentTurn % 10000) == 0)
        {
            fprintf(stdout, "Spoken at turn %i is %i (%llu).\r\n", currentTurn, lastSpoken, (QDateTime::currentSecsSinceEpoch() - start));
            fflush(stdout);
        }
    }
    return lastSpoken;
}


unsigned long long Y20Day15::computSecondResultBasicAndSlow()
{
    QMap<unsigned int /*value*/, unsigned int /*last spoken*/> valueHistory;
    unsigned int currentTurn;
    unsigned int lastSpoken;
    unsigned int speaking;
    const unsigned int turnLimit = 30000000;
    qint64 start = QDateTime::currentSecsSinceEpoch();
    bool initListDone = false;

    for(currentTurn = 1; currentTurn <= turnLimit ; currentTurn++)
    {
        if(!initListDone)
        {
            valueHistory[_input[currentTurn - 1]] = currentTurn;
            lastSpoken = _input[currentTurn - 1];

            if(currentTurn == (unsigned int)_input.size())
                initListDone = true;
        }
        else
        {
            if(valueHistory.keys().contains(lastSpoken))
                speaking = (currentTurn - 1) - valueHistory[lastSpoken];
            else
                speaking = 0;
            valueHistory[lastSpoken] = (currentTurn-1);
            lastSpoken = speaking;
        }

        if((currentTurn % 10000) == 0)
        {
            fprintf(stdout, "Spoken at turn %i is %i (%llu).\r\n", currentTurn, lastSpoken, (QDateTime::currentSecsSinceEpoch() - start));
            fflush(stdout);
        }
    }

    return lastSpoken;

}


unsigned long long Y20Day15::computSecondResultMessUp()
{
    const unsigned int turnLimit = 30000000;
    std::vector<unsigned int> valHito(turnLimit, 0);
    unsigned int currentTurn = 1;
    unsigned int lastSpoken;
    unsigned int speaking;

    qint64 start = QDateTime::currentSecsSinceEpoch();

    for(; currentTurn <= (unsigned int)_input.size() ; currentTurn++)
    {
        valHito[_input[currentTurn - 1]] = currentTurn;
        lastSpoken = _input[currentTurn - 1];
        fprintf(stdout, "Spoken at turn %i is %i (%llu).\r\n", currentTurn, lastSpoken, (QDateTime::currentSecsSinceEpoch() - start));
        fflush(stdout);
    }

    for( ; currentTurn <= turnLimit ; currentTurn++)
    {
        if(valHito[lastSpoken] != 0)
            speaking = (currentTurn - 1) - valHito[lastSpoken];
        else
            speaking = 0;
        valHito[lastSpoken] = (currentTurn-1);
        lastSpoken = speaking;


        if((currentTurn % 10000) == 0)
        {
            fprintf(stdout, "Spoken at turn %i is %i (%llu).\r\n", currentTurn, lastSpoken, (QDateTime::currentSecsSinceEpoch() - start));
            fflush(stdout);
        }
    }
    return lastSpoken;
}


//Example for 1st part
//const QVector<int> Y20Day15::_input = {1,3,2}; // 2020th number spoken is 1.
//const QVector<int> Y20Day15::_input = {2,1,3}; // 2020th number spoken is 10.
//const QVector<int> Y20Day15::_input = {1,2,3}; // 2020th number spoken is 27.
//const QVector<int> Y20Day15::_input = {2,3,1}; // 2020th number spoken is 78.
//const QVector<int> Y20Day15::_input = {3,2,1}; // 2020th number spoken is 438.
//const QVector<int> Y20Day15::_input = {3,1,2}; // 2020th number spoken is 1836.

const QVector<int> Y20Day15::_input = {0,3,1,6,7,5};
