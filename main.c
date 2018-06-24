/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/17 18:06:11 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/19 19:57:42 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

//--supp
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
//-----

int		built(t_env_head *head, char **parsed)
{
	if (parsed == NULL)
		return (1);
	else
	{
		if (searching_on_env(head, "_"))
			ft_updating_var(head, "_", *parsed);
		else
			ft_create_var(head, "_", *parsed);
	}
	if (!ft_strcmp(*parsed, "env"))
		return (environment(head, parsed));
	if (!ft_strcmp(*parsed, "echo"))
		return (echo(head, parsed));
	if (!ft_strcmp(*parsed, "cd"))
		return (cd(head, parsed));
	if (!ft_strcmp(*parsed, "setenv"))
		return (setenvi(head, parsed));
	if (!ft_strcmp(*parsed, "unsetenv"))
		return (unsetenvi(head, parsed));
	return (0);
}

static	int		g_line(char **line)
{
	char		buf[SIZE];
	int			ret;
	char		*tmp;
	char		*test;
	int			i;
	char		*swap;

	if (!line || (read(0, buf, 0) == -1))
		return (-1);
	tmp = ft_strnew(SIZE);
	while ((ret = read(0, buf, SIZE)))
	{
		i = 0;
		buf[ret] = '\0';
		test = ft_strdup(buf);
		if ((i = (int)ft_strchr(test, '\n')))
		{
//			printf("i >> %d\n", i - (int)test);
//			printf("test[i] >> %c", test[i - (int)test]);
			swap = ft_strsub(test, 0, i - (int)test);
			tmp = ft_realloc(tmp, swap);
//			free(test);
//			free(swap);
			break ;
		}
		else
		{
			tmp = ft_realloc(tmp, test);
//			free(test);
		}
	}
	printf("tmp > %s\n", tmp);
	*line = tmp;
//	*line = ft_strdup(tmp);
//	free(tmp);
//	printf("a la fin de g_line\n");
	return (1);
}

void			minishell(t_env_head *head)
{
	char		*line;
	char		**parsed;

	line = NULL;
	parsed = NULL;
	while (101)
	{
		print_prompt(head);
//		get_next_line(0, &line);//modifier
		g_line(&line);
		printf("juste apres g_line dans while minishell\n");
		printf("line >> %s\n", line);//supprimer
//		free(line);//supprimer
//while a rajouter ici au cas ou ';' pour gerer plusiers cmd || voir pour utiliser 3 dimensions dans le parsed
/*		parsed = ft_parsed(head, line);
		if (!ft_strcmp(line, "exit"))// || !ft_strcmp(line, "\0"))
		{
			free(line);
			ft_free_2char(&parsed);
			break ;
		}
		if (built(head, parsed) == 0)
			execute(head, parsed, 0);
		free(line);
		ft_free_2char(&parsed);*/
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
	minishell(head);
	ft_dell(&head);
	return (0);
}
