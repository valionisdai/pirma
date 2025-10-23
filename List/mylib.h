#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <sstream>
#include <chrono>
#include <execution>
#include <list>

using namespace std;

struct Studentas{
string vard;
string pav;
list<int> paz;
int egzas;
float rez;
float med;
};

Studentas skaiciuojam(int a, int b);
list<Studentas> failas(int b, string failvardas);
void vidurkis(Studentas& laik, int sum);
void skmediana(Studentas& laik);
int pazym_gen();
string generuojame();
void isvedimas(int b, const list<Studentas>& Grupe, string failovardas);
stringstream skaitymas(string failvar);
void rusiavimas(int b, list<Studentas>& Grupe, string failovardas);



