# You can put your build options here
-include config.mk

all: libjsmn.a

libjsmn.a: jsmn.o
	$(AR) rc $@ $^

%.o: %.c jsmn.h
	$(CC) -DDEBUG_MODE -c $(CFLAGS) $< -o $@

test: test_default test_strict test_links test_strict_links
test_default: test/tests.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o test/$@
	./test/$@
test_strict: test/tests.c
	$(CC) -DJSMN_STRICT=1 $(CFLAGS) $(LDFLAGS) $< -o test/$@
	./test/$@
test_links: test/tests.c
	$(CC) -DJSMN_PARENT_LINKS=1 $(CFLAGS) $(LDFLAGS) $< -o test/$@
	./test/$@
test_strict_links: test/tests.c
	$(CC) -DJSMN_STRICT=1 -DJSMN_PARENT_LINKS=1 $(CFLAGS) $(LDFLAGS) $< -o test/$@
	./test/$@

jsmn_test.o: example/myjson.c libjsmn.a

myexample: example/new.o libjsmn.a
	 $(CC) $(LDFLAGS) $^ -o $@
simple_example: mysource/filesimple.o libjsmn.a
	$(CC) $(LDFLAGS) $^ -o $@
ex: mysource/productlist.o libjsmn.a
	$(CC) $(LDFLAGS) $^ -o $@
my: mysource/myproduct.o libjsmn.a
	$(CC) $(LDFLAGS) $^ -o $@
jsondump: example/jsondump.o libjsmn.a
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -f *.o example/*.o
	rm -f *.a *.so
	rm -f simple_example
	rm -f ex
	rm -f my
	rm -f jsondump
	rm -f new

.PHONY: all clean test
