/// Copyright [2018] <Joao Fellipe Uller
#ifndef EVENT_HPP
#define EVENT_HPP

#include <cstdint>

namespace structures {

class Event {
  public:
	  // Construtor
	  Event(char type, std::size_t time, void* src);

	  // Destrutor
	  ~Event();

	  // Retorna o tipo de evento
	  char type() const;

	  // Retorna o horario global do evento
	  std::size_t event_time() const;

	  // Retorna referencia para quem gerou o evento
	  void* src() const;

	  // Sobrescrita do operador menor
	  bool operator<(const Event& other) const;

	  // Sobrescrita do operador maior
	  bool operator>(const Event& other) const;

  private:
	  char type_;  // i = in, o = out, s = semaphore_change, a = semaphore_arrive
	  std::size_t event_time_;
	  void* src_;
};

}  // namespace structures

// IMPLEMENTACAO

structures::Event::Event(char type, std::size_t time_, void* src) {
	type_ = type;
	event_time_ = time_;
	src_ = src;
}

structures::Event::~Event() {
	// Empty destructor (nada alocado dinamicamente)
}

char structures::Event::type() const {
	return type_;
}

std::size_t structures::Event::event_time() const {
	return event_time_;
}

void* structures::Event::src() const {
	return src_;
}

bool structures::Event::operator<(const Event& other) const {
	return (event_time_ < other.event_time());
}

bool structures::Event::operator>(const Event& other) const {
	return (event_time_ > other.event_time());
}

#endif
