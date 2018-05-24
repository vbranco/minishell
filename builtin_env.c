#include "mini.h"

int			env(t_env *s)
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
	return (1);
}

void	update_env(t_env *env, char *pwd)
{
	t_env	*tmp;
	char	*datatmp;

	ft_printf("\n\ndebug  ||  pwd >> %s\n\n",pwd);
	tmp = env;//debut;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD") == 0)
			break;
		tmp = tmp->next;
	}
	datatmp = ft_strdup(tmp->data);
	free(tmp->data);
	tmp->data = ft_strdup(pwd);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "OLDPWD") == 0)
			break ;
		tmp = tmp->next;
	}
	free(tmp->data);
	tmp->data = ft_strdup(datatmp);
	free(datatmp);
}
