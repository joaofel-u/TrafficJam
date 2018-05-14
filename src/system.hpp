// Copyright [2018] <Joao Fellipe Uller>
#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <stdexcept>
#include <iostream>
#include "array_list.hpp"
#include "entry_road.hpp"
#include "sink_road.hpp"
#include "semaphore.hpp"
#include "linked_list.hpp"
#include "event.hpp"

using std::cout;
using std::endl;

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

    int input_counter_ = 0;
    int output_counter_ = 0;
    int semaphore_changes_ = 0;
    int road_changes_ = 0;

	ArrayList<Road*> roads_{14u};  // Lista das pistas do sistema
	ArrayList<Semaphore*> semaphores_{2u};  // Lista dos semaforos
	LinkedList<Event>* events_;  // Lista de eventos

    std::size_t next_semaphore_change_;
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
    EntryRoad* n1_south = new EntryRoad(60, 500, 80, 10, 10, 20, 5, (char*) "N1_S");
    EntryRoad* n2_south = new EntryRoad(40, 500, 40, 30, 30, 20, 5, (char*) "N2_S");
    EntryRoad* l1_west = new EntryRoad(30, 400, 30, 30, 40, 10, 2, (char*) "L1_W");
    EntryRoad* s2_north = new EntryRoad(40, 500, 30, 30, 40, 60, 15, (char*) "S2_N");
    EntryRoad* s1_north = new EntryRoad(60, 500, 10, 10, 80, 30, 7, (char*) "S1_N");
    EntryRoad* o1_east = new EntryRoad(80, 2000, 10, 80, 10, 10, 2, (char*) "O1_E");

    // Sumidouros
    SinkRoad* n1_north = new SinkRoad(60, 500, (char*) "N1_N");
    SinkRoad* n2_north = new SinkRoad(40, 500, (char*) "N2_N");
    SinkRoad* l1_east = new SinkRoad(30, 400, (char*) "L1_E");
    SinkRoad* s2_south = new SinkRoad(40, 500, (char*) "S2_S");
    SinkRoad* s1_south = new SinkRoad(60, 500, (char*) "S1_S");
    SinkRoad* o1_west = new SinkRoad(80, 2000, (char*) "O1_W");

    // Centrais
    EntryRoad* c1_east = new EntryRoad(60, 300, 30, 40, 30, 0, 0, (char*) "C1_E");
    EntryRoad* c1_west = new EntryRoad(60, 300, 30, 40, 30, 0, 0, (char*) "C1_W");

    // Ligacao das ruas
    n1_south->out_roads(c1_east, s1_south, o1_west);
    n2_south->out_roads(l1_east, s2_south, c1_west);
    l1_west->out_roads(s2_south, c1_west, n2_north);
    s2_north->out_roads(c1_west, n2_north, l1_east);
    s1_north->out_roads(o1_west, n1_north, c1_east);
    o1_east->out_roads(n1_north, c1_east, s1_south);
    c1_east->out_roads(n2_north, l1_east, s2_south);
    c1_west->out_roads(s1_south, o1_west, n1_north);

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
    Semaphore* s1 = new Semaphore(o1_east, n1_south, c1_west, s1_north, o1_west,
                                  n1_north, c1_east, s1_south);

    Semaphore* s2 = new Semaphore(c1_east, n2_south, l1_west, s2_north, c1_west,
                                  n2_north, l1_east, s2_south);

    // Montagem das listas de probabilidades de cada pista ser tomada para composicao dos semaforos
    // S1
    int prob_o1_west[4];
    for (int i = 0; i < 4; i++)
        prob_o1_west[i] = s1->afferent(i)->road_prob(o1_west);

    int prob_n1_north[4];
    for (int i = 0; i < 4; i++)
        prob_o1_west[i] = s1->afferent(i)->road_prob(n1_north);

    int prob_c1_east[4];
    for (int i = 0; i < 4; i++)
        prob_o1_west[i] = s1->afferent(i)->road_prob(c1_east);

    int prob_s1_south[4];
    for (int i = 0; i < 4; i++)
        prob_o1_west[i] = s1->afferent(i)->road_prob(s1_south);

    s1->road_probs(prob_o1_west, prob_n1_north, prob_c1_east, prob_s1_south);

    // S2
    int prob_c1_west[4];
    for (int i = 0; i < 4; i++)
        prob_o1_west[i] = s1->afferent(i)->road_prob(c1_west);

    int prob_n2_north[4];
    for (int i = 0; i < 4; i++)
        prob_o1_west[i] = s1->afferent(i)->road_prob(n2_north);

    int prob_l1_east[4];
    for (int i = 0; i < 4; i++)
        prob_o1_west[i] = s1->afferent(i)->road_prob(l1_east);

    int prob_s2_south[4];
    for (int i = 0; i < 4; i++)
        prob_o1_west[i] = s1->afferent(i)->road_prob(s2_south);

    s2->road_probs(prob_c1_west, prob_n2_north, prob_l1_east, prob_s2_south);

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
    while (global_time_ < execution_time_) {
        int events_made = 0;  // Numero de eventos feitos nessa execucao
        int i = 0;  // Auxilia no caso de não conseguir realizar um evento

        if (global_time_ == next_semaphore_change_) {  // Dá preferencia para eventos de troca de semaforo sobre outros
            while (events_->at(i).type() != 's')
                i++;
        }

        Event current_event = events_->at(i);

        while (current_event.event_time() <= global_time_) {
            switch(current_event.type()) {
                // Evento de entrada por uma das fontes
                case 'i': {
                    events_made++;
                    Vehicle* new_vehicle = new Vehicle();
                    EntryRoad* road = (EntryRoad*) current_event.src();
                    new_vehicle->direction(road->next_direction());

                    try {
                        // Adiciona o carro a pista (se possivel)
                        road->enqueue(new_vehicle);

                        // Remove o evento realizado da lista de eventos
                        events_->pop(i);

                        // Calcula a proxima entrada na pista
                        std::size_t event_time = global_time_ + road->time_next_vehicle();
                        Event* new_vehicle_event = new Event('i', event_time, road);
                        events_->insert_sorted(*new_vehicle_event);

                        // Calcula a chegada do veiculo criado ao seu semaforo
                        event_time = global_time_ + road->time_of_route();
                        Event* semaphore_arrival = new Event('a', event_time, road);
                        events_->insert_sorted(*semaphore_arrival);
                        input_counter_++;

                    } catch(std::out_of_range error) { // Pista cheia
                        i++;
                        delete new_vehicle;
                        cout << "Pista engarrafada: " << road->name() << endl;
                    }

                    break;
                }

                // Evento de saida por um dos sumidouros
                case 'o': {
                    events_made++;
                    SinkRoad* road = (SinkRoad*) current_event.src();

                    // Remove o evento realizado
                    events_->pop(i);

                    // Exclui o carro do sistema
                    delete road->dequeue();
                    output_counter_++;

                    break;
                }

                // Evento de troca de estado dos semaforos
                case 's': {
                    events_made++;

                    // Faz a troca nos semaforos
                    for (int i = 0; i < semaphores_.size(); i++)
                        semaphores_[i]->change();

                    // Remove o evento realizado
                    events_->pop(i);

                    // Adiciona um evento de troca de semaforos à lista
                    std::size_t event_time = global_time_ + semaphore_time_;
                    Event* e = new Event('s', event_time, semaphores_[0]);
                    events_->insert_sorted(*e);
                    semaphore_changes_++;
                    next_semaphore_change_ = event_time;

                    break;
                }

                // Evento de chegada num semaforo
                case 'a': {
                    events_made++;
                    EntryRoad* road = (EntryRoad*) current_event.src();
                    if (!road->open()) {
                        i++;
                        break;
                    }

                    Vehicle* vehicle = road->front();
                    Road* temp = road->out_road(vehicle->direction());

                    try {
                        temp->enqueue(vehicle);
                        road->dequeue();

                        // Remove o evento completado
                        events_->pop(i);

                        if (temp->type() == 'a') {
                            EntryRoad* r = (EntryRoad*) temp;

                            std::size_t event_time = global_time_ + r->time_of_route();
                            Event* e = new Event('a', event_time, r);
                            events_->insert_sorted(*e);
                        } else {
                            SinkRoad* r = (SinkRoad*) temp;

                            std::size_t event_time = global_time_ + r->time_of_route();
                            Event* e = new Event('o', event_time, r);
                            events_->insert_sorted(*e);
                        }
                        road_changes_++;

                        global_time_++;  // Soma o tempo de saida do carro
                    } catch(std::out_of_range error) {
                        i++;
                        cout << "Troca de pistas falhou: " << road->name() << " para " << temp->name() << endl;
                    }


                    break;
                }

                default:  // Caso inalcancavel
                    break;
            }
            if (global_time_ == next_semaphore_change_) {  // Dá preferencia para eventos de troca de semaforo sobre outros
                while (events_->at(i).type() != 's')
                    i++;
            }
            current_event = events_->at(i);  // Atualiza o evento atual
        }

        global_time_++;
        // Pula o relogio global para o horario do proximo evento no caso de nao ter feito nenhum agora
        if (events_made == 0)
            global_time_ = current_event.event_time();
    }
}

void structures::System::result() {
    int cars_inside_roads_ = 0;
    for (int i = 0; i < roads_.size(); i++)
        cars_inside_roads_ += roads_[i]->cars_on_road();

    cout << "-------------------RESULTADOS-------------------" << endl;
    cout << "Entrada de veículos      |  " << input_counter_ << endl;
    cout << "Trocas de pista          |  " << road_changes_ << endl;
    cout << "Saída de  veíulos        |  " << output_counter_ << endl;
    cout << "Carros dentro do sistema |  " << cars_inside_roads_ << endl;
    cout << "Trocas de semaforo       |  " << semaphore_changes_ << endl;
}

#endif
