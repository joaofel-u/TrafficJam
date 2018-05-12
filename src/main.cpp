// Copyright [2018] <Joao Fellipe Uller>
#include <fstream>
#include <cstdint>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "system.hpp"

#define DEFAULT_SIM_TIME 14400  // 4 horas
#define DEFAULT_SEMAPHORE_TIME 25

using std::cout;
using std::endl;
using std::size_t;

int main(int argc, char const *argv[]) {
	bool comentarios = true;
	size_t tempo_semaforo = DEFAULT_SEMAPHORE_TIME;
	size_t tempo_simulacao = DEFAULT_SIM_TIME;

	std::ifstream arquivo("sim_cfg.dat");
	if (arquivo.is_open()) {
		char line[100];
		while (comentarios){
			arquivo.getline(line,100);
			if (line[0]!='#')
				comentarios = false;
		}

		arquivo >> tempo_simulacao;
		arquivo >> tempo_semaforo;
	}

	cout << "Tempo de Simulação: " << (tempo_simulacao/3600) << ":" << (tempo_simulacao % 3600)/60 << " horas" << endl;
	cout << "Tempo para troca de semaforo: " << tempo_semaforo << " segundos" << endl;

	structures::System sys{tempo_simulacao, tempo_semaforo};
	sys.init();
	sys.run();
	sys.result();

	return 0;
}
