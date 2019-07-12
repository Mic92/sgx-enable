INSTALL ?= install
PREFIX ?= /usr/local

.PHONY: all

all: sgx-enable

sgx-enable: main.c
	$(CC) -O2 $< -o $@

install: sgx-enable
	$(INSTALL) -D sgx-enable $(DESTDIR)$(PREFIX)/bin/sgx-enable
