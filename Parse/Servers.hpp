/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:10:56 by dhaliti           #+#    #+#             */
/*   Updated: 2022/05/30 17:10:58 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#include <iostream>
#include <string>
#include <vector>
#include "parse.hpp"
using namespace std;

typedef struct s_location
{
	string						path;        // location
	vector<string>				methods;     // list of accepted HTTP Methods for the root
	pair<int, string> 			redirection; // HTTP redirection
	string						root;        // directory or a file from where the file should be search
	vector<string>				index;       // default file to answer if the request is a directory
	bool						autoindex;   // turn on or off directory listing
	pair<string, string>  		cgi;         // execute the cgi program
	string						uploadStore; // execute the cgi program
}	t_location;


class Servers
{
public:
	Servers()
	{
		this->_port = 0;
		this->_clientMaxBodySize = 0;
	};

	~Servers()
	{
	};

	Servers(const Servers &other)
	{
		*this = other;
	};

	Servers &operator=(const Servers &other)
	{
		this->_port = other._port;
		this->_ip = other._ip;
		this->_name = other._name;
		this->_errorPages = other._errorPages;
		this->_clientMaxBodySize = other._clientMaxBodySize;
		this->_locations = other._locations;
		return *this;
	}

	void setPort(const int &port) {this->_port = port;};
	void setIP(const string &ip) {this->_ip = ip;};
	void setName(const vector<string> &elem) {this->_name.assign(elem.begin() + 1, elem.end());};
	void setCMBS(int &n) {this->_clientMaxBodySize = n;};

	const int &getPort () const {return this->_port;};
	const string &getIP() const {return this->_ip;};
	const vector<string> &getName() const {return this->_name;};
	const map<int, string> &getErrorPages() const {return this->_errorPages;};
	const int &getCMBS() const {return this->_clientMaxBodySize;};

	vector<t_location>	_locations;

	private:

		int					_port;
		string				_ip;
		vector<string>		_name;
		map<int, string>	_errorPages;
		int					_clientMaxBodySize;

	};
