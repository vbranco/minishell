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

t_env_head		*ft_initialise_head(void)
{
	t_env_head	*head;

	if (!(head = (t_env_head*)malloc(sizeof(t_env_head))))
		return (NULL);
	head->next = NULL;
	return (head);
}

void		ft_add(t_env **s, t_env *add)
{
	t_env	*tmp;

	tmp = *s;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add;
		add->next = NULL;
	}
	else
	{
		add->next = *s;
		*s = add;
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

void		ft_get_env(t_env_head *head, char **env)
{
	int		i;
	char	*var;
	char	*data;

	i = 0;
	if (*env == NULL)
		update_env(head, NULL);
	else
	{
		while (env[i])
		{
			ft_make_var_info(env[i], &var, &data);
			ft_create_var(head, var, data);
			free(var);
			free(data);
			i++;
		}
	}
}
