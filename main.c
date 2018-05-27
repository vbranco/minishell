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
	pid_t	pid;
	char	*exe;
	
	exe = NULL;
	if (test_exe(env, parsed, &exe))
	{
		pid = fork();
		if (pid < 0)
			ft_putendl_fd("ERROR FORK()", 2);
		if (pid == 0)
			execve(exe, parsed, NULL);
		else
			wait(&pid);
		free(exe);
		return ;
	}
	else
	{
		ft_putstr_fd(*parsed, 2);
		ft_putendl_fd(NO_CMD, 2);
		return ;
	}
}

int		built(t_env *envi, char **parsed)
{
	if (*parsed == NULL)
		return (1);
	if (ft_strcmp(*parsed, "env") == 0)
		return (environment(envi));
	if (ft_strcmp(*parsed, "echo") == 0)
		return (echo(parsed));
	if (ft_strcmp(*parsed, "cd") == 0)
		return (cd(envi, parsed));
	if (ft_strcmp(*parsed, "setenv") == 0)
		return (setenvi(envi, parsed));
	if (ft_strcmp(*parsed, "unsetenv") == 0)
		return (unsetenvi(envi, parsed));
	return (0);
}
/*
void	ft_free_line_parsed(char **line, char ***parsed)
{
	if (*line != NULL)
	{
		free(*line);
		*line = NULL;
	}
	if (*parsed != NULL)//pas trop sur de cette methode
	{
		ft_free_2char(parsed);
		*parsed = NULL;
	}
}
*/
void	minishell(t_env **env)
{
	char	*line;
	char	**parsed;
	int		i;

	line = NULL;
	parsed = NULL;
	while (101)
	{
		i = 0;
		ft_printf("$> ");
//		ft_free_line_parsed(&line, &parsed);
		if (line != NULL)
		{
			free(line);
			line = NULL;
		}
		if (parsed != NULL)
		{
			ft_free_2char(parsed);//j'ai des fuites memoire ici
			parsed = NULL;
/*			while (parsed[i])
			{
				free(parsed[i]);
				i++;
			}
			free(parsed);
//			ft_free_2char(&parsed);
			parsed = NULL;
*/		}
		get_next_line(0, &line);
		if (ft_strcmp(line, "exit") == 0)
			break ;
		parsed = ft_split(line);
		if (built(*env, parsed) == 0)
			execute(*env, parsed);
	}
	if (line)
		free(line);
	if (parsed != NULL)
	{
		ft_free_2char(parsed);
	}
}

int		main(int ac, char **av, char **env)
{
	t_env	*info;

	(void)ac;
	(void)av;
	info = ft_get_env(env);
	minishell(&info);
	ft_dell(&info);
	return (0);
}
