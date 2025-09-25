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

Studentas skaiciuojam(int a, int b);
vector<Studentas> failas(int b);

int main()
{
    vector<Studentas> Grupe;
    int n, a, b;
    cout << "Norite apskaiciuoti:" << endl;
    cout << "(1) Vidurki" << endl;
    cout << "(2) Mediana" << endl;
    cout << "(3) Abu" << endl; cin >> b;
    cout << "Norite:" << endl;
    cout << "(1) Generuoti automatiskai rezultatus" << endl;
    cout << "(2) Ranka suvesti rezultatus" << endl;
    cout << "(3) Skaityti rezultatus is failo" << endl; cin >> a;
    if(a==3)
        Grupe = failas(b);
    else
        {
            cout << "Iveskite studentu skaiciu: "; cin >> n;
            for(int i=0; i<n; i++)
                Grupe.push_back(skaiciuojam(a, b));
        }
    cout << setw(10) << right << "Vardas" << " | " << setw(10) << right << "Pavarde " << " | " << setw(16) << right;
    if(b==1) cout << "Galutinis (Vid.)" << endl;
            else if(b==2) cout << "Galutinis (Med.)" << endl;
            else if(b==3) cout << "Galutinis (Vid.)" << " / " << setw(16) << right << "Galutinis (Med.)" << endl;
    for(auto temp: Grupe)
        {
            cout << setw(10) << right << temp.vard << " | " << setw(10) << temp.pav << " | " << setw(16) << fixed << right << setprecision(2);
            if(b==1) cout << temp.rez << endl;
            else if(b==2) cout << setw(16) << right << temp.med << endl;
            else if (b==3) cout << temp.rez << " / " << setw(16) <<  right << temp.med << endl;
        }
}

vector<Studentas> failas(int b)
{
    Studentas laik;
    vector<Studentas> Grupe;
    ifstream rd("kursiokai.txt");
    string z, x;
    int j=0, temp, k, sum=0;
    while(true)
    {
        rd >> z;
        j++;
        if(z=="Egz.")
            break;
    }
    k=j-3;
    while(rd >> z >> x)
    {
        laik.pav = z;
        laik.vard = x;
        for(int i=0;i<k;i++)
        {
            rd >> temp;
            laik.paz.push_back(temp);
            sum+=temp;
        }
        rd >> laik.egzas;

        if(b==1 || b==3)
            laik.rez = laik.egzas*0.6 + ((float)sum/laik.paz.size())*0.4;
            //mediana
        if(b==2 || b==3)
        {
            sort(laik.paz.begin(), laik.paz.end());
            float mediana;
            int paz_sk = laik.paz.size();
            if(paz_sk % 2 == 0)
                mediana = (laik.paz[paz_sk/2-1] + laik.paz[paz_sk/2])/2.0;
            else
                mediana = laik.paz[paz_sk/2];
            laik.med = laik.egzas*0.6 + mediana*0.4;
        }
        Grupe.push_back(laik);
    }
    rd.close();
    return Grupe;
}

Studentas skaiciuojam(int a, int b){
    Studentas laik;
    int sum=0, m, j=0;
    if(a==1){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> generuojam(1, 10);
        cout << "Iveskite varda: "; cin >> laik.vard;
        cout << "Iveskite pavarde: "; cin >> laik.pav;
        int kiek = generuojam(gen);
        cout << "Sugeneruotas pazymiu skaicius: " << kiek << endl;
        for(int i=0; i<kiek; i++)
            {
                int pazymiai = generuojam(gen);
                laik.paz.push_back(pazymiai);
                sum+=pazymiai;
            }

        laik.egzas = generuojam(gen);
    }
    else if(a==2)
    {
        cout << "Iveskite varda: "; cin >> laik.vard;
        cout << "Iveskite pavarde: "; cin >> laik.pav;
        cout << "Iveskite studento pazymius (iveskite 0, jei baigiate vesti pazymius): " << endl;
        while(true)
            {
                cin >> m;
                if(m==0) break;
                laik.paz.push_back(m);
                sum+=m;
                j++;
            }
    cout << "Studento pazymiu skaicius: " << j << endl;
            // vidurkis
    cout << "Iveskite studento egzamino rezultata: "; cin >> laik.egzas;
    }
    if(b==1 || b==3)
        laik.rez = laik.egzas*0.6 + ((float)sum/laik.paz.size())*0.4;
            //mediana
    if(b==2 || b==3)
    {sort(laik.paz.begin(), laik.paz.end());
    float mediana;
    int paz_sk = laik.paz.size();
    if(paz_sk % 2 == 0)
        mediana = (laik.paz[paz_sk/2-1] + laik.paz[paz_sk/2])/2.0;
    else
        mediana = laik.paz[paz_sk/2];
    laik.med = laik.egzas*0.6 + mediana*0.4;
    }
    return laik;
}


