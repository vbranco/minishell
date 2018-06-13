/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 18:06:11 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/05 20:04:52 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

static	int		ft_count_nb_env(t_env *lst)
{
	int			i;

	i = 0;
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i + 1);
}

static	char	**making_env(t_env_head *head)
{
	char		**envi;
	char		tmp[1096];
	int			nb_env;
	int			i;
	t_env		*lst;

	i = 0;
	if (head->next == NULL)
		return (NULL);
	lst = head->next;
	nb_env = ft_count_nb_env(head->next);
	if (!(envi = (char**)malloc(sizeof(char*) * (nb_env + 1))))
		return (NULL);
	while (lst)
	{
		ft_bzero(tmp, 1096);
		ft_strcat(tmp, lst->name);
		ft_strcat(tmp, "=");
		ft_strcat(tmp, lst->data);
		envi[i] = ft_strdup(tmp);
		i++;
		lst = lst->next;
	}
	envi[i] = NULL;
	return	(envi);
}

void			print(char **env)
{
	int			i;

	i = 0;
	ft_printf("\n\n");
	while (env[i])
	{
		ft_printf("env >> %s\n", env[i]);
		i++;
	}
}

void			execute(t_env_head *head, char **parsed, int i)
{
	pid_t		pid;
	char		*exe;
	char		**environment;

	environment = NULL;

	exe = NULL;
	if (test_exe(head->next, parsed, i, &exe))
	{
		environment = making_env(head);
		pid = fork();
		if (pid < 0)
			ft_putendl_fd("ERROR FORK()", 2);
		if (pid == 0)
		{
			if (execve(exe, parsed, environment) == -1)//penser a gere le '~' EX: ls ~
			{
				ft_putstr_fd(parsed[0], 2);
				ft_putendl_fd(NO_CMD, 2);
				ft_free_2char(&environment);
				free(exe);
				exit(1);
			}
		}
		else
		{
			wait(&pid);
			ft_free_2char(&environment);
			free(exe);
		}
		return ;
	}
	else
	{
		ft_putstr_fd(parsed[i], 2);
		ft_putendl_fd(NO_CMD, 2);
		return ;
	}
}

int		built(t_env_head **head, char **parsed)
{
	if (*parsed == NULL)
		return (1);
	if (!ft_strcmp(*parsed, "env"))
		return (environment(*head, parsed));
	if (!ft_strcmp(*parsed, "echo"))
		return (echo(*head, parsed));
	if (!ft_strcmp(*parsed, "cd"))
		return (cd(*head, parsed));
	if (!ft_strcmp(*parsed, "setenv"))
		return (setenvi(*head, parsed));
	if (!ft_strcmp(*parsed, "unsetenv"))
		return (unsetenvi(*head, parsed));
	return (0);
}

void	minishell(t_env_head **head)
{
	char	*line;
	char	**parsed;

	line = NULL;
	parsed = NULL;
	while (101)
	{
		ft_printf("\e[0m$> ");
		get_next_line(0, &line);
//		parsed = ft_split(line);
		parsed = ft_parsed(*head, line);		
		if (!ft_strcmp(line, "exit"))// || !ft_strcmp(line, "\0"))
		{
			free(line);
			ft_free_2char(&parsed);
			break ;
		}
		built(head, parsed);
/*		if (built(head, parsed) == 0)
			execute(*head, parsed, 0);*/
		free(line);
		ft_free_2char(&parsed);
	}
}

int				main(int ac, char **av, char **env)
{
	t_env		*info;
	t_env_head	*head;

	(void)ac;
	(void)av;
	if (!(head = ft_initialise_head()))
		return (1);
	shell_top();
	ft_get_env(head, env);
	minishell(&head);
	ft_dell(&head);
	return (0);
}
