/*
 * StandardIO.h
 *
 * Author: Ori Angel 314617739
 */
#include "StandardIO.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

class StandardIO : public DefaultIO
{
    fstream fI;
    fstream fO;

public:
    StandardIO(string inputFile, string outputFile)
    {
        fI.open(inputFile);
        fO.open(outputFile);
    }
    virtual string read()
    {
        string s;
        fI >> s;
        return s;
    }
    virtual void write(string text)
    {
        fO << text;
    }

    virtual void write(float f)
    {
        fO << f;
    }

    virtual void read(float *f)
    {
        fI >> *f;
    }

    void close()
    {
        if (fI.is_open())
            fI.close();
        if (fO.is_open())
            fO.close();
    }
    ~StandardIO()
    {
        close();
    }
};

// int indexMenu = stoi(firstLine);
// if (indexMenu != 1)
// {
//     exit(1);
// }
// else
// {
//     execute();
// }
