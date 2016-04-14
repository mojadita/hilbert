# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Sun Apr 10 12:09:02 CEST 2016


targets = datos hilbert

datos_objs = datos.o
hilbert_objs = hilbert.o

.PHONY: all clean
all: $(targets)
clean: 
	$(RM) $(targets) $(foreach i, $(targets), $($i_objs))

datos: $(datos_objs)
	$(CC) $(LDFLAGS) -o $@ $($@_objs) $($@_libs)
hilbert: $(hilbert_objs)
	$(CC) $(LDFLAGS) -o $@ $($@_objs) $($@_libs)
