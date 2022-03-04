/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/04 11:13:30 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/04 11:38:02 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!(dst) || (!(src)) || (dstsize == 0))
		return (ft_strlen(src));
	while ((src[i]) && (i < (dstsize - 1)))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;
	char	*s3;

	if ((s1 == NULL) || (s2 == NULL))
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = s1_len + s2_len + 1;
	if (!(s3 = (char *)malloc(sizeof(char) * s3_len)))
		return (NULL);
	ft_strlcpy(s3, s1, s3_len);
	ft_strlcpy((s3 + s1_len), s2, s3_len);
	return (s3);
}