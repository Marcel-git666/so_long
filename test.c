#include "minilibx_linux/mlx.h"
int main()
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 800, 600, "Test Window");
    mlx_string_put(mlx, win, 10, 10, 0xFFFFFF, "Hello, World!");
    mlx_loop(mlx);
    return (0);
}
