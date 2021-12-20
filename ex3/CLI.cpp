#include "CLI.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

CLI::CLI(DefaultIO *dio) : dio(dio)
{
    // this->dio = dio;

    this->commands = Command(dio);
}

void CLI::start()
{
    // File pointer
    fstream f;
    // Open an existing file
    f.open("input.txt", ios::in);
    String firstLine = dio->read();

    f.close();
}
CLI::~CLI()
{
}
