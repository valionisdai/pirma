#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

struct Studentas{
string vard;
string pav;
vector<int> paz;
int egzas;
float rez;
};

Studentas ivesk();


int main()
{
    vector<Studentas> Grupe;
    cout << "Iveskite studentu skaiciu: "; cin >> n;
    for(int i=0; i<n; i++)
    {
        cout << "Iveskite " << i+1 << " studenta:\n";
        Grupe.push_back(ivesk());
    }
    cout << setw(10) << right << "Vardas" << " | " << setw(10) << "Pavarde " << " | " << setw(10) << fixed << "Galutinis (Vid.)" << endl;
    for(auto temp: Grupe)
        cout << setw(10) << right << temp.vard << " | " << setw(10) << temp.pav << " | " << setw(10) << fixed << setprecision(2) << temp.rez << endl;
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
    cout << "Iveskite studento egzamino rezultata: "; cin >> laik.egzas;
    laik.rez = laik.egzas*0.6 + sum/laik.paz.size()*0.4;
    return laik;
}


