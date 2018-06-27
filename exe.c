/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exe.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/28 19:46:28 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/27 18:55:52 by vbranco     ###    #+. /#+    ###.fr     */
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
				return (ft_teste_file_exe(exe));
			}
			i++;
		}
	}
	return (0);
}

int					ft_teste_file_exe(char **exe)
{
	struct stat		st;
	int				i;

	i = 0;
	if (!access(*exe, F_OK))
	{
		if (lstat(*exe, &st) != 0)
		{
			ft_putendl_fd("ERROR de lstat", 2);
			free(*exe);
			return (-2);
		}
		if (S_ISREG(st.st_mode))
		{
			if (!access(*exe, X_OK))
				return (1);
			else
			{
				free(*exe);
				return (-1);
			}
		}
	}
	free(*exe);
	return (-2);
}

static	int			exe_insert_by_user(char **parsed, char **exe)
{
	if (*parsed[0] == '/')
	{
		*exe = ft_strdup(*parsed);
		return (ft_teste_file_exe(exe));
	}
	return (0);
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
	if (i)
		return (i);
	tmp = path_exist(env);
	path = ft_strsplit(tmp, ':');
	free(tmp);
	i = not_in_exe_dir(path, parsed, exe);
	if (i)
		return (i);
	ft_free_2char(&path);
	i = exe_insert_by_user(parsed, exe);
	if (i)
		return (i);
	return (0);
}
