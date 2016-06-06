all:
	@echo "Nothing Yet"

%.ex: %.c
	clang $^ -o $@

measure_read: measure_read.ex 100.raw 1000.raw 10000.raw 100000.raw 1000000.raw
	@mkdir -p data
	@mkdir -p plots
	python read_time.py

measure_cache: measure_cache.ex 31250000.raw
	@mkdir -p data
	@mkdir -p plots
	python measure_cache.py

%.raw:
	dd if=/dev/urandom of=$*.raw bs=1024 count=$* status=progress

clean:
	rm -rf ./*.o ./*.ex __pycache__

cleanall:
	rm -rf ./*.raw data/* plots/*
