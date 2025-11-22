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
#include <filesystem>
#include <list>

using namespace std;
namespace fs = filesystem;

template <template<typename> class Container>
struct Studentas
{
    string vard;
    string pav;
    Container<int> paz;
    int egzas;
    float rez;
    float med;
};

template<template<typename> class Container>
Studentas<Container> skaiciuojam(int a, int b);

template<template<typename> class Container>
Container<Studentas<Container>> failas(int b, string failvardas);

template<template<typename> class Container>
void vidurkis(Studentas<Container>& laik, int sum);

template<template<typename> class Container>
void skmediana(Studentas<Container>& laik);

int pazym_gen();
int generuojame();

template<template<typename> class Container>
void isvedimas(int b, const Container<Studentas<Container>>& Grupe, string failovardas);

stringstream skaitymas(string failvar);

template <template<typename> class Container>
void rusiavimas(int b, Container<Studentas<Container>>& Grupe, string failovardas, int g, int h);

template<template<typename> class Container>
void dirbam(int b, string nfailas, int g, int h, int f);

template <template<typename> class Container>
void trecia_strat_rusiavimas(int b, Container<Studentas<Container>>& Grupe, string failovardas, int g, int h);

template <template<typename> class Container>
void antra_strat_rusiavimas(int b, Container<Studentas<Container>>& Grupe, string failovardas, int g, int h);

template <template<typename> class Container>
void pirma_strat_rusiavimas(int b, Container<Studentas<Container>>& Grupe, string failovardas, int g, int h);


template<template<typename> class Container>
Studentas<Container> skaiciuojam(int a, int b)
{
    Studentas<Container> laik;
    int sum=0, m, j=0;

    cout << "Iveskite varda:" << endl; cin >> laik.vard;
    cout << "Iveskite pavarde:" << endl; cin >> laik.pav;
    if(a==1)
    {
        int kiek;
        cout << "Iveskite pazymiu skaiciu (max 20):" << endl;
        while(true){if(cin >> kiek && kiek>=1 && kiek<=20) break; cout << "Neteisinga ivestis, maksimalus pazym. sk. 20, minimalus 1:" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');}
        for(int i=0; i<kiek; i++)
            {
                int pazymiai = pazym_gen();
                laik.paz.push_back(pazymiai);
                sum+=pazymiai;
            }

        laik.egzas = pazym_gen();
        cout << "Issaugota" << endl;
    }
    else
    {
        cout << "Iveskite studento pazymius (iveskite 0, jei baigiate vesti pazymius): " << endl;
        while(true)
            {
                while(true){if(cin >> m && m>=0 && m<=10) break; cout << "Neteisinga ivestis, maksimalus galimas paz. - 10, minimalus 1 (0 jei norite uzbaigti):" << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');}
                if(m==0) break;
                laik.paz.push_back(m);
                sum+=m;
                j++;
            }
    cout << "Studento pazymiu skaicius: " << j << endl;
    cout << "Iveskite studento egzamino rezultata: " << endl; cin >> laik.egzas;
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

template<template<typename> class Container>
void vidurkis(Studentas<Container>& laik, int sum)
{
    laik.rez = laik.egzas*0.6 + ((float)sum/laik.paz.size())*0.4;
}

template<template<typename> class Container>
void skmediana(Studentas<Container>& laik)
{
    int paz_sk = laik.paz.size();
    float mediana;
    if constexpr (is_same_v<Container<int>,list<int>>)
    {
        laik.paz.sort();
        if (paz_sk == 0)
            mediana = 0.0;
        else
        {
            auto it = laik.paz.begin();
            std::advance(it, paz_sk / 2);
            if (paz_sk % 2 == 0)
            {
                auto it2 = laik.paz.begin();
                std::advance(it2, paz_sk / 2 - 1);
                mediana = (*it + *it2) / 2.0;
            }
            else
                mediana = *it;
        }
    }
    else
    {
        if (paz_sk % 2 == 0)
        {
            nth_element(laik.paz.begin(), laik.paz.begin() + paz_sk / 2 - 1, laik.paz.end());
            int left = laik.paz[paz_sk / 2 - 1];
            nth_element(laik.paz.begin(), laik.paz.begin() + paz_sk / 2, laik.paz.end());
            int right = laik.paz[paz_sk / 2];
            mediana = (left + right) / 2.0;
        }
        else
        {
            nth_element(laik.paz.begin(), laik.paz.begin() + paz_sk / 2, laik.paz.end());
            mediana = laik.paz[paz_sk / 2];
        }
        laik.med = laik.egzas * 0.6 + mediana * 0.4;
    }
}

template<template<typename> class Container>
Container<Studentas<Container>> failas(int b, string failvardas)
{
    string failvar;
    Container<Studentas<Container>> Grupe;
    failvar = failvardas;
    stringstream buffer = skaitymas("./src/"+failvar);
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
    chrono::duration<double> elapsed = endas - startas;
    cout << "Rezultatu skaiciavimo laikas: " << fixed << setprecision(3) << elapsed.count() << " s" << endl;

    return Grupe;
}

template <template<typename> class Container>
void rusiavimas(int b, Container<Studentas<Container>>& Grupe, string failovardas, int g, int h)
{
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
    chrono::duration<double> elaps = end - start;
    cout << "Rikiavimo laikas naudojant konteineri list: " << setprecision(3) << elaps.count() << " s\n";
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
        chrono::duration<double> elaps = end - start;
    cout << "Rikiavimo laikas naudojant konteineri vector: " << fixed << setprecision(3) << elaps.count() << " s\n";
    }
    Container<Studentas<Container>> blogai;
    if constexpr (std::is_same_v<std::remove_cv_t<std::remove_reference_t<decltype(Grupe)>>,std::list<Studentas<Container>>>)
    {
        auto startas = chrono::high_resolution_clock::now();

        for(auto it=Grupe.begin(); it!=Grupe.end();)
        {
            if(it->rez >= 5)
                blogai.splice(blogai.end(), Grupe, it++);
            else ++it;
        }

        auto endas = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = endas - startas;
        cout << "Rusiavimo laikas naudojant list: " << fixed << setprecision(3) << elapsed.count() << " s" << endl;
    }
    else
    {
        auto startas = chrono::high_resolution_clock::now();


        auto it = partition(Grupe.begin(), Grupe.end(), [](const auto& s) {return s.rez < 5;});
        blogai.insert(blogai.end(), std::make_move_iterator(it), std::make_move_iterator(Grupe.end()));
        Grupe.erase(it, Grupe.end());


        auto endas = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = endas - startas;
        cout << "Rusiavimo laikas naudojant vector: " << fixed << setprecision(3) << elapsed.count() << " s" << endl;
    }

    isvedimas(b, Grupe, "gerai_"+failovardas);
    isvedimas(b, blogai, "blogai_"+failovardas);
}

template<template<typename> class Container>
void isvedimas(int b, const Container<Studentas<Container>>& Grupe, string failovardas)
{
    if(failovardas.find("txt") != std::string::npos)
        failovardas = "rez_"+failovardas;
    else
        failovardas = "rez_"+failovardas +".txt";
    ofstream wr(failovardas);
    ostringstream oss;
    auto startas = chrono::high_resolution_clock::now();
    oss << setw(21) << right << "Vardas | " << setw(21) << right << "Pavarde | " << setw(21) << right;
    if(b==1) {oss << "Galutinis (Vid.)"  << " | Adresas atmintyje" << " \n----------------------------------------------------------------" << endl;}
            else if(b==2) {oss << "Galutinis (Med.) "  << " | Adresas atmintyje" << "\n-------------------------------------------------------" << endl;}
            else if(b==3) {oss << "Galutinis (Vid.) | " << setw(21) << right << "Galutinis (Med.)"  << setw(21) << right<<  " | Adresas atmintyje" << "\n---------------------------------------------------------------------------------------------------------" << endl;}
    for(auto it = Grupe.begin(); it != Grupe.end(); ++it)
    {
        const auto& temp = *it;
        oss << setw(18) << right << temp.vard << " | " << setw(18) << temp.pav << " | " << setw(18) << fixed << right << setprecision(2);
        if(b==1) oss << temp.rez << " | " << setw(17) << &(*it) << endl;
        else if(b==2) oss << temp.med << " | " << setw(17) << &(*it) << endl;
        else if (b==3) oss << temp.rez << " | " << setw(22) <<  right << temp.med << " | " << setw(17) << fixed << right << &(*it) << endl;
    }
    wr << oss.str();
    wr.close();
    auto endas = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endas - startas;
    cout << "Failo " << failovardas << " rasymo laikas: " << fixed << setprecision(3) << elapsed.count() << " s" << endl;
}

template<template<typename> class Container>
void dirbam(int b, string nfailas, int g, int h, int f)
{
    Container<Studentas<Container>> Grupe = failas<Container>(b, nfailas);
    if(f==1)
        pirma_strat_rusiavimas(b, Grupe, nfailas, g, h);
    else if(f==2)
        antra_strat_rusiavimas(b, Grupe, nfailas, g, h);
    else if(f==3)
        trecia_strat_rusiavimas(b, Grupe, nfailas, g, h);
    else if(f==4)
        rusiavimas(b, Grupe, nfailas, g, h);
}

template <template<typename> class Container>
void pirma_strat_rusiavimas(int b, Container<Studentas<Container>>& Grupe, string failovardas, int g, int h)
{
    if constexpr (std::is_same_v<std::remove_cv_t<std::remove_reference_t<decltype(Grupe)>>,std::list<Studentas<Container>>>) 
    {
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
    chrono::duration<double> elaps = end - start;
    cout << "Rikiavimo laikas naudojant konteineri list: " << setprecision(3) << elaps.count() << " s\n";
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
        chrono::duration<double> elaps = end - start;
        cout << "Rikiavimo laikas naudojant konteineri vector: " << fixed << setprecision(3) << elaps.count() << " s\n";
    }

    Container<Studentas<Container>> gerai, blogai;
    auto startas = chrono::high_resolution_clock::now();
    for(const auto& temp : Grupe)
    {
        if(temp.rez>=5)
            gerai.push_back(temp);
        else
            blogai.push_back(temp);
    }
    auto endas = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endas - startas;
    cout << "Rusiavimo laikas: " << fixed << setprecision(3) << elapsed.count() << " s" << endl;

    isvedimas(b, gerai, "gerai_"+failovardas);
    isvedimas(b, blogai, "blogai_"+failovardas);
}

template <template<typename> class Container>
void antra_strat_rusiavimas(int b, Container<Studentas<Container>>& Grupe, string failovardas, int g, int h)
{
    if constexpr (std::is_same_v<std::remove_cv_t<std::remove_reference_t<decltype(Grupe)>>,std::list<Studentas<Container>>>) 
    {
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
    chrono::duration<double> elaps = end - start;
    cout << "Rikiavimo laikas naudojant konteineri list: " << setprecision(3) << elaps.count() << " s\n";
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
        chrono::duration<double> elaps = end - start;
        cout << "Rikiavimo laikas naudojant konteineri vector: " << fixed << setprecision(3) << elaps.count() << " s\n";
    }

    Container<Studentas<Container>> blogai, temp = Grupe;
    auto startas = chrono::high_resolution_clock::now(); 
    for(auto it = Grupe.begin(); it != Grupe.end();)
    {
        if(it->rez < 5)
        {
            blogai.push_back(*it);
            it = Grupe.erase(it);
        }
        else ++it;
    }
    auto endas = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endas - startas;
    cout << "Rusiavimo laikas: " << fixed << setprecision(3) << elapsed.count() << " s" << endl;

    isvedimas(b, Grupe, "gerai_"+failovardas);
    isvedimas(b, blogai, "blogai_"+failovardas);
}

template <template<typename> class Container>
void trecia_strat_rusiavimas(int b, Container<Studentas<Container>>& Grupe, string failovardas, int g, int h)
{
    if constexpr (std::is_same_v<std::remove_cv_t<std::remove_reference_t<decltype(Grupe)>>,std::list<Studentas<Container>>>) 
    {
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
    chrono::duration<double> elaps = end - start;
    cout << "Rikiavimo laikas naudojant konteineri list: " << setprecision(3) << elaps.count() << " s\n";
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
        chrono::duration<double> elaps = end - start;
        cout << "Rikiavimo laikas naudojant konteineri vector: " << fixed << setprecision(3) << elaps.count() << " s\n";
    }

    Container<Studentas<Container>> blogai;
    auto startas = chrono::high_resolution_clock::now();
    auto centras = partition(Grupe.begin(), Grupe.end(), [](const Studentas<Container>& temp) { return temp.rez < 5; });
    blogai.insert(blogai.end(), make_move_iterator(centras), make_move_iterator(Grupe.end()));
    Grupe.erase(centras, Grupe.end());
    auto endas = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endas - startas;
    cout << "Rusiavimo laikas: " << fixed << setprecision(3) << elapsed.count() << " s" << endl;

    isvedimas(b, Grupe, "gerai_"+failovardas);
    isvedimas(b, blogai, "blogai_"+failovardas);
}
