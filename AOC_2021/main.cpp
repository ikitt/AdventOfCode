#include <QCoreApplication>


#include "Y21Day01.h"
#include "Y21Day02.h"
#include "Y21Day03.h"
#include "Y21Day04.h"
#include "Y21Day05.h"

int main(int argc, char *argv[])
{
    fprintf(stdout, "start main \r\n");
    fflush(stdout);
    QCoreApplication a(argc, argv);
    fprintf(stdout, "end init\r\n");
    fflush(stdout);

    /*
    //DAY 1
    //=====
    Y21Day01::computFirstResult();
    Y21Day01::computSecondResult();


    //DAY 2
    //=====
    Y21Day02::computFirstResult();
    Y21Day02::computSecondResult();


    //DAY 3
    //=====
    Y21Day03::computFirstResult();
    Y21Day03::computSecondResult();

//    */

    //DAY 4
    //=====
//    Y21Day04::computFirstResult();
    Y21Day04::computSecondResult();

        /*

    //DAY 5
    //=====
    Y21Day05::computFirstResult();
    Y21Day05::computSecondResult();

//    */

    return a.exec();
}
