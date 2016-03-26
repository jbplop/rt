/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiniau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 15:22:26 by jpiniau           #+#    #+#             */
/*   Updated: 2016/03/26 19:19:32 by jpiniau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char *get_info(char *line, char **dst);

int		ft_key_hook(int keycode, t_env *env) //static
{
		(void)env;
		ft_putnbr(keycode);
		if (keycode == 53)
			exit(0);
		return (0);
}

void	affich_obj(t_env env)
{
	t_obj	*obje;

	obje = env.obj;
	while (obje)
	{
		ft_putendl(obje->ref);
		obje = obje->next;
	}
}

int		main(int ac, char **av)
{
	t_env	env;

	(void)ac;
	init_env(&env, av[1]);
	ft_putendl("PLANTE STP FDP!!");
	init_content(&env, av[1]);
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, env.height, env.width, env.name);
	env.img = mlx_new_image(env.mlx, env.height, env.width);
	mlx_key_hook(env.win, ft_key_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
