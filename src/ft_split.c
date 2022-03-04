/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 21:37:19 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/04 11:07:33 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_countparts(const char *s, char c)
{
	size_t	i;
	int		nparts;

	i = 0;
	nparts = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			nparts++;
			while (s[i] && s[i] != c)
				i++;
		}
		else if (s[i] && s[i] == c)
			i++;
	}
	return (nparts);
}

static void	dp_clean(char **dp)
{
	size_t	i;

	i = 0;
	while (dp[i])
	{
		free(dp[i]);
		i++;
	}
	free(dp);
}

static char	*get_word(const	char *s, char c, char **dp)
{
	char	*word;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while ((s[len] != c) && s[len])
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
	{
		dp_clean(dp);
		return (NULL);
	}
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**dp;
	int		i;
	int		n;

	n = ft_countparts(s, c);
	i = 0;
	dp = malloc(sizeof(const char *) * (n + 1));
	if (!dp)
		return (0);
	dp[n] = 0;
	while (*s == c && *s)
		s++;
	while (*s)
	{
		dp[i] = get_word(s, c, dp);
		if (!dp[i])
			return (NULL);
		i++;
		while (*s != c && *s)
			s++;
		while (*s == c && *s)
			s++;
	}
	return (dp);
}