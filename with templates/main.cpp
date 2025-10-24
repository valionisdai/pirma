#include "mylib.h"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b, c, d;
    string failvardas;
    cout << "Norite:\n(1) Sugeneruoti visus duomenis\n(2) Suvesti jau turimus duomenis" << endl;
    while(true)
    {
        if(cin >> c && c>=1 && c<=2) break;
        cout << "Neteisinga ivestis, pasirinkite skaiciu nuo 1 iki 2:" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
     }
    if(c==1)
    {
        failvardas = generuojame();
    }
    cout << "Norite apskaiciuoti:\n(1) Vidurki\n(2) Mediana\n(3) Abu" << endl;
    while(true)
    {
        if(cin >> b && b>=1 && b<=3) break;
        cout << "Neteisinga ivestis, pasirinkite skaiciu nuo 1 iki 3:" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if(c!=2)
    {
    cout << "Norite naudoti konteinerius:\n(1) Vector\n(2) List\n(3) Abu"<< endl;
    while(true)
    {
        if(cin >> d && d>=1 && d<=3) break;
        cout << "Neteisinga ivestis, pasirinkite skaiciu nuo 1 iki 3:" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }}
    if(c==1 && d==1)
    {
        for(int i=1;i<=5;i++)
        {
            vector<Studentas<vector>>Grupe;
            Grupe = failas<vector>(b, failvardas);
            rusiavimas<vector>(b, Grupe, failvardas);
            Grupe.clear();
        }
    }
    else if(c==1 && d==2)
    {
        for(int i=1;i<=5;i++)
        {
            list<Studentas<list>> Grupe;
            Grupe = failas<list>(b, failvardas);
            rusiavimas<list>(b, Grupe, failvardas);
            Grupe.clear();
        }
    }
    else if(d==3 && c==1)
    {
        vector<Studentas<vector>> GrupeV;
        GrupeV = failas<vector>(b, failvardas);
        rusiavimas<vector>(b, GrupeV, failvardas);
        GrupeV.clear();
        list<Studentas<list>> GrupeL;
        GrupeL = failas<list>(b, failvardas);
        rusiavimas<list>(b, GrupeL, failvardas);
        GrupeL.clear();
    }
    if(c==2)
    {
        vector<Studentas<vector>> Grupe;
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
            Grupe = failas<vector>(b,"1");
        }
        else
        {
            cout << "Iveskite studentu skaiciu: "; cin >> n;
            auto start = chrono::high_resolution_clock::now();
            for(int i=0; i<n; i++)
                Grupe.push_back(skaiciuojam<vector>(a, b));
            auto end = chrono::high_resolution_clock::now();
            cout << "Skaiciavimo laikas: " << chrono::duration_cast<chrono::seconds>(end - start).count() << " s" << endl;
        }
        rusiavimas<vector>(b, Grupe, "1");
    }
}
