#pragma once
#include<iostream>
#include"contar.h"
using namespace std;
template <class T>
class sharepointer {
private:
public:
	T a;//donde se guardara el punterp
	int* aqui;//el contador
	sharepointer(T b) {//la funcion constructora,, pone el contador en 1
		a = b;
		aqui = new int(1);
	}
	sharepointer(sharepointer const &p) {//funcion constructora de copia,, pasa el contador, lo aumenta uno y pasa el pointer
		aqui = p.aqui;
		*aqui += 1;
		a = p.a;
	}
	~sharepointer() {//el destructor, le resta uno al constructor y si es cero vorra lo que apunta el puntero
		*aqui -= 1;
		if (*aqui == 0) {
			delete a;
		}
	}
	
	int conta() {//regresa el contador
		return *aqui;
	}
};
template <class T>//nose exactamente que es esto pero si le haces cout al sharepointer te coutea el pointer
	ostream &operator<<(ostream &os, sharepointer<T> const &m) {
		return os << m.a;
	}