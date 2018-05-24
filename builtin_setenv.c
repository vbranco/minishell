#include "mini.h"

static int	ft_count_args(char **parsed)
{
	int		i;

	i = 0;
	if (parsed[i])
	{
		while (parsed[i])
			i++;
	}
	return (i);
}

int			setenvi(t_env **env, char **parsed)
{
	t_env	*tmp;
	t_env	*add;

	tmp = *env;
	add = NULL;
	if (parsed == NULL)
		return (environment(*env));
	else if (ft_count_args(parsed) > 3)
		return (ft_error("setenv: Too many arguments", NULL, 0));
	else
	{
		add = ft_initialise();
		if (tmp->next)
		{
			while (tmp->next)//tester ou changer
				tmp = tmp->next;
			tmp->next = add;
			add->prev = tmp;
			add->next = NULL;
		}
		else
		{
			tmp->next = add;
			add->prev = tmp;
			add->next = NULL;
		}
		add->name = parsed[1];
		add->data = parsed[2];
	}
	return (1);
}
