#include "Y20Day17.h"

Y20Day17::Y20Day17()
{


}

int Y20Day17::computFirstResult()
{
    int turnNumber = 6;
    int currentTurn = 1;

    _currentGrid = Grid17(_input.size() + (turnNumber*2), _input.first().size() + (turnNumber*2), (turnNumber*2)+1);
    _previousGrid = Grid17(_input.size() + (turnNumber*2), _input.first().size() + (turnNumber*2), (turnNumber*2)+1);

    int currentX = turnNumber;
    int currentZ = turnNumber;

    //Fill initial state
    for(QString line : _input)
    {
        int currentY = turnNumber;
        for(QChar cell : line)
        {
            _previousGrid._grid[currentX][currentY][currentZ] = (cell == '#');
            currentY++;
        }
        currentX++;
    }

    for(; currentTurn <= turnNumber ; currentTurn++)
    {
        fprintf(stdout, "Turn %i\r\n======\r\n", currentTurn);
//        _currentGrid.print();
        for(int idX = 0; idX < _previousGrid._grid.size() ; idX++)
        {
            for(int idY = 0; idY < _previousGrid._grid.first().size() ; idY++)
            {
                for(int idZ = 0; idZ < _previousGrid._grid.first().first().size(); idZ++)
                {
                    int aciveNeighbors = _previousGrid.countActiveNeighbors(idX, idY, idZ);
                    if(_previousGrid._grid[idX][idY][idZ])
                    {
                        _currentGrid._grid[idX][idY][idZ] = (aciveNeighbors == 2 || aciveNeighbors ==3);
                    }
                    else
                    {
                        _currentGrid._grid[idX][idY][idZ] = (aciveNeighbors ==3);
                    }
                }
            }
        }
        _previousGrid = _currentGrid;
    }

    int result = 0;
    for(int idX = 0; idX < _previousGrid._grid.size() ; idX++)
    {
        for(int idY = 0; idY < _previousGrid._grid.first().size() ; idY++)
        {
            for(int idZ = 0; idZ < _previousGrid._grid.first().first().size(); idZ++)
            {
                if(_currentGrid._grid[idX][idY][idZ])
                  result++;
            }
        }
    }

    return result;
}

int Y20Day17::computSecondResult()
{
    int turnNumber = 6;
    int currentTurn = 1;

    _currentHyperGrid = HyperGrid17(_input.size() + (turnNumber*2), _input.first().size() + (turnNumber*2), (turnNumber*2)+1, (turnNumber*2)+1);
    _previousHyperGrid = HyperGrid17(_input.size() + (turnNumber*2), _input.first().size() + (turnNumber*2), (turnNumber*2)+1, (turnNumber*2)+1);

    int currentX = turnNumber;
    int currentZ = turnNumber;
    int currentW = turnNumber;

    //Fill initial state
    for(QString line : _input)
    {
        int currentY = turnNumber;
        for(QChar cell : line)
        {
            _previousHyperGrid._grid[currentX][currentY][currentZ][currentW] = (cell == '#');
            currentY++;
        }
        currentX++;
    }

    for(; currentTurn <= turnNumber ; currentTurn++)
    {
        fprintf(stdout, "Turn %i\r\n======\r\n", currentTurn);
//        _currentHyperGrid.print();
        for(int idX = 0; idX < _previousHyperGrid._grid.size() ; idX++)
        {
            for(int idY = 0; idY < _previousHyperGrid._grid.first().size() ; idY++)
            {
                for(int idZ = 0; idZ < _previousHyperGrid._grid.first().first().size(); idZ++)
                {
                    for(int idW = 0; idW < _previousHyperGrid._grid.first().first().first().size(); idW++)
                    {
                        int aciveNeighbors = _previousHyperGrid.countActiveNeighbors(idX, idY, idZ, idW);
                        if(_previousHyperGrid._grid[idX][idY][idZ][idW])
                        {
                            _currentHyperGrid._grid[idX][idY][idZ][idW] = (aciveNeighbors == 2 || aciveNeighbors ==3);
                        }
                        else
                        {
                            _currentHyperGrid._grid[idX][idY][idZ][idW] = (aciveNeighbors ==3);
                        }
                    }
                }
            }
        }
        _previousHyperGrid = _currentHyperGrid;
    }

    int result = 0;
    for(int idX = 0; idX < _previousHyperGrid._grid.size() ; idX++)
    {
        for(int idY = 0; idY < _previousHyperGrid._grid.first().size() ; idY++)
        {
            for(int idZ = 0; idZ < _previousHyperGrid._grid.first().first().size(); idZ++)
            {
                for(int idW = 0; idW < _previousHyperGrid._grid.first().first().first().size(); idW++)
                {
                    if(_currentHyperGrid._grid[idX][idY][idZ][idW])
                        result++;
                }
            }
        }
    }

    return result;

}

Grid17 Y20Day17::_previousGrid(0,0,0);
Grid17 Y20Day17::_currentGrid(0,0,0);

Grid17::Grid17(int max_x, int max_y, int max_z)
{
    QVector<bool> zLine(max_z, false);
    QVector<QVector<bool>> zyPlan(max_y, zLine);
    _grid = QVector<QVector<QVector<bool>>>(max_x, zyPlan);
}



int Grid17::countActiveNeighbors(int x, int y, int z)
{
    int activeCount = 0;
    for(int idX = x-1; idX <= x+1 ; idX++)
    {
        for(int idY = y-1; idY <= y+1 ; idY++)
        {
            for(int idZ = z-1; idZ <= z+1 ; idZ++)
            {
                if(idX < 0 || idY < 0 || idZ < 0 || idX >= _grid.size() || idY >= _grid.first().size() || idZ >= _grid.first().first().size())
                    continue;
                else if((idX == x) && (idY == y) && (idZ == z))
                    continue;
                else if(_grid[idX][idY][idZ])
                    activeCount++;
            }
        }
    }
    return activeCount;
}

void Grid17::print()
{
    for(int idZ = 0; idZ < _grid.first().first().size(); idZ++)
    {
        fprintf(stdout, "Z = %i\r\n", idZ);
        for(int idX = 0; idX < _grid.size() ; idX++)
        {
            for(int idY = 0; idY < _grid.first().size() ; idY++)
            {
                fprintf(stdout, (_grid[idX][idY][idZ] ? "#" : "."));
            }
            fprintf(stdout, "\r\n");
        }
        fprintf(stdout, "\r\n");
    }
    fflush(stdout);
}

HyperGrid17 Y20Day17::_previousHyperGrid(0,0,0,0);
HyperGrid17 Y20Day17::_currentHyperGrid(0,0,0,0);

HyperGrid17::HyperGrid17(int max_x, int max_y, int max_z, int max_w)
{
    QVector<bool> wHyperLine(max_w, false);
    QVector<QVector<bool>> zLines(max_z, wHyperLine);
    QVector<QVector<QVector<bool>>> zyPlans(max_y, zLines);
    _grid = QVector<QVector<QVector<QVector<bool>>>>(max_x, zyPlans);
}


int HyperGrid17::countActiveNeighbors(int x, int y, int z, int w)
{
    int activeCount = 0;
    for(int idX = x-1; idX <= x+1 ; idX++)
    {
        for(int idY = y-1; idY <= y+1 ; idY++)
        {
            for(int idZ = z-1; idZ <= z+1 ; idZ++)
            {
                for(int idW = w-1; idW <= w+1 ; idW++)
                {
                if(idX < 0 || idY < 0 || idZ < 0 || idW < 0 || idX >= _grid.size() || idY >= _grid.first().size() || idZ >= _grid.first().first().size() || idW >= _grid.first().first().first().size())
                    continue;
                else if((idX == x) && (idY == y) && (idZ == z) && (idW == w))
                    continue;
                else if(_grid[idX][idY][idZ][idW])
                    activeCount++;
                }
            }
        }
    }
    return activeCount;
}


void HyperGrid17::print()
{
    for(int idW = 0; idW < _grid.first().first().first().size(); idW++)
    {
        fprintf(stdout, "W = %i ", idW);
        for(int idZ = 0; idZ < _grid.first().first().size(); idZ++)
        {
            fprintf(stdout, "Z = %i\r\n", idZ);
            for(int idX = 0; idX < _grid.size() ; idX++)
            {
                for(int idY = 0; idY < _grid.first().size() ; idY++)
                {
                    fprintf(stdout, (_grid[idX][idY][idZ][idW] ? "#" : "."));
                }
                fprintf(stdout, "\r\n");
            }
            fprintf(stdout, "\r\n");
        }
    }
    fflush(stdout);
}


 /* // test input => 112 after 6 cycles for part 1 and 848 after 6 cycles for part 2
const QVector<QString> Y20Day17::_input = {
".#.",
"..#",
"###"
};
// */

// /* //true input
const QVector<QString> Y20Day17::_input = {
".#..####",
".#.#...#",
"#..#.#.#",
"###..##.",
"..##...#",
"..##.###",
"#.....#.",
"..##..##"
};
// */





















