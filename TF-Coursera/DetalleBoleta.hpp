#pragma once
#include <iostream>
#include <string>

using namespace std;

class DetalleBoleta
{
private:
	string _empresa;
	string _numOperacion;
	string _fecha;
	string _hora;
	string _metodoPago;
	string _correo;
	string _nombreCliente;
	double _subtotal;
	double _descuento;
	double _montoIGV;
	double _montoTotal;
	bool _esPremium;
public:
	DetalleBoleta(string empresa = "Coursera", string numOperacion = "",
		string fecha = "", string hora = "", string metodoPago = "", string correo = "",
		string nombreCliente = "", bool premium = false)
		: _empresa(empresa), _numOperacion(numOperacion), _fecha(fecha), _hora(hora),
		_metodoPago(metodoPago), _correo(correo), _nombreCliente(nombreCliente),
		_subtotal(0.0), _descuento(0.0), _montoIGV(0.),_montoTotal(0.0), _esPremium(premium) {
	}

	double getMontoTotal() const { return _montoTotal; }
	double getMontoIGV() const { return _montoIGV; }
	double getDescuento() const { return _descuento; }
	double getSubtotal() const { return _subtotal; }
	string getNumOperacion() const { return _numOperacion; }
	string getFecha() const { return _fecha; }
	string getHora() const { return _hora; }
	string getMetodoPago() const { return _metodoPago; }
	string getCorreo() const { return _correo; }
	string getNombreCliente() const { return _nombreCliente; }
	bool esPremium() const { return _esPremium; }

	void setMontoTotal(double montoTotal) { _montoTotal = montoTotal; }
	void setMontoIGV(double montoigv) { _montoIGV = montoigv; }
	void setDescuento(double descuento) { _descuento = descuento; }
	void setSubtotal(double subtotal) { _subtotal = subtotal; }
	void setNumOperacion(const string& numOperacion) { _numOperacion = numOperacion; }
	void setFecha(const string& fecha) { _fecha = fecha; }
	void setHora(const string& hora) { _hora = hora; }
	void setMetodoPago(const string& metodoPago) { _metodoPago = metodoPago; }
	void setCorreo(const string& correo) { _correo = correo; }
	void setNombreCliente(const string& nombreCliente) { _nombreCliente = nombreCliente; }
	void setEsPremium(bool esPremium) { _esPremium = esPremium; }

};

