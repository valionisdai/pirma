#include "mylib.h"

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


int pazym_gen()
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<int> distrib(1, 10);
    return distrib(gen);
}

string generuojame()
{
    int a, n;
    cout << "Pasirinkite kiek studentu norite sugeneruoti:" << endl;
    cout << "(1) 1000 stud., (2) 10000 stud., (3) 100000 stud., (4) 1000000 stud., (5) 10000000 stud." << endl;
    while(true)
    {
        if(cin >> a && a>=1 && a<=5) break;
            cout << "Neteisinga ivestis, pasirinkite viena is skaiciu" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if(a==1) a=1000;
    if(a==2) a=10000;
    if(a==3) a=100000;
    if(a==4) a=1000000;
    if(a==5) a=10000000;
    string failovardas = "_stud_"+to_string(a)+".txt";
    ofstream wr(failovardas);
    cout << "Iveskite skaiciu pazymiu, kuriuos norite sugeneruoti (ne daugiau 20, be egz.): " << endl;
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
    oss.str("");
    cout << failovardas << endl;
    wr.close();
    auto end = chrono::high_resolution_clock::now();
    cout << "Failo generavimo laikas: " << chrono::duration_cast<chrono::seconds>(end - start).count() << " s" << endl;
    return failovardas;


}
