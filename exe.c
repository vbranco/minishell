/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exe.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/28 19:46:28 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 17:23:18 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

static	int			try_exe_without_path(char *path, char **exe)
{
	char			*tmp;
	int				slach;

	slach = ft_count_p(path);
	tmp = ft_strsub(path, 0, slach);
	if (inside_dir(tmp, path, exe))
	{
		free (tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

static	int			not_in_exe_dir(char **path, char **parsed, char **exe)
{
	int				i;

	i = 0;
	if (path == NULL)
		return (try_exe_without_path(*parsed, exe));
	else
	{
		while (path[i])
		{
			if (inside_dir(path[i], *parsed, exe))
			{
				ft_free_2char(&path);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int					ft_teste_file_exe(char **exe)
{
	if (access(*exe, F_OK) || access(*exe, X_OK))
	{
		if (access(*exe, F_OK))
		{
			free(*exe);
			return (-2);
		}
		free(*exe);
		return (-1);
	}
	return (1);
}

int					test_exe(t_env *env, char **parsed, int index, char **exe)
{
	char			**path;
	char			*tmp;
	int				i;

//---------
//penser a gerer les PATH = NON /bin/ls
//et les trucs du main
	i = exec_in_dir(parsed, index, exe);
	if (i == 1)
		return (1);
	else if (i == -1)
		return (-1);
	i = 0;
	tmp = path_exist(env);
	path = ft_strsplit(tmp, ':');
	free(tmp);
	i = not_in_exe_dir(path, parsed, exe);
	if (i == 1)
		return (ft_teste_file_exe(exe));
	ft_free_2char(&path);
	return (0);
}
