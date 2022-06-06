/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:33:52 by dhaliti           #+#    #+#             */
/*   Updated: 2022/05/31 15:01:32 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parse.hpp"
#include "Servers.hpp"
using namespace std;


int main(int ac, char **av)
{
	vector<Servers> Webserv;

	try
	{
		switch (ac)
		{
			case 1:
				ft_parse("42.conf", Webserv);
				break;

			case 2:
				ft_parse(av[1], Webserv);
				break ;

			default:
				throw invalid_argument("Too many configuration files");
				break;
		}
	}
	catch (exception &e)
	{
		cout << e.what() << endl;
		exit(0);
	}
	cout << "NB SERVEURS: " << Webserv.size() << endl;
	cout << "NB LOCATIONS: " << Webserv.back()._locations.size() << endl;
	size_t i = -1;
	size_t j = -1;
	while(++i < Webserv.size())
	{
		cout << "Webserv[" << i << "]: " << Webserv[i].getPort() << endl;
		j = -1;
		while(++j < Webserv[i]._locations.size())
			cout << Webserv[i]._locations[j].path << endl;
		cout << endl;;
	}

//	signal(SIGINT, handleSignals);

	//createServers(webserv)
	return 0;
}
