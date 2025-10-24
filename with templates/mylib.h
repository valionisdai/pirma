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
#include <vector>

using namespace std;
template <template<typename> class Container>
struct Studentas{
string vard;
string pav;
Container<int> paz;
int egzas;
float rez;
float med;
};

template <template<typename> class Container>
Studentas<Container> skaiciuojam(int a, int b);
template <template<typename> class Container>
Container<Studentas<Container>> failas(int b, string failvardas);
template <template<typename> class Container>
void vidurkis(Studentas<Container>& laik, int sum);
template <template<typename> class Container>
void skmediana(Studentas<Container>& laik);
int pazym_gen();
string generuojame();
template <template<typename> class Container>
void isvedimas(int b, const Container<Studentas<Container>>& Grupe, string failovardas);
stringstream skaitymas(string failvar);
template <template<typename> class Container>
void rusiavimas(int b, Container<Studentas<Container>>& Grupe, string failovardas);



template <template<typename> class Container>
void rusiavimas(int b, Container<Studentas<Container>>& Grupe, string failovardas)
{
    int g, h;
    cout << "Norite rusiuoti pagal:\n(1) Varda, (2) Pavarde, (3) Gal. Vid., (4) Gal. Med.\n" << endl;
    while(true)
    {
        if(cin >> g && g>=1 && g<=4) break;
        cout << "Neteisinga ivestis, pasirinkite skaiciu nuo 1 iki 4:" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Pasirinkite krypti:\n(1) Didejancia tvarka\n(2) Mazejancia tvarka" << endl;
    while(true)
    {
        if(cin >> h && 0<h && h<3) break;
        cout << "Neteisinga ivestis, pasirinkite skaiciu nuo 1 iki 2:" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if constexpr (std::is_same_v<
    std::remove_cv_t<std::remove_reference_t<decltype(Grupe)>>,std::list<Studentas<Container>>>
) {
    auto start = chrono::high_resolution_clock::now();
    Grupe.sort([=](const Studentas<Container>& a, const Studentas<Container>& b)
    {switch (g)
         {
          case 1: return h==1 ? a.vard < b.vard : a.vard > b.vard;
          case 2: return h==1 ? a.pav < b.pav : a.pav > b.pav;
          case 3: return h==1 ? a.rez < b.rez : a.rez > b.rez;
          case 4: return h==1 ? a.med < b.med : a.med > b.med;
          default: return false;
         }});
    auto end = chrono::high_resolution_clock::now();
    cout << "Rikiavimo laikas naudojant konteineri list: " << chrono::duration_cast<chrono::seconds>(end - start).count() << " s\n";
    }
    else
    {
        auto start = chrono::high_resolution_clock::now();
    sort(std::execution::par, Grupe.begin(), Grupe.end(), [=](const Studentas<Container>& a, const Studentas<Container>& b)
        { switch (g)
         {
          case 1: return h==1 ? a.vard < b.vard : a.vard > b.vard;
          case 2: return h==1 ? a.pav < b.pav : a.pav > b.pav;
          case 3: return h==1 ? a.rez < b.rez : a.rez > b.rez;
          case 4: return h==1 ? a.med < b.med : a.med > b.med;
          default: return false;
         }
        });
        auto end = chrono::high_resolution_clock::now();
        cout << "Rikiavimo laikas naudojant konteineri vector: " << chrono::duration_cast<chrono::seconds>(end - start).count() << " s\n";
    }

    auto startas = chrono::high_resolution_clock::now();
    Container<Studentas<Container>> gerai, blogai;
    for(const auto& temp : Grupe)
    {
        if(temp.rez>=5)
            gerai.push_back(temp);
        else
            blogai.push_back(temp);
    }

    std::string label = (std::is_same_v<
    std::remove_cv_t<std::remove_reference_t<decltype(gerai)>>,
    std::list<Studentas<Container>>
>) ? "list" : "vector";

    auto endas = chrono::high_resolution_clock::now();
    cout << "Rusiavimo laikas: " << chrono::duration_cast<chrono::seconds>(endas - startas).count() << " s" << endl;
    isvedimas(b, gerai, label + "_gerai_"+failovardas);
    isvedimas(b, blogai, label +"_blogai_"+failovardas);
}

template <template<typename> class Container>
void isvedimas(int b, const Container<Studentas<Container>>& Grupe, string failovardas)
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

template <template<typename> class Container>
Container<Studentas<Container>> failas(int b, string failvardas)
{
    string failvar;
    Container<Studentas<Container>> Grupe;
    if("1"==failvardas)
    {
        int l;
        cout << "Is kurio failo norite skaityti duomenis?\n(1) kursiokai.txt\n(2) studentai10000.txt\n(3) studentai100000.txt\n(4) studentai1000000.txt" << endl;
    while(true)
    {
        if(cin >> l && l>=1 && l<=4) break;
        cout << "Neteisinga ivestis, pasirinkite skaiciu nuo 1 iki 4:" << endl;
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
        Studentas<Container> laik;
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

template <template<typename> class Container>
Studentas<Container> skaiciuojam(int a, int b)
{
    Studentas<Container> laik;
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

template <template<typename> class Container>
void vidurkis(Studentas<Container>& laik, int sum)
{
    laik.rez = laik.egzas*0.6 + ((float)sum/laik.paz.size())*0.4;
}

template <template<typename> class Container>
void skmediana(Studentas<Container>& laik)
{
    float mediana;
    if constexpr (std::is_same_v<
    std::remove_cv_t<std::remove_reference_t<decltype(laik)>>,std::list<Studentas<list>>>
) {
    laik.paz.sort();
    int paz_sk = laik.paz.size();

    if (paz_sk == 0) {
        mediana = 0.0;
    } else {
        auto it = laik.paz.begin();
        std::advance(it, paz_sk / 2);

        if (paz_sk % 2 == 0) {
            auto it2 = laik.paz.begin();
            std::advance(it2, paz_sk / 2 - 1);
            mediana = (*it + *it2) / 2.0;
        } else {
            mediana = *it;
        }
    }
    }
    else if constexpr (std::is_same_v<
    std::remove_cv_t<std::remove_reference_t<decltype(laik)>>,std::vector<Studentas<vector>>>)
    {
    int paz_sk = laik.paz.size();

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
    }
    laik.med = laik.egzas * 0.6 + mediana * 0.4;
}
