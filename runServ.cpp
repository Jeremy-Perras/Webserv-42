/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:50:30 by dhaliti           #+#    #+#             */
/*   Updated: 2022/06/08 12:26:09 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.hpp"
using namespace std;

int build_fd_set(int &socks, vector<Servers> Webserv, fd_set &read_fd, fd_set &write_fd, fd_set except_fds)
{
	size_t i;
	size_t j;
	int high_sock = -1;
	(void)except_fds;

	FD_ZERO(read_fd);
	for (j = 0; j < Webserv.size(); ++j)
	{
		if (socks[j] != -1)
			FD_SET(socks[j], read_fds);
		for (i = 0; i < conf->server[j].client.size(); ++i)
		{
			if (conf->server[j].client[i].socket != -1)
				FD_SET(conf->server[j].client[i].socket, read_fds);
			if (conf->server[j].client[i].pipe_cgi_out[0] != -1)
				FD_SET(conf->server[j].client[i].pipe_cgi_out[0], read_fds);
			if (conf->server[j].client[i].fd_file != -1)
				FD_SET(conf->server[j].client[i].fd_file, read_fds);
		}
	}
	FD_ZERO(write_fds);
	for (j = 0; j < conf->server.size(); ++j)
	{
		for (i = 0; i < conf->server[j].client.size(); ++i)
		{
			if (conf->server[j].client[i].socket != -1)
				FD_SET(conf->server[j].client[i].socket, write_fds);
			if (conf->server[j].client[i].pipe_cgi_in[1] != -1)
				FD_SET(conf->server[j].client[i].pipe_cgi_in[1], write_fds);
		}
	}

	for (size_t i = 0; i < conf->server.size(); ++i)
	{
		if (listen_sock[i] > high_sock)
			high_sock = listen_sock[i];
	}
	for (size_t j = 0; j < conf->server.size(); j++)
	{
		for (size_t i = 0; i < conf->server[j].client.size(); i++)
		{
			if (high_sock < conf->server[j].client[i].socket)
				high_sock = conf->server[j].client[i].socket;
			if (high_sock < conf->server[j].client[i].pipe_cgi_in[1])
				high_sock = conf->server[j].client[i].pipe_cgi_in[1];
			if (high_sock < conf->server[j].client[i].pipe_cgi_out[0])
				high_sock = conf->server[j].client[i].pipe_cgi_out[0];
			if (high_sock < conf->server[j].client[i].fd_file)
				high_sock = conf->server[j].client[i].fd_file;
		}
	}
	return (high_sock);
}

bool ListenSocketAssign(int &port, int &socket, const string &ip)
{
	struct sockaddr_in address;

	if ((socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout << "SERV ERROR" << endl << endl;
		perror("Socket");
		cout << RESET;
		return 1;
	}

	fcntl(socket, F_SETFL, O_NONBLOCK);
	int reuse = 1;
	if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) != 0)
	{
		cout << "Serv... ERROR !" << std::endl << std::endl;
		perror("SetSockOpt");
		cout << RESET;
		return 1;
	}

	if (ip == "0.0.0.0")
		address.sin_addr.s_addr = INADDR_ANY;
	else if (ip == "127.0.0.1")
		address.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // htonl pour remettre les octets dans l'ordre
	else
		address.sin_addr.s_addr = inet_addr(ip.c_str()); // fonctionne aussi avec "0.0.0.0" et "127.0.0.1"
	address.sin_family = AF_INET;
	address.sin_port = htons(port);

	memset(&address.sin_zero, 0, sizeof(address.sin_zero));

	if (bind(socket, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		cout << "Serv... ERROR !" << std::endl << std::endl;
		perror("Bind");
		std::cout << RESET;
		return 1;
	}

	if (listen(socket, MAX_QUEUED_CONNEXIONS) < 0)
	{
		cout << "Serv... ERROR !" << std::endl << std::endl;
		perror("Listen");
		std::cout << RESET;
		return 1;
	}
	return 0;
}



int runServ(vector<Servers> &Webserv)
{
	int high_sock;
	fd_set read_fd;
	fd_set write_fd;

	int socks[Webserv.size()];
	for (size_t i = 0; i < Webserv.size(); i++)
		if (assign_socket(Webserv[i].getPort(), socks[i], Webserv[i].getIP())
			return (-1);

	while (1)
	{
		high_sock = build_fd_set(socks, Webserv, read_fd, write_fd, NULL);

		int activity = select(high_sock + 1, &read_fd, &write_fd, NULL, NULL);
		if (exit_status == true)
			return (0);
		if (activity < 0)
		{
			cout <<"Serv... ERROR !" << endl;
			return 1;
		}
	}
}
