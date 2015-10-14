CC ?= gcc
CFLAGS_common ?= -O0 -Wall -std=gnu99 -g

EXEC = phonebook_orig phonebook_opt
all: $(EXEC)

SRCS_common = main.c

phonebook_orig: $(SRCS_common) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) -DORIG -DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

phonebook_opt: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) -DOPT -DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

run: $(EXEC)
	#watch -d -t ./phonebook_orig
	@sudo sh -c "echo 1 > /proc/sys/vm/drop_caches"
	./phonebook_orig
	./phonebook_opt
PERF_STAT = cache-misses,cache-references,L1-dcache-load-misses,L1-dcache-store-misses,L1-dcache-prefetch-misses
perf_stat:
	@sudo sh -c "echo 0 > /proc/sys/kernel/kptr_restrict"
	perf stat -r 10 -e $(PERF_STAT) ./phonebook_orig
	perf stat -r 10 -e $(PERF_STAT) ./phonebook_opt



clean:
	$(RM) $(EXEC) *.o perf.*
