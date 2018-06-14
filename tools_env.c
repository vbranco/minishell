#include "mini.h"

void			update_env(t_env_head *head, char *dir)
{
	char		p[1096];

	getcwd(p, 1096);
	if (searching_on_env(head, "PWD"))
		ft_updating_var(head, "PWD", p);
	else
		ft_create_var(head, "PWD", p);
	if (searching_on_env(head, "OLDPWD"))
		ft_updating_var(head, "OLDPWD", dir);
	else
		ft_create_var(head, "OLDPWD", p);
}

void			ft_updating_var(t_env_head *head, char *var, char *dir)
{
	t_env		*env;

	if (!dir)
		return ;
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

	add = ft_initialise();
	add->name = ft_strdup(var);
	add->data = ft_strdup(data);
	ft_add(head, add);
}
