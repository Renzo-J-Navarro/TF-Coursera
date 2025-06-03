#pragma once
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

template <typename T>
class Cliente
{
private:
	T _nombre, _profesion, _telefono, _correo;

	void guardadoAutomatico() const {
		ofstream archivo("Clientes/cliente.txt", ios::app);
		if (archivo.is_open()) {
			archivo << _nombre << "," << _profesion << ","
				<< _telefono << "," << _correo << "." << endl;
			archivo.close();
		}
	}

public:
	Cliente(T nombre, T profesion, T telefono, T correo) 
		: _nombre(nombre), _profesion(profesion), _telefono(telefono), _correo(correo) {
		guardadoAutomatico();
	}

	T getNombre() const { return _nombre; }
	T getProfesion() const { return _profesion; }
	T getTelefono() const { return _telefono; }
	T getCorreo() const { return _correo; }
	void setNombre(T nombre) { _nombre = nombre; guardadoAutomatico(); }
	void setProfesion(T profesion) { _profesion = profesion; guardadoAutomatico(); }
	void setTelefono(T telefono) { _telefono = telefono; guardadoAutomatico(); }
	void setCorreo(T correo) { _correo = correo; guardadoAutomatico(); }

	void mostrarCliente() const {
		cout << "- Datos del Cliente -" << endl;
		cout << "Nombre: " << _nombre << endl;
		cout << "Profesion: " << _profesion << endl;
		cout << "Telefono: " << _telefono << endl;
		cout << "Correo: " << _correo << endl;
	}
	static Cliente<T> cargarLineas(const string& linea) {
		string nombre, profesion, telefono, correo;
		stringstream ss(linea);
		getline(ss, nombre, ',');
		getline(ss, profesion, ',');
		getline(ss, telefono, ',');
		getline(ss, correo, '.');
		return Cliente<T>(nombre, profesion, telefono, correo);
	}

};


