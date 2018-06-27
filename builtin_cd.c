/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_cd.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/02 10:26:07 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/27 19:58:44 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

static	int		change_dir(t_env_head *head, char **parsed, char *dir)
{
	char		p[1096];

	getcwd(p, 1096);
	if (!dir)
	{
		return (ft_error(CD_NO_FILE, parsed, 1));
	}
	if (access(dir, F_OK))
	{
		return (ft_error(CD_NO_FILE, parsed, 1));
	}
	else if (looking_stat(dir))
	{
		return (ft_error(CD_NO_DIR, &dir, 0));
	}
	else if (access(dir, X_OK))
		return (ft_error(CD_DENIED, parsed, 1));
	if ((chdir(dir)) == -1)
		return (ft_error("CHDIR: cannot open: ", parsed, 1));
	update_env(head, p);
	return (0);
}

char			*ft_get_dir(t_env *env, char **parsed, char *pwd, char **error_message)
{
	char		*dir;
	int			i;
	int			flag;

	flag = 0;
	i = 0;
	if (parsed[1] == NULL || (ft_strcmp(parsed[1], "~") == 0))
		return (dir = get_dir_from_env(env, "HOME", error_message));
	else if (ft_strcmp(parsed[1], "-") == 0)
		return (dir = get_dir_from_env(env, "OLDPWD", error_message));
	else
	{
		ft_get_index_flag(parsed, &i, &flag);
		if (flag == -1)
			return (NULL);
//		return(dir = get_stat(parsed, i, flag, pwd));//a voir comment gerer pour recuperer le bon path en cas de cd -L sur lien symbolique
		return (dir = ft_strdup(parsed[i]));
	}
}

int				cd(t_env_head *head, char **parsed)
{
	char		pwd[1096];
	int			args;
	char		*dir;
	char		*error_message;
	t_env		*env;

	env = head->next;
	dir = NULL;
	error_message = NULL;
	args = ft_count_args_shell(parsed);
	if (args >= 3)
		return (ft_error(CD_TOO_ARGS, NULL, 0));
	getcwd(pwd, 1096);
	dir = ft_get_dir(env, parsed, pwd, &error_message);
	if (error_message)
		ft_putendl_fd(error_message, 2);
	else
		change_dir(head, parsed, dir);
	if (dir)
		free(dir);
	if (error_message)
		free(error_message);
	return (1);
}
