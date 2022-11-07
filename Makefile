################################################################################
#  SOURCES                                                                     #
################################################################################

SRCS	=	srcs/logging.c \
			srcs/maths/matrix/mat_lookat.c \
			srcs/maths/vector/vector_add.c \
			srcs/maths/vector/vector_color.c \
			srcs/maths/vector/vector_cross.c \
			srcs/maths/vector/vector_dot.c \
			srcs/maths/vector/vector_magnitude.c \
			srcs/maths/vector/vector_matrix.c \
			srcs/maths/vector/vector_normalize.c \
			srcs/maths/vector/vector_rotate.c \
			srcs/maths/vector/vector_scalar.c \
			srcs/maths/vector/vector_sub.c \
			srcs/objects/light_point.c \
			srcs/objects/object.c \
			srcs/parsing/objects_unique.c \
			srcs/parsing/parsing.c \
			srcs/raytracing/rt_light.c \
			srcs/raytracing/rt_shadow.c \
			srcs/utils/str_split.c \
			srcs/utils/strl_free.c \
			srcs/utils/strl_len.c \
			srcs/xutils/color.c \

SRCS_MANDATORY	:=	srcs/controls.c \
					srcs/main.c \
					srcs/raytracing/rt_engine.c \
					srcs/raytracing/rt_rays.c \
					srcs/objects/cylinder.c \
					srcs/objects/sphere.c \
					srcs/objects/plane.c \
					srcs/parsing/objects.c \
					srcs/xutils/image.c \

SRCS_BONUS		:=	srcs/controls_bonus.c \
					srcs/main_bonus.c \
					srcs/raytracing/rt_engine_bonus.c \
					srcs/raytracing/rt_rays_bonus.c \
					srcs/objects/cylinder_bonus.c \
					srcs/objects/sphere_bonus.c \
					srcs/objects/plane_bonus.c \
					srcs/parsing/objects_bonus.c \
					srcs/xutils/image_bonus.c \

OBJS			:=	$(SRCS:.c=.o)
OBJS_MANDATORY	:=	$(SRCS_MANDATORY:.c=.o)
OBJS_BONUS		:=	$(SRCS_BONUS:.c=.o)

################################################################################
#  CONSTANTS                                                                   #
################################################################################

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
CFLAGS		+=	-Ofast

NAME		=	miniRT

INCLUDES	= -Iincludes -Ilibs/libft/includes
LIBS		= -Llibs/libft -lft

OS := $(shell uname)
ifeq ($(OS), Darwin)
	INCLUDES	+= -Ilibs/minilibx
	LIBS		+= -Llibs/minilibx -lmlx
	LIBS		+= -framework OpenGL -framework AppKit
else
	INCLUDES	+= -Ilibs/minilibx
	LIBS		+= -L/usr/lib -lmlx -L/usr/lib/x86_64-linux-gnu -lXext -lX11 -lm -lbsd 
endif

OBJ_OPTS	= $(CFLAGS) $(INCLUDES)
BIN_OPTS	= $(LIBS)

################################################################################
#  MAKEFILE VISUALS                                                            #
################################################################################

SHELL	=	zsh
REDO	=	\r\e[2K

# COLORS
BG_RD	=	\033[48;2;237;66;69m
BG_GR	=	\033[48;2;0;194;60m
BG_BL	=	\033[48;2;88;101;242m
FG_WH	=	\033[38;2;255;255;255m
FG_BK	=	\033[38;2;0;0;0m
BOLD	=	\033[1m
NOCOL	=	\033[0m

# CHARS
TICK	=	✓
PEN		=	✐
CROSS	=	𐄂

# MESSAGES
VALID	=	$(BOLD)$(FG_WH)$(BG_GR) $(TICK)
INFO	=	$(BOLD)$(FG_WH)$(BG_BL) $(PEN)
DEL		=	$(BOLD)$(FG_WH)$(BG_RD) $(CROSS)

################################################################################
#  TARGETS / RULES                                                             #
################################################################################

%.o: %.c
	@$(CC) $(OBJ_OPTS) -g -c $< -o $@
	@echo -n '$(REDO)$(INFO) $(notdir $@) $(NOCOL)'

all:
	@make -sC libs/libft
	@make -sC libs/minilibx
	@make $(NAME) SRCS="$(SRCS) $(SRCS_MANDATORY)"

bonus:
	@make -sC libs/libft
	@make -sC libs/minilibx
	@make $(NAME) SRCS="$(SRCS) $(SRCS_BONUS)"

$(NAME): $(OBJS)
	@$(CC) $^ $(BIN_OPTS) -o $(NAME)
	@echo '$(REDO)$(VALID) $@ $(NOCOL)'

debug: fclean
	@make -s CFLAGS="$(CFLAGS) -g" BIN_OPTS="$(BIN_OPTS) -fsanitize=address"

clean:
	@rm -f $(OBJS) $(OBJS_MANDATORY) $(OBJS_BONUS)
	@echo '$(DEL) Removed $(words $(OBJS), $(OBJS_MANDATORY), $(OBJS_BONUS)) object files $(NOCOL)'

fclean: clean
	@rm -f $(NAME)
	@echo '$(DEL) $(NAME) binary $(NOCOL)'

re: fclean all

libs-clean:
	@make -sC libs/libft clean

libs-fclean:
	@make -sC libs/libft fclean

libs-re:
	@make -sC libs/libft re

run: $(NAME)
	@./$(NAME) scenes/subject.rt

.PHONY: all clean fclean re
