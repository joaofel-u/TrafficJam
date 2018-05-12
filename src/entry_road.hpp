/// Copyright [2018] <Joao Fellipe Uller
#ifndef ENTRY_ROAD_HPP
#define ENTRY_ROAD_HPP

#include "array_list.hpp"
#include "road.hpp"

using structures::Road;

namespace structures {
// Implementa uma pista de entrada (fonte ou central)
class EntryRoad : public Road {
 public:
     // Construtor
     EntryRoad(unsigned int velocity,
            std::size_t max_size,
            int prob_rl,
            int prob_rf,
            int prob_rr,
            int avg_new_time,
            int variation,
            char* name);

     // Destrutor
     ~EntryRoad();

     // Insere veiculo no final da fila
     void enqueue(Vehicle* vehicle);

     // Define as ruas adjacentes no cruzamento
     void out_roads(Road* rl, Road* rf, Road* rr);

     // Retorna a referencia para a pista na direção dada
     Road* out_road(int direction);

     // Gera um tempo aleato'rio para entrada de um novo veiculo
     std::size_t time_next_vehicle();

     // Calcula aleatoriamente a direcao de um carro baseado na prob. de cada pista eferente
     int next_direction();  // 0 = left, 1 = front, 2 = right

 private:
	 ArrayList<Road *> out_roads_{3u};  // Lista das pistas de saida
	 int probs_[3];  // Probabilidade de tomar uma determinada pista
     int average_new_time_;
     int variation_;
};

}  // namespace structures

// IMPLEMENTACAO
structures::EntryRoad::EntryRoad(unsigned int velocity,
                                std::size_t max_size,
                                int prob_rl,
                                int prob_rf,
                                int prob_rr,
                                int avg_new_time,
                                int variation,
                                char* name) :
    Road::Road(velocity, max_size, name, 'a'),
    average_new_time_{avg_new_time},
    variation_{variation}
    {
	   probs_[0] = prob_rl;
	   probs_[1] = prob_rf;
	   probs_[2] = prob_rr;
}

structures::EntryRoad::~EntryRoad() {
    Road::clear();
}

void structures::EntryRoad::enqueue(Vehicle* vehicle) {
	vehicle->direction(next_direction());
    Road::enqueue(vehicle);
}

void structures::EntryRoad::out_roads(Road* rl, Road* rf, Road* rr) {
    out_roads_.push_back(rl);  // Road_left
    out_roads_.push_back(rf);  // Road_front
    out_roads_.push_back(rr);  // Road_right
}

Road* structures::EntryRoad::out_road(int direction) {
    return out_roads_[direction];
}

std::size_t structures::EntryRoad::time_next_vehicle() {
    srand(time(NULL));
    return (rand() % (2*variation_)) + (average_new_time_ - variation_);
}

int structures::EntryRoad::next_direction() {
    srand(time(NULL));
    int prob = rand() % 100;
    int prob_acumulada = 0;

    for (int i = 0; i < 3; i++) {
        if (prob < (probs_[i] + prob_acumulada))
            return i;
        else
            prob_acumulada += prob;
    }

    return 0;  // Inalcancavel
}

#endif
