/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:23:13 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/26 21:03:07 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

void free_sprites(t_game *game)
{
	ft_printf("Deestroying images...\n");
	if (game->sprites->player)
	{
		ft_printf("Destroying image player.\n");
		mlx_destroy_image(game->data.mlx_ptr, game->sprites->player);
	}
	if (game->sprites->wall)
	{
		mlx_destroy_image(game->data.mlx_ptr, game->sprites->wall);
		ft_printf("Destroying image wall.\n");
	}
	if (game->sprites->empty)
		mlx_destroy_image(game->data.mlx_ptr, game->sprites->empty);
	if (game->sprites->collectible)
		mlx_destroy_image(game->data.mlx_ptr, game->sprites->collectible);
	if (game->sprites->exit)
		mlx_destroy_image(game->data.mlx_ptr, game->sprites->exit);
	if (game->sprites->free_exit)
		mlx_destroy_image(game->data.mlx_ptr, game->sprites->free_exit);
	free(game->sprites);
}

void free_player_sprites(t_game *game)
{
	ft_printf("Destroying player sprites...\n");
	if (game->player_sprites->up_stand)
	{
		mlx_destroy_image(game->data.mlx_ptr, game->player_sprites->up_stand);
		ft_printf("Destroyed up_stand sprite.\n");
	}
	if (game->player_sprites->up_walk)
	{
        mlx_destroy_image(game->data.mlx_ptr, game->player_sprites->up_walk);
        ft_printf("Destroyed up_walk sprite.\n");
    }
    if (game->player_sprites->up_walk2)
	{
        mlx_destroy_image(game->data.mlx_ptr, game->player_sprites->up_walk2);
        ft_printf("Destroyed up_walk2 sprite.\n");
    }
    if (game->player_sprites->down_stand)
	{
        mlx_destroy_image(game->data.mlx_ptr, game->player_sprites->down_stand);
        ft_printf("Destroyed down_stand sprite.\n");
    }
    if (game->player_sprites->down_walk)
	{
        mlx_destroy_image(game->data.mlx_ptr, game->player_sprites->down_walk);
        ft_printf("Destroyed down_walk sprite.\n");
    }
    if (game->player_sprites->down_walk2) {
        mlx_destroy_image(game->data.mlx_ptr, game->player_sprites->down_walk2);
        ft_printf("Destroyed down_walk2 sprite.\n");
    }
    if (game->player_sprites->left_stand)
	{
        mlx_destroy_image(game->data.mlx_ptr, game->player_sprites->left_stand);
        ft_printf("Destroyed left_stand sprite.\n");
    }
    if (game->player_sprites->left_walk) {
        mlx_destroy_image(game->data.mlx_ptr, game->player_sprites->left_walk);
        ft_printf("Destroyed left_walk sprite.\n");
    }

    if (game->player_sprites->right_stand) {
        mlx_destroy_image(game->data.mlx_ptr, game->player_sprites->right_stand);
        ft_printf("Destroyed right_stand sprite.\n");
    }
    if (game->player_sprites->right_walk) {
        mlx_destroy_image(game->data.mlx_ptr, game->player_sprites->right_walk);
        ft_printf("Destroyed right_walk sprite.\n");
    }
	free(game->player_sprites);
	ft_printf("Player sprites freed.\n");
}

void free_map(char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	deinit(char **map, char *file_content, t_game *game)
{
	ft_printf("Inside deinit function.\n");
	free_sprites(game);
	free_player_sprites(game);
	free_map(map);
	if (file_content)
		free(file_content);
	if (game->data.win_ptr)
		mlx_destroy_window(game->data.mlx_ptr, game->data.win_ptr);
	if (game->data.mlx_ptr)
		mlx_destroy_display(game->data.mlx_ptr);
	free(game);
}