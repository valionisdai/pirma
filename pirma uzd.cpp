#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


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


int main()
{
    vector<Studentas> Grupe;
    int n;
    cout << "Iveskite studentu skaiciu: "; cin >> n;
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


