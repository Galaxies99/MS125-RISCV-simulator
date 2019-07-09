# include "memoryaccess.hpp"
# include "register.hpp"
# include "tools.hpp"

# ifndef _EXECUTION_
	# define _EXECUTION_

class Execution {
		friend class RISCV;
	private:
		Register *reg;

	public:
		Instruction inst;

		Execution(Register *_reg) {
			reg = _reg;
		}

		void go() {
			if(inst.type == ERR) return ;
			switch(inst.type) {
				case LUI: inst.result = inst.imm; break;
				case AUIPC: inst.result = inst.src1 - 4 + inst.imm; break;
				case JALR: inst.resultpc = inst.src1 + inst.imm; inst.resultpc = setlowzero(inst.resultpc); break;
				case BEQ: inst.result = static_cast <uint> (inst.src1 == inst.src2); break;
				case BNE: inst.result = static_cast <uint> (inst.src1 != inst.src2); break;
			  case BLTU: inst.result = static_cast <uint> (inst.src1 < inst.src2); break;
				case BGEU: inst.result = static_cast <uint> (inst.src1 >= inst.src2); break;
				case BLT: inst.result = static_cast <uint> ((int)inst.src1 < (int)inst.src2); break;
			  case BGE: inst.result = static_cast <uint> ((int)inst.src1 >= (int)inst.src2); break;
				case LB:
				case LW:
				case LH:
				case LHU:
				case LBU: inst.src1 = inst.src1 + sgnextend(inst.imm, 11); break;
				case SB:
				case SW:
				case SH: inst.src1 = inst.src1 + sgnextend(inst.imm, 11); break;
				case ADDI: inst.result = inst.src1 + inst.imm; break;
				case SLTI: inst.result = static_cast <uint> ((int)inst.src1 < (int)inst.imm); break;
				case SLTIU: inst.result = static_cast <uint> (inst.src1 < inst.imm); break;
				case ANDI: inst.result = (inst.src1 & inst.imm); break;
				case ORI: inst.result = (inst.src1 | inst.imm); break;
				case XORI: inst.result = (inst.src1 ^ inst.imm); break;
				case SLLI: inst.result = (inst.src1 << inst.imm); break;
				case SRLI: inst.result = (inst.src1 >> inst.imm); break;
				case SRAI: inst.result = ((inst.src1 >> inst.imm) | (inst.src1 >> 31 << 31)); break;
				case ADD: inst.result = inst.src1 + inst.src2; break;
				case SUB: inst.result = inst.src1 - inst.src2; break;
				case SLL: inst.result = (inst.src1 << inst.src2); break;
				case SRL: inst.result = (inst.src1 >> inst.src2); break;
				case SRA: inst.result = ((inst.src1 >> inst.src2) | (inst.src1 >> 31 << 31)); break;
				case SLT: inst.result = static_cast <uint> ((int)inst.src1 < (int)inst.src2); break;
				case SLTU: inst.result = static_cast <uint> (inst.src1 < inst.src2); break;
				case XOR: inst.result = (inst.src1 ^ inst.src2); break;
				case OR: inst.result = (inst.src1 | inst.src2); break;
				case AND: inst.result = (inst.src1 & inst.src2); break;
				default: break;
			}
		}
		
    bool check() {
      if(inst.type == BEQ || inst.type == BNE || inst.type == BGE || inst.type == BLT || inst.type == BGEU || inst.type == BLTU) {
        if(inst.result == 0) {
          reg -> setpc(inst.resultpc);
          return false;
        }
        return true;
      }
      return true;
    }
		
    void pass(MemoryAccess &nxt) {
			nxt.inst = inst;
		}
};

# endif
