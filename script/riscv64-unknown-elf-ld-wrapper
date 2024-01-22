#!/usr/bin/env bash
# This is gcc/linker wrapper that:
#   1. dumps symbols for all input object files
#   2. find functions begin with `__wrap`
#   3. add --wrap option to linekr

LD=riscv64-unknown-elf-ld
WRAP_OPTION=""
for arg in $@; do
    if [[ $arg == *.o ]]; then
        #   9: 0000000000000000    26 FUNC    GLOBAL DEFAULT    1 __wrap_foo
        WRAP_OPTION+=$(riscv64-unknown-elf-readelf -s $arg | \
                       grep __wrap | \
                       awk '$4 ~ /FUNC/ {print $8}' | \
                       sed -E 's/__wrap_(.*)/--wrap=\1/' | \
                       tr '\n' ' ')
    fi
done

# Call the real linker with --wrap args appended.
echo "Original command:"
echo "  $@"
echo "Added --wrap command:"
echo "  $LD $@ $WRAP_OPTION"
$LD $@ $WRAP_OPTION


