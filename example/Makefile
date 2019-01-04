include $(TOP)/config.mk

SOURCES := cfg_test.c
SOURCES += main.c

INCLUDE := -I./ -I../inc 
OBJS := $(patsubst %.c,%.o,$(SOURCES))

TARGET := test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAG) -L../
	$(STRIP) $@

%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(INCLUDE)

clean:
	@rm $(TARGET)
	@rm -f *.o
