#include <iostream> 
#include <vector>

#define CPP2_PRIME_UPPER_LIMIT 1000000 //探索する値の上限値。 

bool IsPrime(int num)
{
	if (num < 2) return false;
	else if (num == 2) return true;
	else if (num % 2 == 0) return false; 

	double sqrtNum = sqrt(num);
	for (int i = 3; i <= sqrtNum; i += 2)
	{
		if (num % i == 0)
		{
			return false;
		}
	}

	return true;
}
/* --------------------------------------------------------------- */
/*
 *  nth_prime
 *
 *  与えられた正整数 a と d と n に対して、この等差数列に含まれる n 番目の
 *  素数を返す。
 *
 *  TODO: この nth_prime 関数を実装せよ。必要であれば他に関数や
 *  ファイルを作成せよ。
 */
 /* -------------------------------------------------------------- */
int nth_prime(unsigned int a, unsigned int d, unsigned int n) {
	unsigned int* numptr;
	numptr = (unsigned int *)malloc(sizeof(unsigned int) * CPP2_PRIME_UPPER_LIMIT);

	unsigned int* prime;
	prime = (unsigned int *)malloc(sizeof(unsigned int) * CPP2_PRIME_UPPER_LIMIT);
	//最初の数字
	numptr[0] = a;

	for (int i = 1; i < CPP2_PRIME_UPPER_LIMIT; i++) {
		numptr[i] = numptr[i - 1] + d;
	}
	
	uint32_t prime_index = 0;
	for (int i = 0; i < CPP2_PRIME_UPPER_LIMIT; i++) {
		if (IsPrime(numptr[i]) == true) {
			prime[prime_index] = numptr[i];
			prime_index++;
		}
	}


	return prime[n - 1];
};


int main() {
	std::cout << nth_prime(367,186,151) << std::endl;

	return 0;
}