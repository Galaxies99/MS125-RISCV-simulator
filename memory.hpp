# include "type.hpp"
# include "tools.hpp"

# ifndef _MEMORY_
	# define _MEMORY_

class memory {
	private:
		unsigned char data[max_memory + 5];
		bool ret;

	public:

		memory() {
			memset(data, 0, sizeof data);
			ret = 0;
		}

		inline void set(uint pos, unsigned char x) {
			data[pos] = x;
			if(pos == 0x30004) ret = 1;
		}

		inline unsigned char get(uint pos) const {return data[pos];}

		inline void loadFromDisk() {
			char buf[15];
			for (int i=0; i<15; ++i) buf[i] = 0;
			int cursor = 0;
			while(~scanf("%s", buf)) {
				if(buf[0] == '@') {
					cursor = decode16(buf + 1);
				} else {
					data[cursor] = static_cast <unsigned char> (decode16(buf));
					cursor ++;
				}
				for (int i=0; i<15; ++i) buf[i] = 0;
			}
		}

		inline bool isEnd() {return ret;}

		inline void debug() {
			for (int i=0; i <= max_memory; ++i)
				if(data[i] != 0) printf("%d %d\n", i, (uint)data[i]);
		}
};

# endif