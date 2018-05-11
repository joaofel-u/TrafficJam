/// Copyright [2018] <Joao Fellipe Uller
#ifndef ROAD_HPP
#define ROAD_HPP

#include <cstdio>
#include "linked_queue.hpp"
#include "vehicle.hpp"
#include "string.h"

namespace structures {
// Implementa uma pista
class Road : private LinkedQueue<Vehicle *> {
 public:
     // Construtor
     Road(unsigned int velocity, std::size_t max_size, char type, char* name);

     // Destrutor
     ~Road();

     /// limpar
     void clear();

     // Insere veiculo no final da fila
     virtual void enqueue(Vehicle* vehicle);

     // Remove o primeiro veiculo da fila
     Vehicle* dequeue();

     /// Retorna o primeiro veiculo da fila
     Vehicle* front() const;

     /// Retorna o ultimo elemento da fila
     Vehicle* back() const;

     // Retorna o tamanho maximo da fila
     std::size_t max_size() const;

     // Retorna o tamanho atual da fila
     std::size_t size() const;

     // Retorna se a pista esta bloqueada
     bool blocked() const;

     // Retorna se a pista esta cheia
     bool full() const;

     // Retorna a velocidade ma'xima da pista
     unsigned int velocity();

     // Retorna o tipo de pista ('e' = eferente, 'a' = aferente)
     char type();

 private:
	 unsigned int velocity_;  // Velocidade da via
	 std::size_t max_size_;  // Tamanho em metros (VER)
     std::size_t size_{0u};
	 bool blocked_;  // Sinaliza se a pista esta bloqueada
     char type_;  // e = eferente (sink), a = aferente (alimenta um semaforo)
     char* name_;  // Nome simbo´lico da pista dentro do sistema
};

}

// IMPLEMENTACAO

structures::Road::Road(unsigned int velocity, std::size_t max_size, char type, char* name) {
    LinkedQueue<Vehicle*>();
    velocity_ = velocity;
    max_size_ = max_size;
    type_ = type;
    blocked_ = false;
    name_ = name;
}

structures::Road::~Road() {
    clear();
}

void structures::Road::clear() {
    LinkedQueue<Vehicle*>::clear();
}

void structures::Road::enqueue(Vehicle* vehicle) {
    LinkedQueue<Vehicle*>::enqueue(vehicle);
    size_ += vehicle->size();
}

structures::Vehicle* structures::Road::dequeue() {
    Vehicle *vehicle = LinkedQueue<Vehicle*>::dequeue();
    size_ -= vehicle->size();
    return vehicle;
}

std::size_t structures::Road::max_size() const {
    return max_size_;
}

bool structures::Road::blocked() const {
    return blocked_;
}

bool structures::Road::full() const {
    return size_ == max_size_;
}

unsigned int structures::Road::velocity() {
    return velocity_;
}

char structures::Road::type() {
    return type_;
}

#endif
