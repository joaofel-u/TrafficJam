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
	std::size_t execution_time_;
	std::size_t semaphore_time_;
	ArrayList<Road*> roads{14u};  // Lista das pistas do sistema
	ArrayList<Semaphore*> semaphores{2u};  // Lista dos semaforos
	LinkedList<Event>* events;
};

}  // namespace structures

// IMPLEMENTACAO

structures::System::System(std::size_t execution_time, std::size_t semaphore_time) {
	execution_time_ = execution_time;
	semaphore_time_ = semaphore_time;
	events = new LinkedList<Event>();
}

structures::System::~System() {
	delete events;
}

void structures::System::init() {

}

void structures::System::run() {

}

void structures::System::result() {

}

#endif
