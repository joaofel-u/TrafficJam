/// Copyright [2018] <Joao Fellipe Uller
#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <cstdio>
#include <stdlib.h>
#include <time.h>

#define SAFETY_DISTANCE 3  // distancia de seguranca entre dois carros

using std::size_t;

namespace structures {
// Define um veiculo dentro do sistema
class Vehicle {
 public:
     // Construtor
     Vehicle();

     // Destrutor
     ~Vehicle();

     // Retorna o tamanho do veiculo ja acrescido da distancia de seguranca
     size_t size() const;

     // Retorna a direcao que o veiculo tomara ao trocar de pista
     int direction() const;

     // Define a direcao que o veiculo tomara' ao trocar de pista
     void direction(int direction);

 private:
	 size_t size_;  // Tamanho do veiculo em metros
     char direction_;  // 0=left, 1=front, 2=right

};

}  // namespace structures

/// IMPLEMENTACAO

structures::Vehicle::Vehicle() {
    srand(time(NULL));
    size_ = ((rand()/RAND_MAX) * 5) + 2;
}

structures::Vehicle::~Vehicle() {
    // Empty destructor (nada alocado dinamicamente)
}

size_t structures::Vehicle::size() const {
    return (size_ + SAFETY_DISTANCE);
}

int structures::Vehicle::direction() const {
    return direction_;
}

void structures::Vehicle::direction(int direction) {
    direction_ = direction;
}

#endif
