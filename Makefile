NAME = philo
LIBNAME = $(NAME).a
CFLAGS = -Wall -Werror -Wextra -g -pthread

CFILES =	SRCS/UTILS/ternaries.c	SRCS/UTILS/printmessages.c \
			SRCS/MAIN/main.c	\
			SRCS/PARSER/parser.c
#SRCS/MAIN/init.c			SRCS/MAIN/quit.c
OFILES =	$(CFILES:.c=.o)

.SECONDARY: $(OBJ)

all: $(NAME)

$(NAME): $(LIBNAME)
	@cc SRCS/MAIN/main.c -L. -l:$(LIBNAME) -o $(NAME) -g

$(LIBNAME): $(OFILES)
	@ar -rc $(LIBNAME) $(OFILES)
	@printf "\033[34m          Compiled $(NAME) successfully!\033[0m\n\n"

%.o: %.c
	@printf "\r\033[K\033[34mCompiling: $<\033[0m"  
	@cc $(CFLAGS) -I INCLUDES -c $< -o $@
	@printf "\r\033[K"

clean:
	@rm -f $(OFILES)
	@echo "    \033[32m$(NAME) object files cleaned\n\033[0m"

fclean:
	@rm -f $(LIBNAME) $(NAME) $(OFILES)
	@echo "    \033[32m$(NAME) object files cleaned\n    $(NAME) cleaned.\n\033[0m"

re: fclean
	@sleep 1 && make -s all

norm:
	@norminette | grep -E --color=always "Error" || echo "\e[32mNorminette is fine!\e[0m"
