TARGET   = main.exe

CC       = cl.exe

CFLAGS   = /nologo /Iinclude /W3 /O2
LDFLAGS  = /link /nologo

SRCS     = $(wildcard src/*.c)
OBJS     = $(SRCS:.c=.obj)

all: $(TARGET)

$(TARGET): $(OBJS) 
	$(CC) $(OBJS) /Fe:$(TARGET) $(LDFLAGS)

%.obj: %.c
	$(CC) $(CFLAGS) /c $< /Fo$@


clean:
	rm -f src/*.obj
	rm -f $(TARGET)