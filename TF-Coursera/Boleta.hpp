#pragma once
#include "DetalleCurso.hpp"
#include "DetalleBoleta.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <filesystem>

using namespace std;
namespace  fs = filesystem;

class Boleta {
private:
	DetalleBoleta _boleta;
	vector<DetalleCurso> seleccionCurso;
public:
	
	Boleta(DetalleBoleta& boleta, vector<DetalleCurso> cursos = {}) 
		:_boleta(boleta), seleccionCurso(cursos) {
		generarBoleta();
	}

	double getMontoTotalBol() const { return _boleta.getMontoTotal();}
	double getMontoIGVBol() const { return _boleta.getMontoIGV(); }
	double getDescuentoBol() const { return _boleta.getDescuento(); }
	double getSubtotalBol() const { return _boleta.getSubtotal(); }

	void gestionarBoleta() {

	}


	bool validarDatosCurso() const {
		for (const auto& curso : seleccionCurso) {
			if (curso.getPrecioCurso() < 0 || curso.getCantidadCurso() <= 0) {
				cout << "Curso con datos inválidos: " << curso.getNombreCurso() << endl;
				return false;
			}
		}
		return true;
	}

	double SubtotalRecursivo(int index = 0) {
		if (index >= seleccionCurso.size()) return 0;
		return seleccionCurso[index].getPrecioCurso() * seleccionCurso[index].getCantidadCurso()
			+ SubtotalRecursivo(index + 1);
	}

	void generarBoleta() {
		if (!validarDatosCurso()) { return; }
		// Calcula el subtotal de los cursos seleccionados
		double calculaSubtoral = SubtotalRecursivo();
		_boleta.setSubtotal(calculaSubtoral);
		// lambda calcular 18% IGV
		auto calculaIGV = [](double subtotal) {return subtotal * 0.18; };
		// lambada calcular 15% descuento
		auto calculaDescuento = [](double subtotal) { return subtotal * 0.15; };

		double IGV_m = calculaIGV(calculaSubtoral);
		double dscto = calculaDescuento(calculaSubtoral);
		double Total_m = calculaSubtoral + IGV_m - dscto;

		_boleta.setMontoIGV(IGV_m);
		_boleta.setDescuento(dscto);
		_boleta.setMontoTotal(Total_m);
	}
	void mostrarBoletaCurso(ostream& texto = cout) const {
		// lambdas para imprimir boleta de curso
		auto imprimerDetalles = [&](ostream& texto) {

			texto << fixed << setprecision(2); // formatea montos a 2 decimales
			texto << endl;
			texto << "\t\t\t\tCOURSERA APRENDIZAJE PARA TODOS  \n";
			texto << "\t\t----------------------------------------------------------------------------\n";
			texto << "\t\tBOLETA ELECTRONICA\n";
			texto << "\t\t----------------------------------------------------------------------------\n";
			texto << endl;
			texto << "\t\tID TRANSACCION: " << _boleta.getNumOperacion() << endl;
			texto << "\t\tFecha de Emision: " << _boleta.getFecha() << "\tHora: " << _boleta.getHora() << endl;
			texto << "\t\tNombre Titular: " << _boleta.getNombreCliente() << endl;
			texto << "\t\tCorreo Titular: " << _boleta.getCorreo() << endl;
			texto << "\t\tMetodo de Pago: " << _boleta.getMetodoPago() << endl;
			texto << "\t\t----------------------------------------------------------------------------\n";
			texto << "\t\tCURSOS ADQUIRIDOS\n";
			texto << "\t\t----------------------------------------------------------------------------\n";
			texto << "\t\tCurso\t\tCantidad\tCategoria\tP. Unitario\tP. total\t\n";
			for (const auto& curso: seleccionCurso)
			{
				texto << "\t\t" << curso.getNombreCurso() << "\t\t"
					<< curso.getCantidadCurso() << "\t\t" 
					<< curso.getCategoriaCurso() << "\t$"
					<< curso.getPrecioCurso() << "\t\t$"
					<< (curso.getPrecioCurso() * curso.getCantidadCurso()) << "\n";
			}
			texto << "\t\t----------------------------------------------------------------------------\n";
			texto << "\t\tRESUMEN DE PAGO\t\n";
			texto << "\t\t----------------------------------------------------------------------------\n";
			texto << "\t\tSubtotal:    \t" << _boleta.getSubtotal() << endl;
			texto << "\t\tDescuentos:  \t" << _boleta.getDescuento() << endl;
			texto << "\t\tIGV (18%):   \t" << _boleta.getMontoIGV() << endl;
			texto << "\t\tMonto Total: \t" << _boleta.getMontoTotal() << endl;;
			texto << "\t\t----------------------------------------------------------------------------\n";
			};

		imprimerDetalles(texto);
	}
	string generarNombreArchivo() const {
		string nombreArchivo = _boleta.getNombreCliente();
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

