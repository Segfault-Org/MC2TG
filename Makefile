TARGET = mc2tg-bot

VERSION := 1
# VERSION := $(VERSION).$(shell git rev-list --count HEAD)

OBJS = main.o \
	   common.o
CFLAGS = -Wall \
		 -O0 \
		 -fno-omit-frame-pointer \
		 -g \
		 -DVERSION=$(VERSION)
LDFLAGS = -lcurl

.PHONY: clean all

all: $(TARGET)

ifeq ($(PREFIX),)
    PREFIX := /usr/
endif

install: $(TARGET)
	install -d $(DESTDIR)$(PREFIX)/bin/
	install -m 755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/

$(TARGET): $(OBJS)
	$(CC) -o $@ $(LDFLAGS) -rdynamic $^

$(OBJS):%.o:%.c

clean:
	rm $(TARGET) $(OBJS)
