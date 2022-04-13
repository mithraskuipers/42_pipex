/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc_mk.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkuipers <mkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 17:50:27 by mkuipers      #+#    #+#                 */
/*   Updated: 2022/03/28 16:52:29 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc_new(size_t count, size_t size)
{
	void			*ptr;
	size_t			i;
	size_t			len;
	unsigned char	*b_uc;
	unsigned char	c;

	ptr = malloc(count * size);
	if (!(ptr))
		return (NULL);
	i = 0;
	len = count * size;
	b_uc = (unsigned char *)ptr;
	c = 0;
	while (i < len)
	{
		b_uc[i] = c;
		i++;
	}
	return (ptr);
}
