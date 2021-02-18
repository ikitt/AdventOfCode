#include "Y20Day13.h"




quint64 ppcm(int X,int Y)
{
  int A=X;
  int B=Y;
  while (A!=B)
  {
    while (A>B) B=B+Y;
    while (A<B) A=A+X;
  }


  fprintf(stdout, "ppcm between %i and %i is %i.\r\n", X, Y, A);
  fflush(stdout);

  return A;
}


int getFirstValidCoef(int period,int  position,int  refPeriod)
{
    int A= period;
    int B= refPeriod;

    while ((A+position)!=B)
    {
      while ((A+position)>B) B=B+refPeriod;
      while ((A+position)<B) A=A+period;

      if(A > (period*refPeriod))
          throw "no futur";
    }
    return (A/period);
}




Y20Day13::Y20Day13()
{

}

int Y20Day13::computFirstResult()
{
    int earliestTime = _input[0].toInt();

    _firstAvailableSchedule = {};

    QStringList busIds = _input[1].split(",");
    busIds.removeAll("x");

    for(QString bus : busIds)
    {
        int frequency = bus.toInt();

        int departure = closestFollowingTime(earliestTime, frequency);

        _firstAvailableSchedule[frequency] = departure;
    }

    int soonerBusId = _firstAvailableSchedule.keys().first();
    int soonerTime = _firstAvailableSchedule[_firstAvailableSchedule.keys().first()];

    for(int id : _firstAvailableSchedule.keys())
    {
        if(_firstAvailableSchedule[id] < soonerTime)
        {
            soonerBusId = id;
            soonerTime = _firstAvailableSchedule[id];
        }
    }
    int solus = soonerBusId * (soonerTime - earliestTime);
    fprintf(stdout, "Sooner bus is %i and you will ride it at %i (solus is %i).", soonerBusId, soonerTime, solus);
    fflush(stdout);

    return 0;
}


quint64 Y20Day13::closestFollowingTime(const quint64 &ref, const quint64 &period, const quint64 &start, const int &position)
{
    quint64 res = start;

//    while (res < ref) {
//        res += period;
//    }

    if(res < (ref + position))
    {
        res = ref / period;

        res = (res+1) * period;
    }


//    fprintf(stdout, "With ref %i and period %i at a start of %i res is %i.\r\n", ref, period, start, res);
//    fflush(stdout);

    return res;
}

//int Y20Day13::computSecondResult(const quint64 & start, const uint & id)
//{
//    _firstAvailableSchedule = {};
//    _timeSheet = {};

//    QStringList busIds = _input[1].split(",");

//    bool findIt = false;


//    fprintf(stdout, "Init\r\n");
//    fflush(stdout);

//    for(int idx = 0; idx<busIds.size(); idx++)
//    {
//        if(busIds[idx] == "x")
//            continue;
//        else
//        {
//            busSchedule boby;
//            boby.period = busIds[idx].toInt();
//            boby.current = 0;
//            boby.position = idx;
//            _timeSheet.push_back(boby);
//        }
//    }

//    busSchedule& firstBus = _timeSheet[0];

//    firstBus.current = start;
//    quint64 lastFirstCurrent = start;

//    fprintf(stdout, "Start boucle\r\n");
//    fflush(stdout);

//    QTime heyCoucou(QTime::currentTime());

//    while (!findIt) {
//        if(heyCoucou.elapsed() >= 2000)
//        {
//            fprintf(stdout, "Plic (%i): %llu.\r\n", id, firstBus.current);
//            fflush(stdout);
//            heyCoucou = QTime::currentTime();
//        }
//        if(lastFirstCurrent > firstBus.current)
//        {
//            fprintf(stdout, "Got %llu > %llu.\r\n", lastFirstCurrent , firstBus.current);
//            fflush(stdout);
//        }
//        lastFirstCurrent = firstBus.current;



//        findIt = true;
//        firstBus.current += firstBus.period;
//        //        for(busSchedule& bus : _timeSheet)
//        for(int idx = 1; idx < _timeSheet.size(); idx++)
//        {
//            busSchedule& bus = _timeSheet[idx];
//            bus.current = closestFollowingTime(firstBus.current, bus.period, bus.current, bus.position);
//            if(bus.current == (firstBus.current + bus.position))
//            {
//                continue;
//            }
//            else
//            {
//                findIt = false;
//                break;
//            }
//        }
//    }

//    fprintf(stdout, "First timestamp to get all bus ok is %llu.", firstBus.current);
//    fflush(stdout);

//    return 0;
//}


////First Brain version
//int Y20Day13::computSecondResultBrain()
//{
//    _firstAvailableSchedule = {};
//    _timeSheet = {};

//    QStringList busIds = _input[1].split(",");

//    bool findIt = false;


//    fprintf(stdout, "Init\r\n");
//    fflush(stdout);

//    for(int idx = 0; idx<busIds.size(); idx++)
//    {
//        if(busIds[idx] == "x")
//            continue;
//        else
//        {
//            busSchedule boby;
//            boby.period = busIds[idx].toInt();
//            boby.position = idx;
//            boby.current = 0;
//            _timeSheet.push_back(boby);
//        }
//    }

//    busSchedule refBus = _timeSheet[0];

//    for(busSchedule& bus : _timeSheet)
//    {
//        bus.dutyCycle = (ppcm(bus.period, _timeSheet[0].period)) / bus.period;
//        bus.firstValidCoef = getFirstValidCoef(bus.period, bus.position, _timeSheet[0].period);

//        fprintf(stdout, "With period %i got first valid value at %llu and  duty cycle of %i.\r\n", bus.period, bus.firstValidCoef, bus.dutyCycle);
//        fflush(stdout);

////        if(refBus.dutyCycle < bus.dutyCycle)
////            refBus = bus;
//    }

//    refBus.current = + (refBus.firstValidCoef * _timeSheet[0].period) - (refBus.dutyCycle * _timeSheet[0].period);


//    QTime heyCoucou(QTime::currentTime());

//    while (!findIt)
//    {
//        if(heyCoucou.elapsed() >= 2000)
//        {
//            fprintf(stdout, "Plic : %llu.\r\n", _timeSheet[0].current);
//            fflush(stdout);
//            heyCoucou = QTime::currentTime();
//        }

//        refBus.current = refBus.current + (refBus.dutyCycle * _timeSheet[0].period);

//        findIt = true;
//        //        for(busSchedule& bus : _timeSheet)
//        for(int idx = 0; idx < _timeSheet.size(); idx++)
//        {
//            busSchedule& bus = _timeSheet[idx];
//            bus.current = closestFollowingTime((refBus.current-refBus.position), bus.period, bus.current, bus.position);
//            if(bus.current == (_timeSheet[0].current + bus.position))
//            {
//                continue;
//            }
//            else
//            {
//                findIt = false;
//                break;
//            }
//        }
//    }

////    quint64 currentCoef = 1;
////    for(int idx = 1; idx < _timeSheet.size(); idx++)
////    {
////        //TODO cycler de dutyCycle en dutyCycle avec un offset de firstValidCoef entre firstBus et _timeSheet[idx] .... à compléter ^^'
////        //   OU
////        //TODO trouver le ppcm de tout les duty cycle, le résultat est nécessairement inférieur à ce ppcm
////        //      ¿ et après comment on cycle en partant des firstValidCoef ?
////    }


//    fprintf(stdout, "First timestamp to get all bus ok is %llu.", _timeSheet[0].current);
//    fflush(stdout);

//    return 0;
//}


//Second Brain version
int Y20Day13::computSecondResultBrain()
{
    _firstAvailableSchedule = {};
    _timeSheet = {};

    QStringList busIds = _input[1].split(",");

    bool findIt = false;


    fprintf(stdout, "Init\r\n");
    fflush(stdout);

    for(int idx = 0; idx<busIds.size(); idx++)
    {
        if(busIds[idx] == "x")
            continue;
        else
        {
            busSchedule boby;
            boby.period = busIds[idx].toInt();
            boby.position = idx;
            boby.current = 0;
            _timeSheet.push_back(boby);
        }
    }

    busSchedule refBus = _timeSheet[0];

    for(busSchedule& bus : _timeSheet)
    {
        bus.dutyCycle = (ppcm(bus.period, _timeSheet[0].period)) / bus.period;
        bus.firstValidCoef = getFirstValidCoef(bus.period, bus.position, _timeSheet[0].period);

        fprintf(stdout, "With period %i got first valid value at %llu and  duty cycle of %i.\r\n", bus.period, bus.firstValidCoef, bus.dutyCycle);
        fflush(stdout);

        //        if(refBus.dutyCycle < bus.dutyCycle)
        //            refBus = bus;
    }

    refBus.current = + (refBus.firstValidCoef * _timeSheet[0].period) - (refBus.dutyCycle * _timeSheet[0].period);


    QTime heyCoucou(QTime::currentTime());

    while (!findIt)
    {
        if(heyCoucou.elapsed() >= 2000)
        {
            fprintf(stdout, "Plic : %llu.\r\n", _timeSheet[0].current);
            fflush(stdout);
            heyCoucou = QTime::currentTime();
        }

        refBus.current = refBus.current + (refBus.dutyCycle * _timeSheet[0].period);

        findIt = true;
        //        for(busSchedule& bus : _timeSheet)
        for(int idx = 0; idx < _timeSheet.size(); idx++)
        {
            busSchedule& bus = _timeSheet[idx];
            bus.current = closestFollowingTime((refBus.current-refBus.position), bus.period, bus.current, bus.position);
            if(bus.current == (_timeSheet[0].current + bus.position))
            {
                continue;
            }
            else
            {
                findIt = false;
                break;
            }
        }
    }

    //    quint64 currentCoef = 1;
    //    for(int idx = 1; idx < _timeSheet.size(); idx++)
    //    {
    //        //TODO cycler de dutyCycle en dutyCycle avec un offset de firstValidCoef entre firstBus et _timeSheet[idx] .... à compléter ^^'
    //        //   OU
    //        //TODO trouver le ppcm de tout les duty cycle, le résultat est nécessairement inférieur à ce ppcm
    //        //      ¿ et après comment on cycle en partant des firstValidCoef ?
    //    }


    fprintf(stdout, "First timestamp to get all bus ok is %llu.", _timeSheet[0].current);
    fflush(stdout);

    return 0;
}


////Test for Thread
//int Y20Day13::computSecondResultBrutThread(const quint64 & start, const quint64 &stop, const uint & id)
//{
//    const QVector<QString> input = {
//    "1000677",
//    "29,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,41,x,x,x,x,x,x,x,x,x,661,x,x,x,x,x,x,x,x,x,x,x,x,13,17,x,x,x,x,x,x,x,x,23,x,x,x,x,x,x,x,521,x,x,x,x,x,37,x,x,x,x,x,x,x,x,x,x,x,x,19"
//    };

//    QVector<busSchedule> timeSheet = {};

//    QStringList busIds = input[1].split(",");

//    bool findIt = false;


//    fprintf(stdout, "Init\r\n");
//    fflush(stdout);

//    for(int idx = 0; idx<busIds.size(); idx++)
//    {
//        if(busIds[idx] == "x")
//            continue;
//        else
//        {
//            busSchedule boby;
//            boby.period = busIds[idx].toInt();
//            boby.current = 0;
//            boby.position = idx;
//            timeSheet.push_back(boby);
//        }
//    }

//    busSchedule& firstBus = timeSheet[0];

//    firstBus.current = start;
//    quint64 lastFirstCurrent = start;

//    fprintf(stdout, "Start boucle\r\n");
//    fflush(stdout);

//    QTime heyCoucou(QTime::currentTime());

//    while (!findIt && (firstBus.current < stop)) {
//        if(heyCoucou.elapsed() >= 2000)
//        {
//            fprintf(stdout, "Plic (%i): %llu.\r\n", id, firstBus.current);
//            fflush(stdout);
//            heyCoucou = QTime::currentTime();
//        }
//        if(lastFirstCurrent > firstBus.current)
//        {
//            fprintf(stdout, "Got %llu > %llu.\r\n", lastFirstCurrent , firstBus.current);
//            fflush(stdout);
//        }
//        lastFirstCurrent = firstBus.current;



//        findIt = true;
//        firstBus.current += firstBus.period;
////        for(busSchedule& bus : timeSheet)
//        for(int idx = 1; idx < timeSheet.size(); idx++)
//        {
//            busSchedule& bus = timeSheet[idx];
//            bus.current = closestFollowingTime(firstBus.current, bus.period, bus.current, bus.position);
//            if(bus.current == (firstBus.current + bus.position))
//            {
//                continue;
//            }
//            else
//            {
//                findIt = false;
//                break;
//            }
//        }
//    }

//    if(findIt)
//    {
//        fprintf(stdout, "First timestamp to get all bus ok is %llu.\r\n", firstBus.current);
//        fflush(stdout);
//    }
//    else
//    {
//        fprintf(stdout, "(%i) Went from %llu to %llu without finding solution.\r\n", id, start, stop);
//        fflush(stdout);
//    }
//    return 0;
//}



//QMap<int /*id*/,int /*schedule*/> Y20Day13::

QVector<busSchedule> Y20Day13::_timeSheet = {};
QMap<int /*id*/,int /*schedule*/> Y20Day13::_firstAvailableSchedule = {};


const QVector<QString> Y20Day13::_input = {
    "",
//    "17,x,13,19" //3417
//"67,7,59,61"  //754018
//"67,x,7,59,61"   // 779210
//"67,7,x,59,61"   // 1261476
"1789,37,47,1889"  // 1202161486
};


/*
const QVector<QString> Y20Day13::_input = {
"1000677",
"29,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,41,x,x,x,x,x,x,x,x,x,661,x,x,x,x,x,x,x,x,x,x,x,x,13,17,x,x,x,x,x,x,x,x,23,x,x,x,x,x,x,x,521,x,x,x,x,x,37,x,x,x,x,x,x,x,x,x,x,x,x,19"
};
// */
