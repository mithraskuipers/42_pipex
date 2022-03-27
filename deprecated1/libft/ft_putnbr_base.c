/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_base.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 21:35:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/22 21:35:32 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(int nbr, int base)
{
	int		result;
	char	print;
	char	*set;

	set = "0123456789ABCDEF";
	if (nbr < 0)
	{
		write(1, "-", 1);
		print = set[(nbr % base) * -1];
		result = (nbr / base) * -1;
	}
	else
	{
		result = nbr / base;
		print = set[nbr % base];
	}
	if (result != 0)
		ft_putnbr_base(result, base);
	write(1, &print, 1);
}
