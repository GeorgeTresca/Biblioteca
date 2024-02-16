#include "Cos.h"
using std::shuffle;

void Cos::addCarteinCos(const Carte& s) {
	this->cosCarti.push_back(s);
}
void Cos::emptyCos() {
	this->cosCarti.clear();
}

void Cos::addRandomCarti(vector<Carte> originalCarti, int howMany) {
	shuffle(originalCarti.begin(), originalCarti.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
	while (cosCarti.size() < howMany && originalCarti.size() > 0) {
		cosCarti.push_back(originalCarti.back());
		originalCarti.pop_back();
	}
}
const vector<Carte>& Cos::getAllCartiCos() {
	return this->cosCarti;
}