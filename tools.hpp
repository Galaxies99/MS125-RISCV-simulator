# include <iostream>
# include <string.h>

using namespace std;

# ifndef _TOOLS_HPP_
	# define _TOOLS_HPP_

	uint decode16(char c) {
		if(c >= '0' && c <= '9') return c - '0';
		else return c - 'A' + 10;
	}

	uint decode16(char *str) {
		uint res = 0;
		for (int i=0; str[i]; ++i)
			res = (res << 4) + decode16(str[i]);
		return res;
	}

	uint sgnextend(uint x, int top) {
		if((x >> top) & 1) x |= (0xffffffff >> top << top);
		return x;
	}

	uint setlowzero(uint x) {
		if(x & 1) return x ^ 1;
		else return x;
	}

	int tosgn(uint x) {
		if ((x >> 31) & 1) {
			x ^= 0xffffffff;
			return -(x + 1);
		} else return x;
	}

	void putinbinary(uint x) {
		int w[33], wn=0;
		for (int i=1; i<=32; ++i) w[i] = 0;
		while(x) {
			w[++wn] = (x&1);
			x >>= 1;
		}
		for (int i=32; i; --i) {
			cout << w[i];
			if(i == 8) cout << ' ';
		}
		cout << endl;
	}

	void puttype(InstructionType type) {
		switch(type) {
			case EMPTY: puts("EMPTY"); break;
			case LUI: puts("LUI"); break;
			case AUIPC: puts("AUIPC"); break;
			case JAL: puts("JAL"); break;
			case JALR: puts("JALR"); break;
			case BEQ: puts("BEQ"); break;
			case BNE: puts("BNE"); break;
			case BLT: puts("BLT"); break;
			case BGE: puts("BGE"); break;
			case BLTU: puts("BLTU"); break;
			case BGEU: puts("BGEU"); break;
			case LB: puts("LB"); break;
			case LH: puts("LH"); break;
			case LW: puts("LW"); break;
			case LBU: puts("LBU"); break;
			case LHU: puts("LHU"); break;
			case SB: puts("SB"); break;
			case SH: puts("SH"); break;
			case SW: puts("SW"); break;
			case ADDI: puts("ADDI"); break;
			case SLTI: puts("SLTI"); break;
			case SLTIU: puts("SLTIU"); break;
			case XORI: puts("XORI"); break;
			case ORI: puts("ORI"); break;
			case ANDI: puts("ANDI"); break;
			case SLLI: puts("SLLI"); break;
			case SRLI: puts("SRLI"); break;
			case SRAI: puts("SRAI"); break;
			case ADD: puts("ADD"); break;
			case SUB: puts("SUB"); break;
			case SLL: puts("SLL"); break;
			case SLT: puts("SLT"); break;
			case SLTU: puts("SLTU"); break;
			case XOR: puts("XOR"); break;
			case SRL: puts("SRL"); break;
			case SRA: puts("SRA"); break;
			case OR: puts("OR"); break;
			case AND: puts("AND"); break;
		}
	}

	inline void putinhex(uint x) {
		int w[6], wn=0;
		for (int i=0;i<6; ++i) w[i] = 0;
		while(x) {
			int p = (x&15);
			w[++wn] = p;
			x >>= 4;
		}
		for (int i=wn; i; --i)
			if(w[i] < 10) printf("%d", w[i]);
			else printf("%c", w[i]-10+'A');
	}


# endif
