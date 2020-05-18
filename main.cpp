#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <typeinfo>
#include <map>
using namespace std;

///---------------------------------------------------------------------------------ABSTRACT CLASS PHARMACY-------------------------------------------------------------------------------------

class Pharmacy{

protected:

    static string owner;         /// toate farmaciile apartin aceluiasi proprietar "X"

    string name;                    /// numele fiecarei farmacii in parte

    int employeeCount;              /// numarul de angajati al fiecarei farmacii

    float profitHistory[1200];          /// istoricul profiturilor in fiecare luna a fiecarei farmacii in parte; profitHistory[n] -> profitul in a n-a luna dupa deschidere; capacitate de retinere: 100 ani * 12 luni/an

    int currentMonth;               /// luna curenta, in raport cu momentul deschiderii farmaciei

public:

    Pharmacy();

    virtual ~Pharmacy() = 0;

    void changeName(string newName);

    void addProfit(float pr);

    void addEmployee();

    void removeEmployee();

    int employeeNumber();

    float getProfit(int month);

    int getCurrentMonth();

    string getName();

    static void setOwner(string newOwner);

    static string getOwner();

    virtual void print(ostream & o) const;

    virtual void read(istream & i);

    friend ostream & operator <<(ostream & o, const Pharmacy & to_read);

    friend istream & operator >>(istream & i, Pharmacy & to_read);
};

string Pharmacy::owner = "(neinitializat)";

Pharmacy::Pharmacy(){

    name = "(neinitializat)";

    employeeCount = 0;
    currentMonth = 0;
    ///cout<<"Base constructor called"<<'\n'<<'\n';
}

Pharmacy::~Pharmacy(){

    ///cout<<"Base destructor called"<<'\n'<<'\n';
}

void Pharmacy::changeName(string newName){

    name = newName;
}

void Pharmacy::addProfit(float pr){

    currentMonth++;

    profitHistory[currentMonth] = pr;
}

void Pharmacy::addEmployee(){

    employeeCount++;
}

void Pharmacy::removeEmployee(){

    if(employeeCount == 0)
        throw "EXCEPTION: employee number is already minimum (0)";

    employeeCount--;
}

int Pharmacy::employeeNumber(){

    return employeeCount;
}

float Pharmacy::getProfit(int month){

    if(month < 0)
        throw "EXCEPTION: cannot search profit by negative month";

    return profitHistory[month];
}

int Pharmacy::getCurrentMonth(){

    return currentMonth;
}

string Pharmacy::getName(){

    return name;
}

void Pharmacy::setOwner(string newOwner){

    owner = newOwner;
}

string Pharmacy::getOwner(){

    return owner;
}

void Pharmacy::print(ostream & o) const{

    if(name == "(neinitializat)"){

        o<<"(Farmacie neinitializata)";
        return;
    }

    o<<"Se afiseaza farmacia cu numele "<<name<<" . Are "<<employeeCount<<" angajati,";

    if(currentMonth != 0)
        o<<" iar profitul din ultima luna este "<<profitHistory[currentMonth];
    else
        o<<" dar nu are nici un profit inregistrat. ";
}

void Pharmacy::read(istream & i){

    cout<<'\n'<<"Se citesc date pentru o farmacie,..."<<'\n';
    cout<<"Introduceti numele pentru farmacie: ";
    getline(i, name);
    cout<<'\n';
    cout<<"Introduceti numarul de angajati: ";
    i>>employeeCount;
    cout<<'\n';
}

ostream & operator <<(ostream & o, const Pharmacy & to_print){

    to_print.print(o);

    return o;
}

istream & operator >>(istream & i, Pharmacy & to_read){

    to_read.read(i);

    return i;
}

///----------------------------------------------------------------------------------CLASS REALPHARMACY--------------------------------------------------------------------------------------------

class RealPharmacy: public Pharmacy{

protected:

    string location;                /// adresa fizica a unei farmacii

    float rentPrice;                  /// pretul spatiului inchiriat; daca spatiul este cumparat, rentValue = 0;

public:

    RealPharmacy();

    ~RealPharmacy();

    void changeLocation(string newLocation);

    void changeRent(float val);

    float rentValue();

    string getLocation();

    void read(istream & i);

    void print(ostream & o) const;
};

RealPharmacy::RealPharmacy(): Pharmacy(){

    location = "(neinitializat)";

    rentPrice = 0;
    ///cout<<"Derived RealPharmacy constructor called"<<'\n'<<'\n';
}

RealPharmacy::~RealPharmacy(){


    ///cout<<"Derived RealPharmacy destructor called"<<'\n'<<'\n';
}

void RealPharmacy::changeLocation(string newLocation){

    location = newLocation;
}

void RealPharmacy::changeRent(float val){

    if(val < 0)
        throw "EXCEPTION: rent value cannot be negative";

    rentPrice = val;
}

float RealPharmacy::rentValue(){

    return rentPrice;
}

string RealPharmacy::getLocation(){

    return location;
}

void RealPharmacy::read(istream & i){

    Pharmacy::read(i);

    cout<<"Introduceti adresa farmaciei: ";

    char * enter = new char;
    gets(enter); ///buffer pentru a citi ENTER de mai sus

    getline(i, location);
    cout<<'\n';

    delete enter;
}

void RealPharmacy::print(ostream & o) const{

    Pharmacy::print(o);

    if(name == "(neinitializat)")
        return;

    o<<"Adresa farmaciei este: "<<location;
}

///----------------------------------------------------------------------CLASS ONLINEPHARMACY---------------------------------------------------------------------------------------------------

class OnlinePharmacy: public Pharmacy{

protected:

    string website;                 /// adresa site ului

    float hostPrice;                /// pretul hostului online

    int guestCount;                 /// numarul total de vizitatori

public:

    OnlinePharmacy();

    ~OnlinePharmacy();

    void changeHostPrice(float val);

    void changeWebsite(string newAddress);

    void addGuest();

    int guestNumber();

    float getHostPrice();

    string websiteName();

    void read(istream & i);

    void print(ostream & o) const;
};

OnlinePharmacy::OnlinePharmacy(): Pharmacy(){

    website = "(neinitializat)";

    hostPrice = 0;
    guestCount = 0;
}

OnlinePharmacy::~OnlinePharmacy(){

    ///cout<<"Derived OnlinePharmacy destructor called"<<'\n'<<'\n';
}

void OnlinePharmacy::changeHostPrice(float val){

    if(val < 0)
        throw "EXCEPTION: host price cannot be negative";

    hostPrice = val;
}

void OnlinePharmacy::changeWebsite(string newAddress){

    website = newAddress;
}

void OnlinePharmacy::addGuest(){

    guestCount++;
}

int OnlinePharmacy::guestNumber(){

    return guestCount;
}

float OnlinePharmacy::getHostPrice(){

    return hostPrice;
}

string OnlinePharmacy::websiteName(){

    return website;
}

void OnlinePharmacy::read(istream & i){

    Pharmacy::read(i);

    cout<<"Introduceti site-ul farmaciei: ";

    char * enter = new char;
    gets(enter); ///buffer pentru a citi ENTER de mai sus

    getline(i, website);
    cout<<'\n';

    delete enter;
}

void OnlinePharmacy::print(ostream & o) const{

    Pharmacy::print(o);

    o<<"Site-ul farmaciei este: "<<website;
}

///----------------------------------------------------------------------------TEMPLATE CLASS MANAGEPHARMA----------------------------------------------------------------------------------

/*  Observatii legate de implementare:

    - un obiect de tipul ManagePharm (GestionareFarmacii) gestioneaza un singur lant de farmacii
    - am creat o clasa de baza abstracta IdClass pentru a ma folosi de o variabila statica comuna tuturor instantelor din ManagePharm,in vederea initializarii id ului (constant) fiecarui lant de farmacii
*/

class IdClass{

protected:

    static int global_id;

    IdClass(){

        global_id++;
    }

    virtual ~IdClass() = 0;
};

IdClass::~IdClass(){};

int IdClass::global_id = 0;

template <class T>
class ManagePharm: public IdClass{

    const int chain_id;

    vector <Pharmacy*> chain;

    T * main_pharm;         ///nu face parte din vectorul chain !!!!

public:

    ManagePharm();

    ManagePharm & operator +=(Pharmacy * to_add){       ///adauga intentionat in lant acel obiect, si nu o copie a lui; nu ar avea sens sa am doua farmacii cu aceleasi valori identice

        chain.push_back(to_add);

        return *this;
    }

    Pharmacy * operator [](int i);

    T * get_main_pharm();

    int get_id();

    void set_main_pharm(Pharmacy * to_set);

    int getIndex(string srch_name);

    void remove_by_index(int i);

    void remove_by_name(string to_remove);

    template <class AUX>
    friend ostream & operator <<(ostream & o, const ManagePharm <AUX> & to_print);

};

template <class T>
ManagePharm <T>:: ManagePharm(): IdClass(), chain_id(global_id){

    main_pharm = new T;

    ///cout<<"ManagePharm constructor called"<<'\n';
    ///cout<<chain_id<<" ";
}

template <class T>
Pharmacy * ManagePharm <T>:: operator [](int i){

    if(i < 0)
        throw "EXCEPTION: cannot access chain by negative index";

    return chain[i];
}

template <class T>
T * ManagePharm <T>:: get_main_pharm(){

    return main_pharm;
}

template <class T>
int ManagePharm <T>:: get_id(){

    return chain_id;
}

template <class T>
void ManagePharm <T>:: set_main_pharm(Pharmacy * to_set){

    Pharmacy * backup = main_pharm;

    main_pharm = dynamic_cast<T*>(to_set);

    if(main_pharm == NULL)
        throw backup;
}

template <class T>
int ManagePharm <T>:: getIndex(string srch_name){

    for(int i = 0; i < chain.size(); i++){

        if(chain[i] -> getName() == srch_name)
            return i;
    }
    return -1;
}

template <class T>
void ManagePharm <T>:: remove_by_index(int i){

    if(i < 0)
        throw "EXCEPTION: cannot remove from chain by negative index";

    chain.erase(chain.begin() + i);
}

template <class T>
void ManagePharm <T>:: remove_by_name(string to_remove){

    for(int i = 0; i < chain.size(); i++){

        if(chain[i] -> getName() == to_remove)
            chain.erase(chain.begin() + i);
    }
}

template <class T>
ostream & operator <<(ostream & o, const ManagePharm <T> & to_print){

    o<<'\n'<<"------------------------------------------------------------------"<<'\n';

    o<<"Se afiseaza toate farmaciile din lantul cu id = "<<to_print.chain_id<<" :"<<'\n'<<'\n';

    o<<"Farmacia principala a lantului este: ----> "<<*(to_print.main_pharm)<<'\n'<<'\n';

    if(!to_print.chain.empty())
        for(int i = 0; i < to_print.chain.size(); i++)
            o << *(to_print.chain[i]) << '\n';
    else
        o<<"(Nici o farmacie existenta in acest lant pe langa cea principala)"<<'\n';

    o<<'\n'<<"------------------------------------------------------------------"<<'\n';

    return o;
}

int main(){

    /*string newOwner ("The famous owner X");
    ///getline(cin, newOwner);
    Pharmacy::setOwner(newOwner);
    ///cout<<Pharmacy::getOwner();

    RealPharmacy rpharm;

    cin>>rpharm;

    cout<<rpharm;

    OnlinePharmacy opharm;

    cin>>opharm;
    cout<<opharm;*/

    ManagePharm <RealPharmacy> x;

    Pharmacy *pc1 = new RealPharmacy;

    pc1 -> changeName("PRIMA FARMACIE DIN LANT");

    x += pc1;

    cout<<x<<'\n';

    pc1 -> addEmployee();

    cout<<x<<'\n';

    Pharmacy *main = new RealPharmacy;
    Pharmacy *test = new OnlinePharmacy;

    main -> changeName("RM PHARMA");
    test -> changeName("THIS SHOULD NEVER BE PRINTED");

    try{

        x.set_main_pharm(main);     ///ok
        x.set_main_pharm(test);     ///throws excepiton
    }
    catch(Pharmacy * backup){

        x.set_main_pharm(backup);

        cout<<"EXCEPTION: downcast of base pointer to_set failed; main_pharma of chain with id "<<x.get_id()<<" was set back to pharmacy with name "<<x.get_main_pharm() -> getName()<<'\n';
    }

    cout<<x<<'\n';

    Pharmacy * p = x[0];

    p -> changeName("eeeee");

    cout<<x<<'\n';

    RealPharmacy * rp = dynamic_cast<RealPharmacy *>(p);

    if(rp != NULL){

        rp -> changeLocation("LOCATIA PRIMEI FARMACII DIN LANT");
    }

    cout<<x<<'\n';

    x.remove_by_index(0);

    cout<<x<<'\n';

    Pharmacy * pc2 = new OnlinePharmacy;

    pc2 -> changeName("A DOUA FARMACIE DIN LANT, ESTE ONLINE");

    x += pc2;

    cout<<x<<" ";

    return 0;
}
