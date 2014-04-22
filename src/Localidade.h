/*
 * Localidade.h
 *
 *  Created on: Apr 16, 2014
 *      Author: daniel
 */

#ifndef LOCALIDADE_H_
#define LOCALIDADE_H_

#include <string>

class Localidade {
public:
	Localidade();
	Localidade(int id, std::string nome, unsigned long populacao);
	Localidade(int id, std::string nome, unsigned long populacao, bool unidadeSaude);
	std::string getNome() const;
	void setNome(const std::string& nome);
	unsigned long getPopulacao() const;
	void setPopulacao(unsigned long populacao);
	bool isUnidadeSaude() const;
	void setUnidadeSaude(bool unidadeSaude);
	bool operator ==(const Localidade &l) const;
	int getID() const;
private:
	int id;
	std::string nome;
	unsigned long populacao;
	bool unidadeSaude;
};

#endif /* LOCALIDADE_H_ */
