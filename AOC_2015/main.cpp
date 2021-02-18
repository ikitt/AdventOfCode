#include <QCoreApplication>

#include "Day1.h"
#include "Y15Day02.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //DAY 1
    //=====

    fprintf(stdout, "End floor is %i\r\n", Day1::computeFloor());
    fflush(stdout);
    fprintf(stdout, "First basement is %i\r\n", Day1::findFirstBasement());
    fflush(stdout);

    //DAY 2
    //=====
    Y15Day02::computFirstResult();
    Y15Day02::computSecondResult();


    return a.exec();
}
