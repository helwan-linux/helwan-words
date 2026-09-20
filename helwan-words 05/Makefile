.RECIPEPREFIX := >

CC = gcc

CFLAGS = -Wall -Wextra -O2 $(shell pkg-config --cflags gtk+-3.0)
LIBS = $(shell pkg-config --libs gtk+-3.0)

TARGET = helwan-words

OBJECTS = src/main.o src/game.o src/ui.o

all: $(TARGET)

$(TARGET): $(OBJECTS)

> $(CC) $(OBJECTS) -o $(TARGET) $(LIBS)

src/main.o: src/main.c

> $(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/game.o: src/game.c src/game.h

> $(CC) $(CFLAGS) -c src/game.c -o src/game.o

src/ui.o: src/ui.c src/ui.h src/game.h

> $(CC) $(CFLAGS) -c src/ui.c -o src/ui.o

clean:

> rm -f $(OBJECTS) $(TARGET)

install:

> install -Dm755 $(TARGET) $(DESTDIR)/usr/bin/helwan-words
> install -Dm644 helwan-words.desktop $(DESTDIR)/usr/share/applications/helwan-words.desktop
> install -Dm644 data/icons/helwan-words.png $(DESTDIR)/usr/share/icons/hicolor/512x512/apps/helwan-words.png
> install -Dm644 resources/helwan-words.css $(DESTDIR)/usr/share/helwan-words/helwan-words.css
> install -Dm644 data/ar.txt $(DESTDIR)/usr/share/helwan-words/data/ar.txt
> install -Dm644 data/en.txt $(DESTDIR)/usr/share/helwan-words/data/en.txt
> install -Dm644 data/es.txt $(DESTDIR)/usr/share/helwan-words/data/es.txt

