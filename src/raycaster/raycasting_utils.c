/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:50 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/21 09:55:15 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void get_line(t_line *line, t_raycast ray, t_data *data)
{
	if (ray.hit_status != SUCCESS)
	{
		line->status = NO_WALL_HIT;
		return ;
	}
	line->x0 = data->player.x_pos * data->x_scale;
	line->y0 = data->player.y_pos * data->y_scale;
	line->x1 = ray.reach_x * data->x_scale;
	line->y1 = ray.reach_y * data->y_scale;
	line->scale = SCREEN;
}

void get_3d_line(t_line *line1, int i, t_data *data)
{
	line1->x0 = i * ((float)SCREEN_WIDTH / 120);
	line1->x1 = i * ((float)SCREEN_WIDTH / 120);
	line1->y0 = data->line_offset;
	line1->y1 = data->line_height  * ((float)SCREEN_HEIGHT2 / 120) + data->line_offset;
	line1->scale = SCREEN;
}

void adjust_vars(t_data *data, float angle)
{
	data->fisheye = data->player.angle - angle;
	data->fisheye = fmod(data->fisheye + PI, 2 * PI) - PI;
	data->min_distance *= cos(data->fisheye);
	data->line_height = SCREEN_HEIGHT2 / (data->min_distance / 4);
	if (data->line_height > SCREEN_HEIGHT2)
		data->line_height = SCREEN_HEIGHT2;
	data->line_offset = ((float)SCREEN_HEIGHT2 / 2) - (data->line_height * WALL_HEIGHT);
}

float	dist(t_line line)
{
	return (sqrt((line.x1 - line.x0) * (line.x1 - line.x0) +
				(line.y1 - line.y0) * (line.y1 - line.y0)));
}

void	calculate_distance(t_data *data, t_line line1, t_line line2)
{
	float min_dist1;
	float min_dist2;	
	
	min_dist1 = dist(line1);
	min_dist2 = dist(line2);
	if (min_dist1 < min_dist2)
	{
		data->hit = NORTH;
    	data->min_distance = min_dist1;
    	line1.scale = MAPSIZE;
    	data->shortest_line = line1;
	}
	else
	{
		data->hit = EAST;
    	data->min_distance = min_dist2;
    	line2.scale = MAPSIZE;
    	data->shortest_line = line2;
	}
	printf("x0 = %f --", data->shortest_line.x0);
	printf("y0 = %f --", data->shortest_line.y0);
	printf("x1 = %f --", data->shortest_line.x1);
	printf("y1 = %f\n", data->shortest_line.y1);
}
