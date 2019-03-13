//
// Created by Megan's ISU on 2019-03-05.
//

#include <stdio.h>

int main(int argc, char *argv[]){
	int i ;
	unsigned long long prod ;
	unsigned long long r = 1 , oo = 2 , Ke = 5 , in = 5 , n = 5 ,
			v = 3251 , a = 3371 , p = 51287 , G = 52027;
	prod = Ke * v * in * ( G * n * a * p * oo + r );
	for ( i = 0; i < 8; i ++) {
		putchar ((( char *) & prod )[ i ]);
	}
	putchar ('\n');
	printf("%llu\n", prod);
	return 0;
}
