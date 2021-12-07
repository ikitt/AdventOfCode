#include "Y21Day06.h"

#include "QStringList"

Y21Day06::Y21Day06()
{

}


void Y21Day06::computFirstResult()
{
    readInput();

    int maxDay = 80;

    for(int day = 1 ; day <= maxDay ; day++)
    {
        unsigned long long int former0 = _population[0];

        for(int internTime = 0 ; internTime < (_population.size() - 1) ; internTime++)
        {
            _population[internTime] = _population[internTime + 1];
        }

        _population[8] = former0;
        _population[6] += former0;
    }

    unsigned long long int totalPop = 0;
    for(int internTime = 0 ; internTime < _population.size() ; internTime++)
    {
        totalPop += _population[internTime];
    }

    printPop();

    fprintf(stdout, "Res for first part is %llu\r\n", totalPop);
    fflush(stdout);
}


void Y21Day06::computSecondResult()
{
    readInput();

    int maxDay = 256;

    for(int day = 1 ; day <= maxDay ; day++)
    {
        unsigned long long int former0 = _population[0];

        for(int internTime = 0 ; internTime < (_population.size() - 1) ; internTime++)
        {
            _population[internTime] = _population[internTime + 1];
        }

        _population[8] = former0;
        _population[6] += former0;
    }

    unsigned long long int totalPop = 0;
    for(int internTime = 0 ; internTime < _population.size() ; internTime++)
    {
        totalPop += _population[internTime];
    }

    printPop();

    fprintf(stdout, "Res for second part is %llu\r\n", totalPop);
    fflush(stdout);
}


void Y21Day06::readInput()
{
    _population = QVector<unsigned long long int>(9, 0);

    QStringList inList = _input.split(",",QString::SkipEmptyParts);
    for(auto strNum : inList)
    {
        _population[strNum.toInt()]++;
    }
}

void Y21Day06::printPop()
{
    fprintf(stdout, "PrintPop\r\n");
    fflush(stdout);
    for(int internTime = 0 ; internTime < _population.size() ; internTime++)
    {
        fprintf(stdout, "Pop[%i] = %llu\r\n",internTime, _population[internTime]);
        fflush(stdout);
    }
}

QVector<unsigned long long int> Y21Day06::_population = {};

//exemple input =>
/*Res first part = 5934
///*Res second part = 26984457539
const QString Y21Day06::_input = {
    "3,4,3,1,2"
};
// */

// /*
// Res first part
// Res second  part
const QString Y21Day06::_input = {
    "1,1,1,1,1,5,1,1,1,5,1,1,3,1,5,1,4,1,5,1,2,5,1,1,1,1,3,1,4,5,1,1,2,1,1,1,2,4,3,2,1,1,2,1,5,4,4,1,4,1,1,1,4,1,3,1,1,1,2,1,1,1,1,1,1,1,5,4,4,2,4,5,2,1,5,3,1,3,3,1,1,5,4,1,1,3,5,1,1,1,4,4,2,4,1,1,4,1,1,2,1,1,1,2,1,5,2,5,1,1,1,4,1,2,1,1,1,2,2,1,3,1,4,4,1,1,3,1,4,1,1,1,2,5,5,1,4,1,4,4,1,4,1,2,4,1,1,4,1,3,4,4,1,1,5,3,1,1,5,1,3,4,2,1,3,1,3,1,1,1,1,1,1,1,1,1,4,5,1,1,1,1,3,1,1,5,1,1,4,1,1,3,1,1,5,2,1,4,4,1,4,1,2,1,1,1,1,2,1,4,1,1,2,5,1,4,4,1,1,1,4,1,1,1,5,3,1,4,1,4,1,1,3,5,3,5,5,5,1,5,1,1,1,1,1,1,1,1,2,3,3,3,3,4,2,1,1,4,5,3,1,1,5,5,1,1,2,1,4,1,3,5,1,1,1,5,2,2,1,4,2,1,1,4,1,3,1,1,1,3,1,5,1,5,1,1,4,1,2,1"
};
// */
