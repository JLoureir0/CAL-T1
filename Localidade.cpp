/*
 * Localidade.cpp
 *
 *  Created on: Apr 16, 2014
 *      Author: daniel
 */

#include "Localidade.h"

Localidade::Localidade() {
	this->nome = "";
	this->populacao = 0;
	this->unidadeSaude = false;
}

Localidade::Localidade(std::string nome, int populacao) {
	this->nome = nome;
	this->populacao = populacao;
	this->unidadeSaude = false;
}

Localidade::Localidade(std::string nome, int populacao, bool unidadeSaude) {
	this->nome = nome;
	this->populacao = populacao;
	this->unidadeSaude = unidadeSaude;
}

std::string Localidade::getNome() const {
	return nome;
}

void Localidade::setNome(const std::string& nome) {
	this->nome = nome;
}

int Localidade::getPopulacao() const {
	return populacao;
}

void Localidade::setPopulacao(int populacao) {
	this->populacao = populacao;
}

bool Localidade::isUnidadeSaude() const {
	return unidadeSaude;
}

void Localidade::setUnidadeSaude(bool unidadeSaude) {
	this->unidadeSaude = unidadeSaude;
}

bool Localidade::operator == (const Localidade &l) const {
	return (this->nome == l.nome && this->populacao == l.populacao && this->unidadeSaude == l.unidadeSaude);
}

Localidade::~Localidade() {
	delete(&nome);
	delete(&populacao);
	delete(&unidadeSaude);
}

