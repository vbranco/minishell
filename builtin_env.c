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
	//-----A GERER----
//	if (parsed[1] == NULL)
		ft_print_env(head);
//	else if (parsed[1][0] == '-')
//	else

//	if (test_env_flags(head, parsed)) //enlever pour tester!!!!
//		ft_printf("test_env_flags\n");
//		return (0);
//	ft_print_env(head);
	return (1);
}

void		update_env(t_env *env, char *pwd)
{
	t_env	*tmp;
	char	*datatmp;
	char	p[1096];

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD") == 0)
			break;
		tmp = tmp->next;
	}
	getcwd(p, 1096);
	datatmp = ft_strdup(tmp->data);
	free(tmp->data);
	tmp->data = ft_strdup(p);
	tmp = env;
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
