#include "mini.h"

void			update_env(t_env_head *head, char *dir)
{
	char		p[1096];

	getcwd(p, 1096);
	if (searching_on_env(head, "OLDPWD"))
		ft_updating_var(head, "OLDPWD", dir);
	else
		ft_create_var(head, "OLDPWD", p);
	if (searching_on_env(head, "PWD"))
		ft_updating_var(head, "PWD", p);
	else
		ft_create_var(head, "PWD", p);
}

void			ft_updating_var(t_env_head *head, char *var, char *dir)
{
	t_env		*env;

	env = head->next;
	while (env)
	{
		if (!ft_strcmp(env->name, var))
			break ;
		env = env->next;
	}
	free(env->data);
	env->data = ft_strdup(dir); 
}

void			ft_create_var(t_env_head *head, char *var, char *data)
{
	t_env		*add;
	t_env		*env;

	add = ft_initialise();
	add->name = ft_strdup(var);
	add->data = ft_strdup(data);
	if (head->next != NULL)
	{
		env = head->next;
		while (env)
		{
			if (env->next == NULL)
				break ;
			env = env->next;
		}
		env->next = add;
	}
	else
		head->next = add;
}
