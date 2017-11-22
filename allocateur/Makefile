CC=gcc

# uncomment to compile in 32bits mode (require gcc-*-multilib packages
# on Debian/Ubuntu)
#HOST32= -m32

CFLAGS+= $(HOST32) -Wall -Werror -std=c99 -O2 -g -DMEMORY_SIZE=128000
CFLAGS+= -DDEBUG
# pour tester avec ls
CFLAGS+= -fPIC
LDFLAGS= $(HOST32) -lpthread
TESTS+=test_init test_policies test_policies test_cheese test_base test_fusion
TESTS+=test_thread
PROGRAMS=memshell $(TESTS)

.PHONY: clean all test_ls dist

all: $(PROGRAMS) libmalloc.so #clean
	#for file in $(TESTS);do ./$$file; done

# dépendences des binaires
$(PROGRAMS) libmalloc.so: %: mem.o common.o

# dépendances des fichiers objects
$(patsubst %.c,%.o,$(wildcard *.c)): %.o: .%.deps

.%.deps: %.c
	$(CC) $(CFLAGS) -MM $< | sed -e 's/\(.*\).o: /.\1.deps \1.o: /' > $@

-include $(wildcard .*.deps)

# seconde partie du sujet
libmalloc.so: malloc_stub.o
	$(CC) -shared -Wl,-soname,$@ $^ -o $@
	echo "libmalloc done"

test_ls: libmalloc.so
	LD_PRELOAD=./libmalloc.so ls

# nettoyage
clean:
	rm -f *.o $(PROGRAMS) libmalloc.so .*.deps


ifeq ($(SOURCES_LIST),)
SOURCES_LIST=$(wildcard *.c)
endif

dist: README Makefile $(SOURCES_LIST) $(wildcard *.h) test_init.c
	mkdir memoire
	cp $^ memoire
	tar cvzf memoire.tar.gz memoire
	rm -r memoire
