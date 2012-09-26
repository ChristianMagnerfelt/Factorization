/*!
 *	\brief		This is a program that performs factorization of numbers
 *	\details	
 *	\author		Christian Magnerfelt
 *	\date		2012.09.27
 */
#include <gmpxx.h>

#include <iostream>

int main(int argc, const char * argv [])
{
	mpz_class value;
	mpz_class sqrt;
	mpz_class q;
	mpz_class r;
	
	for(int i = 0; i < 100; ++i)
	{
		std::cin >> value;
		
		// Fail if input is a prime
		if( mpz_probab_prime_p (value.get_mpz_t(), 10) > 0)
		{
			std::cout << "fail" << std::endl;
			continue;
		}
	
		// Calculate square root
		mpz_sqrt(sqrt.get_mpz_t(), value.get_mpz_t());

		for(mpz_class i = 2; i <= sqrt; ++i)
		{
			if(mpz_probab_prime_p (i.get_mpz_t(), 10) > 0)
			{
				mpz_cdiv_qr(q.get_mpz_t(),r.get_mpz_t(), value.get_mpz_t(), i.get_mpz_t());
				if(r == 0)
				{
					value = q;
					std::cout << i << std::endl;
					--i;
				}
			}
		}
		if(value > 1)
			std::cout << value << std::endl;
		std::cout << std::endl;
	}
	return 0;
}

