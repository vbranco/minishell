/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_env.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/04 17:56:33 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/05 20:04:51 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

int			ft_print_env(t_env_head *head)
{
	t_env	*s;

	s = head->next;
	if (s)
	{
		while (s)
		{
			ft_printf("%s=%s\n", s->name, (s->data == NULL) ? "\0" : s->data);
			s = s->next;
		}
	}
	return (1);
}

int			test_env_flags(t_env_head *head, char **parsed)
{
	char	*tmp;

	if (parsed[1])
	{
		if (!ft_strcmp(parsed[1], "-i"))
		{
			if (access(parsed[2], X_OK))
				return (1);
//			if (searching_on_env(head->next, parsed[2]))
		}

	}
	free(tmp);
	return (0);
}

int			environment(t_env_head *head, char **parsed)
{
	int		i;

	i = 1; // a voir pour l'indice
	//-----A GERER----
	if (parsed[1] == NULL)
		ft_print_env(head);
/*	else if (!ft_strcmp(parsed[1], "-i"))
	{
		i++;
		while (parsed[i])
		{
			if (test_exe())
			i++;
		}

	}*/
//	else

//	if (test_env_flags(head, parsed)) //enlever pour tester!!!!
//		ft_printf("test_env_flags\n");
//		return (0);
//	ft_print_env(head);
	return (1);
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

void			ft_create_var(t_env_head *head, char *var, char *dir)
{
	t_env		*add;
	t_env		*env;

	add = ft_initialise();
	add->name = ft_strdup(var);
	add->data = ft_strdup(dir);
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
