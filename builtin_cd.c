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
	if (ft_strcmp(looking, "HOME"))
		ft_printf("%s\n", dir);
	return (dir);
}

int		change_dir(t_env *env, char **parsed, char *dir)
{
	if ((chdir(dir)) == -1)
	{
		//chercher si permission denied ou dossier inexistant ou fichier
		return (ft_error(CD_NO_FILE, parsed, 1));
	}
	update_env(env, dir);
	return (0);
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
		return (dir = get_prev_dir(parsed, pwd, 1));
	else
		return (dir = get_dir_from_parsed(parsed, pwd));
	return (dir);
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
	(pwd != NULL) ? free(pwd) : 0;
	dir = ft_get_dir(env, parsed, pwd);
	if (dir == NULL)
		return (ft_error(CD_NO_FILE, parsed, 1));
	change_dir(env, parsed, dir);
	(ft_strcmp(dir, pwd)) ? free(dir) : 0;
	return (1);
}
