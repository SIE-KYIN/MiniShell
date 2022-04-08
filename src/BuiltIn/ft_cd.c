/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:16:22 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 01:40:29 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_next_dir(char *arg, t_list *env)
{
	char	*nextdir;

	if (!arg)
		nextdir = search_node(env, "HOME")->data;
	else if (!ft_strcmp(arg, "-"))
	{
		nextdir = search_node(env, "OLDPWD")->data;
		printf("%s\n", nextdir);
	}
	else
		nextdir = arg;
	return (nextdir);
}

static void	set_env(t_list *env, char *newdir)
{
	t_list_node	*pwd;
	t_list_node	*old_pwd;

	pwd = search_node(env, "PWD");
	old_pwd = search_node(env, "OLDPWD");
	if (!old_pwd)
		add_node(env, env->cnt, "OLDPWD", pwd->data);
	else
	{
		free(old_pwd->data);
		old_pwd->data = pwd->data;
	}
	pwd->data = ft_strdup(newdir);
}

int	ft_cd(char *argv[], t_list *env)
{
	char	dir[512];
	char	*nextdir;

	getcwd(dir, sizeof(dir));
	nextdir = get_next_dir(argv[1], env);
	if (chdir(nextdir) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", nextdir);
		strerror(errno);
		return (errno);
	}
	if (!getcwd(dir, sizeof(dir)))
	{
		strerror(errno);
		return (errno);
	}
	getcwd(dir, sizeof(dir));
	set_env(env, dir);
	return (0);
}
