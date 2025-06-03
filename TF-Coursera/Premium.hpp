#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Premium
{
private:
	bool _estadoPremium;
public:
	Premium(bool premium = false) : _estadoPremium(premium) {}
	bool getEstado() const { return _estadoPremium; }
	void setEstado(bool estado) { _estadoPremium = estado; }

	void mostrarEstado() const {
		cout << "Estado Premium: " << (_estadoPremium ? "Activo" : "Inactivo") << endl;
	}
	void activarPremium() {
		_estadoPremium = true;
		cout << "Cuenta Premium activada." << endl;
	}
	void desactivarPremium() {
		_estadoPremium = false;
		cout << "Cuenta Premium desactivada." << endl;
	}
	void guardarEstado(const string& nombreUsuario){
		string ruta = "ListaUsuario/Premium/premium_" + nombreUsuario + ".txt";
		ofstream archivo(ruta);
		if (archivo.is_open()) {
			archivo << (_estadoPremium ? "Activo" : "Inactivo") << endl;
			archivo.close();
			cout << "Estado Premium guardado." << endl;
		}
		else {
			cout << "Error al guardar el estado Premium." << endl;
		}
	}
	static Premium cargarDesdeArchivo(const string& nombreUsuario) {
		string ruta = "ListaUsuario/Premium/premium_" + nombreUsuario + ".txt";
		ifstream archivo(ruta);
		string linea;
		if (archivo.is_open() && getline(archivo,linea)) {
			bool estado = (linea == "Activo");
			return Premium(estado);
		}
		else 
		{
			cout << "No se pudo cargar el estado Premium desde el archivo." << endl;
		}
		return Premium(false);
	}
	static Premium cargarLineas(const string& linea) {
		return Premium(linea == "Activo" || linea == "true" || linea == "1");
	}

};

