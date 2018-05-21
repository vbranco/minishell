#include "libft.h"

void	ft_free_2char(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s[i]);
}
