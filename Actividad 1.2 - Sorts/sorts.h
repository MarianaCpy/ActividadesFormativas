/*
Mariana Castro Payns
A01706038
Act 1.2
*/

#ifndef SORTS_H_
#define SORTS_H_

#include <vector>
#include <list>
#include <iostream>

using namespace std;

template <class T>
class Sorts {
private:
void swap(vector<int>&, int, int);
void arrayMerge(vector<int>&, vector<int>&,vector<int>&);
public:
void ordenaSeleccion(vector<int>&);
void ordenaBurbuja(vector<int>&);
void ordenaMerge(vector<int>&);
int busqSecuencial(const vector<int> &, int);
int busqBinaria(const vector<int> &, int);

};


template <class T>
void Sorts<T>::swap(vector<int> &v, int i, int j) {
	T sus = v[i];
	v[i] = v[j];
	v[j] = sus;
}

template <class T>
void Sorts<T>::ordenaSeleccion(vector<int> &vect){
	int band;
	
	for (int i = vect.size() - 1; i>0; i--){
		band = 0;
		for (int j=1; j<=i; j++){
			if (vect[j]>vect[band]){
				band=j;
			}
		}
		
		if (band !=i){
			swap(vect,i,band);
		}
	}
}

template <class T>
void Sorts<T>::ordenaBurbuja(vector<int> &bubble){

	for(int i = bubble.size() - 1; i>0; i--) {
		for (int j = 0; j < i; j++) {
			if (bubble[j] > bubble[j+1]){
				swap(bubble, j , j + 1);
			}
		}
}
}	

template <class T>
void Sorts<T>::arrayMerge(vector<int> &inf, vector<int> &sup, vector<int> &b){
  int i=0, j=0, k=0;
	
	while (j < inf.size() && k < sup.size()){
		if (inf[j] < sup[k]){
			b[i] = inf[j];
			j++;
		} else {
			b[i]=sup[k];
			k++;
		}
		i++;
	}
	while(j<inf.size()){
    b[i]=inf[j];
    j++; i++;
	}
	while(k<sup.size()){
    b[i]=sup[k];
    k++; i++;
		}
	}
	

template <class T>
void Sorts<T>::ordenaMerge(vector<int> &b){
  if(b.size() <= 1) return;

  int m = b.size() / 2;
  vector<int> left;
  vector<int> right;

  for(size_t j=0; j<m;j++)
    left.push_back(b[j]);
  for(size_t j=0; j<(b.size())-m; j++)
    right.push_back(b[m+j]);

  ordenaMerge(left);
  ordenaMerge(right);
  arrayMerge(left,right,b);
}

template <class T>
int Sorts<T>::busqSecuencial(const vector<int> &b, int val){

for (int i=0; i<b.size(); i++)
  if (b[i]==val)
    return i;
  return -1;
}

template <class T>
int Sorts<T>::busqBinaria(const vector<int> &bin, int val){

int mit;
int inf=0;
int sup=bin.size() - 1;

while(inf<sup){
  mit = (inf+sup)/2;
  if (val==bin[mit]){
    return mit;
  }
  else if(val < bin[mit]){
    sup=mit-1;
  }
  else if(bin[mit]<val){
    inf=mit+1;
  }
}
return inf;
}

#endif
