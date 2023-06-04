/*
 *  Introduction to Software Security Assignment (Laboratory) 5 
 *  Rand() library function vs RDRAND assembly instruction (x86_64 architecture)
 *  Copyright (C) 2023  Roy Simanovich
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * @brief The number of iterations for the benchmark.
 * @note The higher the number, the more accurate the benchmark is.
 * @note The default value is 100 iterations.
*/
#define CYCLES					100

/*
 * @brief A wrapper function for the RDRAND instruction.
 * @return The generated random number (64-bit).
 * @note The function is implemented in assembly, and is compatible with x86_64 architecture only.
*/
__asm__("rdrand_effective:\n" 	// The function name
		"	RDRAND %rax\n" 		// The RDRAND instruction
		"	ret\n"			 	// Return the generated random number
		);

/*
 * @brief Generates a random number using the RDRAND instruction.
 * @return The generated random number (64-bit).
 * @note The function is implemented in assembly.
 * @note The function is implemented for x86_64 architecture.
*/
extern long long int rdrand_effective(void);

int main(void) {
	clock_t start_rand, end_rand;
	clock_t start_rdrand, end_rdrand;
	long long int time_rand = 0, time_rdrand = 0;
	long long int rand_value = 0, rdrand_value = 0;

	for (int i = 0; i < CYCLES; i++)
	{
		start_rand = clock();
		srand(time(NULL)); // The seed is set to the current time, to prevent the rand() function from generating the same number every time.
		rand_value = rand();
		end_rand = clock();

		start_rdrand = clock();
		rdrand_value = rdrand_effective();
		end_rdrand = clock();

		time_rand += (end_rand - start_rand);
		time_rdrand += (end_rdrand - start_rdrand);

		fprintf(stdout, "Iteration #%d:\n", (i + 1));
		fprintf(stdout, "rand() library function took %ld microseconds; Generated number: %lld.\n", end_rand - start_rand, rand_value);
		fprintf(stdout, "RDRAND assembly instruction took %ld microseconds; Generated number: %lld.\n", end_rdrand - start_rdrand, rdrand_value);
	}

	fprintf(stdout, "\nBenchmark results:\n");
	fprintf(stdout, "Number of iterations: %d.\n", CYCLES);
	fprintf(stdout, "Total time for rand() library function: %lld microseconds.\n", time_rand);
	fprintf(stdout, "Total time for RDRAND assembly instruction: %lld microseconds.\n", time_rdrand);
	fprintf(stdout, "Average time for rand() library function: %.3Lf microseconds.\n", ((long double)time_rand / CYCLES));
	fprintf(stdout, "Average time for RDRAND assembly instruction: %.3Lf microseconds.\n", ((long double)time_rdrand / CYCLES));

	return 0;
}