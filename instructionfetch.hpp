# include "instructiondecode.hpp"
# include "register.hpp"
# include "instruction.hpp"

# ifndef _INSTRUCTIONFETCH_
	# define _INSTRUCTIONFETCH_

class InstructionFetch {
		friend class RISCV;
	private:
		Register *reg;

	public:
		Instruction inst;
		bool lock;

		InstructionFetch(Register *_reg) {
			reg = _reg;
			lock = 0;
		}

		void go() {
			if(reg -> usedpc) lock = 1;
			else {
				lock = 0;
				inst.initialize();
				inst.com = reg -> getinst();
			}
		}

		void pass(InstructionDecode &nxt) {
			nxt.inst = inst;
			if(lock) nxt.inst.type = ERR;
		}
};

# endif
