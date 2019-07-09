# include "execution.hpp"
# include "register.hpp"

# ifndef _INSTRUCTIONDECODE_
	# define _INSTRUCTIONDECODE_

class InstructionDecode {
		friend class RISCV;
	private:
		Register *reg;

	public:
		Instruction inst;
		bool lock;

		InstructionDecode(Register *_reg) {
			lock = 0;
			reg = _reg;
		}

		void go() {
			lock = 0;
			if(inst.type == ERR) return ;
			inst.getType();
			inst.getArg();
			if(!getTrueArg()) lock = 1;
			else putlock();
		}

		uint getReg(uint pos) {return reg -> get(pos);}

		bool getTrueArg() {
			switch(inst.type) {
				case AUIPC:
					if(reg -> usedpc) return false;
					inst.src1 = reg -> getpc();
					break;
				case JAL:
					if(reg -> usedpc) return false;
					inst.src1 = reg -> getpc();
					break;
				case JALR:
					if(reg -> usedpc) return false;
					inst.src1 = getReg(inst.rs1);
					inst.result = reg -> getpc();
					break;
				case BEQ:
				case BNE:
				case BLT:
				case BLTU:
				case BGE:
				case BGEU: 
					if(reg -> usedpc) return false;
					inst.src1 = getReg(inst.rs1);
					inst.src2 = getReg(inst.rs2);
					inst.resultpc = reg -> getpc();
					break;
				case LB:
				case LH:
				case LW:
				case LBU:
				case LHU:
					inst.src1 = getReg(inst.rs1);
					break;
				case SW:
				case SH:
				case SB:
					inst.src1 = getReg(inst.rs1);
					inst.src2 = getReg(inst.rs2);
					break;
				case ADDI:
				case SLTI:
				case SLTIU:
				case ANDI:
				case ORI:
				case XORI:
					inst.src1 = getReg(inst.rs1);
					break;
				case SLLI:
				case SRLI:
				case SRAI:
					inst.src1 = getReg(inst.rs1);
					break;
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
					inst.src1 = getReg(inst.rs1);
					inst.src2 = getReg(inst.rs2);
					break;
				default: break;
			}
			return true;
		}

		void pass(Execution &nxt) {
			nxt.inst = inst;
			if(lock) nxt.inst.type = ERR;
		}

		void putlock() {
			switch(inst.type) {
				case JALR:
					reg -> usedpc ++;
					break;
				default: break;
			}
		}

};

# endif
