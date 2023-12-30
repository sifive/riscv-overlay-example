PREFIX = riscv64-unknown-elf
CC = $(PREFIX)-gcc
OBJDUMP = $(PREFIX)-objdump

SRC = \
  func1.c \
  func2.c \
  main.c \
  overlay_manager.c \
  overlay_stub.c \

OBJ = $(patsubst %.c,%.o,$(SRC))
EXE = overlay.exe
DUMP = $(EXE).objdump
LDSCRIPT = overlay.ld

CFLAGS = -Og -g
LDFLAGS = -Wl,--wrap=func1 -Wl,--wrap=func2  -Wl,--verbose -T $(LDSCRIPT) -Wl,-Map=map.txt

all: $(EXE) $(DUMP)

$(EXE): $(OBJ) $(LDSCRIPT)
	$(CC) $(LDFLAGS) $(OBJ) -o $(EXE)

$(DUMP): $(EXE)
	$(OBJDUMP) --disassemble --source $(EXE) > $(EXE).objdump

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -f $(OBJ) $(EXE)
