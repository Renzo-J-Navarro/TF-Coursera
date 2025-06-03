#pragma once
#include "Nodo.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class ListaCurso
{
private:
	Nodo<T>* inicio;
public:
	ListaCurso() : inicio(nullptr) {}
	~ListaCurso() {
		Nodo<T>* actual = inicio;
		while (actual != nullptr) {
			Nodo<T>* temp = actual;
			actual = actual->siguiente;
			delete temp;
		}
		inicio = nullptr;
	}
	Nodo<T>* getInicio() const { return inicio; }
	Nodo<T>* mergeSortPrecio(Nodo<T>* head) {
		if (!head || !head->siguiente) return head;
		Nodo<T>* mitad = dividir(head);
		Nodo<T>* izquierda = mergeSortPrecio(head);
		Nodo<T>* derecha = mergeSortPrecio(mitad);
		return mergePrecio(izquierda, derecha);
	}
	Nodo<T>* mergeSortDuracion(Nodo<T>* head) {
		if (!head || !head->siguiente) return head;
		Nodo<T>* mitad = dividir(head);
		Nodo<T>* izquierda = mergeSortDuracion(head);
		Nodo<T>* derecha = mergeSortDuracion(mitad);
		return mergeDuracion(izquierda, derecha);
	}
	Nodo<T>* dividir(Nodo<T>* head) {
		Nodo<T>* lenta = head;
		Nodo<T>* rapida = head->siguiente;
		while (rapida && rapida->siguiente) {
			lenta = lenta->siguiente;
			rapida = rapida->siguiente->siguiente;
		}
		Nodo<T>* mitad = lenta->siguiente;
		lenta->siguiente = nullptr;
		return mitad;
	}
	Nodo<T>* mergePrecio(Nodo<T>* izquierda, Nodo<T>* derecha) {
		Nodo<T>* dummy = new Nodo<T>(izquierda ? izquierda->valor : derecha->valor);
		Nodo<T>* actual = dummy;

		while (izquierda && derecha) {
			if (izquierda->valor.getPrecio() < derecha->valor.getPrecio()) {
				actual->siguiente = izquierda;
				izquierda = izquierda->siguiente;
			}
			else {
				actual->siguiente = derecha;
				derecha = derecha->siguiente;
			}
			actual = actual->siguiente;
		}

		actual->siguiente = (izquierda) ? izquierda : derecha;
		Nodo<T>* resultado = dummy->siguiente;
		delete dummy;
		return resultado;
	}
	Nodo<T>* mergeDuracion(Nodo<T>* izquierda, Nodo<T>* derecha) {
		Nodo<T>* dummy = new Nodo<T>(izquierda ? izquierda->valor : derecha->valor);
		Nodo<T>* actual = dummy;

		while (izquierda && derecha) {
			int durIzq = extraerDuracion(izquierda->valor.getDuracion());
			int durDer = extraerDuracion(derecha->valor.getDuracion());

			// Desendente
			if (durIzq > durDer) { 
				actual->siguiente = izquierda;
				izquierda = izquierda->siguiente;
			}
			else {
				actual->siguiente = derecha;
				derecha = derecha->siguiente;
			}
			actual = actual->siguiente;
		}

		actual->siguiente = (izquierda) ? izquierda : derecha;
		Nodo<T>* resultado = dummy->siguiente;
		delete dummy;
		return resultado;
	}
	Curso<string>* buscarCursoPorCodigo(int codigo) {
		Nodo<T>* actual = inicio;
		while (actual != nullptr) {
			if (actual->valor.getCodigo() == codigo) {
				return &(actual->valor); // retornamos dirección del curso
			}
			actual = actual->siguiente;
		}
		return nullptr;
	}

	int extraerDuracion(const string& duracion) {
		string numero;
		for (char c : duracion)
			if (isdigit(c)) numero += c;
		return stoi(numero); // Extrae el número de la duración
	}
	void agregarCurso(T v) {
		Nodo<T>* nuevo = new Nodo<T>(v);
		if (inicio == nullptr) {
			inicio = nuevo; // Lista vacía, el nuevo nodo es el inicio
		}
		else {
			Nodo<T>* actual = inicio;
			while (actual->siguiente != nullptr) {
				actual = actual->siguiente; // Avanzar al final de la lista
			}
			actual->siguiente = nuevo; // Agregar el nuevo nodo al final
		}
	}
	void mostrarCursos()  {
		if (inicio == nullptr) {
			cout << "No hay cursos disponibles." << endl;
			return;
		}
		Nodo<T>* actual = inicio;
		cout << "- Lista de Cursos -" << endl;
		while (actual != nullptr) {
			actual->valor.mostrarCurso(); // Asumiendo que T tiene un método mostrarCurso()
			actual = actual->siguiente;
		}
		cout << endl;
	}
	void eliminarCurso(T v) {
		if (inicio == nullptr) {
			cout << "No hay cursos para eliminar." << endl;
			return;
		}
		if (inicio->valor == v) {
			Nodo<T>* temp = inicio;
			inicio = inicio->siguiente; // Eliminar el primer nodo
			delete temp;
			cout << "Curso eliminado." << endl;
			return;
		}
		Nodo<T>* actual = inicio;
		while (actual->siguiente != nullptr && actual->siguiente->valor != v) {
			actual = actual->siguiente; // Buscar el curso a eliminar
		}
		if (actual->siguiente == nullptr) {
			cout << "Curso no encontrado." << endl;
			return;
		}
		Nodo<T>* temp = actual->siguiente;
		actual->siguiente = temp->siguiente; // Eliminar el nodo encontrado
		delete temp;
		cout << "Curso eliminado." << endl;
	}
	void modificarCurso(T v) {
		if (inicio == nullptr) {
			cout << "No hay cursos para modificar." << endl;
			return;
		}
		Nodo<T>* actual = inicio;
		while (actual != nullptr && !(actual->valor == v)) {
			actual = actual->siguiente;
		}
		if (actual == nullptr) {
			cout << "Curso no encontrado." << endl;
			return;
		}
		int nuevoCodigo;
		string nuevoNombre, nuevaCategoria, nuevaDuracion;
		double nuevoPrecio;

		cout << "Ingrese nuevo código: ";
		cin >> nuevoCodigo;
		cin.ignore();
		cout << "Ingrese nuevo nombre: ";
		getline(cin, nuevoNombre);
		cout << "Ingrese nueva categoría: ";
		getline(cin, nuevaCategoria);
		cout << "Ingrese nueva duración: ";
		getline(cin, nuevaDuracion);
		cout << "Ingrese nuevo precio: ";
		cin >> nuevoPrecio;

		T nuevoCurso(nuevoCodigo, nuevoNombre, nuevaCategoria, nuevaDuracion, nuevoPrecio);
		actual->valor = nuevoCurso;

		cout << "Curso modificado correctamente.\n";
	}
	bool existeCodigo(int codigo) {
		Nodo<T>* actual = inicio;
		while (actual != nullptr) {
			if (actual->valor.getCodigo() == codigo)
				return true;
			actual = actual->siguiente;
		}
		return false;
	}
	void buscarCategoria(string categoria) {
		Nodo<T>* actual = inicio;
		bool encontrado = false;
		auto condicion = [categoria](const T& curso) {
			return curso.getCategoria() == categoria;
			};
		while (actual) {
			if (condicion(actual->valor)) {
				actual->valor.mostrarCurso();
				encontrado = true;
			}
			actual = actual->siguiente;
		}
		if (!encontrado) cout << "\nNo hay cursos en esa categoria." << endl;
	}
	void buscarPrecio(double precioMax) {
		Nodo<T>* actual = inicio;
		bool encontrado = false;
		auto condicion = [precioMax](const T& curso) {
			return curso.getPrecio() <= precioMax;
			};
		while (actual) {
			if (condicion(actual->valor)) {
				actual->valor.mostrarCurso();
				encontrado = true;
			}
			actual = actual->siguiente;
		}
		if (!encontrado) cout << "No hay cursos con precio menor o igual a $" << precioMax << endl;
	}
	void ordenarPorPrecio() {
		inicio = mergeSortPrecio(inicio);
		cout << "Lista ordenada por precio (ascendente)." << endl;
	}
	void ordenarPorDuracion() {
		inicio = mergeSortDuracion(inicio);
		cout << "Lista ordenada por duracion (descendente)." << endl;
	}
	void cargarDesdeArchivo(const string& nombreArchivo) {
		ifstream archivo(nombreArchivo);
		string linea;
		while (getline(archivo, linea)) {
			T curso = T::cargarLineas(linea);
			agregarCurso(curso);
		}
		cout << "Cursos cargados desde archivo: " << nombreArchivo << endl;
	}
	void guardarEnArchivo(const string& nombreArchivo) {
		ofstream archivo(nombreArchivo);
		Nodo<T>* actual = inicio;
		while (actual != nullptr) {
			archivo << actual->valor.getCodigo() << ","
				<< actual->valor.getCurso() << ","
				<< actual->valor.getCategoria() << ","
				<< actual->valor.getDuracion() << ","
				<< actual->valor.getPrecio() << endl;
			actual = actual->siguiente;
		}
		cout << "Cursos guardados en: " << nombreArchivo << endl;
	}
};