CC=gcc

all:
	@echo "nothing here"

%.ex: %.c
	$(CC) -std=gnu99 $^ -o $@

rtt: rtt.ex
	mkdir -p data
	@echo "Make sure that the echo servers are running"
	python rtt.py

peak_bandwidth: peak_bandwidth.ex
	mkdir -p data
	@echo "Make sure that the echo servers are running"
	python peak_bandwidth.py

