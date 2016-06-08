CC=gcc

all:
	@echo "Nothing Yet"

.SECONDARY:

%.o: %.c %.h
	$(CC) -std=c99 -c $*.c

%.ex: %.c common.o
	$(CC) -std=c99 -pthread $^ -o $@

measure_read: measure_read.ex 100.raw 1000.raw 10000.raw 100000.raw 1000000.raw
	@mkdir -p data
	@mkdir -p plots
	python measure_read.py 4096
	python measure_read.py 1024

measure_cache: measure_cache.ex 15625000.raw
	@mkdir -p data
	@mkdir -p plots
	python measure_cache.py

measure_contention: measure_contention.ex 10000.raw
	@for number in $$(seq -f "%03g" 0 10); do \
	    cp 10000.raw contention_$$number.raw ; \
	done
	python measure_contention.py

%.raw:
	dd if=/dev/urandom of=$*.raw bs=1024 count=$*

clean:
	rm -rf ./*.o ./*.ex __pycache__

cleanall:
	rm -rf ./*.raw data/* plots/*
