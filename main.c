/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 18:06:11 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/19 19:57:42 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

/*
** en cours de dev
static	void	ft_updating_last_cmd(t_env_head *head, char **parsed)
{
	t_env		*tmp;

	tmp = head->next;
//	if (!tmp)
}
*/
//--supp
void			print(char **env)
{
	int			i;

	i = 0;
	ft_printf("\n\n");
	while (env[i])
	{
		ft_printf("env >> %s\n", env[i]);
		i++;
	}
}
//-----

int		built(t_env_head *head, char **parsed)
{
	if (parsed == NULL)
		return (1);
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

void	minishell(t_env_head *head)
{
	char	*line;
	char	**parsed;

	line = NULL;
	parsed = NULL;
	while (101)
	{
		print_prompt(head);
		get_next_line(0, &line);
//while a rajouter ici au cas ou ';' pour gerer plusiers cmd || voir pour utiliser 3 dimensions dans le parsed
		parsed = ft_parsed(head, line);
		if (!ft_strcmp(line, "exit"))// || !ft_strcmp(line, "\0"))
		{
			free(line);
			ft_free_2char(&parsed);
			break ;
		}
		if (built(head, parsed) == 0)
			execute(head, parsed, 0);
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
		return (1);
	shell_top();
	ft_get_env(head, env);
	minishell(head);
	ft_dell(&head);
	return (0);
}
