#g++ main.cpp ./NCRelayControllerTest/NCRelayControllerTest.cpp -I../src/RelayController/ -I../src/Pin/ -I./mocks/PinMock/ -lcppunit -o test

IDIR =./include
CC=g++
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =./lib

LIBS=-lcppunit

_DEPS = hellomake.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
