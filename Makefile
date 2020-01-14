.POSIX:

CC = tcc
LDFLAGS = -lX11 -lpthread
CFLAGS = -O3

SRC = dwmbar.c
TARGET = dwmbar
OBJ = ${SRC:.c=.o}

COM =\
	components/util\
	components/battery\
	components/dateTime\
	components/volume\
	components/backlight\
	components/memory\
	components/netspeed\
	components/thermal

$(TARGET): $(OBJ) $(COM:=.o)
	$(CC) $(OBJ) $(COM:=.o) -o $(TARGET) $(LDFLAGS) $(CFLAGS)

${COM:=.o}: ${COM:=.c} ${COM:=.h}

$(OBJ): $(SRC) $(SRC:.c=.h)
	$(CC) -c $(SRC) -o $(OBJ) $(CFLAGS)

clean:
	rm -f $(TARGET) $(OBJ) $(COM:=.o)
