all: results

build: bandwidth.ex ram_access.ex page_fault.ex
debug: bandwidth.debug ram_access.debug page_fault.debug

%.ex: %.c
	gcc --std=c99 $< -o $@

%.debug: %.c
	gcc --std=c99 -g $< -o $@

results: build
	mkdir -p ./plots
	mkdir -p ./data
	python ram_access.py
	python bandwidth.py

clean:
	rm -rf ./*.ex ./*.debug ./plots/* ./data/* ./*.dSYM
