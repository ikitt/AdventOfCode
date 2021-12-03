#include "Y21Day01.h"

Y21Day01::Y21Day01()
{

}


void Y21Day01::computFirstResult()
{
    int horizontal = 0;
    int depth = 0;

    for(QString instruction : _input)
    {
        instruction = instruction.simplified();

        QStringList spltInst = instruction.split(" ");
        int value = spltInst[1].toInt();
        QString dir = spltInst[0];

        if("forward" == dir)
        {
            horizontal += value;
        }
        else if("up" == dir)
        {
            depth -= value;
        }
        else if("down" == dir)
        {
            depth += value;
        }
        else
        {
            throw std::domain_error("Not a valid direction");
        }
    }
    fprintf(stdout, "Final posistion is horizontal: %i; depth: %i; res = %i\r\n", horizontal, depth, horizontal*depth);
    fflush(stdout);
}

void Y21Day01::computSecondResult()
{
    int horizontal = 0;
    int depth = 0;
    int aim = 0;

    for(QString instruction : _input)
    {
        instruction = instruction.simplified();

        QStringList spltInst = instruction.split(" ");
        int value = spltInst[1].toInt();
        QString dir = spltInst[0];

        if("forward" == dir)
        {
            horizontal += value;
            depth += (aim * value);
        }
        else if("up" == dir)
        {
            aim -= value;
        }
        else if("down" == dir)
        {
            aim += value;
        }
        else
        {
            throw std::domain_error("Not a valid direction");
        }
    }
    fprintf(stdout, "Final posistion is horizontal: %i; depth: %i; res = %i\r\n", horizontal, depth, horizontal*depth);
    fflush(stdout);
}


//exemple input => h15 d10 => 150 for first part and 5 for second part
/*
const QVector<QString> Y21Day01::_input = {
    "forward 5",
    "down 5   ",
    "forward 8",
    "up 3     ",
    "down 8   ",
    "forward 2"
};
// */

// /*
// first part give horizontal: 2018; depth: 820; res = 1654760
// second part give result horizontal: 2018; depth: 969300; res = 1956047400
const QVector<QString> Y21Day01::_input = {
    "forward 8      ",
    "forward 1      ",
    "down 9         ",
    "down 8         ",
    "down 5         ",
    "forward 4      ",
    "up 9           ",
    "forward 7      ",
    "forward 2      ",
    "down 6         ",
    "forward 7      ",
    "forward 5      ",
    "forward 8      ",
    "down 7         ",
    "up 8           ",
    "forward 1      ",
    "forward 6      ",
    "down 8         ",
    "up 3           ",
    "forward 3      ",
    "down 3         ",
    "down 7         ",
    "forward 5      ",
    "down 1         ",
    "down 9         ",
    "forward 4      ",
    "up 7           ",
    "forward 9      ",
    "forward 1      ",
    "down 6         ",
    "down 5         ",
    "down 4         ",
    "forward 9      ",
    "forward 1      ",
    "forward 4      ",
    "up 3           ",
    "up 6           ",
    "forward 1      ",
    "forward 9      ",
    "forward 4      ",
    "down 1         ",
    "down 9         ",
    "forward 7      ",
    "forward 8      ",
    "down 8         ",
    "down 8         ",
    "down 4         ",
    "down 5         ",
    "up 3           ",
    "forward 4      ",
    "down 1         ",
    "forward 2      ",
    "forward 1      ",
    "forward 8      ",
    "up 2           ",
    "forward 5      ",
    "forward 4      ",
    "forward 5      ",
    "forward 8      ",
    "down 4         ",
    "down 5         ",
    "down 8         ",
    "down 7         ",
    "down 6         ",
    "forward 4      ",
    "up 8           ",
    "forward 6      ",
    "down 2         ",
    "down 7         ",
    "up 7           ",
    "down 2         ",
    "down 6         ",
    "forward 5      ",
    "forward 2      ",
    "forward 8      ",
    "down 5         ",
    "down 6         ",
    "down 6         ",
    "up 7           ",
    "down 7         ",
    "forward 8      ",
    "down 7         ",
    "down 7         ",
    "down 2         ",
    "down 2         ",
    "forward 3      ",
    "up 5           ",
    "down 3         ",
    "up 3           ",
    "down 4         ",
    "up 9           ",
    "down 1         ",
    "up 1           ",
    "forward 3      ",
    "up 3           ",
    "forward 9      ",
    "up 6           ",
    "down 3         ",
    "down 6         ",
    "forward 4      ",
    "forward 5      ",
    "forward 8      ",
    "down 6         ",
    "down 9         ",
    "down 4         ",
    "down 5         ",
    "forward 7      ",
    "down 3         ",
    "forward 8      ",
    "forward 3      ",
    "up 9           ",
    "forward 5      ",
    "forward 8      ",
    "forward 1      ",
    "down 4         ",
    "up 2           ",
    "forward 1      ",
    "down 1         ",
    "forward 5      ",
    "down 8         ",
    "down 2         ",
    "forward 3      ",
    "forward 2      ",
    "forward 1      ",
    "down 7         ",
    "forward 1      ",
    "down 4         ",
    "forward 7      ",
    "forward 5      ",
    "down 8         ",
    "down 2         ",
    "up 4           ",
    "up 8           ",
    "forward 6      ",
    "up 2           ",
    "down 8         ",
    "up 9           ",
    "forward 3      ",
    "up 5           ",
    "down 3         ",
    "down 5         ",
    "up 6           ",
    "forward 3      ",
    "up 9           ",
    "down 4         ",
    "forward 8      ",
    "up 3           ",
    "forward 6      ",
    "forward 7      ",
    "forward 8      ",
    "forward 6      ",
    "down 9         ",
    "forward 4      ",
    "up 8           ",
    "forward 3      ",
    "forward 3      ",
    "forward 6      ",
    "down 3         ",
    "forward 5      ",
    "down 4         ",
    "down 4         ",
    "up 4           ",
    "down 8         ",
    "down 4         ",
    "down 1         ",
    "down 7         ",
    "down 7         ",
    "up 9           ",
    "down 7         ",
    "forward 2      ",
    "down 1         ",
    "down 8         ",
    "forward 8      ",
    "forward 4      ",
    "forward 6      ",
    "forward 8      ",
    "forward 6      ",
    "forward 8      ",
    "forward 7      ",
    "forward 6      ",
    "up 7           ",
    "down 6         ",
    "down 9         ",
    "down 2         ",
    "down 8         ",
    "down 4         ",
    "up 6           ",
    "up 8           ",
    "forward 3      ",
    "down 7         ",
    "down 3         ",
    "forward 3      ",
    "forward 3      ",
    "down 4         ",
    "down 1         ",
    "up 3           ",
    "forward 3      ",
    "down 5         ",
    "up 6           ",
    "down 6         ",
    "forward 1      ",
    "down 3         ",
    "down 6         ",
    "down 9         ",
    "down 3         ",
    "forward 8      ",
    "down 1         ",
    "forward 7      ",
    "forward 1      ",
    "forward 3      ",
    "up 3           ",
    "down 8         ",
    "forward 4      ",
    "down 4         ",
    "down 4         ",
    "down 8         ",
    "down 5         ",
    "down 8         ",
    "forward 6      ",
    "forward 7      ",
    "down 9         ",
    "forward 2      ",
    "up 9           ",
    "down 5         ",
    "forward 2      ",
    "down 5         ",
    "down 8         ",
    "forward 1      ",
    "forward 6      ",
    "forward 2      ",
    "forward 6      ",
    "down 7         ",
    "up 7           ",
    "down 7         ",
    "forward 7      ",
    "up 8           ",
    "forward 9      ",
    "down 5         ",
    "up 6           ",
    "up 6           ",
    "forward 3      ",
    "down 5         ",
    "forward 1      ",
    "down 4         ",
    "down 4         ",
    "down 1         ",
    "up 6           ",
    "down 8         ",
    "down 9         ",
    "down 2         ",
    "up 2           ",
    "up 7           ",
    "forward 5      ",
    "down 5         ",
    "up 2           ",
    "forward 2      ",
    "up 1           ",
    "forward 2      ",
    "up 4           ",
    "up 7           ",
    "forward 2      ",
    "down 4         ",
    "down 1         ",
    "forward 4      ",
    "up 6           ",
    "forward 1      ",
    "up 7           ",
    "down 8         ",
    "down 5         ",
    "down 1         ",
    "up 7           ",
    "down 5         ",
    "forward 4      ",
    "forward 2      ",
    "down 2         ",
    "down 6         ",
    "forward 1      ",
    "forward 2      ",
    "up 6           ",
    "down 1         ",
    "forward 2      ",
    "down 5         ",
    "down 9         ",
    "down 6         ",
    "up 8           ",
    "forward 3      ",
    "down 6         ",
    "up 3           ",
    "down 8         ",
    "down 8         ",
    "forward 2      ",
    "forward 1      ",
    "forward 7      ",
    "forward 8      ",
    "forward 2      ",
    "forward 5      ",
    "down 6         ",
    "down 3         ",
    "forward 5      ",
    "up 8           ",
    "forward 6      ",
    "up 9           ",
    "forward 7      ",
    "up 3           ",
    "down 7         ",
    "down 3         ",
    "up 8           ",
    "down 5         ",
    "forward 3      ",
    "down 1         ",
    "forward 1      ",
    "forward 2      ",
    "down 7         ",
    "down 6         ",
    "down 9         ",
    "forward 3      ",
    "down 7         ",
    "down 7         ",
    "down 5         ",
    "forward 4      ",
    "down 4         ",
    "forward 5      ",
    "forward 1      ",
    "forward 4      ",
    "down 8         ",
    "up 4           ",
    "down 6         ",
    "down 8         ",
    "up 1           ",
    "forward 7      ",
    "up 3           ",
    "forward 6      ",
    "forward 8      ",
    "forward 9      ",
    "forward 2      ",
    "up 6           ",
    "forward 7      ",
    "forward 3      ",
    "up 3           ",
    "up 6           ",
    "down 8         ",
    "up 4           ",
    "forward 9      ",
    "down 9         ",
    "up 3           ",
    "up 3           ",
    "down 4         ",
    "up 3           ",
    "down 2         ",
    "down 4         ",
    "up 9           ",
    "down 1         ",
    "forward 6      ",
    "forward 3      ",
    "down 3         ",
    "forward 4      ",
    "forward 3      ",
    "forward 8      ",
    "forward 1      ",
    "down 1         ",
    "up 4           ",
    "up 9           ",
    "down 8         ",
    "forward 3      ",
    "forward 2      ",
    "down 4         ",
    "down 1         ",
    "forward 8      ",
    "down 8         ",
    "up 8           ",
    "up 7           ",
    "down 4         ",
    "forward 6      ",
    "up 5           ",
    "down 1         ",
    "down 3         ",
    "down 9         ",
    "forward 3      ",
    "forward 9      ",
    "down 1         ",
    "down 6         ",
    "forward 8      ",
    "up 1           ",
    "down 9         ",
    "down 3         ",
    "forward 5      ",
    "forward 9      ",
    "forward 8      ",
    "up 7           ",
    "down 2         ",
    "down 5         ",
    "forward 6      ",
    "down 9         ",
    "down 4         ",
    "down 7         ",
    "down 4         ",
    "forward 7      ",
    "down 8         ",
    "up 8           ",
    "forward 2      ",
    "up 3           ",
    "down 4         ",
    "forward 2      ",
    "forward 4      ",
    "up 4           ",
    "forward 4      ",
    "forward 9      ",
    "down 9         ",
    "up 1           ",
    "forward 1      ",
    "down 8         ",
    "up 7           ",
    "up 9           ",
    "down 8         ",
    "down 7         ",
    "forward 9      ",
    "forward 1      ",
    "up 3           ",
    "forward 8      ",
    "forward 6      ",
    "forward 5      ",
    "up 2           ",
    "forward 8      ",
    "up 7           ",
    "down 8         ",
    "down 2         ",
    "up 9           ",
    "down 7         ",
    "forward 5      ",
    "forward 4      ",
    "down 9         ",
    "forward 4      ",
    "forward 5      ",
    "up 1           ",
    "down 8         ",
    "down 8         ",
    "down 4         ",
    "forward 3      ",
    "down 1         ",
    "up 7           ",
    "down 8         ",
    "forward 4      ",
    "down 5         ",
    "forward 1      ",
    "down 9         ",
    "forward 9      ",
    "up 7           ",
    "up 1           ",
    "down 3         ",
    "forward 3      ",
    "down 8         ",
    "forward 9      ",
    "down 3         ",
    "up 7           ",
    "forward 1      ",
    "up 8           ",
    "up 2           ",
    "up 1           ",
    "forward 8      ",
    "down 3         ",
    "forward 5      ",
    "up 3           ",
    "forward 6      ",
    "forward 9      ",
    "forward 2      ",
    "forward 6      ",
    "down 5         ",
    "forward 2      ",
    "down 7         ",
    "up 6           ",
    "forward 8      ",
    "forward 6      ",
    "down 3         ",
    "forward 8      ",
    "down 1         ",
    "forward 2      ",
    "down 9         ",
    "up 5           ",
    "down 6         ",
    "up 4           ",
    "forward 6      ",
    "forward 5      ",
    "forward 2      ",
    "forward 9      ",
    "forward 8      ",
    "up 4           ",
    "forward 4      ",
    "forward 9      ",
    "forward 4      ",
    "forward 7      ",
    "up 6           ",
    "down 5         ",
    "forward 8      ",
    "down 8         ",
    "up 3           ",
    "down 4         ",
    "up 8           ",
    "up 5           ",
    "forward 3      ",
    "down 8         ",
    "down 9         ",
    "down 1         ",
    "forward 7      ",
    "down 8         ",
    "up 4           ",
    "down 8         ",
    "up 4           ",
    "down 5         ",
    "forward 1      ",
    "forward 3      ",
    "down 6         ",
    "down 5         ",
    "forward 4      ",
    "up 2           ",
    "down 7         ",
    "down 3         ",
    "up 9           ",
    "forward 5      ",
    "forward 3      ",
    "forward 2      ",
    "up 2           ",
    "down 9         ",
    "up 1           ",
    "down 2         ",
    "forward 3      ",
    "forward 8      ",
    "forward 5      ",
    "down 2         ",
    "down 2         ",
    "up 3           ",
    "down 8         ",
    "forward 4      ",
    "forward 6      ",
    "forward 5      ",
    "up 9           ",
    "down 7         ",
    "up 7           ",
    "up 2           ",
    "down 2         ",
    "up 4           ",
    "forward 2      ",
    "forward 2      ",
    "down 7         ",
    "forward 5      ",
    "down 2         ",
    "up 7           ",
    "forward 6      ",
    "forward 5      ",
    "down 1         ",
    "forward 8      ",
    "forward 3      ",
    "forward 2      ",
    "up 3           ",
    "down 1         ",
    "forward 6      ",
    "forward 5      ",
    "forward 9      ",
    "down 5         ",
    "up 3           ",
    "down 1         ",
    "down 5         ",
    "forward 1      ",
    "down 1         ",
    "down 1         ",
    "forward 6      ",
    "up 8           ",
    "forward 9      ",
    "up 5           ",
    "up 5           ",
    "forward 9      ",
    "forward 3      ",
    "forward 4      ",
    "down 8         ",
    "forward 9      ",
    "forward 9      ",
    "up 2           ",
    "down 6         ",
    "down 2         ",
    "forward 1      ",
    "down 7         ",
    "up 4           ",
    "forward 3      ",
    "down 6         ",
    "forward 5      ",
    "down 6         ",
    "up 5           ",
    "forward 6      ",
    "up 6           ",
    "forward 7      ",
    "forward 5      ",
    "forward 1      ",
    "down 9         ",
    "forward 7      ",
    "forward 4      ",
    "forward 1      ",
    "forward 6      ",
    "up 7           ",
    "forward 6      ",
    "down 3         ",
    "forward 4      ",
    "down 1         ",
    "down 9         ",
    "down 8         ",
    "forward 7      ",
    "down 7         ",
    "up 5           ",
    "forward 1      ",
    "forward 4      ",
    "forward 8      ",
    "forward 6      ",
    "forward 2      ",
    "forward 4      ",
    "forward 2      ",
    "forward 6      ",
    "forward 5      ",
    "down 4         ",
    "down 3         ",
    "forward 6      ",
    "forward 3      ",
    "up 6           ",
    "down 3         ",
    "down 2         ",
    "forward 1      ",
    "down 9         ",
    "up 1           ",
    "forward 8      ",
    "forward 1      ",
    "forward 1      ",
    "forward 4      ",
    "down 5         ",
    "forward 7      ",
    "forward 5      ",
    "up 5           ",
    "up 7           ",
    "forward 7      ",
    "forward 5      ",
    "down 3         ",
    "down 2         ",
    "down 7         ",
    "forward 7      ",
    "forward 4      ",
    "down 9         ",
    "forward 2      ",
    "down 6         ",
    "forward 3      ",
    "up 6           ",
    "down 8         ",
    "down 7         ",
    "down 6         ",
    "down 7         ",
    "up 5           ",
    "up 9           ",
    "down 4         ",
    "up 6           ",
    "forward 1      ",
    "forward 2      ",
    "forward 4      ",
    "up 5           ",
    "down 2         ",
    "down 3         ",
    "forward 9      ",
    "down 9         ",
    "down 3         ",
    "forward 5      ",
    "forward 3      ",
    "down 1         ",
    "up 7           ",
    "forward 7      ",
    "forward 5      ",
    "down 8         ",
    "up 6           ",
    "down 7         ",
    "forward 5      ",
    "up 7           ",
    "up 6           ",
    "forward 2      ",
    "forward 6      ",
    "down 1         ",
    "up 8           ",
    "down 9         ",
    "down 1         ",
    "forward 9      ",
    "up 9           ",
    "down 2         ",
    "forward 6      ",
    "up 3           ",
    "down 1         ",
    "up 9           ",
    "down 6         ",
    "up 2           ",
    "up 6           ",
    "forward 9      ",
    "forward 8      ",
    "up 7           ",
    "forward 6      ",
    "up 3           ",
    "up 4           ",
    "down 6         ",
    "forward 1      ",
    "forward 9      ",
    "down 9         ",
    "down 6         ",
    "forward 1      ",
    "forward 2      ",
    "up 3           ",
    "down 4         ",
    "down 9         ",
    "down 3         ",
    "down 2         ",
    "forward 7      ",
    "down 9         ",
    "forward 9      ",
    "forward 5      ",
    "down 9         ",
    "forward 1      ",
    "forward 6      ",
    "down 6         ",
    "up 8           ",
    "up 8           ",
    "up 3           ",
    "forward 7      ",
    "forward 7      ",
    "forward 8      ",
    "down 5         ",
    "forward 3      ",
    "down 4         ",
    "down 6         ",
    "forward 1      ",
    "down 1         ",
    "forward 7      ",
    "forward 2      ",
    "down 7         ",
    "down 1         ",
    "up 6           ",
    "forward 3      ",
    "down 6         ",
    "forward 2      ",
    "down 6         ",
    "forward 8      ",
    "down 4         ",
    "up 8           ",
    "forward 9      ",
    "up 5           ",
    "forward 3      ",
    "down 6         ",
    "forward 4      ",
    "forward 4      ",
    "down 8         ",
    "up 5           ",
    "up 9           ",
    "down 8         ",
    "forward 1      ",
    "down 6         ",
    "down 3         ",
    "forward 1      ",
    "down 4         ",
    "up 6           ",
    "down 6         ",
    "down 6         ",
    "down 5         ",
    "forward 5      ",
    "forward 6      ",
    "down 1         ",
    "down 9         ",
    "down 4         ",
    "up 7           ",
    "down 2         ",
    "forward 5      ",
    "down 8         ",
    "down 8         ",
    "down 6         ",
    "down 1         ",
    "up 8           ",
    "down 1         ",
    "down 4         ",
    "forward 6      ",
    "down 3         ",
    "down 6         ",
    "up 4           ",
    "down 6         ",
    "up 7           ",
    "down 3         ",
    "forward 2      ",
    "up 3           ",
    "forward 7      ",
    "up 7           ",
    "up 4           ",
    "forward 5      ",
    "down 9         ",
    "down 2         ",
    "down 9         ",
    "up 6           ",
    "forward 9      ",
    "forward 3      ",
    "down 1         ",
    "forward 7      ",
    "forward 2      ",
    "down 5         ",
    "forward 3      ",
    "forward 7      ",
    "forward 4      ",
    "forward 7      ",
    "forward 6      ",
    "forward 3      ",
    "down 6         ",
    "forward 3      ",
    "down 1         ",
    "up 6           ",
    "up 9           ",
    "down 1         ",
    "forward 1      ",
    "down 1         ",
    "up 7           ",
    "forward 8      ",
    "forward 4      ",
    "up 4           ",
    "forward 7      ",
    "down 3         ",
    "up 8           ",
    "up 1           ",
    "down 6         ",
    "forward 8      ",
    "forward 7      ",
    "up 7           ",
    "down 4         ",
    "down 4         ",
    "down 8         ",
    "up 3           ",
    "forward 5      ",
    "down 4         ",
    "forward 9      ",
    "forward 6      ",
    "forward 6      ",
    "forward 7      ",
    "down 6         ",
    "down 3         ",
    "forward 2      ",
    "up 8           ",
    "forward 1      ",
    "down 9         ",
    "up 7           ",
    "down 3         ",
    "down 3         ",
    "up 5           ",
    "up 4           ",
    "up 8           ",
    "forward 2      ",
    "down 5         ",
    "forward 7      ",
    "up 8           ",
    "up 6           ",
    "forward 5      ",
    "down 5         ",
    "forward 2      ",
    "down 6         ",
    "forward 7      ",
    "down 6         ",
    "forward 5      ",
    "forward 3      ",
    "forward 9      ",
    "down 7         ",
    "forward 7      ",
    "forward 7      ",
    "forward 7      ",
    "forward 1      ",
    "forward 2      ",
    "forward 2      ",
    "down 6         ",
    "down 8         ",
    "forward 3      ",
    "down 9         ",
    "down 5         ",
    "up 5           ",
    "forward 3      ",
    "forward 9      ",
    "down 7         ",
    "down 9         ",
    "down 9         ",
    "down 9         ",
    "forward 6      ",
    "down 1         ",
    "forward 6      ",
    "forward 8      ",
    "forward 8      ",
    "down 4         ",
    "forward 8      ",
    "down 9         ",
    "forward 6      ",
    "down 2         ",
    "down 1         ",
    "down 5         ",
    "forward 5      ",
    "forward 8      ",
    "forward 7      ",
    "forward 7      ",
    "forward 8      ",
    "down 5         ",
    "forward 3      ",
    "up 5           ",
    "forward 5      ",
    "down 9         ",
    "up 8           ",
    "down 2         ",
    "forward 8      ",
    "forward 5      ",
    "up 5           ",
    "forward 4      ",
    "down 3         ",
    "forward 4      ",
    "up 3           ",
    "forward 1      ",
    "forward 8      ",
    "forward 3      ",
    "down 2         ",
    "up 8           ",
    "forward 2      ",
    "down 8         ",
    "forward 3      ",
    "up 2           ",
    "up 1           ",
    "down 9         ",
    "down 8         ",
    "forward 1      ",
    "forward 1      ",
    "down 8         ",
    "forward 9      ",
    "up 2           ",
    "forward 4      ",
    "forward 2      ",
    "up 2           ",
    "down 8         ",
    "down 1         ",
    "forward 1      ",
    "forward 3      ",
    "forward 6      ",
    "up 6           ",
    "down 2         ",
    "up 1           ",
    "down 3         ",
    "forward 3      ",
    "up 5           ",
    "down 9         ",
    "down 7         ",
    "forward 8      ",
    "up 5           ",
    "up 4           ",
    "forward 8      ",
    "forward 5      ",
    "down 8         ",
    "up 8           ",
    "forward 7      ",
    "up 8           ",
    "down 6         ",
    "down 2         ",
    "down 3         ",
    "forward 9      ",
    "down 4         ",
    "down 2         ",
    "down 1         ",
    "up 2           ",
    "up 4           ",
    "forward 3      ",
    "forward 1      ",
    "forward 9      ",
    "forward 1      ",
    "down 7         ",
    "up 7           ",
    "forward 5      ",
    "down 3         ",
    "forward 3      ",
    "down 4         ",
    "down 1         ",
    "up 5           ",
    "down 8         ",
    "down 2         ",
    "forward 4      ",
    "up 9           ",
    "down 3         ",
    "down 3         ",
    "down 2         ",
    "forward 7      ",
    "down 2         ",
    "forward 6      ",
    "up 8           ",
    "forward 5      ",
    "forward 5      ",
    "up 9           ",
    "forward 8      ",
    "forward 9      ",
    "down 5         ",
    "forward 5      ",
    "down 3         ",
    "forward 5      ",
    "down 1         ",
    "forward 6      ",
    "forward 6      ",
    "forward 1      ",
    "forward 2      ",
    "up 5           ",
    "forward 9      "
};
// */
