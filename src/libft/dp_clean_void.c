/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dp_clean_void.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 21:09:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/04/15 21:10:35 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	dp_clean_void(char **dp)
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
