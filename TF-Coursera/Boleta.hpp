#pragma once
#include "DetalleCurso.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <filesystem>

using namespace std;
namespace  fs = filesystem;

class Boleta {
private:
	string _empresa;
	string _numOperacion;
	string _fecha;
	string _hora;
	string _metodoPago;
	string _correo;
	string _nombreCliente;
	float _subtotal;
	double _descuento;
	double _montoIGV;
	double _montoTotal;
	vector<DetalleCurso> seleccionCurso;
public:
	
	Boleta(string empresa = "Coursera", string numOperacion = "",
		string fecha = "", string hora = "", string metodoPago = "", string correo = "",
		string nombreCliente = "", vector<DetalleCurso> cursos = {})
		: _empresa(empresa), _numOperacion(numOperacion), _fecha(fecha), _hora(hora),
		_metodoPago(metodoPago), _correo(correo), _nombreCliente(nombreCliente),
		seleccionCurso(cursos), _subtotal(0.0), _descuento(0.0), _montoIGV(0.),
		_montoTotal(0.0) {
		generarBoleta();
	}

	double getMontoTotal() const { return _montoTotal; }
	double getMontoIGV() const { return _montoIGV; }
	double getDescuento() const { return _descuento; }

	void setMontoTotal(double montoTotal) { _montoTotal = montoTotal; }
	void setMontoIGV(double montoigv) { _montoIGV = montoigv; }
	void setDescuento(double descuento) { _descuento = descuento; }

	bool validarDatos() const {
		for (const auto& curso : seleccionCurso) {
			if (curso._precioCurso < 0 || curso._cantidadCurso <= 0) {
				cout << "Curso con datos inválidos: " << curso._nombreCurso << endl;
				return false;
			}
		}
		return true;
	}
	float SubtotalRecursivo(int index = 0) {
		if (index >= seleccionCurso.size()) return 0;
		return seleccionCurso[index]._precioCurso * seleccionCurso[index]._cantidadCurso
			+ SubtotalRecursivo(index + 1);
	}
	void generarBoleta() {
		if (!validarDatos()) { return; }
		// Calcula el subtotal de los cursos seleccionados
		_subtotal = SubtotalRecursivo(); 
		// lambda calcular 18% IGV
		auto calculaIGV = [](float subtotal) {return subtotal * 0.18; };
		// lambada calcular 15% descuento
		auto calculaDescuento = [](float subtotal) { return subtotal * 0.15; };

		_montoIGV = calculaIGV(_subtotal);
		_descuento = calculaDescuento(_subtotal);
		_montoTotal = _subtotal + _montoIGV - _descuento; 
	}
	void mostrarBoletaCurso(ostream& texto = cout) const {
		// lambdas para imprimir boleta de curso
		auto boletaCurso = [&](ostream& texto) {

			texto << fixed << setprecision(2); // formatea montos a 2 decimales
			texto << endl;
			texto << "\t\t\t\tCOURSERA APRENDIZAJE PARA TODOS  \n";
			texto << "\t\t----------------------------------------------------------------------------\n";
			texto << "\t\tBOLETA ELECTRONICA\n";
			texto << "\t\t----------------------------------------------------------------------------\n";
			texto << endl;
			texto << "\t\tID TRANSACCION: " << _numOperacion << endl;
			texto << "\t\tFecha de Emision: " << _fecha << "\tHora: " << _hora << endl;
			texto << "\t\tNombre Titular: " << _nombreCliente << endl;
			texto << "\t\tCorreo Titular: " << _correo << endl;
			texto << "\t\tMetodo de Pago: " << _metodoPago << endl;
			texto << "\t\t----------------------------------------------------------------------------\n";
			texto << "\t\tCURSOS ADQUIRIDOS\n";
			texto << "\t\t----------------------------------------------------------------------------\n";
			texto << "\t\tCurso\t\tCantidad\tCategoria\tP. Unitario\tP. total\t\n";
			for (const auto& curso: seleccionCurso)
			{
				texto << "\t\t" << curso._nombreCurso << "\t\t"
					<< curso._cantidadCurso << "\t\t" 
					<< curso._categoriaCurso << "\t$"
					<< curso._precioCurso << "\t\t$"
					<< (curso._precioCurso * curso._cantidadCurso) << "\n";
			}
			texto << "\t\t----------------------------------------------------------------------------\n";
			texto << "\t\tRESUMEN DE PAGO\t\n";
			texto << "\t\t----------------------------------------------------------------------------\n";
			texto << "\t\tSubtotal:    \t" << _subtotal << endl;
			texto << "\t\tDescuentos:  \t" << _descuento << endl;
			texto << "\t\tIGV (18%):   \t" << _montoIGV << endl;
			texto << "\t\tMonto Total: \t" << _montoTotal << endl;;
			texto << "\t\t----------------------------------------------------------------------------\n";
			};

		boletaCurso(texto);
	}
	string generarNombreArchivo() const {
		string nombreArchivo = _nombreCliente;
		replace(nombreArchivo.begin(), nombreArchivo.end(), ' ', '_');
		return "ListaBoleta/boletaCursos/boleta_" + nombreArchivo + ".txt";
	}
	void guardarBoletaEnArchivo(const string& ruta) const {
		fs::create_directories(fs::path(ruta).parent_path());
		ofstream archivo(ruta, ios::app);
		if (archivo.is_open()) {
			archivo << "\n\n====================================================================\n";
			archivo << "                       NUEVA BOLETA\n";
			archivo << "====================================================================\n";
			mostrarBoletaCurso(archivo);
			cout << " Boleta guardada en " << ruta << endl;
		}
		else {
			cout << " Error al guardar la boleta." << endl;
		}
	}
};

