include config.mk

SOURCES := $(TOP)/src/cfg.c 
SOURCES += $(TOP)/src/ini.c 

INCLUDE := -I$(TOP)/inc

OBJS := $(patsubst %.c,%.o,$(SOURCES))

TARGET := libuini.a

.PHONY:all clean exp exp_clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) crs $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(INCLUDE) $(LOC_INC)

exp:
	@make -C example

exp_clean:
	@make clean -C example

clean:
	@rm $(TARGET)
	@rm -f *.o
	@rm -rf $(TOP)/src/*.o
