NAME = philosophers
DIR_SRC = src/
DIR_OBJ = obj/
CC = cc -g
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline
RM = rm -f

SRCS =  $(wildcard $(DIR_SRC)*.c) 

OBJS = $(SRCS:$(DIR_SRC)%.c=$(DIR_OBJ)%.o)

all: $(NAME)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)
	@echo "  "
	@echo "  "
	@echo "PHILOSOPHERS"
	@echo "  "
	@echo "  "

clean:
	@echo "🧹 ALL FILES HAVE BEEN DELETED 🧹"
	rm -rf $(DIR_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all