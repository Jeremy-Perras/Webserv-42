/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:50:09 by dhaliti           #+#    #+#             */
/*   Updated: 2022/05/30 17:10:36 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"

void newServListen(Servers &srv, vector<string> &elem)
{
	size_t		pos = elem[1].find(':');
	string		port;

	if (pos == string::npos)
	{
		 port = elem[1];
		 srv.setIP("127.0.0.1");
	}
	else
	{
		srv.setIP(elem[1].substr(0, pos));
		port = elem[1].substr(pos + 1);
	}

	if (!ft_isNumeric(port) || !ft_isIpAddress(srv.getIP()))
		throw invalid_argument("Configuration error");
	srv.setPort(stoi(port));
	if (srv.getPort() > numeric_limits<unsigned short>().max())
		  throw invalid_argument("Configuration error");
	 return ;
}

void newServErrorPages(Servers &srv, vector<string> &elem)
{
	if (elem.size() < 3)
	   throw invalid_argument("Configuration error");
   for (vector<string>::const_iterator it = elem.begin() + 1; it != elem.end() - 1; it++)
   {
	   int error_code;
	   if (!ft_isNumeric(*it))
			throw invalid_argument("Configuration error");
	   stringstream(*it) >> error_code;
	  if (srv.getErrorPages().find(error_code) != srv.getErrorPages().end())
	  {
		 map<int, string> tmp = srv.getErrorPages();
		 tmp.erase(error_code);
	  }
	  	map<int, string> tmp2 = srv.getErrorPages();
	   tmp2[error_code] = ".www/" + elem.back();
	}
	return ;
}

void newServDirective(Servers &srv, vector<string> &elem)
{

	if (elem.empty())
		return ;
	if (elem[0] == "listen" && elem.size() == 2)
	{
		newServListen(srv, elem);
		return;
	}
	if (elem[0] == "server_name")
	{
		srv.setName(elem);
		return;
	}
	if (elem[0] == "error_page")
	{
		newServErrorPages(srv, elem);
		return;
	}
	if (elem[0] == "client_max_body_size" && elem.size() == 2 && ft_isNumeric(elem[1]))
	{
		 int tmp = (stoi(elem[1]));
		 srv.setCMBS(tmp);
		 return;
	}
	else
		throw invalid_argument("Configuration error");
}

void newServ(vector<Servers> &Webserv, vector<string> &elem, int &state)
{
	if (elem.size() != 1)
		throw invalid_argument("Configuration error");
	Servers srv;
	Webserv.push_back(srv);
	state = NEW_SERVER;
};
