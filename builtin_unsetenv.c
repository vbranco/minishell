#include "mini.h"

static void	ft_free_env(t_env **env, char *s)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, s) == 0)
		{
			free(tmp->name);
			free(tmp->data);
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			free(tmp);
			tmp = NULL;
			break ;
		}
		tmp = tmp->next;
	}
}

int			unsetenvi(t_env **env, char **parsed)
{
	int		i;

	i = 1;
	if (parsed[i] == NULL)
		return (ft_error(UNSETENV_NO_ARG, NULL, 0));
	else
	{
		while (parsed[i])
		{
			ft_free_env(env, parsed[i]);
			i++;
		}
	}
	return (1);
}
