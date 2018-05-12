/// Copyright [2018] <Joao Fellipe Uller
#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include "array_list.hpp"
#include "road.hpp"

namespace structures {

// Implementa um semaforo
class Semaphore {
 public:
     // Construtor
	 Semaphore(EntryRoad* a1, EntryRoad* a2, EntryRoad* a3, EntryRoad* a4,
               Road* e1, int prob_e1, Road* e2, int prob_e2,
               Road* e3, int prob_e3, Road* e4, int prob_e4);

     // Destrutor
     ~Semaphore();

     // Retorna a probabilidade de tomar a pista no indice index
     int roadProb(std::size_t index);

     // Retorna a pista que esta com semaforo aberto no momento
     EntryRoad* open();

     // Abre a proxima pista
     void change();

 private:
	 ArrayList<Road*> efferent_{4};  // Lista das pistas de saida
	 ArrayList<EntryRoad*> afferent_{4};  // Lista das pistas de entrada
	 int probs_[4];  // Probabilidade de tomar cada pista eferente

     int actual_;
     EntryRoad *open_;

};

}  // namespace structures

/// IMPLEMENTACAO

structures::Semaphore::Semaphore(EntryRoad* a1, EntryRoad* a2, EntryRoad* a3, EntryRoad* a4, Road* e1, int prob_e1,
                                 Road* e2, int prob_e2, Road* e3, int prob_e3, Road* e4, int prob_e4) {
              afferent_.push_back(a1);
              afferent_.push_back(a2);
              afferent_.push_back(a3);
              afferent_.push_back(a4);

              efferent_.push_back(e1);
              probs_[0] = prob_e1;
              efferent_.push_back(e2);
              probs_[1] = prob_e2;
              efferent_.push_back(e3);
              probs_[2] = prob_e3;
              efferent_.push_back(e4);
              probs_[3] = prob_e4;

              open_ = afferent_[0];
              open_->open(true);
}

structures::Semaphore::~Semaphore() {
    efferent_.clear();
    afferent_.clear();
}

int structures::Semaphore::roadProb(std::size_t index) {
    return probs_[index];
}

structures::EntryRoad* structures::Semaphore::open() {
    return open_;
}

void structures::Semaphore::change() {
    open_->open(false);
    actual_ = ++actual_ % 4;
    open_ = afferent_[actual_];
    open_->open(true);
}

#endif
