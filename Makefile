CC=gcc
FLAGS := $(shell pkg-config --cflags gtk+-2.0)
LIBS := $(shell pkg-config --libs gtk+-2.0)
INSTALL = /usr/bin/install
STRIP = /usr/bin/strip
prefix = /usr
bindir = ${prefix}/bin
sbindir = ${prefix}/sbin
datarootdir = ${prefix}/share
libdir = ${prefix}/lib`uname -m|cut -b 5-`
sysconfdir = /etc

all:
	$(CC) -o notify-gtk2 src/notify-gtk.c $(FLAGS) $(LIBS)

install:
	$(INSTALL) -D -m 755 notify-gtk2 $(DESTDIR)$(bindir)/notify-gtk2
	$(STRIP) $(DESTDIR)$(bindir)/notify-gtk2
	
	$(INSTALL) -d $(DESTDIR)$(datarootdir)/
	cp -a pixmaps/ $(DESTDIR)$(datarootdir)/
	
clean:
	rm notify-gtk2
