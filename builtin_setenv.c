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

static int	test_var(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if ((s[i] >= 'a' && s[i] <= 'z') ||
			(s[i] >= 'A' && s[i] <= 'Z') ||
			(s[i] >= '0' && s[i] <= '9'))
			i++;
		else
			return (1);
	}
	return (0);
}

int			setenvi(t_env *env, char **parsed)
{
	t_env	*add;

	add = NULL;
	if (parsed[1] == NULL)
		return (environment(env));
	else if (ft_count_args(parsed) > 3)
		return (ft_error("setenv: Too many arguments", NULL, 0));
	else if (test_var(parsed[1]))
		return (ft_error(ENV_VAR, NULL, 0));
	else
	{
//		ft_printf("parsed[1] >> %s\n", parsed[1]);
//		ft_printf("parsed[2] >> %s\n", parsed[2]);
		add = ft_initialise();
		add->name = parsed[1];
		add->data = parsed[2];
		ft_add(&env, add); 
/*		ft_printf("add->name : %s\n", add->name);
		ft_printf("add->data : %s\n", add->data);
		ft_printf("tmp->next->name : %s\n", tmp->next->name);
		ft_printf("tmp->next->data : %s\n", tmp->next->data);
*/	}
	return (1);
}
