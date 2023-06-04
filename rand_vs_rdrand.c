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
#include <unistd.h>

/*
 * @brief The number of iterations for the benchmark.
 * @note The higher the number, the more accurate the benchmark is.
 * @note The default value is 1000000 iterations.
*/
#define CYCLES					1000000

/*
 * @brief The time in seconds to wait before the benchmark starts.
 * @note The default value is 3 seconds.
*/
#define WAIT_TIME				3

/*
 * @brief A flag to show the steps of the benchmark.
 * @note If the flag is defined, the benchmark will show the steps of the benchmark.
 * @note If the flag is not defined, the benchmark will not show the steps of the benchmark.
 * @note The default value is not defined.
*/
//#define SHOW_STEPS

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

#ifdef SHOW_STEPS
	long long int rand_value = 0, rdrand_value = 0;
#endif // SHOW_STEPS

	fprintf(stdout, "\t\t\033[0;36mRand() vs RDRAND benchmark\n\n"
					"\tCopyright (C) 2023  Roy Simanovich\n"
					"\tThis program comes with ABSOLUTELY NO WARRANTY.\n"
					"\tThis is free software, and you are welcome to redistribute it\n"
					"\tunder certain conditions; see `LICENSE' for details.\033[0;37m\n\n");

	fprintf(stdout, "This benchmark compares the performance of rand() library function versus the RDRAND assembly instruction (x86_64 architecture).\n");

	fprintf(stdout, "\033[0;36mThe benchmark will run \033[0;32m%d\033[0;36m times.\033[0;37m\n", CYCLES);
	fprintf(stdout, "\033[0;36mThe benchmark will show the steps:\033[0;37m ");
#ifdef SHOW_STEPS
	fprintf(stdout, "\033[0;32mYes\033[0;37m\n");
#else
	fprintf(stdout, "\033[0;31mNo\033[0;37m\n");
#endif // SHOW_STEPS

	fprintf(stdout, "\033[0;36mThe benchmark will start in %d seconds.\033[0;37m\n", WAIT_TIME);
	sleep(WAIT_TIME);

	srand(time(NULL)); // The seed is set to the current time, to prevent the rand() function from generating the same number every time.

	for (int i = 0; i < CYCLES; i++)
	{
		start_rand = clock();
#ifdef SHOW_STEPS
		rand_value = rand();
#else
		rand();
#endif // SHOW_STEPS
		end_rand = clock();

		start_rdrand = clock();
#ifdef SHOW_STEPS
		rdrand_value = rdrand_effective();
#else
		rdrand_effective();
#endif // SHOW_STEPS
		end_rdrand = clock();

		time_rand += (end_rand - start_rand);
		time_rdrand += (end_rdrand - start_rdrand);

#ifdef SHOW_STEPS
		fprintf(stdout, "Iteration #%d:\n", (i + 1));
		fprintf(stdout, "rand() library function took %ld microseconds; Generated number: %lld.\n", end_rand - start_rand, rand_value);
		fprintf(stdout, "RDRAND assembly instruction took %ld microseconds; Generated number: %lld.\n", end_rdrand - start_rdrand, rdrand_value);
#endif // SHOW_STEPS
	}

	fprintf(stdout, "\n\033[0;32mThe benchmark has finished.\033[0;37m\n\n"
					"\t\t\t\t\033[0;36mBenchmark results:\033[0;37m\n");
	fprintf(stdout, "\tTotal time for rand() library function: \033[0;32m%lld\033[0;37m microseconds.\n", time_rand);
	fprintf(stdout, "\tTotal time for RDRAND assembly instruction: \033[0;32m%lld\033[0;37m microseconds.\n", time_rdrand);
	fprintf(stdout, "\tAverage time for rand() library function: \033[0;32m%.3Lf\033[0;37m microseconds.\n", ((long double)time_rand / CYCLES));
	fprintf(stdout, "\tAverage time for RDRAND assembly instruction: \033[0;32m%.3Lf\033[0;37m microseconds.\n", ((long double)time_rdrand / CYCLES));

	fprintf(stdout, "\n\033[0;36mConclusion:\033[0;37m ");

	if (time_rand > time_rdrand)
		fprintf(stdout, "\033[0;32mRDRAND assembly instruction is faster than rand() library function.\033[0;37m\n");

	else if (time_rand < time_rdrand)
		fprintf(stdout, "\033[0;31mrand() library function is faster than RDRAND assembly instruction.\033[0;37m\n");
	
	else
		fprintf(stdout, "\033[0;33mRDRAND assembly instruction and rand() library function are equally fast.\033[0;37m\n");

	return 0;
}