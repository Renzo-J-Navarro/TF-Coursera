#pragma once
#include "Cliente.hpp"
#include "Premium.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

template <typename T>
class Usuario : public Premium
{
private:
	Cliente<T> _cliente;
	string _usuario, _contra;
public:
	Usuario(const Cliente<T>& cliente, const string& usuario = "", const string& contra = "")
		: _cliente(cliente), _usuario(usuario), _contra(contra), Premium(false) {}

	const Cliente<T>& getCliente() const { return _cliente; }
	string getUsuario() const { return _usuario; }
	string getContra() const { return _contra; }
	void setUsuario(const string& usuario) { _usuario = usuario; }
	void setContra(const string& contra) { _contra = contra; }

	string serilizarUsuario() const {
		stringstream ss;
		ss << _cliente.getNombre() << ","
			<< _cliente.getProfesion() << ","
			<< _cliente.getTelefono() << ","
			<< _cliente.getCorreo() << ","
			<< _usuario << ","
			<< _contra << ","
			<< (getEstado() ? "Activo" : "Inactivo") << ".";
		return ss.str();
	}
	void mostrarUsuario() const {
		cout << "\n\t--- Datos del Usuario ---\n";
		_cliente.mostrarCliente();
		cout << "Usuario: " << _usuario << endl;
		cout << "Contraseña: " << _contra << endl;
		mostrarEstado();
		cout << endl;
	}
	void activarPremium() {
		Premium::activarPremium();
		guardarEstado(_cliente.getCorreo());
		cout << "Cuenta Premium activada para " << _cliente.getNombre() << ".\n";
	}
	void desactivarPremium() {
		Premium::desactivarPremium();
		guardarEstado(_cliente.getCorreo());
		cout << "Cuenta Premium desactivada para " << _cliente.getNombre() << ".\n";
	}
	void cargarEstadoPremium() {
		Premium::cargarDesdeArchivo(getUsuario());
		if (getEstado()) {
			cout << "Cuenta Premium activa para " << _cliente.getNombre() << ".\n";
		}
		else {
			cout << "Cuenta Premium inactiva para " << _cliente.getNombre() << ".\n";
		}
	}
	void mostrarCursosAdquiridos() const {
		ifstream archivo("ListaUsuario/Compras/Curso_adquirido.txt");
		if (archivo.is_open()) {
			string linea;
			cout << "\n\t--- Cursos adquiridos por " << _cliente.getNombre() << " ---\n";
			while (getline(archivo, linea)) {
				cout << linea << endl;
			}
			archivo.close();
		}
		else {
			cout << "No se pudo abrir el archivo de cursos adquiridos.\n";
		}
	}
	static Usuario<T> cargarLineas(const string& linea) {
		string nombre, profesion, telefono, correo, usuario, contra, premiumS;
		stringstream ss(linea);
		getline(ss, nombre, ',');
		getline(ss, profesion, ',');
		getline(ss, telefono, ',');
		getline(ss, correo, ',');
		getline(ss, usuario, ',');
		getline(ss, contra, ',');
		getline(ss, premiumS, '.');
		bool premium = (premiumS == "Activo" || premiumS == "true" || premiumS == "1");
		Cliente<T> cliente(nombre, profesion, telefono, correo);
		Usuario<T> usuarioObj(cliente);
		usuarioObj.setUsuario(usuario);
		usuarioObj.setContra(contra);
		if (premium) {
			usuarioObj.activarPremium();
		}
		else {
			usuarioObj.desactivarPremium();
		}
		return usuarioObj;
	}

};

