#include <QCoreApplication>
#include <QThreadPool>
#include <QThread>
#include <QtConcurrent>

#include "Y20Day1.h"
#include "Y20Day02.h"
#include "Y20Day03.h"
#include "Y20Day04.h"
#include "Y20Day05.h"
#include "Y20Day06.h"
#include "Y20Day07.h"
#include "Y20Day08.h"
#include "Y20Day09.h"
#include "Y20Day10.h"
#include "Y20Day11.h"
#include "Y20Day12.h"
#include "Y20Day13.h"
//#include "Y20Day14.h"
//#include "Y20Day15.h"
//#include "Y20Day16.h"
//#include "Y20Day17.h"
//#include "Y20Day18.h"
//#include "Y20Day19.h"
//#include "Y20Day20.h"
//#include "Y20Day21.h"
//#include "Y20Day22.h"
//#include "Y20Day23.h"
//#include "Y20Day24.h"
//#include "Y20Day25.h"

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

    QDateTime start = QDateTime::currentDateTime();
    Y20Day1::answerPuzzle1();
    QDateTime end = QDateTime::currentDateTime();
    fprintf(stdout, "Solving this take %i\r\n", start.msecsTo(end));
    fflush(stdout);

    start = QDateTime::currentDateTime();
    Y20Day1::answerPuzzle2();
    end = QDateTime::currentDateTime();
    fprintf(stdout, "Solving this take %i\r\n", start.msecsTo(end));
    fflush(stdout);

    start = QDateTime::currentDateTime();
    Y20Day1::answerPuzzle2();
    end = QDateTime::currentDateTime();
    fprintf(stdout, "Solving this take %i\r\n", start.msecsTo(end));
    fflush(stdout);


    //DAY 2
    //=====
    Y20Day02::computFirstResult();
    Y20Day02::computSecondResult();


    //DAY 3
    //=====
    Y20Day03::computFirstResult();
    Y20Day03::computSecondResult();


    //DAY 4
    //=====
    Y20Day04::computFirstResult();
    Y20Day04::computSecondResult();


    //DAY 5
    //=====
    Y20Day05::computFirstResult();
    Y20Day05::computSecondResult();

    //DAY 6
    //=====
    Y20Day06::computFirstResult();
    Y20Day06::computSecondResult();


    //DAY 7
    //=====
    fprintf(stdout, "start day 07\r\n");
    fflush(stdout);
    Y20Day07::computFirstResult();
    Y20Day07::computSecondResult();


    //DAY 8
    //=====
    fprintf(stdout, "start day 08\r\n");
    fflush(stdout);
    Y20Day08::computFirstResult();
    Y20Day08::computSecondResult();


    //DAY 9
    //=====
    fprintf(stdout, "start day 09\r\n");
    fflush(stdout);
    Y20Day09::computFirstResult();
    Y20Day09::computSecondResult();


    //DAY 10
    //======
    fprintf(stdout, "start day 10\r\n");
    fflush(stdout);
    Y20Day10::computFirstResult();
    Y20Day10::computSecondResult();



    //DAY 11
    //======
    fprintf(stdout, "start day 11\r\n");
    fflush(stdout);
    Y20Day11::computFirstResult();
    Y20Day11::computSecondResult();


    //DAY 12
    //======
    fprintf(stdout, "start day 12\r\n");
    fflush(stdout);
    Y20Day12::computFirstResult();
    Y20Day12::computSecondResult();
*/



    //DAY 13
    //======
    fprintf(stdout, "start day 13\r\n");
    fflush(stdout);
//    Y20Day13::computSecondResult();
    Y20Day13::computSecondResultBrain();

//    QThreadPool threadPool;
//    threadPool.setMaxThreadCount(10);
//    for(int idx = 0 ; idx < 10 ; idx++)
//    {
//        QtConcurrent::run(&threadPool, [=]{Y20Day13::computSecondResultBrutThread(107857046991262 + (idx * 500000000000),107857046991262 + ((idx+1) * 500000000000-1), idx);});
//    }


//        void logEvent(const QString &event) {
//            });
//        }

//    private:
//        void logEventCore(const QString &event) {
//            logStream << event;
//        }




//    Y20Day13::computSecondResult(102317032431363, 0);
    /*



    //DAY 14
    //======
    fprintf(stdout, "start day 14\r\n");
    fflush(stdout);
    Y20Day14::computFirstResult();
    Y20Day14::computSecondResult();



    //DAY 15
    //======
    fprintf(stdout, "start day 15\r\n");
    fflush(stdout);
    Y20Day15::computFirstResult();
    Y20Day15::computSecondResult();



    //DAY 16
    //======
    fprintf(stdout, "start day 16\r\n");
    fflush(stdout);
    Y20Day16::computFirstResult();
    Y20Day16::computSecondResult();



    //DAY 17
    //======
    fprintf(stdout, "start day 17\r\n");
    fflush(stdout);
    Y20Day17::computFirstResult();
    Y20Day17::computSecondResult();



    //DAY 18
    //======
    fprintf(stdout, "start day 18\r\n");
    fflush(stdout);
    Y20Day18::computFirstResult();
    Y20Day18::computSecondResult();



    //DAY 19
    //======
    fprintf(stdout, "start day 19\r\n");
    fflush(stdout);
    Y20Day19::computFirstResult();
    Y20Day19::computSecondResult();



    //DAY 20
    //======
    fprintf(stdout, "start day 20\r\n");
    fflush(stdout);
    Y20Day20::computFirstResult();
    Y20Day20::computSecondResult();



    //DAY 21
    //======
    fprintf(stdout, "start day 21\r\n");
    fflush(stdout);
    Y20Day21::computFirstResult();
    Y20Day21::computSecondResult();



    //DAY 22
    //======
    fprintf(stdout, "start day 22\r\n");
    fflush(stdout);
    Y20Day22::computFirstResult();
    Y20Day22::computSecondResult();



    //DAY 23
    //======
    fprintf(stdout, "start day 23\r\n");
    fflush(stdout);
    Y20Day23::computFirstResult();
    Y20Day23::computSecondResult();



    //DAY 24
    //======
    fprintf(stdout, "start day 24\r\n");
    fflush(stdout);
    Y20Day24::computFirstResult();
    Y20Day24::computSecondResult();



    //DAY 25
    //======
    fprintf(stdout, "start day 25\r\n");
    fflush(stdout);
    Y20Day25::computFirstResult();
    Y20Day25::computSecondResult();

    */


    return a.exec();
}
