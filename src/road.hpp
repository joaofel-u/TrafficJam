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
     Road(unsigned int velocity, std::size_t max_size, char* name, char type);

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

     // Retorna o tamanho da pista
     std::size_t max_size() const;

     // Retorna o tamanho atual da fila de carros
     std::size_t size() const;

     // Retorna se a pista esta bloqueada
     bool blocked() const;

     // Retorna se a pista esta cheia
     bool full() const;

     // Retorna o tempo em segundos que um carro leva para percorrer a pista
     std::size_t time_of_route();

     // Retorna se a pista é eferente ou aferente
     char type();

     // Retorna o nome da pista
     char* name();

 private:
	 unsigned int velocity_;  // Velocidade da via
	 std::size_t max_size_;  // Tamanho em metros da pista
     std::size_t size_{0u};  // Tamanho em metros da fila de carros
	 bool blocked_;  // Sinaliza se a pista esta bloqueada
     char* name_;  // Nome simbo´lico da pista dentro do sistema
     char type_;
};

}

// IMPLEMENTACAO

structures::Road::Road(unsigned int velocity, std::size_t max_size, char* name, char type) {
    LinkedQueue<Vehicle*>();
    velocity_ = velocity;
    max_size_ = max_size;
    blocked_ = false;
    name_ = name;
    type_ = type;
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

std::size_t structures::Road::time_of_route() {
    return (max_size_ / (velocity_ / 3,6));
}

char structures::Road::type() {
    return type_;
}

char* structures::Road::name() {
    return name_;
}

#endif
