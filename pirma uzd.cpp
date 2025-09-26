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

Studentas skaiciuojam(char a, char b);
vector<Studentas> failas(char b);

int main()
{
    ofstream wr("rez.txt");
    vector<Studentas> Grupe;
    int n;
    char a, b;
    cout << "Norite apskaiciuoti:" << endl;
        cout << "(1) Vidurki" << endl;
        cout << "(2) Mediana" << endl;
        cout << "(3) Abu" << endl; cin >> b;
    while(true)
    {if(b=='1' || b=='2' || b=='3')break;
     else {cout << "Neteisinga ivestis, pasirinkite skaiciu nuo 1 iki 3:" << endl; cin >> b;}}
    cout << "Norite:" << endl;
    cout << "(1) Generuoti automatiskai rezultatus" << endl;
    cout << "(2) Ranka suvesti rezultatus" << endl;
    cout << "(3) Skaityti rezultatus is failo" << endl; cin >> a;
    while(true)
    {if(a=='1' || a=='2' || a=='3')break;
     else {cout << "Neteisinga ivestis, pasirinkite skaiciu nuo 1 iki 3:" << endl; cin >> a;}}
    if(a=='3')
        Grupe = failas(b);
    else
        {
            cout << "Iveskite studentu skaiciu: "; cin >> n;
            for(int i=0; i<n; i++)
                Grupe.push_back(skaiciuojam(a, b));
        }
    sort(Grupe.begin(), Grupe.end(), [](const Studentas& a, const Studentas& b){
    auto extractNumber = [](const string& vardas){
        size_t pos = vardas.find_first_of("0123456789");
        if (pos != string::npos)
            return stoi(vardas.substr(pos));
        return 0;
        };
    return extractNumber(a.vard) < extractNumber(b.vard);
    });

    wr << setw(15) << right << "Vardas" << " | " << setw(15) << right << "Pavarde " << " | " << setw(18) << right;
    if(b=='1') {wr << "Galutinis (Vid.)" << endl; wr << "------------------------------------------" << endl;}
            else if(b=='2') {wr << "Galutinis (Med.)" << endl; wr << "------------------------------------------" << endl;}
            else if(b=='3') {wr << "Galutinis (Vid.)" << " / " << setw(18) << right << "Galutinis (Med.)" << endl; wr << "---------------------------------------------------------------------------" << endl;}
    for(auto temp: Grupe)
        {
            wr << setw(15) << right << temp.vard << " | " << setw(15) << temp.pav << " | " << setw(18) << fixed << right << setprecision(2);
            if(b=='1') wr << temp.rez << endl;
            else if(b=='2') wr << setw(18) << right << temp.med << endl;
            else if (b=='3') wr << temp.rez << " / " << setw(18) <<  right << temp.med << endl;
        }
}

vector<Studentas> failas(char b)
{
    string failvar;
    char l;
    vector<Studentas> Grupe;
    cout << "Is kurio failo norite skaityti duomenis?" << endl;
    cout << "(1) kursiokai.txt" << endl;
    cout << "(2) studentai10000.txt" << endl;
    cout << "(3) studentai100000.txt" << endl;
    cout << "(4) studentai1000000.txt" << endl;
    cin >> l;
    while(true)
    {if(l=='1' || l=='2' || l=='3' || l=='4')break;
     else {cout << "Neteisinga ivestis, pasirinkite skaiciu nuo 1 iki 4:" << endl; cin >> l;}}

    if(l=='1')
         failvar = "kursiokai.txt";
    else if(l=='2')
         failvar = "studentai10000.txt";
    else if(l=='3')
         failvar = "studentai100000.txt";
    else if(l=='4')
         failvar = "studentai1000000.txt";
    ifstream rd(failvar);
    string z, x;
    int j=0, temp, k, sum=0;
    while(true)
    {
        sum = 0;
        rd >> z;
        j++;
        if(z=="Egz.")
            break;
    }
    k=j-3;
    while(rd >> z >> x)
    {
        sum=0;
        Studentas laik;
        laik.pav = x;
        laik.vard = z;
        for(int i=0;i<k;i++)
        {
            rd >> temp;
            laik.paz.push_back(temp);
            sum+=temp;
        }
        rd >> laik.egzas;

        if(b=='1' || b=='3')
            laik.rez = laik.egzas*0.6 + ((float)sum/laik.paz.size())*0.4;
            //mediana
        if(b=='2' || b=='3')
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

Studentas skaiciuojam(char a, char b){
    Studentas laik;
    int sum=0, m, j=0;
    if(a=='1'){
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
    else if(a=='2')
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
    if(b=='1' || b=='3')
        laik.rez = laik.egzas*0.6 + ((float)sum/laik.paz.size())*0.4;
            //mediana
    if(b=='2' || b=='3')
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



