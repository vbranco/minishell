/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 18:06:11 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/19 16:27:47 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "mini.h"

void	name(char *path, char *line)
{
	while (*line)
	{
		*path = *line;
		path++;
		line++;
	}
	*(path) = '\0';
}

int		main(int ac, char **av, char **env)
{
	t_inf	info;
	pid_t	f;
	int		i;

	f = fork();
	i = 0;
	(void)ac;
//	(void)av;
	ft_initialise(&info);
	ft_getenv(&info, env);
	if (f > 0)
	{
		while (i < 3)
		{
			ft_printf("$> ");
			wait(NULL);
			i++;
		}
	}
	else
	{
		execve("/bin/ls", av, env);
	}
	return  (0);
}
