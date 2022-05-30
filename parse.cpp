/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:47:10 by dhaliti           #+#    #+#             */
/*   Updated: 2022/05/30 17:10:42 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"
#include "Servers.hpp"
using namespace std;

static bool getExtension(const string &conf)
{
	size_t pos = conf.rfind(".");
	if (pos == string::npos)
		return 0;
	string	ext = conf.substr(pos, conf.size());
	if (ext != ".conf")
		return 0;
	return 1;
}

static vector<string> &getElements(const string &line, vector<string> &elem)
{
	char **elements = ft_split2(line.c_str(), "\t ");
	int i = -1;
	while (elements[++i])
	{
		string str(elements[i], strlen(elements[i]));
		elem.push_back(str);
		free(elements[i]);
	}
	free(elements);
	return elem;
}

static void	parseLine(vector<Servers> &Webserv, string &line, int &state)
{
	line = ft_strcut(line, '#');
	vector<string> elem;
	getElements(line, elem);

	if (!elem.empty())
	{
		if (elem[0] == "server" && state == OPEN)
		{
			newServ(Webserv, elem, state);
			return;
		}
		if (elem[0] == "location" && state == IN_SERVER)
		{
			newLocation(Webserv, elem, state);
			return;
		}
		if (elem[0] == "{")
		{
			openBlock(Webserv, elem, state);
			return;
		}
		if (elem[0] == "}")
		{
			closeBlock(Webserv, elem, state);
			return;
		}
		else
		{
			elem = ft_vectorcut(elem, ';');
			if (Webserv.size() == 0)
				throw invalid_argument("Configuration error");
			newDirective(Webserv, elem, state);
	 }
}
}

void	ft_parse(const string &conf, vector<Servers> &Webserv)
{
	fstream		file;
	string		line;

	if (!getExtension(conf))
		throw invalid_argument("Extension");
	file.open(conf);
	if (!file)
		throw invalid_argument("Configuration error");
	static int state = OPEN;
	while (getline(file, line))
		parseLine(Webserv, line, state);
	if (state)
		throw invalid_argument("Configuration error");
	file.close();
}
