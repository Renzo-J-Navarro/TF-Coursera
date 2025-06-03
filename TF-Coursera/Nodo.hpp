#pragma once

template <typename T>
class Nodo
{
public:
	T valor;
	Nodo<T>* siguiente;
	Nodo(T v, Nodo<T>* sig = nullptr) : valor(v), siguiente(sig) {}
};
