#pragma once
#include "Certificado.hpp"
#include "Idioma.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template <typename T>
class Curso : public Certificado
{
private:
	int _codigo;
	T _curso;
	T _categoria;
	T _duracion;
	float _precio;
public:

	Curso(int codigo, T curso, T categoria, T duracion, float precio)
		: _codigo(codigo), _curso(curso), _categoria(categoria), 
		_duracion(duracion), _precio(precio), Certificado(false){}

	int getCodigo() const { return _codigo; }
	T getCurso() const { return _curso; }
	T getCategoria() const { return _categoria; }
	T getDuracion() const { return _duracion; }
	float getPrecio() const { return _precio; }

	void setCodigo(int codi) { _codigo = codi; }
	void setCurso(T curso) { _curso = curso; }
	void setCategoria(T cate) { _categoria = cate; }
	void setDuracion(T dura) { _duracion = dura; }
	void setPrecio(float prec) { _precio = prec; }

	void mostrarCurso() const {
		cout << "[" << _codigo << "] " << _curso << " | " << _categoria << " | "
			<< _duracion << " | $" << _precio << endl;
		mostrarEstadoCerti();
		cout << endl;
	}
	void activarCertificado(const string& nombreUsuario) {
		Certificado::activarCertificado();
		guardarEstadoCerti(nombreUsuario, _curso);
		cout << "Certificado activado para el curso " << _curso << ".\n";
	}
	void cargarEstadoCertificado(const string& nombreUsuario) {
		Certificado certifi = Certificado::cargarArchivoCertificado(nombreUsuario, _curso);
		setEstadoCerti(certifi.getEstadoCerti());
		if (getEstadoCerti()) {
			cout << "Certificado activo para el " << _curso << " del " << nombreUsuario << endl;
		}
		else {
			cout << "Certificado inactivo para el " << _curso << " del " << nombreUsuario << endl;
		}
	}
	void comprarCertificado(const string& nombreUsuario) {
		Certificado certi = Certificado::cargarArchivoCertificado(nombreUsuario, _curso);
		if (!certi.getEstadoCerti()) {
			cout << "Este curso no tiene un certificado activo.\n";
			cout << "¿Deseas comprar el certificado por $15.00? (s/n): ";
			char opc;
			cin >> opc;
			if (tolower(opc) == 's') {
				activarCertificado(nombreUsuario);
			}
			else {
				cout << "No se activó el certificado.\n";
			}
		}
		else {
			cout << "Ya tienes un certificado activo para este curso.\n";
		}
	}

	bool operator==(const Curso<T>& otro) const {
		return _codigo == otro.getCodigo();
	}

	static Curso<T> cargarLineas(const string& linea) {
		string codigoS, curso, categoria, duracion, precioS;
		stringstream ss(linea);
		getline(ss, codigoS, ',');
		getline(ss, curso, ',');
		getline(ss, categoria, ',');
		getline(ss, duracion, ',');
		getline(ss, precioS, ',');
		int codigo = stoi(codigoS);
		float precio = stod(precioS);
		return Curso<T>(codigo, curso, categoria, duracion, precio);
	}
};

