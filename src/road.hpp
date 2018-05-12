/// Copyright [2018] <Joao Fellipe Uller
#ifndef ROAD_HPP
#define ROAD_HPP

#include <cstdio>
#include "linked_queue.hpp"
#include "vehicle.hpp"

using std::size_t;

namespace structures {
// Implementa uma pista
class Road : private LinkedQueue<Vehicle*> {
 public:
     // Construtor
     Road(unsigned int velocity, size_t max_size, char* name, char type);

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
     size_t max_size() const;

     // Retorna o tamanho atual da fila de carros
     size_t size() const;

     // Retorna se a pista esta cheia
     bool full() const;

     // Retorna o tempo em segundos que um carro leva para percorrer a pista
     size_t time_of_route();

     // Retorna se a pista é eferente ou aferente
     char type();

     // Retorna o nome da pista
     char* name();

     // Retorna o numero de carros na pista
     int cars_on_road();

 private:
	 unsigned int velocity_;  // Velocidade da via
	 size_t max_size_;  // Tamanho em metros da pista
     size_t size_{0u};  // Tamanho em metros da fila de carros
     char* name_;  // Nome simbo´lico da pista dentro do sistema
     char type_;  // Pista aferente ou eferente
};

}

// IMPLEMENTACAO

structures::Road::Road(unsigned int velocity, size_t max_size, char* name, char type) {
    LinkedQueue<Vehicle*>();
    velocity_ = velocity;
    max_size_ = max_size;
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
    if ((size_ + vehicle->size()) > max_size_)
        throw std::out_of_range("Pista cheia");

    LinkedQueue<Vehicle*>::enqueue(vehicle);
    size_ += vehicle->size();
}

structures::Vehicle* structures::Road::dequeue() {
    Vehicle *vehicle = LinkedQueue<Vehicle*>::dequeue();
    size_ -= vehicle->size();
    return vehicle;
}

size_t structures::Road::max_size() const {
    return max_size_;
}

structures::Vehicle* structures::Road::front() const {
    return LinkedQueue<Vehicle*>::front();
}

bool structures::Road::full() const {
    return size_ == max_size_;
}

size_t structures::Road::time_of_route() {
    return (max_size_ / (velocity_ / 3,6));
}

char structures::Road::type() {
    return type_;
}

char* structures::Road::name() {
    return name_;
}

int structures::Road::cars_on_road() {
    return LinkedQueue<Vehicle*>::size();
}

#endif
