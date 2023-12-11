#ifndef COMMON_FUNC
#define COMMON_FUNC

#include <QString>
#include <QVector>
#include <fstream>


void fileAsStrVect(QString fullPath, QVector<QString>& out)
{
    std::string line;
    std::ifstream myfile (fullPath.toStdString());
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            out.push_back(QString(line.c_str()));
        }
        myfile.close();
    }
    else
    {
        throw std::runtime_error("Unable to open file.");
    }
}

#endif // COMMON_FUNC
