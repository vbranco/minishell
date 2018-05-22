#include "mini.h"

void	afficher_env(t_env *s)
{
	while (s)
	{
//		if (s->prev)
//			ft_printf("prev >> %s\n", s->prev->name);
//		ft_printf("current >> %s\n", s->name);
		ft_printf("%s = %s\n", s->name, s->data);
//		if (s->next)
//			ft_printf("next >> %s\n", s->next->name);
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
