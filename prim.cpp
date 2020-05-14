// Autor: Magnus Karlson
// Kuupäev: 05/13/2020

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <set>
#include <Windows.h>

using namespace std;

// tipp andmed: tähis number
struct Tipp{
    int number;

    Tipp(int number){
        this->number = number;
    }
    ~Tipp(){}
};

// serva andmed: algustipp -> lõpptipp ja serva kaal
struct Serv{
    Tipp* tipp1;
    Tipp* tipp2;
    int kaal;

    Serv(Tipp* tipp1, Tipp* tipp2, int kaal){
        this->tipp1 = tipp1;
        this->tipp2 = tipp2;
        this->kaal = kaal;
    }
    ~Serv(){}

    string toString(){
        return to_string(tipp1->number) + " -> "+ to_string(tipp2->number) + " : " + to_string(kaal);
    }
};

struct Graaf{
    set<Tipp*> tipud;
    set<Serv*> servad;

    // leiab sobiva kirjeldusega tipu
    Tipp* leiaTipp(int number){
        for(Tipp* x : tipud){
            if(x->number == number)return x;
        }
        return nullptr;
    }

    // otsib, kas viit tipule eksisteerib või tekitab uue viida
    Tipp* lisaTipp(int number){
        Tipp* tipp = leiaTipp(number);
        if(tipp != nullptr)return tipp;
        tipp = new Tipp(number);
        tipud.insert(tipp);
        return tipp;
    }

    // tippude vahele serva tekitamine, suunaks on algustipp -> lõpptipp
    void lisaServ(int n1, int n2, int kaal){
        servad.insert(new Serv(lisaTipp(n1), lisaTipp(n2), kaal));
    }

    // leiab etteantud tipust valjuvad servad
    set<Serv*> valjuvadServad(Tipp* tipp){
        set<Serv*> tulem;
        for(Serv* x : servad){
            if(x->tipp1 == tipp)
                tulem.insert(x);
        }
        return tulem;
    }
    
    // loeb servad sisse etteantud failist
    bool loeServad(string failinimi){
        ifstream f (failinimi);
        if (f.is_open()){
            int a, b, c;
            while(f >> a >> b >> c){
                lisaServ(a, b, c);
            }
            f.close();
            return true;
        }
        return false;
    }
};

// leiab listist väikseima kaaluga serva
Serv* vaikseimaKaalugaServ(set<Serv*> servad){
    Serv* tulem = nullptr;
    for(Serv* x : servad){
        if(tulem == nullptr || x->kaal < tulem->kaal)
            tulem = x;
    }
    return tulem;
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    cout << "Autor: Magnus Karlson" << endl;

    // Graafi genereerimine failis olevate andmete põhjal
    Graaf* graaf = new Graaf();
    graaf->loeServad("servad.txt");

    // Juurtipu leidmine
    Tipp* juurtipp = graaf->leiaTipp(1);

    if(!graaf->servad.size()){
        cout << "servad.txt faili ei leitud või ühtegi serva pole selles failis!" << endl;
    }else if(juurtipp == nullptr){
        cout << "Graafil puudub juurtipp 1!" << endl;
    }else{
        cout << "Graafi andmed sisseloetud, servasid: " << graaf->servad.size() << endl;

        // Primi algoritm
        int kogukaal = 0;
        set<Tipp*> tipud;
        set<Serv*> servad;
        Serv* serv;
        set<Serv*> servadeJK = graaf->valjuvadServad(graaf->leiaTipp(1));

        // Protsess kestab seni, kuni servade eelistusjärjekord on tühi
        while(servadeJK.size() > 0){
            // Leiab hetkel vaadeldavate servade hulgast väikseima kaaluga serva
            serv = vaikseimaKaalugaServ(servadeJK);

            // Eemaldab leitud servade eelistusjärjekorrast
            servadeJK.erase(serv);

            // Kontrollime, kas serva algustipp ja lõpptipp on juba kasutusel -> jätame vahele
            if(tipud.find(serv->tipp1) != tipud.end() && tipud.find(serv->tipp2) != tipud.end())
                continue;
            
            // Lisame serva tipud vaadeldud tippude hulka
            tipud.insert(serv->tipp1);
            tipud.insert(serv->tipp2);

            // Serva lisame minimaalse toespuu servade hulka
            servad.insert(serv);

            // Lisab serva kaalu kogukaalule juurde
            kogukaal += serv->kaal;

            // Lisab eelistusjärjekorda uued servad, mis väljuvad hetkese serva lõpptipust
            set<Serv*> uuedTipud = graaf->valjuvadServad(serv->tipp2);
            servadeJK.insert(uuedTipud.begin(), uuedTipud.end());
        }

        // Toespuu faili tekitamine
        ofstream f ("toespuu.txt");
        if (f.is_open()){
            for(Serv* x : servad){
                f << x->toString() << "\n";
            }
            f << "Kogukaal: " << to_string(kogukaal) << "\n";
            f.close();
            cout << "Graafi toespuu tekitatud faili toespuu.txt" << endl;
        }
    }

    cout << "Sulgemiseks q." << endl;
    string sisend;
    while(true){
        cin >> sisend;
        break;
    }
    return 0;
}