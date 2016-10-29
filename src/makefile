
IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) `pkg-config --cflags gtk+-3.0` -I/usr/include/xfce4/xfconf-0 `xml2-config --cflags`

ODIR=obj
LDIR =../lib

# replaced `pkg-config --libs gtk+-3.0` with -lgtk-3 -lgio-2.0 -lgobject-2.0 -lglib-2.0
LIBS=-lxfconf-0 `xml2-config --libs` -lgtk-3 -lgio-2.0 -lgobject-2.0 -lglib-2.0

_DEPS = theme_struct.h xfconf_functions.h xml_functions.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = theme_chooser.o xml_functions.o xfconf_functions.o theme_struct.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

/home/leopardb/software/theme/w98_plus/packaging/w98plusthemes_1.0/usr/bin/theme_chooser: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 


