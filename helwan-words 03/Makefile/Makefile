CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -O2 \
	$(shell pkg-config --cflags gtk+-3.0)

LIBS = $(shell pkg-config --libs gtk+-3.0)

TARGET = helwan-words

SRC = \
	src/main.c \
	src/game.c \
	src/ui.c

OBJ = $(SRC:.c=.o)

PREFIX ?= /usr
DESTDIR ?=

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	# تثبيت الملف التنفيذي
	install -Dm755 $(TARGET) \
		$(DESTDIR)$(PREFIX)/bin/$(TARGET)

	# تثبيت ملف الـ CSS الخاص بالتصميم والتنسيق
	install -Dm644 resources/helwan-words.css \
		$(DESTDIR)$(PREFIX)/share/$(TARGET)/helwan-words.css

	# تثبيت ملفات الكلمات للغات الثلاثة (عربي، إنجليزي، إسباني)
	install -Dm644 data/ar.txt \
		$(DESTDIR)$(PREFIX)/share/$(TARGET)/data/ar.txt

	install -Dm644 data/en.txt \
		$(DESTDIR)$(PREFIX)/share/$(TARGET)/data/en.txt

	install -Dm644 data/es.txt \
		$(DESTDIR)$(PREFIX)/share/$(TARGET)/data/es.txt

	# تثبيت أيقونة التطبيق
	install -Dm644 data/icons/helwan-words.png \
		$(DESTDIR)$(PREFIX)/share/helwan-words/icons/helwan-words.png

	# تثبيت ملف الـ Desktop Entry الخاص بالقوائم والتاسك بار
	install -Dm644 helwan-words.desktop \
		$(DESTDIR)$(PREFIX)/share/applications/helwan-words.desktop

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	rm -rf $(DESTDIR)$(PREFIX)/share/$(TARGET)
	rm -f $(DESTDIR)$(PREFIX)/share/applications/helwan-words.desktop

clean:
	rm -f $(OBJ)
	rm -f $(TARGET)

.PHONY: all install uninstall clean