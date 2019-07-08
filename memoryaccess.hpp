# include "writeback.hpp"
# include "register.hpp"

# ifndef _MEMORYACCESS_
	# define _MEMORYACCESS_

class MemoryAccess {
		friend class RISCV;
	private:
		Register *reg;

	public:
		Instruction inst;

		MemoryAccess(Register *_reg) {
			reg = _reg;
		}

		void go() {
			if(inst.type == ERR) return ;
			switch(inst.type) {
				case LW: inst.result = reg -> load(inst.src1, 4); break;
				case LH: inst.result = sgnextend(reg -> load(inst.src1, 2), 15); break;
				case LHU: inst.result = reg -> load(inst.src1, 2); break;
				case LB: inst.result = sgnextend(reg -> load(inst.src1, 1), 7); break;
				case LBU: inst.result = reg -> load(inst.src1, 1); break;
				case SW: reg -> store(inst.src1, inst.src2, 4); break;
				case SH: reg -> store(inst.src1, inst.src2, 2); break;
				case SB: reg -> store(inst.src1, inst.src2, 1); break;
				default: break;
			}
		}

		void pass(WriteBack &nxt) {
			nxt.inst = inst;
		}
};

# endif
