CC =gcc
CCFLAGS= -Wall -Wextra

build:
	cp main.py lab3b
	chmod +x lab3b
.PHONY: clean
clean:
	rm lab3b-804794021.tar.gz
.PHONY: dist
dist:
	tar -czvf lab3b-804794021.tar.gz Makefile main.py README
