/*
 * Localidade.h
 *
 *  Created on: Apr 16, 2014
 *      Author: daniel
 */

#ifndef LOCALIDADE_H_
#define LOCALIDADE_H_

#include <iostream>

class Localidade {
public:
	Localidade();
	Localidade(std::string nome, int populacao);
	Localidade(std::string nome, int populacao, bool unidadeSaude);
//	virtual ~Localidade();
	std::string getNome() const;
	void setNome(const std::string& nome);
	int getPopulacao() const;
	void setPopulacao(int populacao);
	bool isUnidadeSaude() const;
	void setUnidadeSaude(bool unidadeSaude);
    bool operator == (const Localidade &l) const;
private:
	std::string nome;
	int populacao;
	bool unidadeSaude;
};

#endif /* LOCALIDADE_H_ */
