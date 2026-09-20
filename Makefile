SRCS = $(wildcard *.c validations/*.c operations/*.c helper/*.c)

OBJS = $(patsubst %.c, %.o, $(SRCS))

CFLAGS = -Iinclude -g

iv: $(OBJS)
	gcc -o iv $(OBJS)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f iv.exe $(OBJS)