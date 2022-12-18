#include "vm.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

VM *new_vm(int64_t memory) {
    assert(memory > MIN_MEMORY);

    VM *vm = malloc(sizeof(VM));
    vm->data_len = memory / (int64_t) sizeof(int64_t);
    vm->data = malloc(sizeof(int64_t) * vm->data_len);

    // Set initial instruction pointer
    vm->data[IP] = USER_START;

    return vm;
}

void vm_free(VM *self) {
    free(self->data);
    free(self);
}

void vm_execute(VM *self) {
    while (self->data[IP] != 0) {
        int64_t l = self->data[self->data[IP]++]; // SRC pointer
        int64_t r = self->data[self->data[IP]++]; // DST pointer

        // Input/output register handling
        assert(l != REG_OUT); // Cannot read from output register
        assert(r != REG_IN); // Cannot write to input register
        if (l == REG_IN) {
            self->data[r] = getc(stdin);
        } else if (r == REG_OUT) {
            putc((int) self->data[l], stdout);
            // No need to update values, nothing has changed
            continue;
        } else if (l == REG_CMP) {
            int64_t a = self->data[REG_A], b = self->data[REG_B], c = self->data[REG_C];
            self->data[r] = c != VM_FALSE ? a : b;
        } else {
            self->data[r] = self->data[l]; // move SRC value to DST
        }

        //todo writing to reserved registers should be a noop (would recomupte to the same value)

        // Update registers (preemptively, could do this lazily)
        int64_t a = self->data[REG_A], b = self->data[REG_B], c = self->data[REG_C];
        self->data[REG_ADD] = a + b;
        self->data[REG_SUB] = a - b;
        self->data[REG_MUL] = a * b;
        self->data[REG_DIV] = a / b;
        self->data[REG_GT] = a > b ? VM_TRUE : VM_FALSE;
        self->data[REG_LT] = a < b ? VM_TRUE : VM_FALSE;
        self->data[REG_EQ] = a == b ? VM_TRUE : VM_FALSE;
        // 11 is input register, handled above
        // 12 is output register, handled above
        self->data[REG_NOT] = c == VM_FALSE ? VM_TRUE : VM_FALSE;
        self->data[REG_XOR] = a ^ b;
        // 15 is the comparison register, handled above
    }
}

