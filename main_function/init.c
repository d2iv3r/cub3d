/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efarhat <efarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:29:10 by mel-harc          #+#    #+#             */
/*   Updated: 2023/09/17 11:49:07 by efarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_angle(t_map *s)
{
	if (s->tmap->pos == 'S')
		s->ongl = 90 * (M_PI / 180);
	if (s->tmap->pos == 'W')
		s->ongl = 180 * (M_PI / 180);
	if (s->tmap->pos == 'E')
		s->ongl = 0;
	if (s->tmap->pos == 'N')
		s->ongl = 270 * (M_PI / 180);
	s->rotation_speed = 2 * (M_PI / 180);
	s->fov = 60 * (M_PI / 180);
	s->move_speed = GRID / 15;
	s->lr_view = 0;
	s->ud_walk = 0;
	s->lr_walk = 0;
}

void	init_value(t_map *s)
{
	init_angle(s);
	get_space(s);
	s->ptr_mlx = mlx_init(s->weight, s->height, "cub3d", true);
	if (!s->ptr_mlx)
		ft_error("Error\nmlx_init", 1, 0);
	s->img = mlx_new_image(s->ptr_mlx, s->weight, s->height);
	if (!s->img)
		ft_error("Error\nmlx_new_imge", 1, 0);
	s->window = mlx_image_to_window(s->ptr_mlx, s->img, 0, 0);
	if (s->window < 0)
		ft_error("Error\nmlx_imge_to window", 1, 0);
	drawing_img(s);
	player_pos(s);
	pixels_player(s, s->px, s->py);
}

void	put_line(t_point *p, t_map *s, float distance)
{
	p->x2 = s->px + (cos(s->ongl) * distance);
	p->y2 = s->py + (sin(s->ongl) * distance);
	p->dx = p->x2 - s->px;
	p->dy = p->y2 - s->py;
	if (_abs(p->dy) > _abs(p->dx))
		p->steps = _abs(p->dy);
	else
		p->steps = _abs(p->dx);
	p->xinc = p->dx / (float)p->steps;
	p->yinc = p->dy / (float)p->steps;
}

void	player_pos(t_map *s)
{
	int	i;
	int	j;

	i = -1;
	s->px = 0;
	s->py = 0;
	while (s->tmap->map[++i])
	{
		j = -1;
		while (s->tmap->map[i][++j])
		{
			if (s->tmap->map[i][j] == 'S' || s->tmap->map[i][j] == 'W' || \
				s->tmap->map[i][j] == 'E' || s->tmap->map[i][j] == 'N')
			{
				s->px = j * GRID;
				s->py = i * GRID;
			}
		}
	}
}

void	put_rays(t_map *s, float angle, double distance)
{
	t_point	p;

	p.x2 = s->px + (cos(angle) * distance);
	p.y2 = s->py + (sin(angle) * distance);
	p.dx = p.x2 - s->px;
	p.dy = p.y2 - s->py;
	if (_abs(p.dy) > _abs(p.dx))
		p.steps = _abs(p.dy);
	else
		p.steps = _abs(p.dx);
	p.xinc = p.dx / (float)p.steps;
	p.yinc = p.dy / (float)p.steps;
	p.x = s->px;
	p.y = s->py;
	put_line(&p, s, distance);
}
