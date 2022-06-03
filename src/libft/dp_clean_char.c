/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dp_clean_char.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/07 15:10:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/15 21:08:31 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	dp_clean_char(char **dp)
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
