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
               Road* e1, Road* e2, Road* e3, Road* e4);

     // Destrutor
     ~Semaphore();

     // Retorna a probabilidade de tomar a pista no indice index
     int roadProb(Road* origin, Road* destination);

     // Adiciona as listas de probabilidades ao semaforo
     void road_probs(int* prob_e1, int* prob_e2, int* prob_e3, int* prob_e4);

     // Retorna a pista que esta com semaforo aberto no momento
     EntryRoad* open();

     // Abre a proxima pista
     void change();

     // Retorna a pista aferente no indice index
     EntryRoad* afferent(std::size_t index);

 private:
	 ArrayList<Road*> efferent_{4};  // Lista das pistas de saida
	 ArrayList<EntryRoad*> afferent_{4};  // Lista das pistas de entrada
	 ArrayList<int*> probs_;  // Lista com probabilidades de tomar cada pista eferente

     int actual_;
     EntryRoad *open_;

};

}  // namespace structures

/// IMPLEMENTACAO

structures::Semaphore::Semaphore(EntryRoad* a1, EntryRoad* a2, EntryRoad* a3, EntryRoad* a4, Road* e1,
                                 Road* e2, Road* e3, Road* e4) {
              afferent_.push_back(a1);
              afferent_.push_back(a2);
              afferent_.push_back(a3);
              afferent_.push_back(a4);

              efferent_.push_back(e1);
              efferent_.push_back(e2);
              efferent_.push_back(e3);
              efferent_.push_back(e4);

              open_ = afferent_[0];
              open_->open(true);
}

structures::Semaphore::~Semaphore() {
    efferent_.clear();
    afferent_.clear();
}

int structures::Semaphore::roadProb(Road* origin, Road* destination) {
    int i = 0;
    int j = -1;
    int k = -1;
    while ((i < 4) && (j == -1) && (k == -1)) {
        if (afferent_[i] == origin)
            k = i;
        if (efferent_[i] == destination)
            j == i;
        i++;
    }
    return probs_[j][k];
}

void structures::Semaphore::road_probs(int* prob_e1, int* prob_e2, int* prob_e3, int* prob_e4) {
    probs_.push_back(prob_e1);
    probs_.push_back(prob_e2);
    probs_.push_back(prob_e3);
    probs_.push_back(prob_e4);
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

structures::EntryRoad* structures::Semaphore::afferent(std::size_t index) {
    return afferent_[index];
}

#endif
