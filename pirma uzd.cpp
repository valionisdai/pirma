#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>


using namespace std;

struct Studentas{
string vard;
string pav;
vector<int> paz;
int egzas;
float rez;
float med;
};

Studentas ivesk();
Studentas generuok();


int main()
{
    vector<Studentas> Grupe;
    int n;
    char a;
    cout << "Iveskite studentu skaiciu: "; cin >> n;
    cout << "Ar norite, kad rezultatai butu sugeneruoti automatiskai? (T/N):"; cin >> a;
    if(a=='T')
        for(int i=0; i<n; i++)
            Grupe.push_back(generuok());
    else if(a=='N')
        for(int i=0; i<n; i++)
        {
            cout << "Iveskite " << i+1 << " studenta:\n";
            Grupe.push_back(ivesk());
        }



    cout << setw(10) << right << "Vardas" << " | " << setw(10) << right << "Pavarde " << " | " << setw(16) << right << "Galutinis (Vid.)" << " / " << setw(16) << right << "Galutinis (Med.)" << endl;
    for(auto temp: Grupe)
        cout << setw(10) << right << temp.vard << " | " << setw(10) << temp.pav << " | " << setw(16) << fixed << right << setprecision(2) << temp.rez << " / " << setw(16) <<  right << temp.med <<  endl;
}

Studentas ivesk(){
    Studentas laik;
    int sum =0, n, m;
        cout << "Iveskite varda: "; cin >> laik.vard;
        cout << "Iveskite pavarde: "; cin >> laik.pav;
        cout << "Iveskite studento pazymiu skaiciu: "; cin >> n;
        for(int i=0; i<n; i++)
            {
                cout << "Iveskite: " << i+1 << " paz. is " << n << ": " << endl; cin >> m;
                laik.paz.push_back(m);
                sum+=m;
            }
            // vidurkis
    cout << "Iveskite studento egzamino rezultata: "; cin >> laik.egzas;
    laik.rez = laik.egzas*0.6 + sum/laik.paz.size()*0.4;

            //mediana
    sort(laik.paz.begin(), laik.paz.end());
    float mediana;
    int paz_sk = laik.paz.size();
    if(paz_sk % 2 == 0)
        mediana = (laik.paz[paz_sk/2-1] + laik.paz[paz_sk/2])/2;
    else
        mediana = laik.paz[paz_sk/2];
    laik.med = laik.egzas*0.6 + mediana*0.4;
    return laik;
}


Studentas generuok(){
    Studentas laik;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> paz(1, 10);
    uniform_int_distribution<int> kiekis(1, 10);
    uniform_int_distribution<int> egzas(1, 10);
    int sum =0;
        cout << "Iveskite varda: "; cin >> laik.vard;
        cout << "Iveskite pavarde: "; cin >> laik.pav;
    int kiek = kiekis(gen);
    cout << "Sugeneruotas pazymiu skaicius: " << kiek << endl;
        for(int i=0; i<kiek; i++)
            {
                int pazymiai = paz(gen);
                laik.paz.push_back(pazymiai);
                sum+=pazymiai;
            }
            // vidurkis

    laik.egzas = egzas(gen);
    laik.rez = laik.egzas*0.6 + sum/laik.paz.size()*0.4;

            //mediana
    sort(laik.paz.begin(), laik.paz.end());
    float mediana;
    int paz_sk = laik.paz.size();
    if(paz_sk % 2 == 0)
        mediana = (laik.paz[paz_sk/2-1] + laik.paz[paz_sk/2])/2;
    else
        mediana = laik.paz[paz_sk/2];
    laik.med = laik.egzas*0.6 + mediana*0.4;
    return laik;
}



