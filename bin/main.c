#include <stdio.h>
#include <stdint.h>

#include <vm.h>

int main() {
    VM *vm = new_vm(1024);
    int64_t code = USER_START;
    int64_t data = USER_START + 50;

    // Code
    vm->data[code++] = data + 1; // Move 55 to A
    vm->data[code++] = REG_A;
    vm->data[code++] = data + 2; // Move 45 to B
    vm->data[code++] = REG_B;
    vm->data[code++] = REG_ADD; // Move ADD to A
    vm->data[code++] = REG_A;
    vm->data[code++] = data;    // Halt
    vm->data[code++] = IP;

    // Data
    vm->data[data++] = 0;
    vm->data[data++] = 55;
    vm->data[data++] = 45;

    /*
     mov #55 A
     mov #45 B
     mov ADD A
     halt
     */

    vm_execute(vm);

    printf("%lld\n", vm->data[1]);

    vm_free(vm);
    return 0;
}
