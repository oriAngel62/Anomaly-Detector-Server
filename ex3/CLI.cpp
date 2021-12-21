#include "CLI.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

CLI::CLI(DefaultIO *dio)
{
    this->dio = dio;
    this->commands.push_back(new upload_command(dio));

    // this->commands = Command(dio);
}

void CLI::printMenu()
{

    string line1 = "Welcome to the Anomaly Detection Server.\n";
    string line2 = "Please choose an option :\n";
    string line3 = "1.upload a time series csv file\n";
    string line4 = "2.algorithm settings\n";
    string line5 = "3.detect anomalies\n";
    string line6 = "4.display results\n";
    string line7 = "5.upload anomalies and analyze results\n";
    string line8 = "6.exit\n";
    dio->write(line1);
    dio->write(line2);
    dio->write(line3);
    dio->write(line4);
    dio->write(line5);
    dio->write(line6);
    dio->write(line7);
    dio->write(line8);
}

void CLI::start()
{
    printMenu();
    string line = dio->read();
    int numOfUsersOption = stoi(line);
    while (numOfUsersOption >= 1 && numOfUsersOption <= 6)
    {
        switch (numOfUsersOption)
        {
        case 1:
            commands[0]->execute();
            return;
        case 6:
            return;
        default:
            return;
        }
    }

    dio->close();
}
CLI::~CLI()
{
}
