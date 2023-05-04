NAME = minishell
LIBFT = libft/libft.a
CFLAG = -Wall -Wextra -Werror
RM = rm -f
SRC = minishell.c linked_list.c ft_spit_pro_max.c ft_expand.c \

OBJ = $(SRC:.c=.o)

all: $(NAME) $(LIBFT)

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAG)  -lreadline  $(SRC) $(LIBFT) -o $(NAME)

$(LIBFT):
	make all -C libft

clean:
	$(RM) $(OBJ)
	make clean -C libft 

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft 

re: fclean all 


# -fsanitize=address 