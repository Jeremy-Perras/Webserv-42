/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:26:54 by dhaliti           #+#    #+#             */
/*   Updated: 2022/05/30 17:10:47 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


# include <arpa/inet.h>
# include <sys/select.h>
# include <sys/types.h>
# include <sys/event.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/cdefs.h>
# include <netinet/in.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <signal.h>

# include <string>
# include <cstring>
# include <cstdio>
# include <cstdlib>
# include <cctype>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <sstream>
# include <exception>

# include <map>
# include <vector>
# include <list>
# include <algorithm>

using namespace std;

#include "Servers.hpp"
#include <iostream>



enum	e_config
{
	OPEN,
	NEW_SERVER,
	IN_SERVER,
	NEW_LOCATION,
	IN_LOCATION
};

bool 			ft_isNumeric(const string &str);
string    		ft_strcut(const string& str, char delimiter);
vector<string>	ft_vectorcut(const vector<string>& vect, char delimiter);
char			**ft_split2(const char *str, const char *charset);
bool			ft_isIpAddress(const std::string &str);
void			ft_parse(const string &conf, vector<Servers> &Webserv);
void 			openBlock(vector<Servers> &Webserv, vector<string> &elem, int &state);
void 			closeBlock(vector<Servers> &Webserv, vector<string> &elem, int &state);
void 			newServDirective(Servers &srv, vector<string> &elem);
void 			newDirective(vector<Servers> &Webserv, vector<string> &elem, int &state);
void 			newServ(vector<Servers> &Webserv, vector<string> &elem, int &state);
void 			newServListen(Servers &srv, vector<string> &elem);
void 			newServErrorPages(Servers &srv, vector<string> &elem);
void 			newLocation(vector<Servers> &Webserv, vector<string> &elem, int &state);
void			newLocationDirective(Servers &srv, vector<string> &elem);
bool			ft_isDirectory(const string& path);
