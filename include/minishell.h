/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:45:30 by alfreire          #+#    #+#             */
/*   Updated: 2024/07/24 15:23:20 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <signal.h>
# include <time.h>
//# include <readline/readline.h>
//# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_minish
{
	char	**env_list;
}			t_minish;

//Utils - Initialising
void	init_ms(t_minish *ms, char **envp);
//Utils - Signaling
void	set_signals(void);
//Utils - Handling
void	handle_interrupt(int signum);

/*typedef struct s_point
{
	int	x;
	int	y;
}		t_point;

typedef struct s_map
{
	char			**layout;
	int				num_coins;
	struct s_point	map_size;
	struct s_point	pos_exit;
	struct s_point	pos_player;
}			t_map;

typedef struct s_sprite
{
	int		width;
	int		height;
	void	*img;
}			t_sprite;

typedef struct s_graph
{
	void	*mlx;
	void	*win;
}			t_graph;

typedef struct s_game
{
	struct s_map	*map;
	struct s_sprite	*sprite;
	struct s_graph	display;
	struct s_point	curr;
	struct s_point	next;
	int				moves;
	int				coins;
	int				nsprites;
	int				textpos_y;
}			t_game;

//Utils - Error Handling
int		error_msg(char *msg);
void	error_exit(char *msg, t_game *g);
void	error_map(char *msg, t_game *g);
//Utils - Loading
void	load_map(t_game *g, char *file);
void	load_graphics(t_game *g);
void	load_sprites(t_game *g, int nsprites);
//Utils - Rendering
void	render_map(t_game *g);
int		render_movement(t_game *g);
//Utils - Moving
int		move_handler(int keypress, t_game *g);
void	move_player(t_game *g);
//Utils - Destroying
void	destroy_map(t_game *g);
int		destroy_game(t_game *game);
//Utils - Other
void	validate_map(t_game *g);*/

#endif
