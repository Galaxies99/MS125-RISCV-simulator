# include "type.hpp"
# include "forward.hpp"
# include "tools.hpp"
# include "instruction.hpp"
# include "memory.hpp"
# include "register.hpp"
# include "instructionfetch.hpp"
# include "instructiondecode.hpp"
# include "execution.hpp"
# include "memoryaccess.hpp"
# include "writeback.hpp"

# ifndef _RISCV_HPP_
	# define _RISCV_HPP_

	class RISCV {
		private:
			memory *mem;
			Register reg;
			InstructionFetch IF;
			InstructionDecode ID;
			Execution EX;
			MemoryAccess MA;
			WriteBack WB;
			pipelineType type;

			void pararrel() {
				int cnt = 0;
        while(1) {
					WB.go();
					MA.go();
					Forward(MA, EX);
					EX.go();
					if(EX.inst.type != ERR && EX.check() == 0) ID.reget();
					ID.go();
					if(!ID.lock) {
            Forward(MA, ID);
					  Forward(EX, ID);
					  if(ID.inst.type == JAL) {
					    reg.set(ID.inst.rd, ID.inst.src1);
              reg.setpc(ID.inst.src1 - 4 + ID.inst.imm);
              ID.inst.type = ERR;
            }
					}
					if(!ID.lock) IF.go();
          if(mem -> isEnd()) break;
					MA.pass(WB);
					EX.pass(MA);
					ID.pass(EX);
					if(!ID.lock) IF.pass(ID);
				}
			}

			void serial() {
				while(!mem -> isEnd()) {
					IF.go();
					IF.pass(ID);
					ID.go();
					ID.pass(EX);
					EX.go();
					EX.pass(MA);
					MA.go();
					MA.pass(WB);
					WB.go();
				}
			}

		public:
			RISCV (memory *_mem, pipelineType _type) : reg(0, _mem), IF(&reg), ID(&reg), EX(&reg), MA(&reg), WB(&reg) { mem = _mem; type = _type; }

			void run() {
				if(type == Pararrel) pararrel();
				if(type == Serial) serial();
			}

			uint output() {
				return ((reg.get(10)) & 255u);
			}
	};


# endif

