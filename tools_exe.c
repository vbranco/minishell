/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_exe.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/27 20:00:23 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/27 20:00:24 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

int					ft_count_p(char *s)
{
	int				i;
	int				a;

	i = 0;
	a = 0;
	while (s[i])
	{
		if (s[i] == '/')
			a = i;
		i++;
	}
	return (a);
}

int					exec_in_dir(char **parsed, int index, char **exe)
{
	char			pwd[1096];
	int				p;

	p = 0;
	if (*parsed[index] == '.')
	{
		p = ft_count_p(parsed[index]);
		getcwd(pwd, 1096);
		*exe = get_prev_dir(parsed, pwd, index);
		*exe = ft_strjoin(*exe, &parsed[index][p]);
		return (ft_teste_file_exe(exe));
	}
	return (0);
}

char				*path_exist(t_env *env)
{
	t_env			*tmp;
	char			*data;

	data = NULL;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PATH") == 0)
		{
			data = ft_strdup(tmp->data);
			return (data);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char				*making_path(char *s1, char *s2, int i)
{
	char			*tmp;

	tmp = ft_memalloc(1024);
	if (i)
	{
		ft_strcat(tmp, s1);
		ft_strcat(tmp, "/");
	}
	ft_strcat(tmp, s2);
	return (tmp);
}

int					inside_dir(char *path_dir, char *parsed, char **ret)
{
	DIR				*dir;
	struct dirent	*pdir;
	char			*path;
	char			*exe;

	if (!(dir = opendir(path_dir)))
		return (0);
	while ((pdir = readdir(dir)) != NULL)
	{
		path = making_path(path_dir, pdir->d_name, 1);
		if (parsed[0] != '/')
			exe = making_path(path_dir, parsed, 1);
		else
			exe = making_path(path_dir, parsed, 0);
		if (ft_strcmp (path, exe) == 0)
		{
			*ret = ft_strdup(exe);
			closedir(dir);
			free(path);
			free(exe);
			return (1);
		}
		free(path);
		free(exe);
	}
	closedir(dir);
	return (0);
}
