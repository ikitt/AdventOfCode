#include "Y21Day18.h"

Y21Day18::Y21Day18()
{
    QString *testStr = new QString("Olly");

    fprintf(stdout, "(Olly) testStr is %s\r\n", (*testStr).toStdString().c_str());
    fflush(stdout);

    quickAndDirtyPointerTest(testStr);

    fprintf(stdout, "(Olly) testStr is %s\r\n", (*testStr).toStdString().c_str());
    fflush(stdout);

    *testStr  = "boby";

    fprintf(stdout, "(boby) testStr is %s\r\n", (*testStr).toStdString().c_str());
    fflush(stdout);

    bisQuickAndDirtyPointerTest(testStr);

    fprintf(stdout, "(Tony) testStr is %s\r\n", (*testStr).toStdString().c_str());
    fflush(stdout);
}


void Y21Day18::quickAndDirtyPointerTest(QString * pstr){
    pstr = new QString("Teddy");
}
void Y21Day18::bisQuickAndDirtyPointerTest(QString * pstr){
    *pstr = QString("Tony");
}


void Y21Day18::computFirstResult()
{
//    fprintf(stdout, "Test for first part\r\n");
//    fflush(stdout);


//    fprintf(stdout, "Explode pair:\r\n[[[[[9,8],1],2],3],4]\r\n");
//    fflush(stdout);
//    QString myPair = "[[[[[9,8],1],2],3],4]";
//    explode(myPair);
//    fprintf(stdout, "Which give:\r\n%s\r\n", myPair.toStdString().c_str());
//    fflush(stdout);


//    fprintf(stdout, "Explode pair:\r\n[7,[6,[5,[4,[3,2]]]]]\r\n");
//    fflush(stdout);
//    myPair = "[7,[6,[5,[4,[3,2]]]]]";
//    explode(myPair);
//    fprintf(stdout, "Which give:\r\n%s\r\n", myPair.toStdString().c_str());
//    fflush(stdout);


//    fprintf(stdout, "Explode pair:\r\n[[6,[5,[4,[3,2]]]],1]\r\n");
//    fflush(stdout);
//    myPair = "[[6,[5,[4,[3,2]]]],1]";
//    explode(myPair);
//    fprintf(stdout, "Which give:\r\n%s\r\n", myPair.toStdString().c_str());
//    fflush(stdout);


//    fprintf(stdout, "Split pair:\r\n[[[[0,7],4],[15,[0,13]]],[1,1]]\r\n");
//    fflush(stdout);
//    myPair = "[[[[0,7],4],[15,[0,13]]],[1,1]]";
//    split(myPair);
//    fprintf(stdout, "Which give:\r\n%s\r\n", myPair.toStdString().c_str());
//    fflush(stdout);


//    fprintf(stdout, "Split pair:\r\n[[[[0,7],4],[[7,8],[0,13]]],[1,1]]\r\n");
//    fflush(stdout);
//    myPair = "[[[[0,7],4],[[7,8],[0,13]]],[1,1]]";
//    split(myPair);
//    fprintf(stdout, "Which give:\r\n%s\r\n", myPair.toStdString().c_str());
//    fflush(stdout);

    QString pair = _input[0].simplified();
    for(int idx = 1 ; idx < _input.size() ; idx++)
    {
        pair = addPair(pair, _input[idx].simplified());
        reducePair(pair);
        fprintf(stdout, "Pair after add and reduce is %s\r\n", pair.toStdString().c_str());
        fflush(stdout);
    }

    unsigned long long int res = getMagnitude(pair);



    fprintf(stdout, "Res for first part %llu\r\n", res);
    fflush(stdout);
}


void Y21Day18::computSecondResult()
{
    unsigned long long int max = 0;
    unsigned long long int current = 0;
    for(int idxX = 0 ; idxX < _input.size() ; idxX++) {
        fprintf(stdout, "Start idxX %i/%i\r\n", idxX, _input.size());
        fflush(stdout);
        for(int idxY = 0 ; idxY < _input.size() ; idxY++) {
            if(idxX == idxY)
                continue;
            QString pair = addPair(_input[idxX], _input[idxY]);
            reducePair(pair);
            current  = getMagnitude(pair);
            max = std::max(max, current);
        }
    }
    fprintf(stdout, "Res for second part %llu\r\n", max);
    fflush(stdout);
}


QString Y21Day18::addPair(QString left, QString right)
{
    return QString("["+left+","+right+"]");
}

void Y21Day18::reducePair(QString &pair)
{
    bool wasReduced = false;
    do
    {
        wasReduced = false;
        if(explode(pair))
        {
            wasReduced = true;
            continue;
        }
        if(split(pair))
        {
            wasReduced = true;
            continue;
        }
    }while(wasReduced);
}


//Return wheter pair explode or not
bool Y21Day18::explodev0(QString &pair, int depth)
{
    bool res = false;
    if(!isPair(pair)) {
        res = false; return res;
    }

    QPair<QString, QString> splitPair = getLeftRight(pair);
    bool leftIsPair;
    if(isPair(splitPair.first)){
        leftIsPair = true;
    }
    else if(isPair(splitPair.second)){
        leftIsPair = false;
    }
    else{
        res = false; return res;
    }

    QString toSplit = (leftIsPair ? splitPair.first : splitPair.second);
    if(depth == 3)
    {
//        fprintf(stdout, "into explosion");

        res = true;
        QPair<QString, QString> explodingPair = getLeftRight(toSplit);
        QString left = ""; QString right = "";
        left = (leftIsPair ? "0" : QString::number(explodingPair.first.toInt() + splitPair.first.toInt()));
        right = ((!leftIsPair) ? "0" : QString::number(explodingPair.second.toInt() + splitPair.second.toInt()));
//        left = (leftIsPair ? "0" : QString::number(explodingPair.second.toInt() + splitPair.second.toInt()));
//        right = ((!leftIsPair) ? "0" : QString::number(explodingPair.first.toInt() + splitPair.first.toInt()));

//        fprintf(stdout, " which give left %s and right %s from exploding pair %s (leftIsPair %i)\r\n", left.toStdString().c_str(), right.toStdString().c_str(), makePair(explodingPair.first, explodingPair.second).toStdString().c_str(), leftIsPair);
//        fflush(stdout);

//        fprintf(stdout, "Pair was %s", pair.toStdString().c_str());
//        fflush(stdout);
        pair = makePair(left, right);
//        fprintf(stdout, "and become %s\r\n", pair.toStdString().c_str());
//        fflush(stdout);
    }
    else{
        if(leftIsPair)
        {
            res = explodev0(splitPair.first, depth+1);
        }

        if(!res && isPair(splitPair.second))
        {
            res = explodev0(splitPair.second, depth+1);
        }

        pair = makePair(splitPair.first, splitPair.second);;
        if(res)
        {
//            fprintf(stdout, "New pair is  %s\r\n", pair.toStdString().c_str());
//            fflush(stdout);
        }
    }

    return res;
}

bool Y21Day18::explode(QString &pair)
{

    int openedBracket = 0;
    int startIdxExp = 0;
    int endIdxExp = 0;
    QString left = "";
    QString right = "";
    bool explosion = false;
    bool inLeft = true;

    for(int idx = 0 ; idx < pair.size() ; idx++)
    {
        if(pair[idx] == "["){
            openedBracket++;
            if(openedBracket == 5){
                explosion = true;
                startIdxExp = idx;
            }
            continue;
        }
        else if(pair[idx] == ","){
            if(explosion){
                inLeft = false;
            }
            continue;
        }
        else if(pair[idx] == "]"){
            openedBracket--;
            if(explosion){
                endIdxExp = idx;
                break;
            }
        }
        else if(openedBracket == 5)
        {
            inLeft ? left.push_back(pair[idx]) : right.push_back(pair[idx]);
        }
    }

    if(explosion){
//        fprintf(stdout, "Pair before propagate %s:\r\n", pair.toStdString().c_str());
//        fflush(stdout);
        propagateRightFrom(pair, right.toInt(), endIdxExp);
//        fprintf(stdout, "Pair after propagate right %s:\r\n", pair.toStdString().c_str());
//        fflush(stdout);
        pair.replace(startIdxExp, endIdxExp - startIdxExp + 1, "0");
//        fprintf(stdout, "Pair after mid replace %s:\r\n", pair.toStdString().c_str());
//        fflush(stdout);
        propagateLeftFrom(pair, left.toInt(), startIdxExp-1);
//        fprintf(stdout, "Pair after propagate left %s:\r\n", pair.toStdString().c_str());
//        fflush(stdout);
    }


    return explosion;
}


void Y21Day18::propagateRightFrom(QString &pair, int toProp, int from)
{
    bool inInt = false;
    QString toReplace = "";
    int startIntIdx = 0;
    for(int idx = from ; idx<pair.length() ; idx++){
        if(inInt){
            if(pair[idx].isDigit()){
                toReplace.push_back(pair[idx]);
                continue;
            }
            else{
                break;
            }
        }
        else{
            if(pair[idx].isDigit()){
                inInt = true;
                startIntIdx = idx;
                toReplace.push_back(pair[idx]);
            }
            else{
                continue;
            }
        }
    }
    if(inInt)
        pair.replace(startIntIdx, toReplace.size(), QString::number(toReplace.toInt() + toProp));
}


void Y21Day18::propagateLeftFrom(QString &pair, int toProp, int from)
{
    bool inInt = false;
    QString toReplace = "";
    int startIntIdx = 0;
    for(int idx = from ; idx>= 0 ; idx--){
        if(inInt){
            if(pair[idx].isDigit()){
                toReplace.push_front(pair[idx]);
                startIntIdx = idx;
                continue;
            }
            else{
                break;
            }
        }
        else{
            if(pair[idx].isDigit()){
                inInt = true;
                startIntIdx = idx;
                toReplace.push_front(pair[idx]);
            }
            else{
                continue;
            }
        }
    }
    if(inInt)
        pair.replace(startIntIdx, toReplace.size(), QString::number(toReplace.toInt() + toProp));
}

bool Y21Day18::split(QString &pair)
{
    bool res = false;
    QPair<QString, QString> splitPair = getLeftRight(pair);

//    QString boby = splitPair.first;
//    QString billy = splitPair.first;
//    QString jonhy = splitPair.first;

    QVector<QString*> sides;

    sides.push_back(&splitPair.first);
    sides.push_back(&splitPair.second);

    for(QString *side : sides)
    {
        if(isPair(*side))
        {
            res = split(*side);
            if(res)
            {
//                fprintf(stdout, "After split is true %s (first %s; second %s)\r\n", side->toStdString().c_str(),splitPair.first.toStdString().c_str(),splitPair.second.toStdString().c_str());
//                fflush(stdout);
                pair = makePair(splitPair.first, splitPair.second);
                return res;
            }
        }
        else if(side->toInt()>9)
        {

//            fprintf(stdout, "Side before split %s (first %s; second %s)\r\n", side->toStdString().c_str(),splitPair.first.toStdString().c_str(),splitPair.second.toStdString().c_str());
//            fflush(stdout);
            *side = getPairFromSplit(*side);
            pair = makePair(splitPair.first, splitPair.second);
//            fprintf(stdout, "Side after split %s (first %s; second %s)\r\n", side->toStdString().c_str(),splitPair.first.toStdString().c_str(),splitPair.second.toStdString().c_str());
//            fflush(stdout);
            res = true; return res;
        }
    }
    return res;
}

unsigned long long Y21Day18::getMagnitude(const QString &pair)
{
    if(!isPair(pair)){
        return pair.toInt();
    }
    QPair<QString, QString> splitPair = getLeftRight(pair);
    return (3*getMagnitude(splitPair.first) + 2*getMagnitude(splitPair.second));

}

QPair<QString, QString> Y21Day18::getLeftRight(const QString &pair)
{
    QString left = "";
    QString right =  "";
    bool inLeft = true;
    int openedBracket = 0;
    for(QChar schar : pair)
    {
        if(openedBracket == 0){
            openedBracket++; //first bracket open
            continue;
        }
        else if(schar == "," && openedBracket == 1)
        {
            inLeft = false;
            continue;
        }
        else if(schar == "["){
            openedBracket++;
        }
        else if(schar == "]"){
            openedBracket--;
            if(openedBracket == 0){
                continue; //escape from last bracket
            }
        }

        inLeft ? (left += schar) : (right += schar);
    }
    return QPair<QString, QString>{left,right};
}

bool Y21Day18::isPair(const QString &str){ return str[0] == "[";}

QString Y21Day18::makePair(const QString &left, const QString &right){ return QString("[" + left + "," + right + "]");}

QString Y21Day18::getPairFromSplit(const QString &highIntStr)
{
    int highInt = highIntStr.toInt();
    int left = highInt / 2;
    int right = (highInt / 2) + highInt%2;

    return makePair(QString::number(left), QString::number(right));
}


//exemple input => 3488
/*Res first part =
///*Res second part =
const QVector<QString> Y21Day18::_input = {
    "[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]             ",
    "[7,[[[3,7],[4,3]],[[6,3],[8,8]]]]                     ",
    "[[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]             ",
    "[[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]] ",
    "[7,[5,[[3,8],[1,4]]]]                                 ",
    "[[2,[2,2]],[8,[8,1]]]                                 ",
    "[2,9]                                                 ",
    "[1,[[[9,3],9],[[9,0],[0,7]]]]                         ",
    "[[[5,[7,4]],7],1]                                     ",
    "[[[[4,2],2],6],[8,7]]                                 "
};
// */




//exemple input => 4140
/*Res first part =
///*Res second part =
const QVector<QString> Y21Day18::_input = {
    "[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]",
    "[[[5,[2,8]],4],[5,[[9,9],0]]]                    ",
    "[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]                ",
    "[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]                ",
    "[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]            ",
    "[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]            ",
    "[[[[5,4],[7,7]],8],[[8,3],8]]                    ",
    "[[9,3],[[9,9],[6,[4,9]]]]                        ",
    "[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]            ",
    "[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]        "
};
//*/

// /*
// Res first part
// Res second  part
const QVector<QString> Y21Day18::_input = {
    "[[[[7,2],[0,2]],9],[[[7,8],6],[0,[2,3]]]]                                             ",
    "[[[0,9],3],1]                                                                         ",
    "[[[[0,5],6],[[0,6],[7,8]]],[[[2,2],[1,5]],[9,5]]]                                     ",
    "[[2,1],[[3,1],[[3,2],9]]]                                                             ",
    "[[[[9,3],[7,5]],[5,9]],[[0,[0,4]],2]]                                                 ",
    "[[[9,9],4],[8,[[4,9],7]]]                                                             ",
    "[[[1,9],[[8,3],[6,1]]],[5,1]]                                                         ",
    "[[[[8,6],[1,3]],[3,[1,1]]],[[[6,4],[0,4]],[[0,0],3]]]                                 ",
    "[[[[6,4],[3,3]],[7,5]],[[6,5],[0,4]]]                                                 ",
    "[[[[6,4],[2,3]],5],[9,[[4,4],[7,7]]]]                                                 ",
    "[[1,[[7,9],1]],[[[8,2],5],[[7,2],8]]]                                                 ",
    "[[[2,[7,2]],[5,3]],[1,5]]                                                             ",
    "[[[[2,2],[1,5]],[[1,6],[0,5]]],[6,[9,[9,9]]]]                                         ",
    "[[7,2],[[3,8],[5,[6,7]]]]                                                             ",
    "[[[6,5],[[8,0],1]],[2,[6,0]]]                                                         ",
    "[[[8,7],6],[[[7,2],[7,0]],3]]                                                         ",
    "[[[[9,1],[0,1]],[0,4]],[8,0]]                                                         ",
    "[[[8,2],[8,[2,7]]],[[2,[2,6]],[2,[1,2]]]]                                             ",
    "[[[1,7],[[0,0],3]],[[3,[3,6]],[6,3]]]                                                 ",
    "[[[[5,9],[1,2]],[0,0]],[[8,8],9]]                                                     ",
    "[[[1,2],[4,2]],[3,4]]                                                                 ",
    "[[[9,[0,0]],[[3,5],7]],[[[8,0],[2,1]],[3,[1,5]]]]                                     ",
    "[[[[9,2],[7,1]],[[0,4],5]],[9,2]]                                                     ",
    "[[3,[6,1]],2]                                                                         ",
    "[[[0,[0,6]],[4,[5,9]]],[[5,9],1]]                                                     ",
    "[[[9,[8,3]],7],[[0,7],[[8,0],[9,2]]]]                                                 ",
    "[[[[0,7],7],[[1,8],[4,4]]],[[0,[6,4]],[[4,9],4]]]                                     ",
    "[[[[3,3],3],7],4]                                                                     ",
    "[[4,[[5,6],[8,7]]],[[[7,5],2],[2,4]]]                                                 ",
    "[[[[3,8],[3,7]],2],[[[4,4],[9,7]],4]]                                                 ",
    "[[[9,[2,9]],0],[7,[[3,2],[3,2]]]]                                                     ",
    "[[[7,[6,6]],[[6,0],1]],9]                                                             ",
    "[[3,4],[[5,[9,5]],[[2,6],2]]]                                                         ",
    "[[[[7,4],[6,8]],[1,[8,7]]],[[[2,6],[1,4]],[8,7]]]                                     ",
    "[[3,[[0,8],3]],[[1,8],9]]                                                             ",
    "[[3,[5,[0,7]]],[[[2,9],[9,3]],[0,[8,8]]]]                                             ",
    "[[[[1,7],5],[[4,0],[7,4]]],8]                                                         ",
    "[[[[3,4],3],4],0]                                                                     ",
    "[[[[1,3],7],[4,[8,0]]],[[[5,9],[4,8]],[8,[7,8]]]]                                     ",
    "[[[9,1],[[7,2],7]],[[3,0],9]]                                                         ",
    "[[[[6,7],2],1],[[[1,1],6],[9,[3,4]]]]                                                 ",
    "[[[3,8],[4,0]],[[6,[1,0]],[8,[8,3]]]]                                                 ",
    "[[[9,[4,1]],8],2]                                                                     ",
    "[[[4,3],[[7,8],5]],[[[0,2],[0,5]],[[1,2],2]]]                                         ",
    "[[2,7],[[5,[8,5]],[[3,5],[9,9]]]]                                                     ",
    "[6,[[[2,6],1],[[2,4],9]]]                                                             ",
    "[[[[8,0],[1,2]],[[1,6],0]],[[0,4],[4,6]]]                                             ",
    "[[[[7,0],6],[8,1]],[6,3]]                                                             ",
    "[[[8,4],[[7,7],[2,4]]],[[7,8],[4,5]]]                                                 ",
    "[[[4,[5,6]],[[3,4],0]],4]                                                             ",
    "[[0,6],[[6,1],[8,[9,7]]]]                                                             ",
    "[[4,[0,6]],[5,[[3,3],[8,0]]]]                                                         ",
    "[7,[[[8,4],4],[6,7]]]                                                                 ",
    "[[[[7,0],5],[1,[4,4]]],[[9,[0,9]],[[5,1],9]]]                                         ",
    "[[[[4,3],[9,1]],2],[0,[[8,8],[1,3]]]]                                                 ",
    "[[[7,0],[0,[2,8]]],[[0,5],[[2,9],5]]]                                                 ",
    "[[[8,8],[2,[0,2]]],[[4,5],9]]                                                         ",
    "[[3,9],5]                                                                             ",
    "[[[[8,6],3],[[5,1],[0,5]]],[3,1]]                                                     ",
    "[[[7,[1,8]],[3,4]],[4,[[7,9],5]]]                                                     ",
    "[[[[4,5],[4,3]],[[6,5],[6,9]]],[[3,[7,5]],[8,[2,9]]]]                                 ",
    "[[5,0],[[[2,9],1],[[0,6],6]]]                                                         ",
    "[[4,[8,[3,0]]],[[[9,6],[1,9]],[[1,6],[8,0]]]]                                         ",
    "[[[[8,7],[5,9]],[[2,1],[3,4]]],[5,9]]                                                 ",
    "[[[3,3],[2,8]],[[[1,2],9],[3,2]]]                                                     ",
    "[[[[0,1],5],[[0,6],[9,3]]],[5,[[5,8],5]]]                                             ",
    "[[[5,6],[4,5]],[[7,[2,7]],[[3,1],[0,4]]]]                                             ",
    "[7,[[6,2],[[7,3],6]]]                                                                 ",
    "[[[5,3],[5,7]],6]                                                                     ",
    "[1,[[[6,4],[8,1]],[5,[7,5]]]]                                                         ",
    "[[[3,6],[[7,5],7]],[[4,[4,6]],[6,4]]]                                                 ",
    "[[[6,3],4],5]                                                                         ",
    "[[[0,9],[9,[0,1]]],[0,[4,9]]]                                                         ",
    "[[[1,0],0],[[1,4],[9,6]]]                                                             ",
    "[[[1,[8,0]],[[9,4],[2,0]]],[4,[[6,2],3]]]                                             ",
    "[[[[6,0],[5,1]],2],[[[9,6],[5,1]],7]]                                                 ",
    "[[[9,[3,1]],[8,1]],[[6,[0,9]],[[7,1],4]]]                                             ",
    "[[[9,2],[4,[5,3]]],[[[7,1],[2,0]],[3,[2,2]]]]                                         ",
    "[[[3,[7,0]],1],[6,[[9,6],[4,4]]]]                                                     ",
    "[[2,9],[6,[7,3]]]                                                                     ",
    "[1,[[7,[1,9]],5]]                                                                     ",
    "[[[5,3],[[1,5],[7,8]]],[[[5,3],[6,8]],[1,[5,0]]]]                                     ",
    "[[[1,[7,4]],[3,8]],[1,[4,[6,3]]]]                                                     ",
    "[[[3,[8,9]],7],[[[3,4],3],[6,[3,6]]]]                                                 ",
    "[[[3,[1,7]],[3,[1,8]]],[[[6,4],[6,4]],[[8,6],[3,4]]]]                                 ",
    "[[4,6],[[6,[8,4]],6]]                                                                 ",
    "[[[2,[7,7]],[[1,0],[6,6]]],[[[8,0],[1,6]],[[0,5],9]]]                                 ",
    "[[[[3,0],[2,1]],[4,7]],3]                                                             ",
    "[[[[1,7],2],[[8,3],[8,9]]],[[0,4],[[6,4],2]]]                                         ",
    "[[[[3,6],9],[0,[6,0]]],[7,8]]                                                         ",
    "[3,[[7,8],9]]                                                                         ",
    "[[1,[[7,9],[1,2]]],[2,9]]                                                             ",
    "[[[3,[3,0]],4],[[1,[5,9]],[[9,6],5]]]                                                 ",
    "[[1,[3,4]],[[8,[2,3]],3]]                                                             ",
    "[[[8,0],8],[[[1,9],3],[[0,1],[8,6]]]]                                                 ",
    "[[[[4,1],[3,7]],[[6,2],[5,8]]],[[[4,0],[2,4]],[4,7]]]                                 ",
    "[[[[9,0],[5,8]],3],2]                                                                 ",
    "[7,[[[1,0],[9,7]],[[8,3],0]]]                                                         ",
    "[[[0,1],[4,[4,5]]],[9,[[3,6],[6,8]]]]                                                 ",
    "[8,[[7,[4,7]],[[0,5],3]]]                                                             "
};
// */
