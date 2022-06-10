/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:47:01 by dhaliti           #+#    #+#             */
/*   Updated: 2022/05/30 17:11:06 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"

void openBlock(vector<Servers> &Webserv, vector<string> &elem, int &state)
{
	(void)Webserv;
	if (elem.size() != 1)
		throw invalid_argument("Configuration error");
	if (state == NEW_SERVER || state == NEW_LOCATION)
		state++;
	else
	{
		cout << elem[0] << endl;
		cout << "state open block2: " << state << endl;
		throw invalid_argument("Configuration error");
	}
};

void closeBlock(vector<Servers> &Webserv, vector<string> &elem, int &state)
{
	(void)Webserv;
	if (elem.size() != 1)
		throw invalid_argument("Configuration error");
	cout << "close_state: " << state << endl;
	if (state == IN_LOCATION)
	{
		state = IN_SERVER;
		return;
	}
	if (state == IN_SERVER)
	{
		state = OPEN;
		return;
	}
	else
		throw invalid_argument("Configuration error");
};



void newDirective(vector<Servers> &Webserv, vector<string> &elem, int &state)
{
	if (state == IN_SERVER)
	{
		newServDirective(Webserv.back(), elem);
		return ;
	}
	else if (state == IN_LOCATION)
	{
		cout << "state_in_location: " << state << endl;
		newLocationDirective(Webserv.back(), elem);
		return ;
	}
	else
	{
		throw invalid_argument("Configuration error");
	}
};
