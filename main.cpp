# include <iostream>
# include <stdio.h>
# include <string.h>
# include "register.hpp"
# include "memory.hpp"
# include "RISCV.hpp"

using namespace std;

memory mem;
RISCV riscv(&mem, Pararrel);

int main() {
	mem.loadFromDisk();
	riscv.run();
	cout << riscv.output() << endl;
	return 0;
}
