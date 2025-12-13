NAME:=9cc

SRCDIR:=srcs
SRCS:=9cc.c utils.c error.c
OBJDIR:=obj
OBJS:=$(addprefix $(OBJDIR)/,$(SRCS:%.c=%.o))
SRCS:=$(addprefix $(SRCDIR)/, $(SRCS)) 

HEADDIR:=includes
HEADERS:=cc9.h
HEADERS:=$(addprefix $(HEADDIR)/, $(HEADERS)) 

CC=cc
CFLAGS=-std=c11 -g -static -I$(HEADDIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)	

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)	
	$(CC) $(CFLAGS) -c $< -o $@	

test: $(NAME)
	./test.sh

clean:
	rm -rf $(OBJDIR)	
	rm -f *~ tmp*

fclean: clean
	rm -f $(NAME)	

re: fclean all	

.PHONY: all test clean
