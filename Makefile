NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS =  ft_print.c \
		ft_basic_str.c \
		ft_hexa_str.c \
		ft_atoi.c \
		ft_padding.c \
		ft_c_s_percent_conversion.c \
		ft_p_conversion.c \
		ft_d_precision_part.c \
		ft_d_conversion.c \
		ft_u_conversion.c \
		ft_low_x_conversion.c \
		ft_cap_x_conversion.c \
		ft_read_info.c \
		ft_process_formatting.c \


OBJS = $(SRCS:.c=.o)

BONUS_SRCS =  .

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

RM = rm -f

%.o : %.c
		${CC} ${CFLAGS} -c $< -o $@

$(NAME) : ${OBJS}
		ar cr $@ ${OBJS}
	
all :	${NAME}

clean:
		${RM} ${OBJS} ${BONUS_OBJS}

fclean:	clean
		${RM} ${NAME} $(bonus)

re:		fclean all

bonus : ${OBJS} ${BONUS_OBJS}
		ar cr $(NAME) $?
