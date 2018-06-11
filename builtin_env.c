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

void			ft_make_var_info(char *s, char **var_name, char **var_data)
{
	int			i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	*var_name = ft_strsub(s, 0, i);
	*var_data = ft_strsub(s, i + 1, ft_strlen(s) - (i + 1));
}

static	void	ft_env_error(char *s)
{
	int			i;

	i = 0;
	if (s[i] == '-')
	{
		while (s[i] && s[i] == '-')
			i++;
		ft_putstr_fd("env: illegal option -- ", 2);
		ft_putendl_fd((s + i), 2);
		ft_putendl_fd(ENV_USAGE, 2);
	}
	else
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(s, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
}

int				environment(t_env_head *head, char **parsed)
{
	int			i;
	t_env_head	*exe_head;
	char		*var;
	char		*data;
	
	if (!(exe_head = ft_initialise_head()))
		return (1);
	i = 1;
	if (parsed[i] == NULL)
		ft_print_env(head);
	else if (!ft_strcmp(parsed[i], "-i"))
	{
		i++;
		if (parsed[i] != NULL)
		{
			while (parsed[i] && ft_strchr(parsed[i], '='))
			{
				ft_make_var_info(parsed[i], &var, &data);
				ft_create_var(exe_head, var, data); 
				free(var);
				free(data);
				i++;
			}
		}
		if (parsed[i] == NULL)
			ft_print_env(exe_head);
		else
			execute(exe_head, parsed, i);
		ft_dell(&exe_head);
	}
	else
		ft_env_error(parsed[i]);
	return (1);
}
