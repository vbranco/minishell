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
	int			nb_env;
	int			i;
	t_env		*lst;

	lst = head->next;
	if (head->next == NULL)
		return (NULL);
	i = 0;
	nb_env = ft_count_nb_env(lst);
	ft_printf("nb_env >> %d\n", nb_env);
	if (!(envi = (char**)malloc(sizeof(char) * (nb_env + 1))))
		return (NULL);
	while (nb_env > 0)
	{
		if (lst->name)
		{
			envi[i] = ft_strdup(lst->name);
			envi[i] = ft_realloc(envi[i], "=");
		}
		if (lst->data)
			envi[i] = ft_realloc(envi[i], lst->data);
		i++;
		lst = lst->next;
		nb_env--;
	}
	envi[i] = NULL;
	return	(envi);
}

void			execute(t_env_head *head, char **parsed)
{
	pid_t		pid;
	char		*exe;
	char		**environment;

	environment = NULL;

	exe = NULL;
	if (test_exe(head->next, parsed, &exe))
	{
//		environment = making_env(head); //a traiter
		pid = fork();
		if (pid < 0)
			ft_putendl_fd("ERROR FORK()", 2);
		if (pid == 0)
		{
			//penser a changer environment suivant le flag env -i
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
		ft_putstr_fd(*parsed, 2);
		ft_putendl_fd(NO_CMD, 2);
		return ;
	}
}

int		built(t_env_head **head, char **parsed)
{
	if (*parsed == NULL)
		return (1);
	if (!ft_strcmp(*parsed, "env"))
	{
		if (!searching_on_env(*head, "PATH"))
		{
			ft_putendl_fd("env: Command not found", 2);
			return (1);
		}
		return (environment(*head, parsed));
	}
	if (ft_strcmp(*parsed, "echo") == 0)
		return (echo(*head, parsed));
	if (ft_strcmp(*parsed, "cd") == 0)
		return (cd(*head, parsed));
	if (ft_strcmp(*parsed, "setenv") == 0)
		return (setenvi(*head, parsed));
	if (ft_strcmp(*parsed, "unsetenv") == 0)
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
		ft_printf("$> ");
		get_next_line(0, &line);
		parsed = ft_split(line);
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			ft_free_2char(&parsed);
			break ;
		}
		if (built(head, parsed) == 0)
			execute(*head, parsed);
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
	if (!(head = (t_env_head*)malloc(sizeof(t_env_head))))
		return (0);
	info = ft_get_env(env);
	head->next = info;
	minishell(&head);
	ft_dell(&head);
	return (0);
}
