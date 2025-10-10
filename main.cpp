#include "mylib.h"



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
        string failvardas = generuojame();
        for(int i=1;i<=5;i++)
        {
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



