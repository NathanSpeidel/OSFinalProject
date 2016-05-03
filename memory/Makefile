all: results

build: bandwidth.ex ram_access.ex
debug: bandwidth.debug ram_access.debug

%.ex: %.c
	clang $< -o $@

%.debug: %.c
	clang -g $< -o $@

results: build
	mkdir -p ./plots
	mkdir -p ./data
	python ram_access.py
	python bandwidth.py

clean:
	rm -rf ./*.ex ./*.debug ./plots/* ./data/* ./*.dSYM
