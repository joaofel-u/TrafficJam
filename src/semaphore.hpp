/// Copyright [2018] <Joao Fellipe Uller
#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include <cstdio>
#include "array_list.hpp"
#include "road.hpp"

namespace structures {

// Implementa um semaforo
class Semaphore {
 public:
     // Construtor
	 Semaphore(Road& a1, Road& a2, Road& a3, Road& a4,
               Road& e1, int prob_e1, Road& e2, int prob_e2,
               Road& e3, int prob_e3, Road& e4, int prob_e4);

     // Destrutor
     ~Semaphore();

     // Retorna a probabilidade de tomar a pista no indice index
     int roadProb(std::size_t index);

     // Fecha o semaforo
     void close();

     // Abre a proxima pista
     void open();

 private:
	 ArrayList<Road *> efferent_{4};  // Lista das pistas de saida
	 ArrayList<Road *> afferent_{4};  // Lista das pistas de entrada
	 int probs_[4];  // Probabilidade de tomar cada pista eferente

     Road *next_;  // VER -> Proxima pista a abrir
     Road *open_;  // VER -> Se for CircList usar head no lugar

     // Ver atributo para o tempo que cada pista fica aberta

};

}  // namespace structures

/// IMPLEMENTACAO

structures::Semaphore::Semaphore(Road& a1, Road& a2, Road& a3, Road& a4, Road& e1, int prob_e1,
                                 Road& e2, int prob_e2, Road& e3, int prob_e3, Road& e4, int prob_e4) {
              afferent_.push_back(&a1);
              afferent_.push_back(&a2);
              afferent_.push_back(&a3);
              afferent_.push_back(&a4);

              efferent_.push_back(&e1);
              probs_[0] = prob_e1;
              efferent_.push_back(&e2);
              probs_[1] = prob_e2;
              efferent_.push_back(&e3);
              probs_[2] = prob_e3;
              efferent_.push_back(&e4);
              probs_[3] = prob_e4;
}

structures::Semaphore::~Semaphore() {
    efferent_.clear();
    afferent_.clear();
}

int structures::Semaphore::roadProb(std::size_t index) {
    return probs_[index];
}

void structures::Semaphore::close() {
    // VER
}

void structures::Semaphore::open() {
    // VER
}

#endif
