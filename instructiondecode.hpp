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
					inst.src1 = reg -> getpc() - 4;
					break;
				case JAL:
					if(reg -> usedpc) return false;
					inst.src1 = reg -> getpc() - 4;
					break;
				case JALR:
					if(inst.rs1 && reg -> used[inst.rs1]) return false;
					if(reg -> usedpc) return false;
					inst.src1 = getReg(inst.rs1);
					inst.src2 = reg -> getpc();
					break;
				case BEQ:
				case BNE:
				case BLT:
				case BLTU:
				case BGE:
				case BGEU:
					if(inst.rs1 && reg -> used[inst.rs1]) return false;
					if(inst.rs2 && reg -> used[inst.rs2]) return false;
					if(reg -> usedpc) return false;
					inst.src1 = getReg(inst.rs1);
					inst.src2 = getReg(inst.rs2);
					inst.rd = reg -> getpc();
					break;
				case LB:
				case LH:
				case LW:
				case LBU:
				case LHU:
					if(inst.rs1 && reg -> used[inst.rs1]) return false;
					inst.src1 = getReg(inst.rs1);
					break;
				case SW:
				case SH:
				case SB:
					if(inst.rs1 && reg -> used[inst.rs1]) return false;
					if(inst.rs2 && reg -> used[inst.rs2]) return false;
					inst.src1 = getReg(inst.rs1);
					inst.src2 = getReg(inst.rs2);
					break;
				case ADDI:
					if(inst.rs1 && reg -> used[inst.rs1]) return false;
					inst.src1 = getReg(inst.rs1);
					break;
				case SLTI:
				case SLTIU:
					if(inst.rs1 && reg -> used[inst.rs1]) return false;
					inst.src1 = getReg(inst.rs1);
					break;
				case ANDI:
				case ORI:
				case XORI:
					if(inst.rs1 && reg -> used[inst.rs1]) return false;
					inst.src1 = getReg(inst.rs1);
					break;
				case SLLI:
				case SRLI:
				case SRAI:
					if(inst.rs1 && reg -> used[inst.rs1]) return false;
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
					if(inst.rs1 && reg -> used[inst.rs1]) return false;
					if(inst.rs2 && reg -> used[inst.rs2]) return false;
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
				case LUI:
					reg -> used[inst.rd] ++;
					break;
				case AUIPC:
					reg -> used[inst.rd] ++;
					break;
				case JAL:
					reg -> used[inst.rd] ++;
					reg -> usedpc ++;
					break;
				case JALR:
					reg -> used[inst.rd] ++;
					reg -> usedpc ++;
					break;
				case BEQ:
				case BNE:
				case BLT:
				case BLTU:
				case BGE:
				case BGEU:
					reg -> usedpc ++;
					break;
				case LB:
				case LW:
				case LH:
				case LBU:
				case LHU:
					reg -> used[inst.rd] ++;
					break;
				case ADDI:
					reg -> used[inst.rd] ++;
					break;
				case SLTI:
				case SLTIU:
					reg -> used[inst.rd] ++;
					break;
				case ANDI:
				case ORI:
				case XORI:
					reg -> used[inst.rd] ++;
					break;
				case SLLI:
				case SRLI:
				case SRAI:
					reg -> used[inst.rd] ++;
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
					reg -> used[inst.rd] ++;
					break;
				default: break;
			}
		}

};

# endif
