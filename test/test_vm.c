#include <vm.h>
#include <assert.h>

void test_basic_add() {
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

    vm_execute(vm);

    assert(100 == vm->data[REG_A]);

    vm_free(vm);
}

void test_if_stmt() {
    VM *vm = new_vm(1024);
    int64_t code = USER_START;
    int64_t data = USER_START + 50;

    // Code is essentially `1 == 2 ? 50 : 500`

    // Code
    vm->data[code++] = data + 1; // Move 1 to A
    vm->data[code++] = REG_A;
    vm->data[code++] = data + 2; // Move 2 to B
    vm->data[code++] = REG_B;
    vm->data[code++] = REG_EQ; // Move EQ to C
    vm->data[code++] = REG_C;
    // We will move CMP to the IP register, so need to set A to the true case, B to the false case
    vm->data[code++] = data + 3;    // Move 50 to A
    vm->data[code++] = REG_A;
    vm->data[code++] = data + 4;    // Move 500 to B
    vm->data[code++] = REG_B;
    // Compare instruction to A, should now contain the right result
    vm->data[code++] = REG_CMP;
    vm->data[code++] = REG_A;
    vm->data[code++] = data;    // Halt
    vm->data[code++] = IP;

    // Data
    vm->data[data++] = 0;
    vm->data[data++] = 1;
    vm->data[data++] = 2;
    vm->data[data++] = 50;
    vm->data[data++] = 500;

    vm_execute(vm);

    assert(500 == vm->data[REG_A]);

    vm_free(vm);
}

void test_hello_world() {
    VM *vm = new_vm(1024);
    int64_t code = USER_START;
    int64_t data = USER_START + 50;

    // Code
    for (int i = 0; i < 13; i++) {
        vm->data[code++] = data + i + 1;
        vm->data[code++] = REG_OUT;
    }
    vm->data[code++] = data;
    vm->data[code++] = IP;

    // Data
    vm->data[data++] = 0;
    vm->data[data++] = 'H';
    vm->data[data++] = 'e';
    vm->data[data++] = 'l';
    vm->data[data++] = 'l';
    vm->data[data++] = 'o';
    vm->data[data++] = ' ';
    vm->data[data++] = 'W';
    vm->data[data++] = 'o';
    vm->data[data++] = 'r';
    vm->data[data++] = 'l';
    vm->data[data++] = 'd';
    vm->data[data++] = '!';
    vm->data[data++] = '\n';

    vm_execute(vm);
    vm_free(vm);
}

int main() {
    test_basic_add();
    test_if_stmt();
    test_hello_world();
    return 0;
}
