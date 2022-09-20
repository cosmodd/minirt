################################################################################
#  SOURCES                                                                     #
################################################################################

SRCS	=	srcs/main.c \
			srcs/xutils/image.c \

OBJS	=	$(SRCS:.c=.o)

################################################################################
#  CONSTANTS                                                                   #
################################################################################

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

NAME		=	minirt

INCLUDES	= -Iincludes
INCLUDES	+= -Ilibs/minilibx
INCLUDES	+= -Ilibs/libft/includes

LIBS		= -Llibs/minilibx -lmlx
LIBS		+= -Llibs/libft -lft

OBJ_OPTS	= $(INCLUDES) $(CFLAGS)
BIN_OPTS	= $(LIBS) $(INCLUDES) -framework OpenGL -framework AppKit

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
	@make -sC ./libs/libft
	@make -sC ./libs/minilibx
	@$(CC) $(OBJ_OPTS) -c $< -o $@
	@echo -n '$(REDO)$(INFO) $(notdir $@) $(NOCOL)'

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(BIN_OPTS) $^ -o $(NAME)
	@echo '$(REDO)$(VALID) $@ $(NOCOL)'

clean:
	@make -sC ./libs/libft clean
	@make -sC ./libs/minilibx clean
	@rm -f $(OBJS)
	@echo '$(DEL) Removed $(words $(OBJS)) object files $(NOCOL)'

fclean: clean
	@rm -f $(NAME)
	@echo '$(DEL) $(NAME) binary $(NOCOL)'

re: fclean all

run: $(NAME)
	@./$(NAME)

.PHONY: all clean fclean re
