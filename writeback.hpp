# include "register.hpp"
# include "tools.hpp"
# include "instruction.hpp" 

# ifndef _WRITEBACK_
	# define _WRITEBACK_

class WriteBack {
		friend class RISCV;
	private:
		Register *reg;

	public:
		Instruction inst;

		WriteBack(Register *_reg) {
			reg = _reg;
		}

		void go() {
			if(inst.type == ERR) return ;
			switch(inst.type) {
				case JAL:
				case JALR:
					reg -> set(inst.rd, inst.result);
					reg -> setpc(inst.resultpc);
					break;
				case BEQ:
				case BNE:
				case BLT:
				case BLTU:
				case BGE:
				case BGEU:
					if(inst.result) reg -> setpc(inst.resultpc);
					break;
				case LUI:
				case AUIPC:
				case LB:
				case LW:
				case LH:
				case LBU:
				case LHU:
				case ADDI:
				case SLTI:
				case SLTIU:
				case ANDI:
				case ORI:
				case XORI:
				case SLLI:
				case SRLI:
				case SRAI:
				case ADD:
				case SUB:
				case SLL:
				case SLT:
				case SLTU:
				case XOR:
				case SRL:
				case SRA:
				case OR:
				case AND:
					reg -> set(inst.rd, inst.result);
					break;
				default: break;
			}
			dellock();
		}

		void dellock() {
			switch(inst.type) {
				case JALR:
				case BEQ:
				case BNE:
				case BLT:
				case BLTU:
				case BGE:
				case BGEU:
					reg -> usedpc --;
					break;
				default: break;
			}
		}
};

# endif
