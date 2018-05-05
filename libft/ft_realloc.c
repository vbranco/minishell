#include "libft.h"

char	*ft_realloc(char *s1, char *s2)
{
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}
