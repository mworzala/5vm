#ifndef INC_5VM_VM_H
#define INC_5VM_VM_H

#include <stdint.h>

#define MIN_MEMORY (USER_START * sizeof(int64_t))

#define VM_TRUE (-1)
#define VM_FALSE 0

#define IP 0 // Instruction pointer
#define USER_START 13

#define REG_A 1 // Register A
#define REG_B 2 // Register B
#define REG_C 3 // Register C

#define REG_ADD 4 // Addition register
#define REG_SUB 5 // Subtraction register
#define REG_MUL 6 // Multiplication register
#define REG_DIV 7 // Division register
#define REG_GT 8 // Greater than register
#define REG_LT 9 // Less than register
#define REG_EQ 10 // Equal register
#define REG_IN 11 // Input register
#define REG_OUT 12 // Output register
#define REG_NOT 13 // NOT register
#define REG_XOR 14 // XOR register
#define REG_CMP 15 // Comparison register

typedef struct vm_s {
    int64_t *data;
    int64_t data_len;
} VM;

VM *new_vm(int64_t memory);
void vm_free(VM *self);

void vm_execute(VM *self);

#endif //INC_5VM_VM_H
