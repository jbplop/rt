/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiniau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 17:58:15 by jpiniau           #+#    #+#             */
/*   Updated: 2016/03/23 17:39:58 by jpiniau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		set_var(t_env *env, char *var, char *val)
{
	char	**tmp;

	if (!ft_strcmp(var, "name"))
		env->name = val;
	if (!ft_strcmp(var, "cam_pos"))
	{
		tmp = ft_strsplit(val, ' ');
		env->cam_pos.x = ft_atoi(tmp[0]);
		env->cam_pos.y = ft_atoi(tmp[1]);
		env->cam_pos.z = ft_atoi(tmp[2]);
	}
	if (!ft_strcmp(var, "cam_dir"))
	{
		tmp = ft_strsplit(val, ' ');
		env->cam_dir.x = ft_atoi(tmp[0]);
		env->cam_dir.y = ft_atoi(tmp[1]);
		env->cam_dir.z = ft_atoi(tmp[2]);
	}
	if (!ft_strcmp(var, "render"))
	{
		tmp = ft_strsplit(val, ' ');
		env->height = ft_atoi(tmp[0]);
		env->width = ft_atoi(tmp[1]);
	}
}

static void		set_scene(t_env *env, char *scene)
{
	char	*line;
	char	*var;
	char	*val;

	while(gnlv(scene, &line) != -1)
	{
		var = get_info(line, &val);
		set_var(env, ft_strtrim(var), val);
	}
	var = get_info(line, &val);
	set_var(env, ft_strtrim(var), val);
}

static void		get_scene(char *file, char **scene)
{
	int		i;

	*scene = ft_strdup(ft_strstr(file, "scene\n["));
	i = ft_strcchr(*scene, ']') - 1;
	*scene = ft_strncpy(*scene, *scene, i);
	*scene = *scene + 8;
}

static void		get_file(char *filename, char **file)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	*file = ft_strnew(0);
	if (fd >= 0)
	{
		while (get_next_line(fd, &line))
			*file = ft_strjoin3(*file, line, "\n");
		close(fd);
		free(line);
	}
}

void	init_env(t_env *env, char *filename)
{
	char *file;
	char *scene;

	(void)env;
	get_file(filename, &file);
	get_scene(file, &scene);
	set_scene(env, scene);
}
