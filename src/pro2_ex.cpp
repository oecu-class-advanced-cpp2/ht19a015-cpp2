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
	if (n == 0) {
		throw std::exception("n must be more than one, or else, could cause access error");
	}

	//なんとなくnまでの整数を残しておく...
	//メモリアクセスの遅さを感じた
	uint32_t* prime;
	prime = (uint32_t *)malloc(sizeof(uint32_t) * n);

	//素数リストのインデックス
	uint32_t prime_index = 0;
	//最初の数字
	uint32_t num = a;

	for (int i = 1; i < CPP2_PRIME_UPPER_LIMIT; i++) {
		if (IsPrime(num) == true) {
			prime[prime_index] = num;
			prime_index++;
			if (prime_index > n) {
				break;
			}
		}
		num += d;
	}
	return prime[n - 1];
};


int main() {
	std::cout << nth_prime(367,186,151) << std::endl;
	std::cout << nth_prime(179, 10, 203) << std::endl;
	std::cout << nth_prime(271,37,39) << std::endl;
	std::cout << nth_prime(103,230,1) << std::endl;
	std::cout << nth_prime(27,104,185) << std::endl;
	std::cout << nth_prime(253,50,85) << std::endl;
	std::cout << nth_prime(1,1,1) << std::endl;
	std::cout << nth_prime(9075,337,210) << std::endl;
	std::cout << nth_prime(307,24,79) << std::endl;
	std::cout << nth_prime(331,221,177) << std::endl;
	std::cout << nth_prime(259,170,40) << std::endl;
	std::cout << nth_prime(269,58,102) << std::endl;
	return 0;
}