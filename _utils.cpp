/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:21:09 by dhaliti           #+#    #+#             */
/*   Updated: 2022/05/30 16:28:47 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_main.hpp"

using namespace std;

bool	ft_isDirectory(const string& path)
{
	cout << "ft_isDirectory\n";
	cout << "path: " << path << endl;
	struct stat	stat_buf;

	stat(path.c_str(), &stat_buf);
	return (S_ISDIR(stat_buf.st_mode) != 0);
}

bool ft_isNumeric(const std::string &str)
{
	int i = -1;

	while (str[++i])
	{
		if (!std::isdigit(str[i]))
			return (false);
	}
	return (true);
}

vector<string>	ft_vectorcut(const vector<string>& vect, char delimiter)
{
	std::vector<std::string>					newVect(vect);
	std::vector<std::string>::const_iterator	it;
	size_t										pos = 0;

	for(it = newVect.begin(); it != newVect.end(); ++it, ++pos)
	{
		if (*it != ft_strcut(*it, delimiter))
		{
			newVect[pos] = ft_strcut(*it, delimiter);
			if (!newVect[pos].empty())
				++it;
			break ;
		}
	}
	newVect.erase(it, newVect.end());
	return newVect;
}

string    ft_strcut(const string& str, char delimiter)
{
	size_t	pos = str.find(delimiter);

	if (pos == string::npos)
		return str;
	return str.substr(0, pos);
}

bool	ft_isIpAddress(const std::string &str)
{
	size_t 		x;
	size_t 		n = 0;
	std::string	tmp = "";

	for (size_t i = 0; i < str.size(); ++i)
	{
		if (!std::isdigit(str[i]) && str[i] != '.')
			return false;
		if (std::isdigit(str[i]))
			tmp += str[i];
		if (str[i] == '.' || i == (str.size() - 1))
		{
			++n;
			std::stringstream(tmp) >> x;
			if (x > 255 || n > 4)
				return false;
			tmp = "";
		}
	}
	if (n != 4)
		return false;
	return true;
}

static int	ft_is_separator(const char *str, const char *charset)
{
	while (*charset)
		if (*str == *charset++)
			return (1);
	return (0);
}

static int	ft_wordlen(const char *str, const char *charset)
{
	int	i;

	i = 0;
	while (str[i] && !ft_is_separator(str + i, charset))
		i++;
	return (i);
}

static int	ft_wordcount(const char *str, const char *charset)
{
	int	i;
	int	w;

	w = 0;
	while (*str)
	{
		while (*str && ft_is_separator(str, charset))
			str++;
		i = ft_wordlen(str, charset);
		str += i;
		if (i)
			w++;
	}
	return (w);
}

static char	*ft_wordcpy(const char *src, int n)
{
	char	*dest;

	dest = (char *)malloc((n + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	dest[n] = '\0';
	while (n--)
		dest[n] = src[n];
	return (dest);
}

char	**ft_split2(const char *str, const char *charset)
{
	char	**t;
	int		size;
	int		i;
	int		n;

	size = ft_wordcount(str, charset);
	t = (char **)malloc((size + 1) * sizeof(char *));
	if (t == NULL)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		while (*str && ft_is_separator(str, charset))
			str++;
		n = ft_wordlen(str, charset);
		t[i] = ft_wordcpy(str, n);
		if (t[i] == NULL)
			return (NULL);
		str += n;
	}
	t[size] = 0;
	return (t);
}
