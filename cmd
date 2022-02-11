gcc -I ./mlx -I ./libft -o main.o -c main.c     
gcc  -o main main.o -L ./mlx -lmlx -lXext -lX11 -L ./libft -lft

