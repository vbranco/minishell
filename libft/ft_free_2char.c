#include "libft.h"

void	ft_free_2char(char **s)
{
	size_t	i;

	i = 0;
	if (s[i])
	{
		while (s[i])
		{
			free(s[i]);
			i++;
		}
	}
	free(s);
	s = NULL;
}
