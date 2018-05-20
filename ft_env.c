/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 18:06:15 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/17 19:38:14 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

static int  test(char *str, char *search, int i)
{
	char        tmp;

	tmp = str[i];
	str[i] = '\0';
	if (ft_strcmp(str, search) == 0)
	{
		str[i] = tmp;
		return (1);
	}
	str[i] = tmp;
	return (0);
}

void    ft_getenv(t_inf *info, char **env)
{
	int     i;

	i = 0;
	while (env[i])
	{
		if (test(env[i], "PWD", 3) == 1)
			info->pwd = ft_strsub(env[i], 4, ft_strlen(env[i]) - 4);
		if (test(env[i], "OLDPWD", 6) == 1)
			info->oldpwd = ft_strsub(env[i], 7, ft_strlen(env[i]) - 7);
		if (test(env[i], "HOME", 4) == 1)
			info->home = ft_strsub(env[i], 5, ft_strlen(env[i]) - 5);
		if (test(env[i], "PATH", 4) == 1)
			info->path = ft_strsub(env[i], 5, ft_strlen(env[i]) - 5);
		if (test(env[i], "USER", 4) == 1)
			info->user = ft_strsub(env[i], 5, ft_strlen(env[i]) - 5);
		if (test(env[i], "_", 1) == 1)
			info->lastcmd = ft_strsub(env[i], 2, ft_strlen(env[i]) - 2);
		i++;
	}
}
