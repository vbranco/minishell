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

void		ft_add(t_env **s, t_env *new)
{
	t_env	*tmp;

	tmp = *s;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
	else
	{
		new->next = *s;
		*s = new;
	}
}

void		ft_dell(t_env_head **head)
{
	t_env	*tmp;
	t_env	*s;

	s = (*head)->next;
	while (s)
	{
		tmp = (s)->next;
		free((s)->name);
		free((s)->data);
		free(s);
		(s) = tmp;
	}
	s = NULL;
	free(*head);
	head = NULL;

}

void		ft_get(t_env **s, char *s1, int i)
{
	t_env	*new;

	new = ft_initialise();
	if (new == NULL)
		return ;
	new->name = ft_strsub(s1, 0, i);
	new->data = ft_strsub(s1, i + 1, ft_strlen(s1) - (i + 1));
	ft_add(s, new);
}

t_env		*update(t_env *current)
{
	t_env	*p;
	t_env	*o;
	char	pwd[1096];

	p = ft_initialise();
	if (current == NULL)
	{
		getcwd(pwd, 1096);
		p->name = ft_strdup("PWD");
		p->data = ft_strdup(pwd);
		o = ft_initialise();
		o->name = ft_strdup("OLDPWD");
		o->data = ft_strdup(pwd);
		p->next = o;
	}
	return (p);
}

t_env		*ft_get_env(char **env)
{
	t_env	*s;
	int		i;
	int		a;

	s = NULL;
	i = 0;
	if (*env == NULL)
		s = update(s);
	else
	{
		while (env[i])
		{
			a = 0;
			while (env[i][a] && env[i][a] != '=')
				a++;
			ft_get(&s, env[i], a);
			i++;
		}
	}
	return (s);
}
