.PHONY:clean all
.DEFAULT_GOAL := all

COMMON_CFLAGS = -std=gnu99 -O0 -g
COMMON_LDFLAGS = -lcrypto -I./include
COMMON_SRCS :=
BINDIR=bin
BINS=cipher_demo digest_demo

all:
	gcc -o cipher_demo block_cipher/block_cipher.c $(COMMON_SRCS) $(COMMON_CFLAGS) $(COMMON_LDFLAGS)
	gcc -o digest_demo block_digest/block_digest.c $(COMMON_SRCS) $(COMMON_CFLAGS) $(COMMON_LDFLAGS)
	mkdir -p $(BINDIR)
	mv $(BINS) $(BINDIR)

clean:
	rm -rf $(BINDIR)