
/*
 * Server.cpp
 *
 * Author: Ori Angel 314617739
 */
#include "Server.h"

Server::Server(int port) throw(const char *)
{
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		throw "socket inCorrect";

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);

	if (bind(fd, (struct sockaddr *)&server, sizeof(server)) < 0)
		throw "bind inCorrect";

	if (listen(fd, 3) < 0)
		throw "listen inCorrect";
	stopTheLoop = false;
}

void Server::start(ClientHandler &ch) throw(const char *)
{
	t = new thread([&ch, this]()
				   {
		while(!(stopTheLoop))
		{
			socklen_t clientSize = sizeof(client);
			int acceptClient = accept(fd, (struct sockaddr*)&client, &clientSize);
			if(acceptClient<0){
				throw "acceptClient inCorrect";
			}
			if(acceptClient >= 0)
			{ 
				ch.handle(acceptClient);
				close(acceptClient);
			}
		}
		close(fd); });
}

void Server::stop()
{
	stopTheLoop = true;
	t->join(); // do not delete this!
}

Server::~Server()
{
}
