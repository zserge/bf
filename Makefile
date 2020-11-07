all: bf0 bf1 bf2 bf3

bf2.o: bf2.dasc
	$(CC) dynasm/minilua.c -lm -o minilua
	./minilua dynasm/dynasm.lua $^ > bf2.c
	$(CC) -c bf2.c

bf3: bf3.o
	$(CC) $^ -ltcc -ldl -o $@

clean:
	rm -f bf0 bf1 bf2.o bf2.c bf2 bf3 bf3.o minilua
