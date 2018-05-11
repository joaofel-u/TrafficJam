// Copyright [2018] <Joao Fellipe Uller>
#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "array_list.hpp"
#include "entry_road.hpp"
#include "sink_road.hpp"
#include "semaphore.hpp"
#include "linked_list.hpp"
#include "event.hpp"

namespace structures {

// Define o sistema de simulacao
class System {
  public:

	// Construtor
	System(std::size_t execution_time, std::size_t semaphore_time);

	// Destrutor
	~System();

	// Cria o ambiente de simulacao
	void init();

	// Executa a simulacao
	void run();

	// Imprime os resultados na tela
	void result();

  private:
    std::size_t global_time_{0u};  // Relogio global dentro do sistema
	std::size_t execution_time_;  // Tempo de simulacao
	std::size_t semaphore_time_;  // Tempo entre trocas no semaforo

	ArrayList<Road*> roads_{14u};  // Lista das pistas do sistema
	ArrayList<Semaphore*> semaphores_{2u};  // Lista dos semaforos
	LinkedList<Event>* events_;  // Lista de eventos
};

}  // namespace structures

// IMPLEMENTACAO

structures::System::System(std::size_t execution_time, std::size_t semaphore_time) {
	execution_time_ = execution_time;
	semaphore_time_ = semaphore_time;
	events_ = new LinkedList<Event>();
}

structures::System::~System() {
	delete events_;
}

void structures::System::init() {
    // Fontes
    Road* n1_south = new EntryRoad(60, 500, 80, 10, 10, 20, 5, (char*) "N1_S");
    Road* n2_south = new EntryRoad(40, 500, 40, 30, 30, 20, 5, (char*) "N2_S");
    Road* l1_west = new EntryRoad(30, 400, 30, 30, 40, 10, 2, (char*) "L1_W");
    Road* s2_north = new EntryRoad(40, 500, 30, 30, 40, 60, 15, (char*) "S2_N");
    Road* s1_north = new EntryRoad(60, 500, 10, 10, 80, 30, 7, (char*) "S1_N");
    Road* o1_east = new EntryRoad(80, 2000, 10, 80, 10, 10, 2, (char*) "O1_E");

    // Sumidouros
    Road* n1_north = new SinkRoad(60, 500, (char*) "N1_N");
    Road* n2_north = new SinkRoad(40, 500, (char*) "N2_N");
    Road* l1_east = new SinkRoad(30, 400, (char*) "L1_E");
    Road* s2_south = new SinkRoad(40, 500, (char*) "S2_S");
    Road* s1_south = new SinkRoad(60, 500, (char*) "S1_S");
    Road* o1_west = new SinkRoad(80, 2000, (char*) "O1_W");

    // Centrais
    Road* c1_east = new EntryRoad(60, 300, 30, 40, 30, 0, 0, (char*) "C1_E");
    Road* c1_west = new EntryRoad(60, 300, 30, 40, 30, 0, 0, (char*) "C1_W");

    // Ligacao das ruas
    ((EntryRoad*)n1_south)->out_roads(c1_east, s1_south, o1_west);
    ((EntryRoad*)n2_south)->out_roads(l1_east, s2_south, c1_west);
    ((EntryRoad*)l1_west)->out_roads(s2_south, c1_west, n2_north);
    ((EntryRoad*)s2_north)->out_roads(c1_west, n2_north, l1_east);
    ((EntryRoad*)s1_north)->out_roads(o1_west, n1_north, c1_east);
    ((EntryRoad*)o1_east)->out_roads(n1_north, c1_east, s1_south);
    ((EntryRoad*)c1_east)->out_roads(n2_north, l1_east, s2_south);
    ((EntryRoad*)c1_west)->out_roads(s1_south, o1_west, n1_north);

    // Insercao das pistas na lista de ruas
    roads_.push_back(n1_south);
    roads_.push_back(n2_south);
    roads_.push_back(l1_west);
    roads_.push_back(s2_north);
    roads_.push_back(s1_north);
    roads_.push_back(o1_east);
    roads_.push_back(n1_north);
    roads_.push_back(n2_north);
    roads_.push_back(l1_east);
    roads_.push_back(s2_south);
    roads_.push_back(s1_south);
    roads_.push_back(o1_west);
    roads_.push_back(c1_east);
    roads_.push_back(c1_west);

    // Criacao dos semaforos
    Semaphore* s1 = new Semaphore(o1_east, n1_south, c1_west, s1_north, o1_west, 0,
                                  n1_north, 0, c1_east, 0, s1_south, 0);

    Semaphore* s2 = new Semaphore(c1_east, n2_south, l1_west, s2_north, c1_west, 0,
                                  n2_north, 0, l1_east, 0, s2_south, 0);

    // Insercao dos semaforos na lista de semaforos
    semaphores_.push_back(s1);
    semaphores_.push_back(s2);

    // Calcula os primeiros eventos de entrada de carros
    for (int i = 0;i < 6; i++) {
        EntryRoad* road = (EntryRoad*) roads_[i];  // 0 - 5 sao as seis fontes na lista de pistas
        std::size_t event_time = global_time_ + road->time_next_vehicle();
        Event* e = new Event('i', event_time, road);
        events_->insert_sorted(*e);
    }

    // Primeiro evento de troca de semáforo
    std::size_t event_time = global_time_ + semaphore_time_;
    Event* e = new Event('s', event_time, (void*) semaphores_[0]);
    events_->insert_sorted(*e);
}

void structures::System::run() {

}

void structures::System::result() {

}

#endif
