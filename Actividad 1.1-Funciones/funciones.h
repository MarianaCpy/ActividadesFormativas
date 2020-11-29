#ifndef funciones_h
#define funciones_h

#include <iostream>
using namespace std;

class Funciones{
	public:
	long sumaIterativa(int n){
			long acum=0;		
			for (int i=1; i<=n; i++){
				acum += i;
			}
			if (n != 0)
				return acum;
			else
				return 0;
	}

	int sumaRecursiva(int n){
		if (n != 0)
			return n+sumaRecursiva(n-1);
		else
			return 0;
	}
	
	int sumaDirecta(int n){
		return (n*(n+1))/2;
		return 0;
	}
};

#endif