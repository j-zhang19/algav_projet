CC=gcc
CFLAGS=-g -Wall
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))


main: $(filter-out obj/tests.o, $(OBJS))
	$(CC) $(CFLAGS) $(filter-out obj/tests.o, $(OBJS)) -o $@ -lm

tests: $(filter-out obj/main.o, $(OBJS))
	$(CC) $(CFLAGS) $(filter-out obj/main.o, $(OBJS)) -o $@ -lm

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -lm

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -lm

clean:
	rm -f tests $(BIN) ./$(OBJ)/*.o *.html *.dot