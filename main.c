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

void	execute(char *line)
{
	(void)line;
	pid_t	pid;

	ft_printf("%s\n", line);
	pid = fork();
	if (pid < 0)
		ft_printf("ERROR FORK()\n");
	if (pid == 0)
		execve("/bin/ls", NULL, NULL);
	else
	wait(&pid);
	return ;
}

void	minishell(void)
{
	char	*line;
	int		ret;
//	char	*av[] = {"ls", "-l", NULL};

	while (101)
	{
		ft_printf("$> ");
		if ((ret = get_next_line(STDIN_FILENO, &line)) == 0)
			break;
		ft_printf("ici");
		ft_printf("%s", line);
		execute(line);
	}
}

int		main(int ac, char **av, char **env)
{
	t_env	*info;

	(void)ac;
	(void)av;
	info = ft_get_env(env);
	minishell();
	return (0);
}
