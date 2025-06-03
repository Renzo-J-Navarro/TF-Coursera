#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Idioma
{
private:
	bool _estadoIdioma;
	string _idioma;
	string _seleccionIdioma;
public:
	Idioma(bool activo, string idioma, string seleccion) 
		: _estadoIdioma(activo), _idioma(idioma), _seleccionIdioma(seleccion) {}

	bool getActivo() const { return _estadoIdioma; }
	string getIdioma() const { return _idioma; }
	string getSeleccionIdioma() const { return _seleccionIdioma; }
	void setActivo(bool activo) { _estadoIdioma = activo; }
	void setIdioma(const string& idioma) { _idioma = idioma; }
	void setSeleccion(const string& seleccion) { _seleccionIdioma = seleccion; }

	void mostrarIdioma() const {
		cout << "Seleccionado: " << _seleccionIdioma << endl;
		cout << "Estado: " << (_estadoIdioma ? "Activo" : "Nulo") << endl;
	}
	void activarIdioma() {
		_estadoIdioma = true;
		cout << "Idioma activado." << endl;
	}
	void desactivarIdioma() {
		_estadoIdioma = false;
		cout << "Idioma desactivado." << endl;
	}
	void guardarIdioma() const {
		ofstream archivo("Idioma/estado_idioma.txt");
		if (archivo.is_open()) {
			archivo << (_estadoIdioma ? "1" : "0") << ","
				<< _idioma << "," << _seleccionIdioma << "." << endl;
			archivo.close();
			cout << "Estado del idioma guardado." << endl;
		}
		else {
			cout << "Error al guardar el estado del idioma." << endl;
		}
	}

	static Idioma cargarLineas(const string& linea) {
		string activoS, idioma, selecion;
		stringstream ss(linea);
		getline(ss, activoS, ',');
		getline(ss, idioma, ',');
		getline(ss, selecion, '.');
		bool activo = (activoS == "Activo" || activoS == "true" || activoS == "1");
		return Idioma(activo, idioma, selecion);
	}

};



