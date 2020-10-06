#include <cstdio>
#include <_Time.h>

template<unsigned long long order>struct Group
{
	//table[a][b] = a*b
	unsigned long long table[order][order];
	unsigned long long inverse[order];

	Group() = default;
	Group(unsigned long long _table[order][order])
		:
		table(),
		inverse()
	{
		::memcpy(table, _table, sizeof(table));
		for (unsigned long long c0(0); c0 < order; ++c0)
			for (unsigned long long c1(0); c1 < order; ++c1)
				if (_table[c0][c1] == 0)inverse[c0] = c1;
	}
	unsigned long long operator()(unsigned long long a, unsigned long long b)const
	{
		return table[a][b];
	}
	bool judge(unsigned long long exchange[order])
	{
		for (unsigned long long c0(0); c0 < order; ++c0)
		{
			unsigned long long ai(exchange[c0]);
			for (unsigned long long c1(0); c1 < order; ++c1)
			{
				unsigned long long aj(exchange[c1]);
				if (table[ai][aj] != exchange[table[c0][c1]])
					return false;
			}
		}
		return true;
	}
};

unsigned long long D3Table[6][6]
{
	{0, 1, 2, 3, 4, 5},
	{1, 2, 0, 5, 3, 4},
	{2, 0, 1, 4, 5, 3},
	{3, 4, 5, 0, 1, 2},
	{4, 5, 3, 2, 0, 1},
	{5, 3, 4, 1, 2, 0}
};

unsigned long long factorial(unsigned long long a)
{
	unsigned long long r(1);
	while (a)r *= a--;
	return r;
}

int main()
{
	Group<6> origin(D3Table);
	unsigned long long factorials[6]
	{
		factorial(0),
		factorial(1),
		factorial(2),
		factorial(3),
		factorial(4),
		factorial(5)
	};
	unsigned long long num(factorials[5]);
	for (unsigned long long c0(0); c0 < num; ++c0)
	{
		unsigned long long selected[5]{ 0 };
		unsigned long long exchange[6];
		unsigned long long r(c0);
		exchange[0] = 0;
		for (long long c1(4); c1 >= 0; --c1)
		{
			unsigned long long p(r / factorials[c1]);
			unsigned long long pos(0), q(0);
			while (q != p || selected[pos])
				if (selected[pos++] == 0)q++;
			selected[pos] = 1;
			exchange[c1 + 1] = pos + 1;
			r %= factorials[c1];
		}
		if (origin.judge(exchange))
		{
			for (unsigned long long c1(0); c1 < 6; ++c1)
				::printf("%llu ", exchange[c1]);
			::printf("\n");
		}
	}
	::printf("\n");
	for (unsigned long long c0(0); c0 < 6; ++c0)
	{
		for (unsigned long long c1(0); c1 < 6; ++c1)
			::printf("%llu ", origin(origin(c0, c1), origin.inverse[c0]));
		::printf("\n");
	}
}
