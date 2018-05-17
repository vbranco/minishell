/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 18:06:11 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/17 19:38:13 by vbranco     ###    #+. /#+    ###.fr     */
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
	int		i = 0;

	ft_initialise(&info);
	ft_getenv(&info, env);

	return  (0);
}
