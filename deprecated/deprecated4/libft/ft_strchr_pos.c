/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr_pos.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/07 14:56:42 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/07 15:11:36 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_pos(const char *s, int c)
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
