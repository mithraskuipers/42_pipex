/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/19 20:59:29 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/19 20:59:29 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = n * -1;
	}
	else
		nbr = n;
	if (nbr >= 10)
		ft_putnbr_fd(nbr / 10, fd);
	ft_putchar_fd(nbr % 10 + '0', fd);
}

int	ft_strchr(const char *s, int c)
{
	int		i;
	char	*s_uc;

	i = 0;
	s_uc = (char *)s;
	while (s_uc[i])
	{
		if (s_uc[i] == (char)c)
			return (i);
		i++;
	}
	if (s_uc[i] == (char)c)
		return (i);
	return (-1);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!(dup))
		return (NULL);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strndup(char *src, int len)
{
	int		i;
	char	*s;

	i = 0;
	if ((!(src)) || (len == 0))
		return (NULL);
	s = malloc(sizeof(char) * len + 1);
	while ((src[i]) && (i < (len - 1)))
	{
		s[i] = src[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_uc;
	unsigned char	*s2_uc;

	i = 0;
	s1_uc = (unsigned char *)s1;
	s2_uc = (unsigned char *)s2;
	while (i < n)
	{
		if ((!s1_uc[i]) && (s1_uc[i] == s2_uc[i]))
			return (0);
		if (s1_uc[i] != s2_uc[i])
			return (s1_uc[i] - s2_uc[i]);
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int		ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
