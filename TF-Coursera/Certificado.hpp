#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;

class Certificado
{
private:
	bool _estadoCertificado;
public:
	Certificado(bool estado = false) : _estadoCertificado(estado) {}
	bool getEstadoCerti() const { return _estadoCertificado; }
	void setEstadoCerti(bool estado) { _estadoCertificado = estado; }
	
	void mostrarEstadoCerti() const {
		cout << "Estado del Certificado: " << (_estadoCertificado ? "Disponible" : "No Disponible") << endl;
	}
	void activarCertificado() {
		_estadoCertificado = true;
		cout << "Certificado activado." << endl;
	}
	void desactivarCertificado() {
		_estadoCertificado = false;
		cout << "Certificado desactivado." << endl;
	}
	void guardarEstadoCerti(const string& nombreUsuario, const string& curso = "") const {
		string ruta = "ListadoCurso/Certificado/" + nombreUsuario + ".txt";
		if (!curso.empty())
		{
			ruta += "_" + curso;
		}
		ruta += ".txt";
		ofstream archivo(ruta);
		if (archivo.is_open())
		{
			archivo << (_estadoCertificado ? "Activo" : "Inactivo");
			archivo.close();
			cout << "Certificado guardado para " << nombreUsuario << " (" << curso << ")." << endl;
		}
		else
		{
			cout << "No se pudo guardar el certificado para " << nombreUsuario << "." << endl;
		}

	}
	static Certificado cargarArchivoCertificado(const string& nombreUsuario, const string& curso = "") {
		string ruta = "ListadoCurso/Certificado/" + nombreUsuario + "_" + curso +".txt";
		if (!curso.empty())
		{
			ruta += "_" + curso;
		}
		ruta += ".txt";
		ifstream archivo(ruta);
		string linea;
		if (archivo.is_open() && getline(archivo, linea)) {
			bool estado = (linea == "Activo" || linea == "true" || linea == "1");
			return Certificado(estado);
		}
		else
		{
			cout << "No se pudo cargar el certificado desde el archivo: " << ruta << endl;
		}
		return Certificado(false);
	}


};

