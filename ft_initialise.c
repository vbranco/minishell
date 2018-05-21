#include "mini.h"

t_env		*ft_initialise(void)
{
	t_env	*env;

	env = NULL;
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	env->name = NULL;
	env->data = NULL;
	env->next = NULL;
	return (env);
}

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

t_env		*ft_get(char *s1, int i)
{
	t_env	*new;

	new = ft_initialise();
	if (new == NULL)
		return (NULL);
	new->name = ft_strsub(s1, 0, i);
	new->data = ft_strsub(s1, i + 1, ft_strlen(s1) - (i + 1));
//	ft_printf("%s = %s\n", new->name, new->data);
	return (new);
}

void		ft_add(t_env **s, t_env *new)
{
	t_env	*tmp;

	tmp = *s;
	if (tmp)
	{
		while (tmp)
			tmp = tmp->next;
	}
	new->next = tmp;
	tmp = new;
	*s = tmp;
}

void		ft_dell(t_env **s)
{
	t_env	*tmp;

	while (*s)
	{
		tmp = (*s)->next;
		free((*s)->name);
		free((*s)->data);
		free(*s);
		(*s) = tmp;
	}
}

t_env		*ft_get_env(char **env)
{
	t_env	*s;
	t_env	*new;

	s = NULL;
	while (*env != NULL)
	{
		if (test(*env, "PWD", 3))
			new = ft_get(*env, 3);
		if (test(*env, "OLDPWD", 6))
			new = ft_get(*env, 6);
		if (test(*env, "HOME", 4))
			new = ft_get(*env, 4);
		if (test(*env, "PATH", 4))
			new = ft_get(*env, 4);
		if (test(*env, "USER", 4))
			new = ft_get(*env, 4);
		if (test(*env, "_=", 2))
			new = ft_get(*env, 1);
//		ft_printf("%s = %s\n", new->name, new->data);
		ft_add(&s, new);
		env++;
	}
	return (s);
}
