#include "mini.h"

char		*get_dir_from_env(t_env *env, char *looking)
{
	t_env	*tmp;
	char	*dir;

	tmp = env;
	dir = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, looking) == 0)
			dir = ft_strdup(tmp->data);
		tmp = tmp->next;
	}
	return (dir);
}

int		change_dir(t_env *env, char *dir)
{
	if ((chdir(dir)) == -1)
		return (ft_error(CD_NO_FILE, &dir, 0));
	update_env(env, dir);
	return (0);
}

char		*get_prev_dir(char **parsed, char *pwd)
{
	char	*dir;
	int		i;
	int		a;
	int		z;

	i = 0;
	a = 0;
	z = 0;
	dir = NULL;
	while (parsed[1][i] && parsed[1][i] == '.')
		i++;
	if (i >= 7)
		return (NULL);
	i--;
	if (i == 0)
		return (pwd);
	while (pwd[a])
	{
		if (pwd[a] == '/')
			z++;
		a++;
	}
	if (i >= z)
		return (ft_strdup("/"));//attention fuite de memoire
	else
	{
		a = ft_strlen(pwd) - 1;
		while (a >= 0)
		{
			if (pwd[a] == '/')
			{
				i--;
				if (i == 0)
				{
					dir = ft_strsub(pwd, 0, a);
					break ;
				}
			}
			a--;
		}
	}
	return (dir);
}

char		*get_dir_from_parsed(char **parsed, char *pwd)
{
	char	*dir;

	dir = NULL;
	if (parsed[1][0] != '/')
	{
		dir = ft_strdup(pwd);
		dir = ft_realloc(dir, "/");
		dir = ft_realloc(dir, parsed[1]);
	}
	else
		dir = ft_strdup(parsed[1]);
	return (dir);
}

char		*ft_get_dir(t_env *env, char **parsed, char *pwd)
{
	char	*dir;

	if (parsed[1] == NULL || (ft_strcmp(parsed[1], "~") == 0))
		return (dir = get_dir_from_env(env, "HOME"));
	else if (ft_strcmp(parsed[1], "-") == 0)
		return (dir = get_dir_from_env(env, "OLDPWD"));
	else if (parsed[1][0] == '.')
		return (dir = get_prev_dir(parsed, pwd));
	else
		return (dir = get_dir_from_parsed(parsed, pwd));
	return (dir);
}

int		ft_error(char *error_message, char **parsed, int index)
{

	ft_putstr_fd(error_message, 2);
	if (parsed != NULL)
		ft_putendl_fd(parsed[index], 2);
	else
		ft_putchar_fd('\n', 2);
	return (1);
}

int		cd(t_env *env, char **parsed)
{
	char	*pwd;
	int		args;
	char	*dir;

	dir = NULL;
	args = 0;
	pwd = NULL;
	while (parsed[args])
		args++;
	if (args > 3)
		return (ft_error(CD_TOO_ARGS, NULL, 0));
	pwd = getcwd(pwd, 10000);
	if (parsed[1] != NULL && parsed[2] != NULL)
		ft_error(CD_NOT_PWD, parsed, 1);//pas finalise, pas bonne erreur
	else
		dir = ft_get_dir(env, parsed, pwd);
	if (dir == NULL)
		return (ft_error(CD_NO_FILE, parsed, 1));
	change_dir(env, dir);
	(pwd != NULL) ? free(pwd) : 0;
	(dir != NULL) ? free(dir) : 0;
	return (1);
}
