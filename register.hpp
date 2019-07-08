# include "memory.hpp"
# include "type.hpp"

# ifndef _REGISTER_
	# define _REGISTER_

	class Register {
		private:
			uint data[32];
			uint pc;
			memory *mem;

		public:

			int usedpc;
			int used[32];

			Register(uint _pc, memory *_mem) {
				for (int i=0; i<32; ++i) data[i] = 0, used[i] = 0;
				pc = _pc; usedpc = 0;
				mem = _mem;
			}

			void setpc(uint dat) {
				pc = dat;
			}

			void set(int pos, uint dat) {
				if(pos == 0) return ;
				data[pos] = dat;
			}

			uint get(int pos) {
				if(pos == 0) return 0u;
				return data[pos];
			}

			uint getpc() {
				return pc;
			}

			uint load(uint pos, int p) {
				uint res = 0, temp[4];
				for (int i=0; i<p; ++i) temp[i] = static_cast <uint> (mem -> get(pos + i));
				for (int i=p-1; ~i; --i) res = (res << 8) + temp[i];
				return res;
			}

			void store(uint pos, uint x, int p) {
				uint temp[4];
				for (int i=0; i<4; ++i) {
					temp[i] = (x & 255);
					x >>= 8;
				}
				for (int i=0; i<p; ++i) {
					mem -> set(pos, static_cast <unsigned char> (temp[i]));
					++pos;
				}
			}

			uint getinst() {
				uint res = load(pc, 4);
				pc += 4;
				return res;
			}

			bool isClear() {
				if(usedpc) return false;
				for (int i=0; i<32; ++i) if(used[i]) return false;
				return true;
			}

	};


# endif
