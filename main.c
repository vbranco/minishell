/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 18:06:11 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/19 18:33:39 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "mini.h"

void	execute(t_env *env, char **parsed)
{
	if (ft_strcmp(*parsed, "env") == 0)
		afficher_env(env);
	if (ft_strcmp(*parsed, "echo") == 0)
		echo(parsed);
/*	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_printf("ERROR FORK()\n");
	if (pid == 0)
		execve(parsed[0], parsed, NULL);
	else
		wait(&pid);
*/	return ;
}

void	minishell(t_env *env)
{
	char	*line;
	char	**parsed;

	line = NULL;
	parsed = NULL;
	while (101)
	{
		ft_printf("$> ");
		if (line != NULL)
		{
			free(line);
			line = NULL;
		}
		if (parsed != NULL)
		{
			ft_free_2char(parsed);
			parsed = NULL;
		}
		get_next_line(0, &line);
		if (ft_strcmp(line, "exit") == 0)
			break ;
		parsed = ft_strsplit(line, ' ');
		execute(env, parsed);
	}
	free(line);
	if (parsed)
		ft_free_2char(parsed);
}

int		main(int ac, char **av, char **env)
{
	t_env	*info;

	(void)ac;
	(void)av;
	info = ft_get_env(env);
//	afficher_env(info);
	minishell(info);
	ft_dell(&info);
	return (0);
}
