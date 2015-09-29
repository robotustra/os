# Makefile для руководств по сборке ядра - автор James Molloy.
# Правила обработки C и C++ указаны как используемые по умолчанию.
# Единственное, что нужно изменить, это указать правила обработки 
# ассемблера, поскольку мы используем nasm вместо GNU as.

SOURCES=boot.o main.o
CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32

LDFLAGS=-Tlink.ld -melf_i386
ASFLAGS=-felf

all: $(SOURCES) link 

clean:

	rm *.o kernel

link:

	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:

	nasm $(ASFLAGS) $< 
