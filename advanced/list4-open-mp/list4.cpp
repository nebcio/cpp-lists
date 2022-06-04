/* 1 
#include <iostream>
#include <omp.h>
int main()
{
#pragma omp parallel

	{
		std::cout << "pragma omp parallel\nThread nr " << omp_get_thread_num()
			<< " / " << omp_get_num_threads() << "\n";
		//std::cout << "pragma omp parallel2\nThread nr " << omp_get_thread_num()
			//<< " / " << omp_get_num_threads() << "\n";
	}
#pragma omp single
	{	// Thread 0 / 1
		std::cout << "pragma omp single\nThread nr " << omp_get_thread_num()
			<< " / " << omp_get_num_threads() << "\n";
	}
#pragma omp master
	{	// Thread 0 / 1
		std::cout << "pragma omp master\nThread nr " << omp_get_thread_num()
			<< " / " << omp_get_num_threads() << "\n";
	}
#pragma omp critical
	{	// Thread 0 / 1
		std::cout << "pragma omp critical\nThread nr " << omp_get_thread_num()
			<< " / " << omp_get_num_threads() << "\n";
	}
}
/*
parallel okresla segment kodu ktory bedzie wykonywany przez wiele watkow
1. Nie. Dlatego ze rozne watki obsluguja w roznym tempie te sama instrukcje,
   naszemu programowi moze zostac przydzielony inny zestaw rdzeni/watkow,
   tworzy domyslnie watki na 1 rdzeniu, umnie 4, dodatkowo strumien cout jest wspoldzielony 
2. single - dany fragment kodu wykonywany jest przez jeden watek, w parallel mozna dac kilka razy wtedy 
   master - single, tylko przez watek glowny programu
   critical - rozne watki ale po kolei (jeden watek na raz)
*/

/* 2 */

#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <iostream>
int main()
{
	const int N = 1000000000;
	int i = 0;
	double sum = 0;
	clock_t t0 = clock();

	/* bez parallel 3.257 s
	// z parallel 1.171 s
	// aby zawsze wyświetlał się poprawny wynik potrzeba floaty zaminić na double
	// clock nie zwraca czasu rzeczywistego
	// clock zwraca ilosc taktow zegara od poczatku programu, 
	// specyficznie dla kazdego systemu okreslenie najmniejszej jednostki (CLOCKS_PER_SEC)
	// w zalezności od obciazenia CPU moze być szybszy lub wolniejszy niz wallclock */

#pragma omp parallel for private(i) reduction(+:sum)
	for (i = N - 1; i >= 0; --i) {
		sum += 1.0 / (i + 1.0);
	}

	clock_t t1 = clock();
	printf("4: s = %g\n", sum);
	printf("4: t = %g\n", ((double)t1 - t0) / CLOCKS_PER_SEC);
	
	sum = 0.0, t0 = clock();
#pragma omp parallel for private(i) reduction(+:sum) num_threads(2)
	for (i = N - 1; i >= 0; --i) {
		sum += 1.0 / (i + 1.0);
	}

	t1 = clock();
	printf("2: s = %g\n", sum);
	printf("2: t = %g\n", ((double)t1 - t0) / CLOCKS_PER_SEC);

	sum = 0.0, t0 = clock();
#pragma omp parallel for private(i) reduction(+:sum) num_threads(1)
	for (i = N - 1; i >= 0; --i) {
		sum += 1.0 / (i + 1.0);
	}

	t1 = clock();
	printf("1: s = %g\n", sum);
	printf("1: t = %g\n", ((double)t1 - t0) / CLOCKS_PER_SEC);

	/* dla wiekszej liczby watkow program jest szybszy
	 * jednak przy daniu float wyniki sie roznia dla kazdej liczby watkow
	 * najmniejszy wynik przyszedl dla 1 watku a najwiekszy dla 4, ale zaden prawdziwy
	 * Polecenie usr/bin/time -> elapsed/real oznacza czas tzw wallclock
	 * nie znalazlam informacji o ilosci watkow, ale jest informacja o procencie CPU ktory wykonal ten program
	 * nie znalazlam sposobu na zmiane liczby watkow z terminala, wiec zrobilam to z kodu
	*/
}