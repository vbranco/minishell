#include "mini.h"

void	afficher_env(t_env *s)
{
	while (s)
	{
		ft_printf("%s = %s\n", s->name, s->data);
		s = s->next;
	}
}

/*
static int  test(char *str, char *search, int i)
{
	char        tmp;

	tmp = str[i];
	str[i] = '\0';
	if (ft_strcmp(str, search) == 0)
	{
		str[i] = tmp;
		return (1);
	}
	str[i] = tmp;
	return (0);
}
*/
