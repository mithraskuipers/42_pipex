
#include "libft.h"

int	ft_strchr_new(const char *s, int c)
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
