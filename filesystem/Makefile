all:
	@echo "Nothing Yet"

%.ex: %.c
	clang $^ -o $@

measure_read: measure_read.ex 100.raw 1000.raw 10000.raw 100000.raw 1000000.raw
	@mkdir -p data
	@mkdir -p plots
	python measure_read.py

measure_cache: measure_cache.ex 31250000.raw
	@mkdir -p data
	@mkdir -p plots
	python measure_cache.py

measure_contention: measure_contention.ex 10000.raw
	@for number in $$(seq -f "%03g" 0 10); do \
	    cp 10000.raw contention_$$number.raw ; \
	done

%.raw:
	dd if=/dev/urandom of=$*.raw bs=1024 count=$*
#dd if=/dev/urandom of=$*.raw bs=1024 count=$* status=progress

clean:
	rm -rf ./*.o ./*.ex __pycache__

cleanall:
	rm -rf ./*.raw data/* plots/*
