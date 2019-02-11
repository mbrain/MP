#include <iostream>
#include <string>
#include "Parser.h"

int main() {
	std::string input;

	while (true) {
		std::cout << "> ";
		std::getline(std::cin, input);
        if(input.length()<1) continue;
		Parser p(input);
		// Baum generieren (Achtung: Speicher freigeben nicht vergessen!)
		Node *n = p.parse();
		std::cout << " " << n->eval() << std::endl;
		// Speicher freigeben
		delete n;
	}
}