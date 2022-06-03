/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/05 17:52:49 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/05 17:53:22 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
