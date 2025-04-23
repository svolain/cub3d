# cub3d

Cub3d is a 3D game coded by using raycasting and a minimalistic C graphichs library [42mlx](https://github.com/codam-coding-college/MLX42). The general style and graphics of the game has been done by using [Wolfenstein 3D](https://fr.wikipedia.org/wiki/Wolfenstein_3D) as a reference. All the work in this repo has been done in cooperation by [Jarnomer](https://github.com/Jarnomer) & [Svolain](https://github.com/svolain).

![cubed gif](gif/cubd-gif.gif)

## Install & Run

Install needed dependencies for mlx42 library according to [codam instructions](https://github.com/codam-coding-college/MLX42?tab=readme-ov-file#for-linux). The actual mlx42 library is installed by below commands so only dependencies are needed from codam.

Keys:

- WASD is used for moving around
- Left and Right arrows are used for rotating camera
- Space or left click for shooting
- E for opening doors

Full version
```
git clone git@github.com:svolain/cub3d.git
cd cub3d
make bonus
./cub3D maps/bonus/map.cub
```

Simplified version with minimalistic graphics
```
git clone git@github.com:svolain/cub3d.git
cd cub3d
make bonus
./cub3D maps/mandatory/map.cub 
```
