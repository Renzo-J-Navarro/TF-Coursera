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
	float _precioCurso;
	int _cantidadCurso;

	DetalleCurso(string cod, string nom, string cate, float pre, int cant)
		: _codigoCurso(cod), _nombreCurso(nom), _categoriaCurso(cate)
		, _precioCurso(pre), _cantidadCurso(cant) {
	}
};