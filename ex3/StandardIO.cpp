/*
 * StandardIO.h
 *
 * Author: Ori Angel 314617739
 */
#include "StandardIO.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

StandardIO::StandardIO()
{
}

StandardIO::~StandardIO()
{
}

void StandardIO::write(string text)
{
}

string read()
{
    // File pointer
    fstream f;
    // Open an existing file
    f.open("input.txt", ios::in);
    // first line
    if (f.is_open())
    {
        string oneLine;
        getline(f, oneLine);
        f.close();
        return oneLine;
    }

    // int indexMenu = stoi(firstLine);
    // if (indexMenu != 1)
    // {
    //     exit(1);
    // }
    // else
    // {
    //     execute();
    // }
}