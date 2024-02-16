#include "Carte.h"
#include <assert.h>
void Carte::setAutor(string autorNou) {
	this->autor = autorNou;
}
void Carte::setTitlu(string titluNou) {
	this->titlu = titluNou;
}
void Carte::setGen(string genNou) {
	this->gen = genNou;
}
void Carte::setAn(int anNou) {
	this->an_ap = anNou;
}

bool cmpTitlu(const Carte& c1, const Carte& c2) {
	return c1.getTitlu() < c2.getTitlu();
}

bool cmpAutor(const Carte& c1, const Carte& c2) {
	return c1.getAutor() < c2.getAutor();
}

//bool cmpGen(const Carte& c1, const Carte& c2) {
	//return c1.getGen() < c2.getGen();
//}

void testGetSet() {
	Carte song1{ "Pictures of Home", "Deep Purple","rock",1972 };
	assert(song1.getTitlu() == "Pictures of Home");
	assert(song1.getAutor() == "Deep Purple");
	assert(song1.getGen() == "rock");
	assert(song1.getAn() == 1972);

	Carte song2{ "Lucky Man", "Emerson, Lake & Palmer","rock",1934 };
	assert(song2.getTitlu() == "Lucky Man");
	assert(song2.getAutor() == "Emerson, Lake & Palmer");
	assert(song2.getGen() == "rock");
	assert(song2.getAn() == 1934);

	song2.setTitlu("Goodbye Blue Sky");
	song2.setAutor("Pink Floyd");
	song2.setGen("psychedelic rock");
	song2.setAn(1952);

	assert(song2.getTitlu() == "Goodbye Blue Sky");
	assert(song2.getAutor() == "Pink Floyd");
	assert(song2.getGen() == "psychedelic rock");
	assert(song2.getAn() == 1952);



}

void testeDomain() {
	testGetSet();
}