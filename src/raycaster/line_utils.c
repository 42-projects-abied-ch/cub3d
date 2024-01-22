/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:50:31 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/22 16:56:57 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	set_shortest_line_vars(t_data *data, float min, t_line line, float hit)
{
	data->min_distance = min;
	data->hit_pos = hit;
	line.scale = MAPSIZE;
	data->hit = line.hit;
	data->shortest_line = line;
}

void	set_line_vars(t_line *line, int size)
{
	line->step = 0;
	line->neg_size = -(size / 2) - 1;
	line->x_step = line->x1 - line->x0;
	line->y_step = line->y1 - line->y0;
	line->max = fmax(fabs(line->x_step), fabs(line->y_step));
	line->x_step /= line->max;
	line->y_step /= line->max;
}

void	get_line(t_line *line, t_raycast ray, t_data *data)
{
	line->x0 = data->player.x_pos * SCALE;
	line->y0 = data->player.y_pos * SCALE;
	line->x1 = ray.reach_x * SCALE;
	line->y1 = ray.reach_y * SCALE;
	line->hit = ray.hit;
	line->scale = SCREEN;
}

void	get_3d_line(t_line *line, int i, t_data *data)
{
	line->x0 = i * ((float)SCREEN_WIDTH / 120);
	line->x1 = i * ((float)SCREEN_WIDTH / 120);
	line->y0 = data->line_offset;
	line->y1 = data->line_height * ((float)SCREEN_HEIGHT2 / 120)
		+ data->line_offset;
	line->wall_height = data->line_height;
	line->scale = SCREEN;
}

void	scale_line_to_minimap(t_line *line)
{
	line->x0 = line->x0 / SCALE * 10;
	line->x1 = line->x1 / SCALE * 10;
	line->y0 = line->y0 / SCALE * 10;
	line->y1 = line->y1 / SCALE * 10;
}
