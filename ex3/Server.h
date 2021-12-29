/*
 * Server.h
 *
 * Author: Ori Angel 314617739
 */
#include <pthread.h>
#include <thread>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "CLI.h"

#ifndef SERVER_H_
#define SERVER_H_

using namespace std;

// edit your ClientHandler interface here:
class ClientHandler
{
public:
	virtual void handle(int clientID) = 0;
};

// you can add helper classes here and implement on the cpp file

// edit your AnomalyDetectionHandler class here

// implement on Server.cpp
class Server
{
	int fd;
	sockaddr_in server;
	sockaddr_in client;
	thread *t; // the thread to run the start() method in
	volatile bool stopTheLoop;

public:
	Server(int port) throw(const char *);
	virtual ~Server();
	void start(ClientHandler &ch) throw(const char *);
	void stop();
};
// socket class
class SocketIO : public DefaultIO
{
	int clientKey;

public:
	SocketIO(int clientID) : clientKey(clientID) {}

	virtual string read()
	{
		string message = "";
		char everyLetter = 'a';
		while (everyLetter != '\n')
		{
			recv(clientKey, &everyLetter, sizeof(char), 0);
			message += everyLetter;
		}
		return message;
	}
	virtual void write(string text)
	{
		const char *message = text.c_str(); // not percise need to check
		send(clientKey, message, strlen(message), 0);
	}
	virtual void write(float f)
	{
	}
	virtual void read(float *f)
	{
	}
	virtual void close()
	{
	}
	virtual ~SocketIO()
	{
	}
};

class AnomalyDetectionHandler : public ClientHandler
{
public:
	virtual void handle(int clientID)
	{
		SocketIO s(clientID);
		CLI cli(&s);
		cli.start();
	}
};

#endif /* SERVER_H_ */
