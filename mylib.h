#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <sstream>
#include <chrono>
#include <execution>

using namespace std;

struct Studentas{
string vard;
string pav;
vector<int> paz;
int egzas;
float rez;
float med;
};

Studentas skaiciuojam(int a, int b);
vector<Studentas> failas(int b, string failvardas);
void vidurkis(Studentas& laik, int sum);
void skmediana(Studentas& laik);
int pazym_gen();
string generuojame();
void isvedimas(int b, const vector<Studentas>& Grupe, string failovardas);
stringstream skaitymas(string failvar);
void rusiavimas(int b, vector<Studentas>& Grupe, string failovardas);




