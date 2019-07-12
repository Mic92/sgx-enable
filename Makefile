.PHONY: all

all: sgx-enable

sgx-enable: main.c
	$(CC) -O2 $< -o $@
