PREFIX = riscv64-unknown-elf
CC = $(PREFIX)-gcc
OBJDUMP = $(PREFIX)-objdump
READELF = $(PREFIX)-readelf

SRC = \
  func1.c \
  func2.c \
  main.c \
  overlay_manager.c \
  overlay_stub.c \

OBJ = $(patsubst %.c,%.o,$(SRC))
EXE = overlay.exe
DUMP = $(EXE).objdump
SYM = $(EXE).sym
LDSCRIPT = overlay.ld

CFLAGS = -Og -g -msmall-data-limit=0
LDFLAGS = -Wl,--wrap=func1 -Wl,--wrap=func2  -Wl,--verbose -T $(LDSCRIPT) -Wl,-Map=map.txt -mno-relax

all: $(EXE) $(DUMP)

$(EXE): $(OBJ) $(LDSCRIPT)
	$(CC) $(LDFLAGS) $(OBJ) -o $(EXE)

$(DUMP): $(EXE)
	$(OBJDUMP) --disassemble --section-headers --source $(EXE) > $@

$(SYM): $(EXE)
	$(READELF) -Ss $(EXE) > $(@)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -f $(OBJ) $(EXE)
