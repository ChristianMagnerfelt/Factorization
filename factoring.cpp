/*!
 *	\brief		This is a program that performs factorization of numbers
 *	\details
 *	\author		Christian Magnerfelt and Rasmus Göransson
 *	\date		2012.09.27
 */
#include <gmpxx.h>

#include <iostream>
#include <sstream>

#include "primes1.h"
#include "wheel1.h"

int main(int argc, const char * argv [])
{
	const int num_wheel1 = sizeof(wheel1) / sizeof(int);
	const int num_primes1 = sizeof(primes1) / sizeof(int);
	int biggest_prime = primes1[num_primes1-1];
	// base0 is the highest multiple of wheel1_n which is lower than the biggest prime
	int base0 = (biggest_prime/wheel1_n) * wheel1_n;

	mpz_class value;
	mpz_class sqrt;
	mpz_class q;
	mpz_class r;
	mpz_class p;

	for(int i = 0; i < 100; ++i)
	{
		// Read value to factor
		std::cin >> value;

		// Don't attempt to factor if input is a prime
		if( mpz_probab_prime_p (value.get_mpz_t(), 10) )
		{
			std::cout << value << std::endl;
			std::cout << std::endl;
			continue;
		}

		// Postpone output
		std::stringstream ss;
		bool done = false;

		// Calculate square root
		mpz_sqrt(sqrt.get_mpz_t(), value.get_mpz_t());

		// Trial division against known primes
		for(int i = 0; i < num_primes1; ++i)
		{
			// Division with the ith prime number
			p = primes1[i];

			// Stop when we reach the sqrt
			if (p > sqrt)
			{
				done = true;
				break;
			}

			// Test division
			mpz_cdiv_qr(q.get_mpz_t(),r.get_mpz_t(), value.get_mpz_t(), p.get_mpz_t());

			if (r == 0)
			{
				// If a factor is found, divide away until the factor is gone
				do
				{
					// Update value and print factor
					value = q;
					ss << p << std::endl;
					mpz_cdiv_qr(q.get_mpz_t(),r.get_mpz_t(), value.get_mpz_t(), p.get_mpz_t());
				} while(r == 0);

				// Stop if the value looks like a prime now
				if( value == 1 || mpz_probab_prime_p (value.get_mpz_t(), 10) )
				{
					done = true;
					break;
				}

				// Recalculate sqrt
				mpz_sqrt(sqrt.get_mpz_t(), value.get_mpz_t());
			}
		}

		// Wheel factoring
		if ( !done )
		{
			// Iterate over the circles in the wheel (radius)
			mpz_class base = base0;
			for (int k = 0; !done && k < 20; ++k, base += wheel1_n)
			{
				// Try the spokes in the wheel (angle)
				for (int i = 0; i < num_wheel1; ++i)
				{
					p = base + wheel1[i];

					// Stop when we reach the sqrt
					if (p > sqrt)
					{
						done = true;
						break;
					}

					// Test division
					mpz_cdiv_qr(q.get_mpz_t(),r.get_mpz_t(), value.get_mpz_t(), p.get_mpz_t());

					if (r == 0)
					{
						// If a factor is found, divide away until the factor is gone
						do
						{
							// Update value and print factor
							value = q;
							ss << p << std::endl;
							mpz_cdiv_qr(q.get_mpz_t(),r.get_mpz_t(), value.get_mpz_t(), p.get_mpz_t());
						} while(r == 0);

						// Stop if the value looks like a prime now
						if( value == 1 || mpz_probab_prime_p (value.get_mpz_t(), 10) )
						{
							done = true;
							break;
						}

						// Recalculate sqrt
						mpz_sqrt(sqrt.get_mpz_t(), value.get_mpz_t());
					}
				}
			}
		}

		// Did we nail it?
		if( done )
		{
			// Print the factors
			std::cout << ss.str();

			// Print the last factor
			if(value > 1)
				std::cout << value << std::endl;
		}
		else
		{
			std::cout << "fail" << std::endl;
		}

		// Empty line between each answer
		std::cout << std::endl;
	}
	return 0;
}
