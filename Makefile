
NAME = FDF

CC = cc
C_FLAGS = -Wall -Wextra -Werror
FRAM = -lmlx -framework OpenGL -framework AppKit

LFT_PATH = ./libraries/libft/
MLX_PATH = ./libraries/minilibx_macos/
LFT_INC_PATH = ./libraries/libft/includes/
MLX_INC_PATH = ./libraries/minilibx_macos/
OBJ_PATH = ./objs/
INC_PATH = ./includes/
SRC_PATH = ./srcs/

LFT_NAME = libft.a
MLX_NAME = libmlx.a
OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = fdf.h
SRC_NAME = fdf.c fdf_image.c fdf_create_map.c fdf_key_events.c fdf_bresenham.c

LFT = $(addprefix $(LFT_PATH),$(LFT_NAME))
MLX = $(addprefix $(MLX_PATH),$(MLX_NAME))
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LFT_INC = $(addprefix -I,$(LFT_INC_PATH))
MLX_INC = $(addprefix -I,$(MLX_INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LFT_PATH)
	@make -C $(MLX_PATH)
	@$(CC) -o $@ $(FRAM) -L $(MLX_PATH) -L $(LFT_PATH) -lft $^
	@echo "Obj folder & files created"
	@echo "Executable created"
	@echo "Compilation finished"

$(OBJ): | $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(C_FLAGS) $(INC) $(LFT_INC) $(MLX_INC) -o $@ -c $<

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true

clean:
	@make clean -C $(LFT_PATH)
	@make clean -C $(MLX_PATH)
	@rm -rf $(OBJ_PATH) 2> /dev/null || true
	@echo "Obj folder & files suppressed"

fclean: clean
	@make fclean -C $(LFT_PATH)
	@rm -f $(NAME)
	@echo "Executable suppressed"

re: fclean
	@$(MAKE) all

bonus: all

norme:
	@norminette -R CheckForbiddenSourceHeader $(SRC)
	@echo "C files norme check finished"
	@norminette -R CheckDefine $(INC_PATH)
	@echo "Header files norme check finished"
