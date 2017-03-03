EXECS = sntloop sntall sntgamma sntrandom
OBJS = sn3218.o i2c.o
H = sn3218.h

all: $(EXECS)

sntloop: $(OBJS) $(H)

sntall: $(OBJS) $(H)

sntgamma: $(OBJS) $(H)

sntrandom: $(OBJS) $(H)

#sntest: $(OBJS) $(H)

sn3218.o: sn3218.h i2c.h

i2c.o: i2c.h

.PHONY: clean tags
clean:
	-rm -f $(EXECS) *.o *~

tags:
	-ctags *.c *.h