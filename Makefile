CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = Academia.exe
SRCS = Academia.c menu.c aluno.c treino.c utils.c persistencia.c ui.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
