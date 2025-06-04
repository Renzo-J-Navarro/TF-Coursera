#pragma once
#include <iostream>
#include <string>

using namespace std;

class DetalleCurso
{
public:
	string _codigoCurso;
	string _nombreCurso;
	string _categoriaCurso;
	double _precioCurso;
	int _cantidadCurso;

	DetalleCurso(string cod, string nom, string cate, double pre, int cant)
		: _codigoCurso(cod), _nombreCurso(nom), _categoriaCurso(cate)
		, _precioCurso(pre), _cantidadCurso(cant) {
	}

	string getCodigoCurso() const { return _codigoCurso; }
	string getNombreCurso() const { return _nombreCurso; }
	string getCategoriaCurso() const { return _categoriaCurso; }
	double getPrecioCurso() const { return _precioCurso; }
	int getCantidadCurso() const { return _cantidadCurso; }



};