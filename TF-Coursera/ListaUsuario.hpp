#pragma once
#include "Nodo.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class ListaUsuario
{
private:
	Nodo<T>* inicio;
	Nodo<T>* fin;
public:
	ListaUsuario() : inicio(nullptr), fin(nullptr) {}
	~ListaUsuario() {
		Nodo<T>* actual = inicio;
		while (actual != nullptr) {
			Nodo<T>* temp = actual;
			actual = actual->siguiente;
			delete temp;
		}
		inicio = nullptr;
	}
	Nodo<T>* getInicio() const { return inicio; }
	Nodo<T>* getFinal() const { return fin; }

	void agregarUsuario(T v) {
		Nodo<T>* nuevo = new Nodo<T>(v);
		if (inicio == nullptr) {
			inicio = nuevo; // Lista vacía, el nuevo nodo es el inicio
			fin = nuevo; // El primer nodo también es el nodo final
		}
		else {
			fin->siguiente = nuevo; // Agregar el nuevo nodo al final
			fin = nuevo; // Actualizar el final de la lista
		}
		cout << "Usuario agregado correctamente." << endl;
	}
	void mostrarUsuarios() const {
		if (inicio == nullptr) {
			cout << "No hay usuarios registrados." << endl;
			return;
		}
		Nodo<T>* actual = inicio;
		cout << "- Lista de Usuarios -" << endl;
		while (actual != nullptr) {
			actual->valor.mostrarUsuario(); // Asumiendo que T tiene un método mostrarUsuario()
			actual = actual->siguiente;
		}
		cout << endl;
	}
	void eliminarUsuario(T v) {
		if (inicio == nullptr) {
			cout << "No hay usuarios para eliminar." << endl;
			return;
		}
		if (inicio->valor == v) {
			Nodo<T>* temp = inicio;
			inicio = inicio->siguiente; // Eliminar el primer nodo
			if (inicio == nullptr)
			{
				fin = nullptr; // Si la lista queda vacía, actualizar fin
			}
			delete temp;
			cout << "Usuario eliminado." << endl;
			return;
		}
		Nodo<T>* actual = inicio;
		while (actual->siguiente != nullptr && actual->siguiente->valor != v) {
			actual = actual->siguiente; // Buscar el usuario a eliminar
		}
		if (actual->siguiente == nullptr) {
			cout << "Usuario no encontrado." << endl;
			return;
		}
		Nodo<T>* temp = actual->siguiente;
		actual->siguiente = temp->siguiente; // Eliminar el nodo encontrado
		if (temp == fin) {
			fin = actual; // Si se eliminó el último nodo, actualizar fin
		}
		delete temp;
		cout << "Usuario eliminado." << endl;
	}
	void modificarUsuario(T v) {
		if (inicio == nullptr) {
			cout << "No hay usuarios para modificar." << endl;
			return;
		}
		Nodo<T>* actual = inicio;
		while (actual != nullptr && !(actual->valor == v)) {
			actual = actual->siguiente;
		}
		if (actual == nullptr) {
			cout << "Usuario no encontrado." << endl;
			return;
		}
		string nuevoNombre, nuevaProfesion, nuevoTelefono, nuevoCorreo, nuevoUsuario, nuevaContra;
		cout << "Ingrese nuevo nombre: ";
		cin.ignore();
		getline(cin, nuevoNombre);
		cout << "Ingrese nueva profesion: ";
		getline(cin, nuevaProfesion);
		cout << "Ingrese nuevo telefono: ";
		getline(cin, nuevoTelefono);
		cout << "Ingrese nuevo correo: ";
		getline(cin, nuevoCorreo);
		cout << "Ingrese nuevo usuario: ";
		getline(cin, nuevoUsuario);
		cout << "Ingrese nueva contraseña: ";
		getline(cin, nuevaContra);
		T nuevoUsuarioObj(nuevoNombre, nuevaProfesion, nuevoTelefono, nuevoCorreo);
		nuevoUsuarioObj.setUsuario(nuevoUsuario);
		nuevoUsuarioObj.setContra(nuevaContra);
		actual->valor = nuevoUsuarioObj;
		cout << "Usuario modificado correctamente.\n";
	}
	T* obtenerUsuario(const string& correo) const {
		Nodo<T>* actual = inicio;
		while (actual != nullptr) {
			if (actual->valor.getCorreo() == correo) { // Asumiendo que T tiene un método getCorreo()
				return &actual->valor; // Retorna el usuario encontrado
			}
			actual = actual->siguiente;
		}
		return nullptr; // Usuario no encontrado
	}
	bool usuarioExiste(const string& correo) const {
		Nodo<T>* actual = inicio;
		while (actual != nullptr) {
			if (actual->valor.getCorreo() == correo) { // Asumiendo que T tiene un método getCorreo()
				return true; // Usuario encontrado
			}
			actual = actual->siguiente;
		}
		return false; // Usuario no encontrado
	}
	bool contraseniaExiste(const string& contra) const {
		Nodo<T>* actual = inicio;
		while (actual != nullptr) {
			if (actual->valor.getContra() == contra) { // Asumiendo que T tiene un método getContra()
				return true; // Contraseña encontrada
			}
			actual = actual->siguiente;
		}
		return false; // Contraseña no encontrada
	}
	void buscarUsuario() const {
		if (inicio == nullptr) {
			cout << "No hay usuarios registrados." << endl;
			return;
		}
		string correo;
		cout << "Ingrese el correo del usuario a buscar: ";
		cin.ignore();
		getline(cin, correo);
		Nodo<T>* actual = inicio;
		while (actual != nullptr) {
			if (actual->valor.getCorreo() == correo) { // Asumiendo que T tiene un método getCorreo()
				actual->valor.mostrarUsuario(); // Mostrar el usuario encontrado
				return;
			}
			actual = actual->siguiente;
		}
		cout << "Usuario no encontrado." << endl;
	}
	void buscarPorProfesion() const {
		if (inicio == nullptr) {
			cout << "No hay usuarios registrados." << endl;
			return;
		}
		string categoria;
		cout << "Ingrese la categoria a buscar: ";
		cin.ignore();
		getline(cin, categoria);
		Nodo<T>* actual = inicio;
		bool encontrado = false;
		while (actual != nullptr) {
			if (actual->valor.getCategoria() == categoria) { // Asumiendo que T tiene un método getCategoria()
				actual->valor.mostrarUsuario(); // Mostrar el usuario encontrado
				encontrado = true;
			}
			actual = actual->siguiente;
		}
		if (!encontrado) {
			cout << "No se encontraron usuarios en la categoria: " << categoria << endl;
		}
	}
	void cargarDesdeArchivo(const string& nombreArchivo) {
		ifstream archivo(nombreArchivo);
		string linea;
		while (getline(archivo, linea)) {
			T usuario = T::cargarLineas(linea);
			agregarUsuario(usuario);
		}
		cout << "Usuarios cargados desde archivo: " << nombreArchivo << endl;
	}
	void guardarEnArchivo(const string& nombreArchivo) {
		ofstream archivo(nombreArchivo);
		Nodo<T>* actual = inicio;
		while (actual != nullptr) {
			archivo << actual->valor.serilizarUsuario() << endl;
			actual = actual->siguiente;
		}
		cout << "Usuarios guardados en archivo: " << nombreArchivo << endl;
	}

	// --- Funcionalidad de Pila ---
	void push_pila(T v) {
		Nodo<T>* nuevo = new Nodo<T>(v);
		nuevo->siguiente = inicio; // El nuevo nodo apunta al inicio actual
		inicio = nuevo; // El nuevo nodo se convierte en el nuevo inicio
		cout << "Usuario apilado correctamente." << endl;
	}
	T pop_pila() {
		if (inicio == nullptr) {
			cout << "Pila vacia. No se puede desapilar." << endl;
			// Podrías lanzar una excepción o retornar un T construido por defecto aquí
			// Para simplificar, retornamos un T por defecto e imprimimos un error
			return T();
		}
		Nodo<T>* temp = inicio;
		T valorDesapilado = temp->valor;
		inicio = inicio->siguiente;
		if (inicio == nullptr) {
			fin = nullptr; // Si la pila queda vacía, actualizamos fin a nullptr
		}
		delete temp;
		cout << "Usuario desapilado correctamente." << endl;
		return valorDesapilado;
	}
	T top_pila() const {
		if (inicio == nullptr) {
			cout << "Pila vacia. No hay elemento superior." << endl;
			// De nuevo, considera lanzar una excepción o retornar un T por defecto
			return T();
		}
		return inicio->valor;
	}
	bool isEmpty_pila() const {
		return inicio == nullptr;
	}

	// --- Funcionalidad de Cola ---
	void en_cola(T v) {
		Nodo<T>* nuevo = new Nodo<T>(v);
		if (isEmpty_cola()) {
			inicio = nuevo; // Si la cola está vacía, el nuevo nodo es el inicio
			fin = nuevo; // El nuevo nodo también es el fin de la cola
		}
		else {
			fin->siguiente = nuevo; // El nodo actual fin apunta al nuevo nodo
			fin = nuevo; // Actualizamos el fin de la cola
		}
		cout << "Usuario encolado correctamente." << endl;
	}
	T de_cola() {
		if (inicio == nullptr) {
			cout << "Cola vacia. No se puede desencolar." << endl;
			// Considera lanzar una excepción o retornar un T por defecto
			return T();
		}
		Nodo<T>* temp = inicio;
		T valorDesencolado = temp->valor;
		inicio = inicio->siguiente;
		if (inicio == nullptr) {
			fin = nullptr; // Si la cola queda vacía, actualizamos fin a nullptr
		}
		delete temp;
		cout << "Usuario desencolado correctamente." << endl;
		return valorDesencolado;
	}
	T front_cola() const {
		if (isEmpty_cola()) {
			cout << "Cola vacia. No hay elemento al frente." << endl;
			// Considera lanzar una excepción o retornar un T por defecto
			return T();
		}
		return inicio->valor;
	}
	bool isEmpty_cola() const {
		return inicio == nullptr;
	}

};

