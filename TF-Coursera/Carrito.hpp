#pragma once
#include "Boleta.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class Carrito
{
private:
	vector<T> items;
public:
	Carrito() {}
	~Carrito() {}
	void agregarItem(const T& item) {
		items.push_back(item);
	}
	void eliminarItem(const T& item) {
		auto it = find(items.begin(), items.end(), item);
		if (it != items.end()) {
			items.erase(it);
		}
	}
	void mostrarItems() const {
		for (const auto& item : items) {
			cout << item << endl;
		}
	}
	size_t cantidadItems() const {
		return items.size();
	}
	void vaciarCarrito() {
		items.clear();
	}


};

