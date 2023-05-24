#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <cmath>
#include <random>
#include <set>
#include <windows.h>
#include <typeinfo>
using namespace std;

class IOInterface{
public:
    virtual istream& citire(istream&) = 0;
    virtual ostream& afisare(ostream&) const = 0;
};

class Transport:public IOInterface{
    int seats;
    string fuel, name;
    pair<int, int> curLocation;
    vector<pair<int, int>> route;
public:
    void addToRoute(pair<int, int> point){ this->route.push_back(point); }
    void setRoute(vector<pair<int, int>> route){
        this->route = route;
    }
    pair<int, int> getLocation() const { return this->curLocation; }
    string getName(){ return this->name; }
    int getSeatsNumber(){ return this->seats; }
    Transport(){
        this->name = "";
        this->seats = 0;
        this->fuel = "";
        this->curLocation = {0, 0};
        this->route = {};
    }
    Transport(string name, int seats, string fuel, pair<int, int> curLocation, vector<pair<int, int>> route){
        this->seats = seats;
        this->curLocation = curLocation;
        this->name = name;
        this->fuel = fuel;
        this->route = route;
    }
    Transport(const Transport& t){
        this->seats = t.seats;
        this->curLocation = t.curLocation;
        this->fuel = t.fuel;
        this->name = t.name;
        this->route = t.route;
    }
    Transport& operator =(const Transport&);
    virtual ostream& afisare(ostream& out) const;
    virtual istream& citire(istream& in);
    friend istream& operator>>(istream& in, Transport&);
    friend ostream& operator<<(ostream& out, const Transport&);
};
Transport& Transport::operator=(const Transport& t){
    if(this!=&t){
        this->name = t.name;
        this->seats = t.seats;
        this->curLocation = t.curLocation;
        this->fuel = t.fuel;
        this->route = t.route;
    }
    return *this;
}
istream& Transport::citire(istream& in){
    cout<<"Name: "; in>>this->name;
    cout<<"Seats: "; in>>this->seats;
    cout<<"fuel: "; in>>this->fuel;
    int X, Y, N;
    cout<<"Current location X: "; in>>X;
    cout<<"Current location Y: "; in>>Y;
    this->curLocation = {X, Y};
    cout<<"Number of route points: "; in>>N;
    for(int i=0; i<N; i++){
        cout<<"X and Y: "; cin>>X>>Y;
        this->route.push_back(make_pair(X, Y));
    }
    return in;
}
ostream& Transport::afisare(ostream& out) const {
    cout<<"Name: "<<this->name<<endl;
    cout<<"Seats: "<<this->seats<<endl;
    cout<<"fuel: "<<this->fuel<<endl;
    cout<<"Current location: "<<this->curLocation.first<<" "<<this->curLocation.second<<endl;
    for(int i=0; i<this->route.size(); i++){
        cout<<this->route[i].first<<" "<<this->route[i].second<<endl;
    }
    return out;
}
istream& operator>>(istream& in, Transport& t){
    return t.citire(in);
}
ostream& operator<<(ostream& out, const Transport& t){
    return t.afisare(out);
}

class Car:public Transport{
    const int id;
    static int carNumber;
    string color, model, plate;
public:
    string getModel(){ return this->model; }
    string getPlates(){ return this->plate; }
    string getColor(){ return this->color; }

    Car();
    Car(string, string, string, int, pair<int, int>, string, vector<pair<int, int>>);
    Car(const Car&);
    Car& operator= (const Car& c);
    ~Car();
    virtual istream& citire(istream&);
    virtual ostream& afisare(ostream&) const;
    friend istream& operator>>(istream&, Car&);
    friend ostream& operator<<(ostream&, const Car&);
};
Car::Car():id(carNumber++),Transport(){
    this->model = "";
    this->color = "";
    this->plate = "";
}
Car::Car(string name, string model, string plate, int seats, pair<int, int> curLocation, string fuel, vector<pair<int, int>> route)
        :id(carNumber++),Transport(name, seats, fuel, curLocation, route){
    this->color = color;
    this->model = model;
    this->plate = plate;
}
Car::Car(const Car& c):id(carNumber++), Transport(c){
    this->model = c.model;
    this->color = c.color;
    this->plate = c.plate;
}
Car& Car::operator=(const Car& c){
    if(this != &c){
        Transport::operator=(c);
        this->model = c.model;
        this->color = c.color;
        this->plate = c.plate;
    }
    return *this;
}
Car::~Car(){
    this->model.clear();
    this->color.clear();
    this->plate.clear();
}
istream& Car::citire(istream& in){
    Transport::citire(in);
    cout<<"Model: "; in>>this->model;
    cout<<"Color: "; in>>this->color;
    cout<<"Plate: "; in>>this->plate;

    return in;
}
ostream& Car::afisare(ostream& out) const {
    Transport::afisare(out);
    cout<<"Model: "<<this->model<<endl;
    cout<<"Color: "<<this->color<<endl;
    cout<<"Plate: "<<this->plate<<endl;

    return out;
}
istream& operator>>(istream& in, Car& c){
    return c.citire(in);
}
ostream& operator<<(ostream& out, const Car& c){
    return c.afisare(out);
}

class LuxuryCar:public Car{
    list<string> champagne;
    bool massage, fridge;
    unordered_map<string, int> screens;
public:
    bool hasTV(){
        if(!this->screens.empty()) return true;
        return false;
    }
    bool hasFridge(){
        return this->fridge;
    }
    bool hasChampagne(){
        if(!this->champagne.empty()) return true;
        return false;
    }
    bool hasMassage(){
        return this->massage;
    }

    LuxuryCar();
    LuxuryCar(string, string, string, int, pair<int, int>, string, list<string>, bool, bool, unordered_map<string, int>, vector<pair<int, int>>);
    LuxuryCar(const LuxuryCar& c);
    LuxuryCar& operator=(const LuxuryCar& c);
    ~LuxuryCar();
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    friend istream& operator>>(istream& in, LuxuryCar& c);
    friend ostream& operator<<(ostream& out, const LuxuryCar& c);
};
LuxuryCar::LuxuryCar():Car(){
    this->champagne = {};
    this->massage = false;
    this->fridge = false;
    this->screens = {};
}
LuxuryCar::LuxuryCar(string name, string model, string plate, int seats, pair<int, int> curLocation, string fuel, list<string> champagne, bool massage, bool fridge, unordered_map<string, int> screens, vector<pair<int, int>> route)
        :Car(name, model, plate, seats, curLocation, fuel, route)
{
    this->champagne = champagne;
    this->massage = massage;
    this->fridge = fridge;
    this->screens = screens;
}
LuxuryCar::LuxuryCar(const LuxuryCar& c):Car(c){
    this->champagne = c.champagne;
    this->massage = c.massage;
    this->fridge = c.fridge;
    this->screens = c.screens;
}
LuxuryCar::~LuxuryCar(){
    this->champagne.clear();
    this->massage = false;
    this->fridge = false;
    this->screens.clear();
}
LuxuryCar& LuxuryCar::operator=(const LuxuryCar& c){
    if(this!=&c){
        Car::operator=(c);
        this->champagne = c.champagne;
        this->massage = c.massage;
        this->fridge = c.fridge;
        this->screens = c.screens;
    }
    return *this;
}
istream& LuxuryCar::citire(istream& in){
    Car::citire(in);
    int n;
    cout<<"Number of champagne bottles: "; in>>n;
    string champ;
    for(int i=0; i<n; i++){
        cout<<"Please add a new champagne bottle name: "; in>>champ;
        this->champagne.push_back(champ);
    }
    cout<<"Does this car have massage? Yes(1) or no(0): "; in>>massage;
    cout<<"Does this car have a second fridge? Yes(1) or no(0): "; in>>fridge;
    cout<<"Number of screens: "; in>>n; string tv; int size;
    for(int i=0; i<n; i++){
        cout<<"Please add a new TV name: "; in>>tv;
        cout<<"Add this tv's screen size: "; in>>size;
        this->screens[tv] = size;
    }
    return in;
}
ostream& LuxuryCar::afisare(ostream& out) const {
    Car::afisare(out);
    cout<<"Champagne stored in the vehicle: "<<endl;
    int k=0;
    for(auto i : this->champagne){
        cout<<"Champagne "<<k++<<": "<<i<<endl;
    }
    if(this->massage) cout<<"This car also has massage."<<endl;
    if(this->fridge) cout<<"This car also has a fridge with goods."<<endl;
    cout<<"Screens: "<<endl;
    for(auto& i : this->screens){
        cout<<i.first<<": "<<i.second<<endl;
    }
}
istream& operator>>(istream& in, LuxuryCar& c){
    return c.citire(in);
}
ostream& operator<<(ostream& out, LuxuryCar& c){
    return c.afisare(out);
}


class SuperCar:public Car{
    int hp, maxSpeed;
public:
    int getHorsePower(){ return this->hp; }
    int getMaxSpeed(){ return this->maxSpeed; }

    SuperCar();
    SuperCar(string, string, string, int, pair<int, int>, string, int, int, vector<pair<int, int>>);
    SuperCar(const SuperCar&);
    ~SuperCar();
    SuperCar& operator=(const SuperCar& c);
    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;
    friend istream& operator>>(istream& in, SuperCar& c);
    friend ostream& operator<<(ostream& out, const SuperCar& c);
};
SuperCar::SuperCar():Car(){
    this->hp = 0;
    this->maxSpeed = 0;
}
SuperCar::SuperCar(string name, string model, string plate, int seats, pair<int, int> curLocation, string fuel, int hp, int maxSpeed, vector<pair<int, int>> route)
        :Car(name, model, plate, seats, curLocation, fuel, route){
    this->hp = hp;
    this->maxSpeed = maxSpeed;
}
SuperCar::SuperCar(const SuperCar& c):Car(c){
    this->hp = c.hp;
    this->maxSpeed = c.maxSpeed;
}
SuperCar::~SuperCar(){
    this->hp = 0;
    this->maxSpeed = 0;
}
istream& SuperCar::citire(istream& in){
    Car::citire(in);
    cout<<"Horse power: "; cin>>this->hp;
    cout<<"Max. maxSpeed: "; cin>>this->maxSpeed;
    return in;
}
ostream& SuperCar::afisare(ostream& out) const {
    Car::afisare(out);
    cout<<"Horse power: "<<this->hp<<endl;
    cout<<"Max. maxSpeed: "<<this->maxSpeed<<endl;
    return out;
}
istream& operator>>(istream& in, SuperCar& c){
    return c.citire(in);
}
ostream& operator<<(ostream& out, SuperCar& c){
    return c.afisare(out);
}
SuperCar& SuperCar::operator=(const SuperCar& c){
    if(this!=&c){
        Car::operator=(c);
        this->hp = c.hp;
        this->maxSpeed = c.maxSpeed;
    }
    return *this;
}

class Helicopter:public Transport{
    const int id;
    static int planeNumber;
    int size, maxSpeed;
    string emergencySys, camo;
public:
    string getCamo(){ return this->camo; }
    int getMaxSpeed(){ return this->maxSpeed; }

    Helicopter();
    Helicopter(string, int, string, pair<int, int>, int, int, string, string, vector<pair<int, int>>);
    Helicopter(const Helicopter&);
    ~Helicopter();
    Helicopter& operator=(const Helicopter&);
    virtual istream& citire(istream&);
    virtual ostream& afisare(ostream&) const;
    friend istream& operator>>(istream&, Helicopter&);
    friend ostream& operator<<(ostream&, const Helicopter&);
};
Helicopter::Helicopter():id(planeNumber++),Transport(){
    this->size = 0;
    this->maxSpeed = 0;
    this->emergencySys = "";
    this->camo = "";
}
Helicopter::Helicopter(string name, int seats, string fuel, pair<int, int> curLocation, int size, int maxSpeed, string emergencySys, string camo, vector<pair<int, int>> route):id(planeNumber++),
                                                                                                                                                                                Transport(name, seats, fuel, curLocation, route){
    this->size = size;
    this->maxSpeed = maxSpeed;
    this->emergencySys = emergencySys;
    this->camo = camo;
}
Helicopter::Helicopter(const Helicopter& a):id(planeNumber++),Transport(a){
    this->size = a.size;
    this->camo = a.camo;
    this->emergencySys = a.emergencySys;
    this->maxSpeed = a.maxSpeed;
}
Helicopter::~Helicopter(){
    this->size = 0;
    this->camo.clear();
    this->emergencySys.clear();
    this->maxSpeed = 0;
}
Helicopter& Helicopter::operator=(const Helicopter& a){
    if(this!=&a){
        Transport::operator=(a);
        this->size = a.size;
        this->camo = a.camo;
        this->emergencySys = a.emergencySys;
        this->maxSpeed = a.maxSpeed;
    }
    return *this;
}
istream& Helicopter::citire(istream& in){
    Transport::citire(in);
    cout<<"Size: "; in>>this->size;
    cout<<"Emergency System: "; in>>this->emergencySys;
    cout<<"Camo: "; in>>this->camo;
    cout<<"Maximum speed: "; in>>this->maxSpeed;

    return in;
}
ostream& Helicopter::afisare(ostream& out) const{
    Transport::afisare(out);
    cout<<"Size: "<<this->size;
    cout<<"Emergency System: "<<this->emergencySys;
    cout<<"Camo: "<<this->camo;
    cout<<"Maximum speed: "<<this->maxSpeed;
    return out;
}
istream& operator>>(istream& in, Helicopter& a){
    return a.citire(in);
}
ostream& operator<<(ostream& out, const Helicopter& a){
    return a.afisare(out);
}

int Car::carNumber = 0;
int Helicopter::planeNumber = 0;



class OutOfBounds : public exception {
    string errorMessage;
public:
    OutOfBounds(const string& message) noexcept: errorMessage(message) {}

    ~OutOfBounds() noexcept {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
};
class WrongInput : public exception {
    string errorMessage;
public:
    WrongInput(const string& message) noexcept: errorMessage(message){};
    ~WrongInput() noexcept {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
};




class Driver:public IOInterface{
    string name, phoneNumber;
    int curSpeed;
    pair<int, int> curLocation;
    vector<pair<int, int>> route;
    vector<Transport*> transport;
    Transport* currentVehicle;
    float dollars, charge;

public:
    void push_front_route(pair<int, int> point){
        this->route.insert(this->route.begin(), point);
    }
    void addToRoute(pair<int, int> point){ this->route.push_back(point); }
    Transport* getVehicle(){
        return this->currentVehicle;
    }
    void eraseFirstPoint(){
        this->route.erase(this->route.begin());
    }
    const vector<pair<int, int>> getRoute() const {
        return this->route;
    }
    void setRoute(vector<pair<int, int>> route){
        this->route = route;
    }
    pair<int, int> getLocation() const { return this->curLocation; }
    void changeX(int value){ this->curLocation.first += value; }
    void changeY(int value){ this->curLocation.second += value; }
    int getX() const { return this->curLocation.first; }
    int getY() const { return this->curLocation.second; }
    void showVehicleInfo() const {
        cout<<"Vehicle name: "<<this->currentVehicle->getName()<<endl;
        cout<<"Number of seats: "<<this->currentVehicle->getSeatsNumber()<<endl;

        if(dynamic_cast<SuperCar*>(this->currentVehicle) != nullptr){
            SuperCar* c = dynamic_cast<SuperCar*>(this->currentVehicle);
            cout<<"Model: "<<c->getModel()<<endl;
            cout<<"Plates: "<<c->getPlates()<<endl;
            cout<<"Color: "<<c->getColor()<<endl;
            cout<<"Horse Power: "<<c->getHorsePower()<<endl;
            cout<<"Maximum speed: "<<c->getMaxSpeed()<<endl;
        } else if(dynamic_cast<LuxuryCar*>(this->currentVehicle) != nullptr){
            LuxuryCar* c = dynamic_cast<LuxuryCar*>(this->currentVehicle);
            cout<<"Model: "<<c->getModel()<<endl;
            cout<<"Plates: "<<c->getPlates()<<endl;
            cout<<"Color: "<<c->getColor()<<endl;
            cout<<"This vehicle has ";
            if(c->hasChampagne()) cout<<"champagne ";
            if(c->hasMassage()) cout<<", massage ";
            if(c->hasTV()) cout<<", TV";
            if(c->hasFridge()) cout<<"and fridge!";
            cout<<endl;
        } else if(dynamic_cast<Car*>(this->currentVehicle) != nullptr){
            Car* c = dynamic_cast<Car*>(this->currentVehicle);
            cout<<"Model: "<<c->getModel()<<endl;
            cout<<"Plates: "<<c->getPlates()<<endl;
            cout<<"Color: "<<c->getColor()<<endl;
        } else if(dynamic_cast<Helicopter*>(this->currentVehicle) != nullptr){
            Helicopter* h = dynamic_cast<Helicopter*>(this->currentVehicle);
            cout<<"Camo: "<<h->getCamo()<<endl;
            cout<<"Max speed: "<<h->getMaxSpeed()<<endl;
        }
    }
    string getName() const { return this->name; }

    Driver();
    Driver(float, float, string, string, int, pair<int, int>, vector<pair<int, int>>, vector<Transport*>);
    Driver(const Driver&);
    ~Driver(){
        for(int i=0; i<this->transport.size(); i++){
            delete this->transport[i];
        }
        this->transport.clear();
    }
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    friend istream& operator>>(istream& in, Driver&);
    friend ostream& operator<<(ostream& out, const Driver&);
    Driver& operator=(const Driver&);
};
Driver::Driver(){
    this->name = "";
    this->phoneNumber = "";
    this->curSpeed = 0;
    this->curLocation = {0, 0};
    this->route = {};
    this->transport = {};
    this->dollars = 0;
    this->charge = 0;
}
Driver::Driver(float dollars, float charge, string name, string phoneNumber, int curSpeed, pair<int, int> curLocation, vector<pair<int, int>> route, vector<Transport*> transport){
    this->name = name;
    this->phoneNumber = phoneNumber;
    this->curSpeed = curSpeed;
    this->curLocation = curLocation;
    this->route = route;
    this->transport = transport;
    this->dollars = dollars;
    this->charge = charge;
    this->currentVehicle = transport[0];
}
Driver::Driver(const Driver& dr){
    this->name = dr.name;
    this->phoneNumber = dr.phoneNumber;
    this->curSpeed = dr.curSpeed;
    this->curLocation = dr.curLocation;
    this->route = dr.route;
    this->transport = dr.transport;
}
istream& Driver::citire(istream& in){
    cout<<"Name: "; cin>>this->name;
    cout<<"Number: "; cin>>this->phoneNumber;
    int X, Y;
    cout<<"Location:"<<endl;
    cout<<"X: "; cin>>X;
    cout<<"Y: "; cin>>Y;
    this->curLocation = {X, Y};
    cout<<"Amount: "; cin>>this->dollars;
    cout<<"Charge per km: "; cin>>this->charge;
    int n, inp;
    cout<<"Number of vehicles: "; cin>>n;
    for(int i=0; i<n; i++){
        cout<<"Choose type of vehicle "<<i+1<<" car(1), luxury car(2), super car(3) or Helicopter (4):";
        cin>>inp;
        switch(inp){
            case 1: {
                this->transport.push_back(new Car());
                cin>>*this->transport.back();
                break;
            }
            case 2: {
                this->transport.push_back(new LuxuryCar());
                cin>>*this->transport.back();
                break;
            }
            case 3: {
                this->transport.push_back(new SuperCar());
                cin>>*this->transport.back();
                break;
            }
            case 4: {
                this->transport.push_back(new Helicopter());
                cin>>*this->transport.back();
                break;
            }
            default: {
                break;
            }
        }
    }
    this->currentVehicle = this->transport[0];
    return in;
}
ostream& Driver::afisare(ostream& out) const {
    cout<<"Name: "<<this->name;
    cout<<"Number: "<<this->phoneNumber;
    cout<<"Current speed: "<<this->curSpeed;
    cout<<"Transport: ";
    for(int i=0; i<this->transport.size(); i++){
        cout<<i<<": "<<endl; cout<<*this->transport[i]<<endl;
    }
    cout<<"Location: "<<this->curLocation.first<<" "<<this->curLocation.second<<endl;
    cout<<"Destination: "<<this->route.back().first<<" "<<this->route.back().second<<endl;
    cout<<"Money: "<<this->dollars<<endl;
    cout<<"Charge rate: "<<this->charge<<" per km"<<endl;
    return out;
}
istream& operator>>(istream& in, Driver& dr){
    return dr.citire(in);
}
ostream& operator<<(ostream& out, const Driver& dr){
    return dr.afisare(out);
}
Driver& Driver::operator=(const Driver& dr){
    if(this != &dr){
        this->name = dr.name;
        this->phoneNumber = dr.phoneNumber;
        this->curSpeed = dr.curSpeed;
        this->curLocation = dr.curLocation;
        this->route = dr.route;
        this->transport = dr.transport;
    }
    return *this;
}




class Menu {
private:
    vector<Transport*> vehicles;
    vector<Driver*> drivers;
    vector<Driver*> createdDrivers;
    char map[30][30];
    int requestedDriver = -1;

    template <typename T> void read(T& object_ptr){
        cin>>object_ptr;
    }
    template <typename T> float getDistance(const T& obj, int X, int Y){
        pair<int, int> location = obj->getLocation();
        return sqrt(pow(location.first-X, 2) + pow(location.second-Y, 2));
    }
    template <typename T> void createRoute(T& obj){
        int n, X, Y;
        cout<<"How many places do you wanna add? "; cin>>n;
        for(int i=1; i<=n; i++){
            cout<<"Please give us place number "<<i<<": ";

            while(true){
                try{
                    cin>>X>>Y;
                    if(!this->allowed(X, Y)){
                        throw OutOfBounds("Location out of bounds. Please try again.");
                    }
                    break;
                }
                catch (OutOfBounds& err){
                    cout<<err.what()<<endl;
                }
            }

            obj.addToRoute(make_pair(X, Y));
        }
    }

    static Menu* instance;
    Menu() = default;
    ~Menu() = default;
    int findDriver(string name){
        for(int i=0; i<this->createdDrivers.size(); i++){
            if(this->createdDrivers[i]->getName() == name){
                return i;
            }
        }
        throw 404;
    }
    int findVehicle(string name){
        for(int i=0; i<this->vehicles.size(); i++){
            if(this->vehicles[i]->getName() == name){
                return i;
            }
        }
        throw 404;
    }
    bool allowed(int X, int Y){
        if(this->map[X][Y] != '#' && X > 0 && X < 29 && Y > 0 && Y < 29) return true;
        return false;
    };
    void createMap(int, int);
    void crud();
    void commandApp();
    void showMap(){
        for(int i=0; i<30; i++){
            for(int j=0; j<30; j++){
                if(this->map[i][j] == '0') cout<<"  ";
                else cout<<this->map[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    void modifyDriverLocation(pair<int, int>);
    void updateMap();
    void modifyRandomDrivers(){
        int number = this->getNumberOfDrivers();
        set<int> randomDrivers = {};
        while(number > 0){
            int rndDriver = this->getRandomDriverIndex(this->requestedDriver);
            randomDrivers.insert(rndDriver);
            number--;
        }
        for(auto& driverIdx : randomDrivers){
            int action = this->getRandomXY();
            int value = this->getRandomVal();
            int X = this->drivers[driverIdx]->getX();
            int Y = this->drivers[driverIdx]->getY();
            if(action == 1){
                try{
                    if(this->map[X][Y] != 'X')
                        this->map[X][Y] = '0';
                    this->drivers[driverIdx]->changeX(value);
                    if(!this->allowed(X, Y)){
                        throw OutOfBounds("Out of bounds error");
                    }
                }
                catch(OutOfBounds& err){
                    this->drivers[driverIdx]->changeX(-value);
                }
            } else if(action == 2){
                try{
                    if(this->map[X][Y] != 'X')
                        this->map[X][Y] = '0';
                    this->drivers[driverIdx]->changeY(value);
                    if(!this->allowed(X, Y)){
                        throw OutOfBounds("Out of bounds error");
                    }
                }
                catch(OutOfBounds& err){
                    this->drivers[driverIdx]->changeY(-value);
                }
            }
            if(this->map[this->drivers[driverIdx]->getLocation().first][this->drivers[driverIdx]->getLocation().second] != 'X')
                this->map[this->drivers[driverIdx]->getLocation().first][this->drivers[driverIdx]->getLocation().second] = '&';
        }
        this->updateMap();
    }
    int getRandomDriverIndex(int avoid){
        int res;
        int n = (this->drivers.size()-1) - 0 + 1;
        int remainder = RAND_MAX % n;
        int x;
        do{
            x = rand();
        }while (x >= RAND_MAX - remainder);
        res = 0 + x % n;

        while(res == avoid){
            int n = (this->drivers.size()-1) - 0 + 1;
            int remainder = RAND_MAX % n;
            int x;
            do{
                x = rand();
            }while (x >= RAND_MAX - remainder);
            res = 0 + x % n;
        }

        return res;
    }
    int getRandomXY(){
        int n = 2 - 1 + 1;
        int remainder = RAND_MAX % n;
        int x;
        do{
            x = rand();
        }while (x >= RAND_MAX - remainder);
        return 1 + x % n;
    }
    int getRandomVal(){
        int n = 1 - (-1) + 1;
        int remainder = RAND_MAX % n;
        int x;
        do{
            x = rand();
        }while (x >= RAND_MAX - remainder);
        return (-1) + x % n;
    }
    int getNumberOfDrivers(){
        int n = (this->drivers.size()-1) - 0 + 1;
        int remainder = RAND_MAX % n;
        int x;
        do{
            x = rand();
        }while (x >= RAND_MAX - remainder);
        return x % n;
    }
    void start();
    void importDrivers();
public:
    static Menu* getInstance() {
        if(!instance){
            instance = new Menu();
        }
        return instance;
    }
    Menu(const Menu& obj) = delete;
    void startApp();
};
void Menu::importDrivers(){
    for(int i=0; i<this->createdDrivers.size(); i++){
        try{
            if(!this->allowed(this->createdDrivers[i]->getX(), this->createdDrivers[i]->getY())){
                throw OutOfBounds("One of the created drivers is out of bounds!");
            }
            this->drivers.push_back(this->createdDrivers[i]);
        }
        catch (OutOfBounds& err){
            throw OutOfBounds(err);
        }
    }
}
void Menu::updateMap(){
    for(int i=0; i<this->drivers.size(); i++){
        if(this->map[this->drivers[i]->getLocation().first][this->drivers[i]->getLocation().second] != 'X')
            this->map[this->drivers[i]->getLocation().first][this->drivers[i]->getLocation().second] = '&';
    }
}
void Menu::modifyDriverLocation(pair<int, int> target) {
    while(this->drivers[this->requestedDriver]->getLocation() != target){
        pair<int, int> drloc = this->drivers[this->requestedDriver]->getLocation();
        int X = drloc.first, Y = drloc.second;
        int rand = this->getRandomXY();
        if(rand == 1){
            if(target.first < X){
                try{
                    if(!this->allowed(this->drivers[this->requestedDriver]->getX()-1, this->drivers[this->requestedDriver]->getY()))
                        throw OutOfBounds("Driver out of bounds!");
                    this->drivers[this->requestedDriver]->changeX(-1);
                }
                catch(OutOfBounds& err){
                    throw OutOfBounds(err);
                }
            } else if(target.first > X){
                try{
                    if(!this->allowed(this->drivers[this->requestedDriver]->getX()+1, this->drivers[this->requestedDriver]->getY()))
                        throw OutOfBounds("Driver out of bounds!");
                    this->drivers[this->requestedDriver]->changeX(1);
                }
                catch(OutOfBounds& err){
                    throw OutOfBounds(err);
                }
            }
        } else {
            if(target.second < Y){
                try{
                    if(!this->allowed(this->drivers[this->requestedDriver]->getX(), this->drivers[this->requestedDriver]->getY()-1))
                        throw OutOfBounds("Driver out of bounds!");
                    this->drivers[this->requestedDriver]->changeY(-1);
                }
                catch(OutOfBounds& err) {
                    throw OutOfBounds(err);
                }
            } else if(target.second > Y) {
                try{
                    if(!this->allowed(this->drivers[this->requestedDriver]->getX(), this->drivers[this->requestedDriver]->getY()+1))
                        throw OutOfBounds("Driver out of bounds!");
                    this->drivers[this->requestedDriver]->changeY(1);
                }
                catch(OutOfBounds& err) {
                    throw OutOfBounds(err);
                }
            }
        }
        bool change = 1;
        for(int i=0; i<this->drivers.size(); i++){
            if(this->drivers[i]->getLocation().first == X && this->drivers[i]->getLocation().second == Y){
                change = 0;
                break;
            }
        }
        if(change && this->map[X][Y] != 'X'){
            this->map[X][Y] = '0';
        }
        this->modifyRandomDrivers();
        this->updateMap();
        system("cls");
        this->showMap();cout<<endl;
        Sleep(380);
    }
}
void Menu::start(){
    int i = 0;
    Driver* dr = this->drivers[this->requestedDriver];
    while(!dr->getRoute().empty()){
        system("cls");
        this->showMap();cout<<endl;
        pair<int, int> loc = {dr->getRoute()[0].first, dr->getRoute()[0].second};
        try{
            this->modifyDriverLocation(loc);
        }
        catch (OutOfBounds& err){
            continue;
        }
        i++;
        if(i==1){
            this->map[dr->getRoute()[0].first][dr->getRoute()[0].second] = '0';
        }
        Sleep(800);
        dr->eraseFirstPoint();
    }
}
void Menu::startApp(){
    int inp;

    bool stop = 0;
    while(!stop){
        cout<<"CRUD (1) or make a command (2): ";

        while(true){
            try{
                cin>>inp;
                if(inp != 1 && inp != 2){
                    throw WrongInput("Wrong number! Please choose between 1 and 2");
                }
                break;
            }
            catch (WrongInput& err){
                cout<<err.what()<<endl;
            }
        }

        switch(inp){
            case 1: {
                this->crud();
                stop = 1;
                break;
            }
            case 2: {
                this->commandApp();
                stop = 1;
                break;
            }
            default: {
                break;
            }
        }
    }
}
void Menu::crud(){
    int inp;
    bool stop = 0;
    while(!stop){
        cout<<"Create (1), read (2), update (3) or delete (4):"; cin>>inp;
        switch(inp){
            case 1: {
                cout<<"Create a new driver(1) or create a new vehicle(2)?"; cin>>inp;
                switch(inp){
                    case 1: {
                        this->createdDrivers.push_back(new Driver());
                        this->read(*this->createdDrivers.back());
                        break;
                    }
                    case 2: {
                        cout<<"Create a new normal Car(1), Luxury Car(2), Sports Car(3) or Helicopter(4)?"; cin>>inp;
                        switch(inp){
                            case 1: {
                                this->vehicles.push_back(new Car());
                                break;
                            }
                            case 2: {
                                this->vehicles.push_back(new LuxuryCar());
                                break;
                            }
                            case 3: {
                                this->vehicles.push_back(new SuperCar());
                                break;
                            }
                            case 4: {
                                this->vehicles.push_back(new Helicopter());
                                break;
                            }
                            default: {
                                break;
                            }
                        }
                        this->read(*this->vehicles.back());
                        break;
                    }
                    default: {
                        break;
                    }
                }
                break;
            }
            case 2: {
                string name;
                cout<<"Want to read a driver(1) or vehicle(2)?"; cin>>inp;
                switch(inp){
                    case 1: {
                        cout<<"Please give us the name of the driver:"; cin>>name;
                        try{
                            cout<<*this->createdDrivers[this->findDriver(name)];
                        }
                        catch (int nr){
                            cout<<nr<<": Driver not found!"<<endl;
                        }
                        break;
                    }
                    case 2: {
                        cout<<"Please give us the name of the vehicle: "; cin>>name;
                        try{
                            cout<<*this->vehicles[this->findVehicle(name)];
                        }
                        catch (int nr){
                            cout<<nr<<": Vehicle not found!"<<endl;
                        }
                        break;
                    }
                    default: {
                        break;
                    }
                }
                break;
            }
            case 3: {
                string name;
                cout<<"Want to delete a driver(1) or vehicle(2)?"; cin>>inp;
                switch(inp){
                    case 1: {
                        cout<<"Please give us the name of the driver:"; cin>>name;
                        try{
                            int i = this->findDriver(name);
                            this->createdDrivers.erase(this->createdDrivers.begin() + i);
                        }
                        catch (int nr){
                            cout<<nr<<": Driver not found!"<<endl;
                        }
                        break;
                    }
                    case 2: {
                        string type;
                        cout<<"Please give us the name of the vehicle: "; cin>>name;
                        try{
                            int i = this->findVehicle(name);
                            this->vehicles.erase(this->vehicles.begin() + i);
                        }
                        catch (int nr){
                            cout<<nr<<": Vehicle not found!"<<endl;
                        }
                        break;
                    }
                    default: {
                        break;
                    }
                }
                break;
            }
            case 4: {
                string name;
                cout<<"Want to update a driver(1) or vehicle(2)?"; cin>>inp;
                switch(inp){
                    case 1: {
                        cout<<"Please give us the name of the driver:"; cin>>name;
                        try{
                            int i = this->findDriver(name);
                            cin>>*this->createdDrivers[i];
                        }
                        catch (int nr){
                            cout<<nr<<": Driver not found!"<<endl;
                        }
                        break;
                    }
                    case 2: {
                        string type;
                        cout<<"Please give us the name of the vehicle: "; cin>>name;
                        try{
                            int i = this->findVehicle(name);
                            cin>>*this->vehicles[i];
                        }
                        catch (int nr){
                            cout<<nr<<": Vehicle not found!"<<endl;
                        }
                        break;
                    }
                    default: {
                        break;
                    }
                }
                break;
            }
            default: {
                break;
            }
        }
        cout<<"Stop? Yes(1) or no(0):"; cin>>stop;
    }
    cout<<"Make a command?"; cin>>inp;
    if(inp) this->commandApp();
}
void Menu::commandApp(){
    int inp;
    Car c1("Honda", "Civic", "BZ 39 XYZ", 4, {17, 23}, "comb", {});
    Car c2("Lexus", "Mars", "B 839 YOS", 4, {13, 11}, "comb", {});
    LuxuryCar c3("Ford", "Focus", "CJ 55 ZZW", 4, {22, 15}, "comb", {}, 1, 1, {}, {});
    vector<Transport*> t1 = {}, t2 = {}, t3 = {};
    t1.push_back(&c1);
    t2.push_back(&c2);
    t3.push_back(&c3);
    Driver d1(50, 1.6, "Alex Ion", "0794521223", 40, {17, 23}, {}, t1);
    Driver d2(50, 1.6, "Iulian Ion", "0795623223", 40, {13, 11}, {{}}, t2);
    Driver d3(50, 1.6, "Alexandru Ali", "0753461223", 40, {22, 15}, {{}}, t3);

    cout<<"Import drivers from CRUD? Yes(1) or no(0):";
    try{
        cin>>inp;
        if(inp != 1 && inp != 0) throw WrongInput("Wrong input! We will choose the default drivers.");
        if(!inp){
            this->drivers = {&d1, &d2, &d3};
        } else {
            try{
                this->importDrivers();
            }
            catch (OutOfBounds& err){
                cout<<err.what()<<endl;
                this->drivers.clear();
                this->drivers = {&d1, &d2, &d3};
            }
        }
    }
    catch (WrongInput& err){
        cout<<err.what()<<endl;
        this->drivers = {&d1, &d2, &d3};
    }

    int X, Y;
    cout<<"Please give us your location: "<<endl;

    while(true){
        try{
            cout<<"X: "; cin>>X;
            cout<<"Y: "; cin>>Y;

            if(!this->allowed(X, Y)){
                throw OutOfBounds("Player placed out of bounds");
            }
            break;
        }
        catch (OutOfBounds& err){
            cout<<err.what()<<endl;
        }
    }

    this->createMap(X, Y);

    int n;
    while(true){
        cout<<"Please choose a driver to come pick you up:"<<endl;
        for(int i=0; i<this->drivers.size(); i++){
            cout<<"Name: "<<this->drivers[i]->getName()<<endl;
            this->drivers[i]->showVehicleInfo();
            cout<<"Distance between you and driver: "<<this->getDistance(this->drivers[i], X, Y)<<endl;
            cout<<"Is this a good driver? Yes(1) or no(0): ";

            try{
                cin>>inp;
                if(inp != 0 && inp != 1) throw WrongInput("Wrong input. We will chose 1");

                if(inp == 1) {
                    this->requestedDriver = i;
                    cout<<"Great choice! Your driver will be on his way shortly!"<<endl;
                    break;
                }
            }
            catch (WrongInput& err){
                inp = 1;
                cout<<err.what()<<endl;
            }
        }
        if(this->requestedDriver == -1) {
            cout<<"We will choose a suitable driver for you!"<<endl;
            this->requestedDriver = 0;
        }
        Driver* dr = this->drivers[this->requestedDriver];
        this->createRoute(*dr);
        dr->push_front_route(make_pair(X, Y));
        for(int i=1; i<dr->getRoute().size(); i++){
            this->map[dr->getRoute()[i].first]
            [dr->getRoute()[i].second] = 'X';
        }
        dr->getVehicle()->setRoute(dr->getRoute());

        this->start();
        return;
        Sleep(2000);
    }
}
void Menu::createMap(int X, int Y){
    for(int i=0; i<30; i++){
        this->map[i][0] = '#';
        this->map[0][i] = '#';
        this->map[29][i] = '#';
        this->map[i][29] = '#';
    }
    for(int i=1; i<29; i++){
        for(int j=1; j<29; j++){
            this->map[i][j] = '0';
        }
    }
    for(int i=0; i<this->drivers.size(); i++){
        this->map[this->drivers[i]->getLocation().first][this->drivers[i]->getLocation().second] = '&';
    }
    this->map[X][Y] = 'Y';
}

Menu* Menu::instance = nullptr;

int main() {
    Menu* a = Menu::getInstance();
    a->startApp();

    return 0;
}
