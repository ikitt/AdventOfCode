#include <QCoreApplication>


#include "Y21Day01.h"
#include "Y21Day02.h"
#include "Y21Day03.h"

int main(int argc, char *argv[])
{
    fprintf(stdout, "start main \r\n");
    fflush(stdout);
    QCoreApplication a(argc, argv);
    fprintf(stdout, "end init\r\n");
    fflush(stdout);

//    /*
    //DAY 1
    //=====
    Y21Day01::computFirstResult();
    Y21Day01::computSecondResult();

//    */

    //DAY 2
    //=====
    Y21Day02::computFirstResult();
    Y21Day02::computSecondResult();


    //DAY 3
    //=====
    Y21Day03::computFirstResult();
    Y21Day03::computSecondResult();

    return a.exec();
}
