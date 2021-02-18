#include "Y20Day12.h"

Y20Day12::Y20Day12()
{
}

int Y20Day12::computFirstResult()
{
    Ship arcadia(EST, {0,0});

    arcadia.printPosition();

    for(QString instru : _input)
    {
        instru = instru.simplified();
        arcadia.move(instructionFromString(instru.left(1)), instru.mid(1).toInt());
//        arcadia.printPosition();
    }
    arcadia.printPosition();


    fprintf(stdout, "Manhattan distance from start is %i\r\n", std::abs(arcadia._coordinate.first) + std::abs(arcadia._coordinate.second));
    fflush(stdout);

    return 0;
}


int Y20Day12::computSecondResult()
{

    Ship arcadia(EST, {0,0});
    Ship earth(EST, {10,1});

    arcadia.printPosition();

    for(QString instru : _input)
    {
        instru = instru.simplified();
        Ship::moveWithWaypoint(instructionFromString(instru.left(1)), instru.mid(1).toInt(), arcadia, earth);
//        arcadia.printPosition();
//        earth.printPosition();
    }
    arcadia.printPosition();


    fprintf(stdout, "Manhattan distance from start is %i\r\n", std::abs(arcadia._coordinate.first) + std::abs(arcadia._coordinate.second));
    fflush(stdout);

    return 0;
}

instruction Y20Day12::instructionFromString(QString instru)
{
    if(instru == "N")
        return N;
    else if(instru == "S" )
        return S;
    else if(instru == "E")
        return E;
    else if(instru == "W" )
        return W;
    else if(instru == "L")
        return L;
    else if(instru == "R")
        return R;
    else if(instru == "F")
        return F;
    else
        throw ("Unknown instruction : " + instru.toStdString());
}

QString Y20Day12::instructionToString(instruction instru)
{
    if(instru == N)
        return "N";
    else if(instru == S )
        return "S";
    else if(instru == E)
        return "E";
    else if(instru == W )
        return "W";
    else if(instru == L)
        return "L";
    else if(instru == R)
        return "R";
    else if(instru == F)
        return "F";
    else
        throw ("Unknown instruction");
}


QString Y20Day12::directionToString(direction dir)
{
    if(dir == NORTH)
        return "NORTH";
    else if(dir ==  SOUTH)
        return "SOUTH";
    else if(dir == WEST )
        return "WEST";
    else if(dir == EST)
        return "EST";
    else
        throw ("Unknown direction.") ;
}


Ship::Ship(direction orientation, coordinate position) :
    _direction(orientation),
    _coordinate(position)
{
}


void Ship::move(instruction instru, int power)
{

//    fprintf(stdout, "Instruction is %s %i\r\n", Y20Day12::instructionToString(instru).toStdString().c_str(), power);
//    fflush(stdout);

    int quarterTurn;
    switch (instru) {
    case N:
        _coordinate.second = _coordinate.second + power;
        break;

    case S:
        _coordinate.second = _coordinate.second - power;
        break;

    case E:
        _coordinate.first = _coordinate.first + power;
        break;

    case W:
        _coordinate.first = _coordinate.first - power;
        break;

    case L:
        quarterTurn = power/90;
        if((quarterTurn * 90) != power)
            throw "Non integer quarter turn count";
        for(int idx = 0; idx < quarterTurn; idx++)
        {
            turnLeft();
        }
        break;

    case R:
//        fprintf(stdout, "Enter Right");
//        fflush(stdout);
        quarterTurn = (power/90);
//        fprintf(stdout, "quarter turn is %i", quarterTurn);
//        fflush(stdout);
        if((quarterTurn * 90) != power)
            throw "Non integer quarter turn count";
//        fprintf(stdout, "Turn once");
//        fflush(stdout);
        for(int idx = 0; idx < quarterTurn; idx++)
        {
            turnRight();
        }
        break;

    case F:
        switch (_direction) {
        case NORTH:
            _coordinate.second = _coordinate.second + power;
            break;

        case SOUTH:
            _coordinate.second = _coordinate.second - power;
            break;

        case EST:
            _coordinate.first = _coordinate.first + power;
            break;

        case WEST:
            _coordinate.first = _coordinate.first - power;
            break;

        }
        break;

    }

}

void Ship::moveWithWaypoint(instruction instru, int power, Ship& ship, Ship& waypoint)
{

//    fprintf(stdout, "Instruction is %s %i\r\n", Y20Day12::instructionToString(instru).toStdString().c_str(), power);
//    fflush(stdout);

    int quarterTurn;
    switch (instru) {
    case N:
        waypoint._coordinate.second = waypoint._coordinate.second + power;
        break;

    case S:
        waypoint._coordinate.second = waypoint._coordinate.second - power;
        break;

    case E:
        waypoint._coordinate.first = waypoint._coordinate.first + power;
        break;

    case W:
        waypoint._coordinate.first = waypoint._coordinate.first - power;
        break;

    case L:
        quarterTurn = power/90;
        if((quarterTurn * 90) != power)
            throw "Non integer quarter turn count";
        for(int idx = 0; idx < quarterTurn; idx++)
        {
            waypoint.rotateLeft();
        }
        break;

    case R:
        quarterTurn = (power/90);
        if((quarterTurn * 90) != power)
            throw "Non integer quarter turn count";
        for(int idx = 0; idx < quarterTurn; idx++)
        {
            waypoint.rotateRight();
        }
        break;

    case F:
//        fprintf(stdout, "Enter Forward");
//        fflush(stdout);
        for(int idx = 0 ; idx < power ; idx++)
        {
//            fprintf(stdout, "Move Forward");
//            fflush(stdout);
            ship._coordinate.first += waypoint._coordinate.first;
            ship._coordinate.second += waypoint._coordinate.second;
        }
        break;

    }

}

void Ship::turnLeft()
{
    switch (_direction) {
    case NORTH:
        _direction = WEST;
        break;

    case SOUTH:
        _direction = EST;
        break;

    case EST:
        _direction = NORTH;
        break;

    case WEST:
        _direction = SOUTH;
        break;
    }
}

void Ship::turnRight()
{
    switch (_direction) {
    case NORTH:
        _direction = EST;
        break;

    case SOUTH:
        _direction = WEST;
        break;

    case EST:
        _direction = SOUTH;
        break;

    case WEST:
        _direction = NORTH;
        break;
    }
}


void Ship::rotateLeft()
{
    coordinate origin = _coordinate;
    _coordinate.first = -origin.second;
    _coordinate.second = origin.first;
}


void Ship::rotateRight()
{
    coordinate origin = _coordinate;
    _coordinate.first = origin.second;
    _coordinate.second = -origin.first;
}


void Ship::printPosition()
{
    std::string billy = Y20Day12::directionToString(_direction).toStdString();
    fprintf(stdout, "Position is x:%i y:%i facing %s \r\n", _coordinate.first, _coordinate.second, billy.c_str());
    fflush(stdout);
}



//const QVector<QString> Y20Day12::_input = {
//"F10",
//"N3 ",
//"F7 ",
//"R90",
//"F11"
//};


///*

const QVector<QString> Y20Day12::_input = {
    "N3  ",
    "F18 ",
    "L180",
    "F40 ",
    "N3  ",
    "R90 ",
    "S5  ",
    "R90 ",
    "N4  ",
    "F24 ",
    "R90 ",
    "E5  ",
    "F36 ",
    "R180",
    "W3  ",
    "W4  ",
    "F63 ",
    "N4  ",
    "W1  ",
    "N1  ",
    "E1  ",
    "L90 ",
    "W1  ",
    "N2  ",
    "E2  ",
    "S2  ",
    "F39 ",
    "W4  ",
    "S3  ",
    "F93 ",
    "N1  ",
    "F83 ",
    "S1  ",
    "R90 ",
    "W3  ",
    "R90 ",
    "W4  ",
    "L90 ",
    "F53 ",
    "S4  ",
    "F4  ",
    "L90 ",
    "W3  ",
    "F83 ",
    "L180",
    "W2  ",
    "L90 ",
    "W2  ",
    "L90 ",
    "W1  ",
    "N3  ",
    "F63 ",
    "R90 ",
    "N2  ",
    "N3  ",
    "E4  ",
    "F10 ",
    "S3  ",
    "E4  ",
    "R90 ",
    "F11 ",
    "L90 ",
    "R90 ",
    "S2  ",
    "W2  ",
    "F100",
    "W5  ",
    "R270",
    "F40 ",
    "S5  ",
    "L90 ",
    "E2  ",
    "L90 ",
    "E2  ",
    "L180",
    "N5  ",
    "F81 ",
    "N4  ",
    "E4  ",
    "L180",
    "F38 ",
    "W2  ",
    "F22 ",
    "W5  ",
    "N5  ",
    "E1  ",
    "N2  ",
    "W4  ",
    "N2  ",
    "F68 ",
    "N1  ",
    "F2  ",
    "S1  ",
    "F47 ",
    "W5  ",
    "F80 ",
    "N3  ",
    "E3  ",
    "S2  ",
    "L180",
    "F87 ",
    "L180",
    "E4  ",
    "L90 ",
    "E2  ",
    "S3  ",
    "L180",
    "E2  ",
    "L90 ",
    "W2  ",
    "N4  ",
    "F21 ",
    "S4  ",
    "W5  ",
    "F70 ",
    "F4  ",
    "N2  ",
    "F14 ",
    "E2  ",
    "S3  ",
    "R90 ",
    "W3  ",
    "N2  ",
    "E3  ",
    "S1  ",
    "F85 ",
    "R90 ",
    "E1  ",
    "F80 ",
    "L90 ",
    "F100",
    "R90 ",
    "W1  ",
    "R180",
    "S4  ",
    "F58 ",
    "L90 ",
    "N3  ",
    "R90 ",
    "E1  ",
    "F42 ",
    "E3  ",
    "F93 ",
    "S3  ",
    "R90 ",
    "W2  ",
    "N3  ",
    "L90 ",
    "W3  ",
    "W2  ",
    "N2  ",
    "W1  ",
    "S4  ",
    "R180",
    "N5  ",
    "R180",
    "F52 ",
    "N5  ",
    "F20 ",
    "L180",
    "E5  ",
    "R90 ",
    "W2  ",
    "S4  ",
    "E1  ",
    "S3  ",
    "F75 ",
    "R90 ",
    "F49 ",
    "L180",
    "N3  ",
    "F31 ",
    "S3  ",
    "E3  ",
    "S5  ",
    "L180",
    "N3  ",
    "E2  ",
    "R270",
    "W5  ",
    "N3  ",
    "W5  ",
    "N3  ",
    "L270",
    "F54 ",
    "R90 ",
    "W5  ",
    "F73 ",
    "S3  ",
    "W2  ",
    "R90 ",
    "N2  ",
    "R90 ",
    "S5  ",
    "R90 ",
    "W4  ",
    "S2  ",
    "L90 ",
    "F3  ",
    "S2  ",
    "R90 ",
    "F76 ",
    "S3  ",
    "F56 ",
    "L90 ",
    "F5  ",
    "N1  ",
    "R180",
    "E3  ",
    "N2  ",
    "F20 ",
    "E2  ",
    "L180",
    "F38 ",
    "R180",
    "W4  ",
    "R90 ",
    "S3  ",
    "N5  ",
    "E5  ",
    "F26 ",
    "S2  ",
    "L180",
    "E4  ",
    "R90 ",
    "F52 ",
    "N3  ",
    "L90 ",
    "N5  ",
    "E4  ",
    "F63 ",
    "L90 ",
    "F48 ",
    "W5  ",
    "F29 ",
    "N1  ",
    "E3  ",
    "L90 ",
    "N5  ",
    "L90 ",
    "S3  ",
    "F8  ",
    "N2  ",
    "R90 ",
    "E4  ",
    "S2  ",
    "E2  ",
    "F10 ",
    "W2  ",
    "L90 ",
    "N2  ",
    "R90 ",
    "F2  ",
    "E2  ",
    "N4  ",
    "R90 ",
    "F74 ",
    "W3  ",
    "W5  ",
    "S2  ",
    "R90 ",
    "N3  ",
    "L90 ",
    "E3  ",
    "F58 ",
    "N4  ",
    "E5  ",
    "S4  ",
    "E3  ",
    "F72 ",
    "L180",
    "E3  ",
    "S2  ",
    "L90 ",
    "W4  ",
    "S1  ",
    "F14 ",
    "W1  ",
    "N1  ",
    "E3  ",
    "W4  ",
    "L90 ",
    "N1  ",
    "F97 ",
    "R90 ",
    "N4  ",
    "E3  ",
    "F95 ",
    "F95 ",
    "L90 ",
    "S4  ",
    "F55 ",
    "R90 ",
    "W2  ",
    "N1  ",
    "R90 ",
    "F16 ",
    "L90 ",
    "S5  ",
    "F4  ",
    "R90 ",
    "F24 ",
    "S4  ",
    "E2  ",
    "R90 ",
    "W5  ",
    "E1  ",
    "L270",
    "F12 ",
    "L90 ",
    "F100",
    "W1  ",
    "S5  ",
    "W2  ",
    "S3  ",
    "F95 ",
    "L90 ",
    "F44 ",
    "N5  ",
    "F79 ",
    "S4  ",
    "R180",
    "E2  ",
    "S1  ",
    "F40 ",
    "R90 ",
    "W2  ",
    "R90 ",
    "F67 ",
    "S5  ",
    "F15 ",
    "L90 ",
    "N4  ",
    "L90 ",
    "S5  ",
    "E1  ",
    "R90 ",
    "N3  ",
    "W5  ",
    "N4  ",
    "L270",
    "F61 ",
    "L90 ",
    "E1  ",
    "L90 ",
    "E1  ",
    "F38 ",
    "E2  ",
    "F19 ",
    "W2  ",
    "L90 ",
    "S4  ",
    "R180",
    "W4  ",
    "F59 ",
    "N1  ",
    "F26 ",
    "N1  ",
    "W5  ",
    "F7  ",
    "N4  ",
    "F72 ",
    "E2  ",
    "R90 ",
    "F59 ",
    "N1  ",
    "F58 ",
    "N5  ",
    "F13 ",
    "N2  ",
    "F2  ",
    "S2  ",
    "W1  ",
    "F85 ",
    "R270",
    "S2  ",
    "F17 ",
    "R90 ",
    "F96 ",
    "S2  ",
    "L90 ",
    "E1  ",
    "N4  ",
    "F9  ",
    "R270",
    "F58 ",
    "N1  ",
    "L90 ",
    "W2  ",
    "S2  ",
    "F73 ",
    "W1  ",
    "S2  ",
    "F20 ",
    "E2  ",
    "S4  ",
    "F94 ",
    "L180",
    "F27 ",
    "S2  ",
    "F48 ",
    "N1  ",
    "L270",
    "S2  ",
    "F77 ",
    "E3  ",
    "F10 ",
    "W3  ",
    "L270",
    "S4  ",
    "F53 ",
    "F66 ",
    "E5  ",
    "S2  ",
    "F33 ",
    "S5  ",
    "L90 ",
    "W3  ",
    "S3  ",
    "E3  ",
    "R90 ",
    "E1  ",
    "F62 ",
    "S1  ",
    "L90 ",
    "S3  ",
    "E3  ",
    "N1  ",
    "S1  ",
    "E5  ",
    "S2  ",
    "F66 ",
    "N4  ",
    "N1  ",
    "W4  ",
    "F84 ",
    "R180",
    "F23 ",
    "F20 ",
    "E1  ",
    "S3  ",
    "R90 ",
    "E2  ",
    "F48 ",
    "F89 ",
    "L90 ",
    "F97 ",
    "R180",
    "N3  ",
    "F62 ",
    "L90 ",
    "N5  ",
    "F28 ",
    "W5  ",
    "N4  ",
    "L180",
    "N4  ",
    "W1  ",
    "N3  ",
    "L90 ",
    "F95 ",
    "N1  ",
    "W5  ",
    "R180",
    "N5  ",
    "F34 ",
    "S1  ",
    "W2  ",
    "N4  ",
    "F3  ",
    "S2  ",
    "E1  ",
    "R90 ",
    "E2  ",
    "F36 ",
    "S4  ",
    "E5  ",
    "F42 ",
    "W1  ",
    "L180",
    "S1  ",
    "F74 ",
    "F38 ",
    "N4  ",
    "R270",
    "N3  ",
    "W2  ",
    "S4  ",
    "L180",
    "F26 ",
    "S4  ",
    "F51 ",
    "R90 ",
    "F83 ",
    "R90 ",
    "F9  ",
    "S2  ",
    "W1  ",
    "F99 ",
    "S4  ",
    "W1  ",
    "F84 ",
    "W1  ",
    "R180",
    "F59 ",
    "W5  ",
    "R90 ",
    "F75 ",
    "S1  ",
    "F34 ",
    "E4  ",
    "N3  ",
    "L90 ",
    "F43 ",
    "W5  ",
    "N1  ",
    "R90 ",
    "F59 ",
    "W1  ",
    "N3  ",
    "W4  ",
    "S2  ",
    "F36 ",
    "N5  ",
    "W4  ",
    "E2  ",
    "F96 ",
    "R180",
    "F44 ",
    "R90 ",
    "F12 ",
    "E5  ",
    "F24 ",
    "W3  ",
    "F39 ",
    "S2  ",
    "L180",
    "W3  ",
    "W4  ",
    "F70 ",
    "N4  ",
    "E4  ",
    "F36 ",
    "E2  ",
    "N1  ",
    "F30 ",
    "L90 ",
    "S2  ",
    "F81 ",
    "R270",
    "R90 ",
    "F66 ",
    "W1  ",
    "L90 ",
    "W2  ",
    "F98 ",
    "S1  ",
    "E1  ",
    "L90 ",
    "E3  ",
    "N2  ",
    "F100",
    "W3  ",
    "N3  ",
    "R90 ",
    "F88 ",
    "E4  ",
    "L180",
    "F52 ",
    "L90 ",
    "E4  ",
    "F76 ",
    "W2  ",
    "L90 ",
    "E3  ",
    "F72 ",
    "S3  ",
    "L180",
    "F12 ",
    "F34 ",
    "E5  ",
    "F90 ",
    "S5  ",
    "W5  ",
    "E1  ",
    "N5  ",
    "L180",
    "E5  ",
    "F84 ",
    "E5  ",
    "E3  ",
    "L90 ",
    "E3  ",
    "F14 ",
    "L90 ",
    "W3  ",
    "L90 ",
    "S1  ",
    "L90 ",
    "W2  ",
    "F54 ",
    "R90 ",
    "S2  ",
    "F73 ",
    "S4  ",
    "E1  ",
    "S1  ",
    "F55 ",
    "E5  ",
    "N4  ",
    "R180",
    "L180",
    "N4  ",
    "R90 ",
    "F91 ",
    "L180",
    "F5  ",
    "E2  ",
    "N1  ",
    "W2  ",
    "F27 ",
    "W2  ",
    "S5  ",
    "R90 ",
    "S3  ",
    "F39 ",
    "S3  ",
    "W2  ",
    "F59 ",
    "F83 ",
    "W3  ",
    "E3  ",
    "E4  ",
    "L90 ",
    "S1  ",
    "R90 ",
    "E4  ",
    "F81 ",
    "E4  ",
    "R90 ",
    "W5  ",
    "F74 ",
    "W3  ",
    "E3  ",
    "F30 ",
    "L180",
    "S2  ",
    "E3  ",
    "F33 ",
    "S3  ",
    "R90 ",
    "F22 ",
    "S5  ",
    "F97 ",
    "S1  ",
    "E2  ",
    "F50 ",
    "E2  ",
    "F19 ",
    "E3  ",
    "L90 ",
    "L90 ",
    "S5  ",
    "W3  ",
    "F80 ",
    "F33 ",
    "E1  ",
    "R90 ",
    "N3  ",
    "L90 ",
    "F70 ",
    "L180",
    "W4  ",
    "N2  ",
    "R180",
    "S2  ",
    "F38 ",
    "S3  ",
    "F7  ",
    "R90 ",
    "E1  ",
    "N5  ",
    "F86 ",
    "W4  ",
    "F49 ",
    "W4  ",
    "F51 ",
    "S4  ",
    "F47 ",
    "R90 ",
    "W3  ",
    "R180",
    "R180",
    "W1  ",
    "F98 ",
    "S1  ",
    "W3  ",
    "S4  ",
    "L90 ",
    "F76 ",
    "E1  ",
    "F76 ",
    "R180",
    "S4  ",
    "R180",
    "W3  ",
    "F26 ",
    "N5  ",
    "F35 ",
    "S2  ",
    "F94 ",
    "F24 ",
    "N2  ",
    "F45 ",
    "E1  ",
    "L90 ",
    "F32 ",
    "S1  ",
    "R180",
    "F78 ",
    "F84 ",
    "L90 ",
    "N2  ",
    "F42 ",
    "R90 ",
    "F72 ",
    "S1  ",
    "E3  ",
    "N2  ",
    "W1  ",
    "F23 ",
    "E2  ",
    "F69 ",
    "L90 ",
    "F29 ",
    "R90 ",
    "S5  ",
    "W5  ",
    "L90 ",
    "W1  ",
    "S2  ",
    "E1  ",
    "F96 ",
    "S5  ",
    "R180",
    "F26 ",
    "S5  ",
    "W1  ",
    "S3  ",
    "F38 ",
    "S1  ",
    "E2  ",
    "S5  ",
    "W2  ",
    "S5  ",
    "F52 ",
    "L90 ",
    "F11 ",
    "E3  ",
    "R90 ",
    "E4  ",
    "F6  ",
    "L90 ",
    "R90 ",
    "W1  ",
    "R90 ",
    "E3  ",
    "F1  ",
    "E4  ",
    "N3  ",
    "E5  ",
    "R90 ",
    "N2  ",
    "R180",
    "W2  ",
    "N5  ",
    "F46 ",
    "N3  ",
    "E5  ",
    "F83 ",
    "R90 ",
    "F42 ",
    "S3  ",
    "R90 ",
    "N5  ",
    "F10 "
};


// */
