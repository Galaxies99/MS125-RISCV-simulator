# ifndef _TYPE_HPP_
	# define _TYPE_HPP_

	typedef unsigned int uint;

	enum InstructionType {EMPTY, ERR, LUI, AUIPC, JAL, JALR, BEQ, BNE, BLT, BGE, BLTU,BGEU, LB, LH, LW, LBU, LHU, SB, SH, SW, ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI, SRAI, ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND};
	enum pipelineType {Serial, Pararrel};

	const int max_memory = 0x3fffff;

# endif
