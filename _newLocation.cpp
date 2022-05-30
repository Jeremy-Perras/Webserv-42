/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _newLocation.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:03:46 by dhaliti           #+#    #+#             */
/*   Updated: 2022/05/30 16:49:38 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_main.hpp"

/*******************************LOCATION METHODS*******************************/

static void setMethods(t_location &location, vector<string> elem)
{
	static std::string			methods[] = {
		"GET",
		"POST",
		"DELETE",
		""
	};
	bool						exist;
	size_t						i;
	vector<string>::const_iterator	it;
	vector<string>::const_iterator	it1;

	for (it = elem.begin() + 1; it != elem.end(); it++)
	{
		for (i = 0; !methods[i].empty(); ++i)
		{
			if (*it == methods[i])
			{
				exist = false;
				for (it1 = location.methods.begin(); it1 != location.methods.end(); ++it1)
				{
					if (*it1 == methods[i])
						exist = true;
				}
				if (!exist)
					location.methods.push_back(methods[i]);
				break ;
			}
		}
		if (i == 3)
			throw invalid_argument("Configuration error");
	}
}

/****************************LOCATION RETIRECTIONS*****************************/

static void setRedirection(t_location  &loc, vector<string> &elem)
{
	if (elem.size() != 3 || !ft_isNumeric(elem[1]))
		throw invalid_argument("Configuration error");;
	std::stringstream(elem[1]) >> loc.redirection.first;
	if (loc.redirection.first != 307 && loc.redirection.first != 308
		&& (loc.redirection.first < 300 || loc.redirection.first > 304))
	throw invalid_argument("Configuration error");;
	loc.redirection.second = elem[2];
}

/********************************LOCATION ROOT*********************************/

static void	setRoot(t_location  &loc, vector<string> &elem)
{
	if (elem.size() != 2)
		throw invalid_argument("Configuration error");;
	if (elem[1][0] != '/')
		loc.root = loc.path + elem[1];
	else
		loc.root = elem[1];
}

/******************************LOCATION AUTOINDEX******************************/

void	setAutoIndex(t_location  &loc, vector<string> &elem)
{
	if (elem.size() != 2)
		throw invalid_argument("Configuration error");
	if (elem[1] == "on")
		loc.autoindex = 1;
	else if (elem[1] != "off")
		throw invalid_argument("Configuration error");
}

/*********************************LOCATION CGI*********************************/

void 	setCgi(t_location  &loc, vector<string> &elem)
{
	 if (elem.size() != 3)
		throw invalid_argument("Configuration error");
	loc.cgi.first = elem[1];
	loc.cgi.second = elem[2];
}

/*****************************LOCATION UPLOADSTORE*****************************/

void	setUploadStore(t_location  &loc, vector<string> &elem)
{
	if (elem.size() != 2 || !ft_isDirectory("./www" + elem[1]))
		throw invalid_argument("Configuration error");
	loc.uploadStore = elem[1];
	if (elem[1].back() != '/')
		loc.uploadStore += "/";
}


/****************************LOCATION NEW DIRECTIVE****************************/

void	newLocationDirective(Servers &srv, vector<string> &elem)
{
//	cout << "new_location_directive\n";
	t_location tmp = srv._locations.back();
	if (elem[0] == "allow")
	{
		setMethods(tmp, elem);
		return ;
	}
	if (elem[0] == "return")
	{
		setRedirection(tmp, elem);
		return ;
	}
	if (elem[0] == "root")
	{
		setRoot(tmp, elem);
		return ;
	}
	 if (elem[0] == "index")
	 {
		 tmp.index.assign(elem.begin() + 1, elem.end());
		 return ;
	 }
	 if (elem[0] == "autoindex")
	 {
		setAutoIndex(tmp, elem);
		return ;
	 }
	if (elem[0] == "cgi_pass")
	{
		setCgi(tmp, elem);
		return ;
	}
	if (elem[0] == "upload_store")
	{
		setUploadStore(tmp, elem);
		return ;
	}
	else
		throw invalid_argument("Configuration error");
}

void newLocation(vector<Servers> &Webserv, vector<string> &elem, int &state)
{
	cout << "newLocation: " << elem[0] << " " << elem[1] << endl << "newLocation state: " << state << endl;
	if (elem.size() != 2 || elem[1].find(';') != string::npos)
		throw invalid_argument("Configuration error");
	t_location loc;
	loc.path = elem[1];
	loc.methods.push_back("GET");
	loc.autoindex = 0;
	loc.redirection = make_pair(0, "");
	loc.cgi = make_pair("", "");
	Webserv.back()._locations.push_back(loc);
	state = NEW_LOCATION;
};
