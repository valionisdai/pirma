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
string generuojame(string g);
void isvedimas(int b, const vector<Studentas>& Grupe, string failovardas);
stringstream skaitymas(string failvar);
void rusiavimas(int b, vector<Studentas> Grupe, string failovardas);


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<Studentas> Grupe;
    int n, a, b, c;
    cout << "Norite:\n(1) Sugeneruoti visus duomenis\n(2) Suvesti jau turimus duomenis" << endl;
    while(true)
    {
        if(cin >> c && c>=1 && c<=2) break;
        cout << "Neteisinga ivestis, pasirinkite skaiciu nuo 1 iki 3:" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
     }
        cout << "Norite apskaiciuoti:\n(1) Vidurki\n(2) Mediana\n(3) Abu" << endl;
    while(true)
    {
        if(cin >> b && b>=1 && b<=3) break;
        cout << "Neteisinga ivestis, pasirinkite skaiciu nuo 1 iki 3:" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
     }
    if(c==1)
    {

        for(int i=1;i<=5;i++)
        {
            cout << "Pasirinkinte " << i << " faila" << endl;
            string failvardas = generuojame(to_string(i));
            Grupe = failas(b, failvardas);
            rusiavimas(b, Grupe, failvardas);
            Grupe.clear();
        }

    }
    if(c==2)
    {
        cout << "Norite:\n(1) Generuoti automatiskai rezultatus\n(2) Ranka suvesti rezultatus\n(3) Skaityti rezultatus is failo" << endl;
        while(true)
        {
            if(cin >> a && a>=1 && a<=4) break;
            cout << "Neteisinga ivestis, pasirinkite skaiciu nuo 1 iki 4:" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if(a==3)
        {
            Grupe = failas(b,"1");
        }
        else
        {
            cout << "Iveskite studentu skaiciu: "; cin >> n;
            auto start = chrono::high_resolution_clock::now();
            for(int i=0; i<n; i++)
                Grupe.push_back(skaiciuojam(a, b));
            auto end = chrono::high_resolution_clock::now();
            cout << "Skaiciavimo laikas: " << chrono::duration_cast<chrono::seconds>(end - start).count() << " s" << endl;
        }
        rusiavimas(b, Grupe, "1");
    }
}
void rusiavimas(int b, vector<Studentas> Grupe, string failovardas)
{
    auto startas = chrono::high_resolution_clock::now();
    sort(std::execution::par, Grupe.begin(), Grupe.end(), [](const Studentas& a, const Studentas& b)
    { return a.rez > b.rez; });

    vector<Studentas> gerai, blogai;
    for(const auto& temp : Grupe)
    {
        if(temp.rez>=5)
            gerai.push_back(temp);
        else
            blogai.push_back(temp);
    }
    auto endas = chrono::high_resolution_clock::now();
    cout << "Rusiavimo ir rikiavimo laikas: " << chrono::duration_cast<chrono::seconds>(endas - startas).count() << " s" << endl;
    isvedimas(b, gerai, "gerai_"+failovardas);
    isvedimas(b, blogai, "blogai_"+failovardas);
}

void isvedimas(int b, const vector<Studentas>& Grupe, string failovardas)
{
    auto startas = chrono::high_resolution_clock::now();
    if("1"==failovardas)
        failovardas = "rez.txt";
    else
        failovardas = "rez_"+failovardas;
    ofstream wr(failovardas);
    ostringstream oss;
    wr << setw(15) << right << "Vardas | " << setw(15) << right << "Pavarde | " << setw(18) << right;
    if(b==1) {wr << "Galutinis (Vid.)\n------------------------------------------" << endl;}
            else if(b==2) {wr << "Galutinis (Med.)\n------------------------------------------" << endl;}
            else if(b==3) {wr << "Galutinis (Vid.) / " << setw(18) << right << "Galutinis (Med.)\n---------------------------------------------------------------------------" << endl;}
    for(const auto&temp: Grupe)
        {
            oss << setw(15) << right << temp.vard << " | " << setw(15) << temp.pav << " | " << setw(18) << fixed << right << setprecision(2);
            if(b==1) oss << temp.rez << endl;
            else if(b==2) oss << setw(18) << right << temp.med << endl;
            else if (b==3) oss << temp.rez << " / " << setw(18) <<  right << temp.med << endl;
        }
    wr << oss.str();
    wr.close();
    auto endas = chrono::high_resolution_clock::now();
    cout << "Failo " << failovardas << " rasymo laikas: " << chrono::duration_cast<chrono::seconds>(endas - startas).count() << " s" << endl;
}


stringstream skaitymas(string failvar)
{
    ifstream rd(failvar);
    stringstream buffer;
    if (!rd.is_open()) {
        cerr << "Nepavyko atidaryti failo!" << endl;
        return buffer;
    }
    auto startas = chrono::high_resolution_clock::now();
    buffer << rd.rdbuf();
    auto endas = chrono::high_resolution_clock::now();
    cout << "Failo skaitymo laikas: " << chrono::duration_cast<chrono::seconds>(endas - startas).count() << " s" << endl;
    rd.close();
    return buffer;
}

vector<Studentas> failas(int b, string failvardas)
{
    string failvar;
    vector<Studentas> Grupe;
    if("1"==failvardas)
    {
        int l;
        cout << "Is kurio failo norite skaityti duomenis?\n(1) kursiokai.txt\n(2) studentai10000.txt\n(3) studentai100000.txt\n(4) studentai1000000.txt" << endl;
    while(true)
    {
        if(cin >> l && l>=1 && l<=4) break;
        cout << "Neteisinga ivestis, pasirinkite skaiciu nuo 1 iki 3:" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
     }
    if(l==1)
         failvar = "kursiokai.txt";
    else if(l==2)
         failvar = "studentai10000.txt";
    else if(l==3)
         failvar = "studentai100000.txt";
    else if(l==4)
         failvar = "studentai1000000.txt";
    }
    else failvar = failvardas;
    stringstream buffer = skaitymas(failvar);
    string line, z;

    int k = 0;
    getline(buffer, line);
    istringstream header(line);
    string word;
    while (header >> word) {
        if (word == "Egz.") break;
        k++;
    }
    k -= 2;
    auto startas = chrono::high_resolution_clock::now();
    while (getline(buffer, line))
    {
        if (line.empty()) continue;
        istringstream iss(line);
        Studentas laik;
        int paz, sum = 0;
        iss >> laik.vard >> laik.pav;
        for (int i = 0; i < k; i++) {
            if (!(iss >> paz)) break;
            laik.paz.push_back(paz);
            sum += paz;
        }
        iss >> laik.egzas;

        if (b == 1) vidurkis(laik, sum);
        else if (b == 2) skmediana(laik);
        else if (b == 3)
        {
            vidurkis(laik, sum);
            skmediana(laik);
        }
        Grupe.emplace_back(std::move(laik));
    }
    auto endas = chrono::high_resolution_clock::now();
    cout << "Rezultatu skaiciavimo laikas: " << chrono::duration_cast<chrono::seconds>(endas - startas).count() << " s" << endl;

    return Grupe;
}

int pazym_gen()
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<int> distrib(1, 10);
    return distrib(gen);
}

string generuojame(string g)
{
    int a, n;
    cout << "Pasirinkite kiek studentu norite sugeneruoti:" << endl;
    cout << setw(8) << right << "1000" << endl;
    cout << setw(8) << right << "10000" << endl;
    cout << setw(8) << right << "100000" << endl;
    cout << setw(8) << right << "1000000" << endl;
    cout << setw(8) << right << "10000000" << endl;
    while(true)
    {
        if(cin >> a && (a==1000 || a==10000 || a==100000 || a==1000000 || a==10000000)) break;
            cout << "Neteisinga ivestis, pasirinkite viena is skaiciu" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    string failovardas = g+"_stud_"+to_string(a)+".txt";
    ofstream wr(failovardas);
    cout << "Iveskite skaiciu pazymiu, kuriuos norite sugeneruoti (tarp ne daugiau 20, be egz.): " << endl;
    while(true)
    {
        if(cin >> n && n>0 && n<21) break;
            cout << "Neteisinga ivestis, pasirinkite skaiciu nuo 1 iki 20." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    auto start = chrono::high_resolution_clock::now();
    ostringstream oss;
    oss << "Vardas" << " " << "Pavarde" << " " << right;
    for(int i=0; i<n;i++)
    {
        oss << "ND" << i+1 << " ";
    }
    oss << "Egz.\n";
    for(int i=0;i<a;i++)
    {
        oss << "Vardas" << i+1 << " Pavarde" << i+1 << " ";
        for(int j=0;j<n+1;j++)
            oss << pazym_gen() << " ";
        oss << "\n";
    }
    wr << oss.str();
    oss.clear();
    cout << failovardas << endl;
    wr.close();
    auto end = chrono::high_resolution_clock::now();
    cout << "Failo generavimo laikas: " << chrono::duration_cast<chrono::seconds>(end - start).count() << " s" << endl;
    return failovardas;


}


Studentas skaiciuojam(int a, int b)
{
    Studentas laik;
    int sum=0, m, j=0;
    if(a==1){
        cout << "Iveskite varda: "; cin >> laik.vard;
        cout << "Iveskite pavarde: "; cin >> laik.pav;
        int kiek = pazym_gen();
        cout << "Sugeneruotas pazymiu skaicius: " << kiek << endl;
        for(int i=0; i<kiek; i++)
            {
                int pazymiai = pazym_gen();
                laik.paz.push_back(pazymiai);
                sum+=pazymiai;
            }

        laik.egzas = pazym_gen();
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
    if(b==1)
        vidurkis(laik, sum);
    if(b==2)
        skmediana(laik);
    if(b==3)
    {
        vidurkis(laik, sum);
        skmediana(laik);
    }
    return laik;
}


void vidurkis(Studentas& laik, int sum)
{
    laik.rez = laik.egzas*0.6 + ((float)sum/laik.paz.size())*0.4;
}

void skmediana(Studentas& laik)
{
    int paz_sk = laik.paz.size();
    float mediana;

    if (paz_sk % 2 == 0) {
        nth_element(laik.paz.begin(), laik.paz.begin() + paz_sk / 2 - 1, laik.paz.end());
        int left = laik.paz[paz_sk / 2 - 1];
        nth_element(laik.paz.begin(), laik.paz.begin() + paz_sk / 2, laik.paz.end());
        int right = laik.paz[paz_sk / 2];
        mediana = (left + right) / 2.0;
    } else {
        nth_element(laik.paz.begin(), laik.paz.begin() + paz_sk / 2, laik.paz.end());
        mediana = laik.paz[paz_sk / 2];
    }
    laik.med = laik.egzas * 0.6 + mediana * 0.4;
}

