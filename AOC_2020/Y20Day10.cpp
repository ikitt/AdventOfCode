#include "Y20Day10.h"

Y20Day10::Y20Day10()
{

}


int Y20Day10::computFirstResult()
{
    QVector<int> cpInput(_input);

    std::sort(cpInput.begin(), cpInput.end());
    cpInput.push_back(cpInput[cpInput.size()-1] + 3); //Final joltage is last adapter +3.

    QMap<int, int> output ={};
//    output[0] = 0;
    output[1] = 0;
    output[2] = 0;
    output[3] = 0;

    int lastRatio = 0;
    int difference = 0;

    for(int ratio : cpInput)
    {
        difference = ratio - lastRatio;

        fprintf(stdout, "Get a difference of %i between %i and %i\r\n", difference, lastRatio, ratio);
        fflush(stdout);

        lastRatio = ratio;

        if((difference <1) || (difference>3))
        {

            fprintf(stdout, "Get a difference of %i which is incorret\r\n", difference);
            fflush(stdout);
            return  -1;
        }

        output[difference] = output[difference] + 1;
    }
    fprintf(stdout, "Jolt difference count are\r\n", difference);
    fprintf(stdout, "1: %i\r\n", output[1]);
    fprintf(stdout, "2: %i\r\n", output[2]);
    fprintf(stdout, "3: %i\r\n", output[3]);
    fprintf(stdout, "Diff[1] * Diff[3]: %i\r\n", output[1] * output[3]);

    fflush(stdout);

    return 0;
}

int Y20Day10::computSecondResult()
{
    QVector<int> cpInput(_input);

    std::sort(cpInput.begin(), cpInput.end());
    cpInput.push_back(cpInput[cpInput.size()-1] + 3); //Final joltage is last adapter +3.

    QMap<int, int> output ={};
//    output[0] = 0;
    output[1] = 0;
    output[2] = 0;
    output[3] = 0;

    int lastRatio = 0;
    int difference = 0;
    unsigned long long possibilityCounter = 1;


    QVector<int> nonThreeChain = {0};
    for(int ratio : cpInput)
    {
        difference = ratio - lastRatio;

        if(difference < 3)
        {
            nonThreeChain.push_back(ratio);
        }
        else
        {
            if(nonThreeChain.size() > 1)
            {
                unsigned long long tmp = countPossibility(nonThreeChain);
    //            fprintf(stdout, "Count possibility return %i\r\n", tmp);
    //            fflush(stdout);
                possibilityCounter = (possibilityCounter * tmp);
                fprintf(stdout, "Count possibility is %i (x %i)\r\n", possibilityCounter, tmp);
                fflush(stdout);
            }
            nonThreeChain.clear();
            nonThreeChain.push_back(ratio);
        }

//        fprintf(stdout, "Get a difference of %i between %i and %i\r\n", difference, lastRatio, ratio);
//        fflush(stdout);

        lastRatio = ratio;

        if((difference <1) || (difference>3))
        {

//            fprintf(stdout, "Get a difference of %i which is incorret\r\n", difference);
//            fflush(stdout);
            return  -1;
        }

        output[difference] = output[difference] + 1;
    }
    fprintf(stdout, "Jolt difference count are\r\n", difference);
    fprintf(stdout, "1: %i\r\n", output[1]);
    fprintf(stdout, "2: %i\r\n", output[2]);
    fprintf(stdout, "3: %i\r\n", output[3]);
    fprintf(stdout, "Total count of possibility is: %i\r\n", possibilityCounter);

    fflush(stdout);

    return 0;
}


//First and last item are mandatory (diff == 3 for nonThreeChain[-1] and nonThreeChain[size])
int Y20Day10::countPossibility(const QVector<int> &nonThreeChain, int position)
{
    int ans = 0; //Removing 0

//    for(int idx = 0 ; idx < nonThreeChain.size(); idx ++){

//    }

    if(position < (nonThreeChain.size() -1))
    {
        //Keep current
        ans += countPossibility(nonThreeChain, position+1);
        //Remove current
        QVector<int> copyChain(nonThreeChain);
        copyChain.remove(position);
        ans += countPossibility(copyChain, position);

        return ans;
    }
    else if(position == (nonThreeChain.size() -1))
    {
        bool isOk = true;
        int previousAdapt = nonThreeChain[0];
        for(int idx = 1; idx < nonThreeChain.size(); idx++)
        {
            if((nonThreeChain[idx] - previousAdapt) > 3)
            {
                isOk = false;
                break;
            }
            previousAdapt = nonThreeChain[idx];
        }
        if(isOk)
            ans++;

//        fprintf(stdout, "Got the following chain which is %s:", (isOk ? "OK" : "KO"));
        for(int ratio: nonThreeChain)
        {
//            fprintf(stdout, " %i", ratio);

        }
//        fprintf(stdout, "\r\n");
//        fflush(stdout);

        return ans;
    }
    else
    {
        fprintf(stdout, "Got problem in countPossibility:");
        for(int ratio: nonThreeChain)
        {
            fprintf(stdout, " %i", ratio);
        }
        fprintf(stdout, " with position %i \r\n", position);

        fflush(stdout);

        return -1;
    }

}




//const QVector<int> Y20Day10::_input = {
//    1  ,
//    2  ,
//    3  ,
//    4 ,
//    5 ,
//    8  ,
//    10  ,
//    12 };





const QVector<int> Y20Day10::_input = {
    80  ,
    87  ,
    10  ,
    122 ,
    57  ,
    142 ,
    134 ,
    59  ,
    113 ,
    139 ,
    101 ,
    41  ,
    138 ,
    112 ,
    46  ,
    96  ,
    43  ,
    125 ,
    36  ,
    54  ,
    133 ,
    17  ,
    42  ,
    98  ,
    7   ,
    114 ,
    78  ,
    67  ,
    77  ,
    28  ,
    149 ,
    58  ,
    20  ,
    105 ,
    31  ,
    19  ,
    18  ,
    27  ,
    40  ,
    71  ,
    117 ,
    66  ,
    21  ,
    72  ,
    146 ,
    90  ,
    97  ,
    94  ,
    123 ,
    1   ,
    119 ,
    30  ,
    84  ,
    61  ,
    91  ,
    118 ,
    2   ,
    29  ,
    104 ,
    73  ,
    13  ,
    76  ,
    24  ,
    148 ,
    68  ,
    111 ,
    131 ,
    83  ,
    49  ,
    8   ,
    132 ,
    9   ,
    64  ,
    79  ,
    124 ,
    95  ,
    88  ,
    135 ,
    3   ,
    51  ,
    39  ,
    6   ,
    60  ,
    108 ,
    14  ,
    35  ,
    147 ,
    89  ,
    34  ,
    65  ,
    50  ,
    145 ,
    128
};
// */
