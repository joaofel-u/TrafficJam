/// Copyright [2018] <Joao Fellipe Uller
#ifndef SINK_ROAD_HPP
#define SINK_ROAD_HPP

#include "road.hpp"

namespace structures {
// Implementa uma pista de saida (sumidouro)
class SinkRoad : public Road {
 public:
     // Construtor
     SinkRoad(unsigned int velocity, std::size_t max_size);

     // Destrutor
     ~SinkRoad();

     // Insere veiculo no final da fila
     virtual void enqueue(Vehicle* vehicle);
};

}

// IMPLEMENTACAO
structures::SinkRoad::SinkRoad(unsigned int velocity, std::size_t max_size) :
    Road::Road(velocity, max_size, 'e')
    {
}

structures::SinkRoad::~SinkRoad() {
    Road::clear();
}

void structures::SinkRoad::enqueue(Vehicle* vehicle) {
    Road::enqueue(vehicle);
}

#endif
