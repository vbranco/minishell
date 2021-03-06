/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 18:06:11 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 14:13:13 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

int				built(t_env_head *head, char **parsed)
{
	if (parsed == NULL)
		return (1);
	else
	{
		if (searching_on_env(head, "_"))
			ft_updating_var(head, "_", *parsed);
		else
			ft_create_var(head, "_", *parsed);
	}
	if (!ft_strcmp(*parsed, "env"))
		return (environment(head, parsed));
	if (!ft_strcmp(*parsed, "echo"))
		return (echo(head, parsed));
	if (!ft_strcmp(*parsed, "cd"))
		return (cd(head, parsed));
	if (!ft_strcmp(*parsed, "setenv"))
		return (setenvi(head, parsed));
	if (!ft_strcmp(*parsed, "unsetenv"))
		return (unsetenvi(head, parsed));
	return (0);
}

static	char	*g_line(void)
{
	char		buf[SIZE];
	int			ret;
	char		*tmp;

	if ((read(0, buf, 0) == -1))
		return (NULL);
	tmp = ft_memalloc(SIZE + 1);
	while ((ret = read(0, buf, SIZE)))
	{
		buf[ret] = '\0';
		if (buf[0] == '\n')
			break ;
		tmp = ft_realloc(tmp, buf);
	}
	if (ret == 0)
		tmp = ft_strdup("exit");
	return (tmp);
}

void			minishell(t_env_head *head)
{
	char		*line;
	char		**parsed;

	line = NULL;
	parsed = NULL;
	while (101)
	{
		print_prompt(head);
		line = g_line();
		parsed = ft_parsed(head, line);
		if (parsed && *parsed)
		{
			if (parsed && !ft_strcmp(*parsed, "exit"))
			{
				free(line);
				ft_free_2char(&parsed);
				break ;
			}
			if (built(head, parsed) == 0)
				execute(head, parsed, 0);
		}
		free(line);
		ft_free_2char(&parsed);
	}
}

int				main(int ac, char **av, char **env)
{
	t_env		*info;
	t_env_head	*head;

	(void)ac;
	(void)av;
	if (!(head = ft_initialise_head()))
		return (0);
	shell_top();
	ft_get_env(head, env);
	minishell(head);
	ft_dell(&head);
	return (0);
}
