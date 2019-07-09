# include "type.hpp"
# include "tools.hpp"

# ifndef _INSTRUCTION_
	# define _INSTRUCTION_

class Instruction {
	public:
		InstructionType type;
		uint com;
		uint rs1, rs2, rd, imm;

		uint src1, src2;
		uint result;
		uint resultpc; 
		uint pred;

		Instruction() {
			initialize();
		}

		void initialize() {
			com = rs1 = rs2 = rd = imm = 0;
			src1 = src2 = 0; pred = 0;
			result = 0; resultpc = 0;
		}

		void getType() {
			uint opcode, func3, func7;
			opcode = (com & 127);
			func3 = ((com >> 12) & 7);
			func7 = ((com >> 25) & 127);
			switch (opcode) {
				case 55: type = LUI; break;				// 0110111
				case 23: type = AUIPC; break;  		// 0010111
				case 111: type = JAL; break;			// 1101111
				case 103: type = JALR; break; 		// 1100111
				case 99: 													// 1100011
					switch (func3) {
						case 0: type = BEQ; break;		// 000
						case 1: type = BNE; break; 		// 001
						case 4: type = BLT; break;		// 100
						case 5: type = BGE; break;		// 101
						case 6: type = BLTU; break;		// 110
						case 7: type = BGEU; break;		// 111
					}
					break;
				case 3:														// 0000011
					switch(func3) {
						case 0: type = LB; break;			// 000
						case 1: type = LH; break;			// 001
						case 2: type = LW; break;			// 010
						case 4: type = LBU; break;		// 100
						case 5: type = LHU; break;		// 101
					}
					break;
				case 35:													// 0100011
					switch(func3) {
						case 0:	type = SB; break;			// 000
						case 1: type = SH; break;			// 001
						case 2: type = SW; break;			// 010
					}
					break;
				case 19:													// 0010011
					switch(func3) {
						case 0: type = ADDI; break;		// 000
						case 1:	type = SLLI; break;		// 001
						case 2: type = SLTI; break;		// 010
						case 3: type = SLTIU; break;	// 011
						case 4: type = XORI;	break; 	// 100
						case 5:												// 101
							if(func7 == 0) type = SRLI;	// 0000000
							else type = SRAI;						// 0100000
							break;
						case 6: type = ORI; break;		// 110
						case 7: type = ANDI; break;		// 111
					}
					break;
				case 51:
					switch(func3) {
						case 0:												// 000
							if (func7 == 0) type = ADD;	// 0000000
							else type = SUB;						// 0100000
							break;
						case 1: type = SLL; break;		// 001
						case 2: type = SLT;	break;		// 010
						case 3: type = SLTU; break;		// 011
						case 4: type = XOR; break;		// 100
						case 5:												// 101
							if(func7 == 0) type = SRL;	// 0000000
							else type = SRA; 						// 0100000
							break;
						case 6: type = OR; break;			// 110
						case 7: type = AND; break;		// 111
					}
					break;
				default: type = ERR;
			}
		}

		void getArg() {
			uint tem1, tem2, tem3, tem4;
			switch(type) {
				case LUI:
				case AUIPC:
					imm = (com >> 12 << 12);
					rd = ((com >> 7) & 31);
					break;
				case JAL:
					tem1 = ((com >> 12) & 255), tem2 = ((com >> 20) & 1);
					tem3 = ((com >> 21) & 1023), tem4 = ((com >> 31) & 1);
					imm = (tem3 << 1) + (tem2 << 11) + (tem1 << 12) + (tem4 << 20);
					imm = sgnextend(imm, 20);
					rd = ((com >> 7) & 31);
					break;
				case JALR:
					imm = ((com >> 20) & 4095);
					imm = sgnextend(imm, 11);
					rd = ((com >> 7) & 31);
					rs1 = ((com >> 15) & 31);
					break;
				case BEQ:
				case BNE:
				case BLT:
				case BGE:
				case BLTU:
				case BGEU:
					tem1 = ((com >> 7) & 1), tem2 = ((com >> 8) & 15);
					tem3 = ((com >> 25) & 63), tem4 = ((com >> 31) & 1);
					imm = (tem2 << 1) + (tem3 << 5) + (tem1 << 11) + (tem4 << 12);
					imm = sgnextend(imm, 12);
					rs1 = ((com >> 15) & 31);
					rs2 = ((com >> 20) & 31);
					break;
				case LB:
				case LH:
				case LW:
				case LBU:
				case LHU:
					imm = ((com >> 20) & 4095);
					imm = sgnextend(imm, 11);
					rd = ((com >> 7) & 31);
					rs1 = ((com >> 15) & 31);
					break;
				case SB:
				case SH:
				case SW:
					tem1 = ((com >> 7) & 31);
					tem2 = ((com >> 25) & 127);
					imm = tem1 + (tem2 << 5);
					imm = sgnextend(imm, 11);
					rs1 = ((com >> 15) & 31);
					rs2 = ((com >> 20) & 31);
					break;
				case ADDI:
				case SLTI:
				case SLTIU:
				case XORI:
				case ORI:
				case ANDI:
					imm = ((com >> 20) & 4095);
					imm = sgnextend(imm, 11);
					rs1 = ((com >> 15) & 31);
					rd = ((com >> 7) & 31);
					break;
				case SLLI:
				case SRLI:
				case SRAI:
					rd = ((com >> 7) & 31);
					rs1 = ((com >> 15) & 31);
					imm = ((com >> 20) & 31);
					imm = sgnextend(imm, 4);
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
					rd = ((com >> 7) & 31);
					rs1 = ((com >> 15) & 31);
					rs2 = ((com >> 20) & 31);
					break;
			}
		}
};

# endif
