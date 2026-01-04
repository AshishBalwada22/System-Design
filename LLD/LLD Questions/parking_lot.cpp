// parking lot

/*
10 steps - 
1) clarify and scope requirement
   - separate functional and non-functional requirement
   - ask what features must exist?
   - ask what features are out of scope?
   
   key points -
   - Type support (do we support mutiple vechicle type)
   - Multiplicity (do we have multi levels parking)
   - algorithm/logic (how do we decide which vehicle goes to which parking spot, how do we calculate fees)
   - concurrency (is there a multple entry or exit point)

2) Use case and Api's -  
   - max to max 3 functionaily can be implemented in given time
   - getAvailabilitySpot(), parkVehicle(), unparkVehicle()

3) Data model
   - identify entities and relationships

4) Core class design
5) Identify and apply design pattern
6) Sequence for main flow
7) Concurrency and consistency
8) Edge cases and error handling
9) Full c++ code
10) Extension and scaling

vehicle
- licensePlate : string
- type : enum
parkingSpot
- id : string
- type
- isOccupied : bool
parkingLevel
- id
- level
- vector<parkingSpot> parkingSpots
parkingLot
- id
- parkinglevels
ticket
- id
- licensePlate
- parkingSpotId
- parkingLevelId
- entryTime
- exitTime
- fees

flow
- user come to parking lot
- find available parkingSpot
- mark parkingspot occupied
- generate a ticket
- assign vehicle to parkingspot
- user going out of parking lot
- get a ticket and mark parkingspot free
- compute fees

pattern 
- finding a spot is a strategy pattern
- calculate a fee is a strategy pattern
- parkingLotService is a singleton pattern

*/

#include<bits/stdc++.h>
using namespace std;

using Clock = chrono::system_clock;
using TimePoint = chrono::time_point<Clock>;

enum class vechicleType{
    motorcyle,
    car,
    bus
};
class vehicle{
    string licensePlate;
    vechicleType type;
};
enum class spotType{
    small,
    medium,
    large
};
class parkingSpot{
    string id;
    spotType type;
    bool isOccupied;
    public:
    bool getIsOccupied(){
        return isOccupied;
    }
    bool canFitIntoParkingSpot(vechicleType vtype){
        // TODO
        return true;
    }
    void markedOccupied(){
        isOccupied = true;
    }
    void markedFree(){
        isOccupied = false;
    }
};
class parkingLevel{
    int id;
    int floor;
    vector<parkingSpot>parkingSpots;
    public:
    int countFreeSpots(vechicleType vtype){
        int cnt = 0;
        for(auto pspot : parkingSpots){
            if(!pspot.getIsOccupied() && pspot.canFitIntoParkingSpot(vtype)) cnt++;
        }
        return cnt;
    }
    parkingSpot* findSpot(vechicleType vtype){
        for(auto pspot : parkingSpots){
            if(!pspot.getIsOccupied() && pspot.canFitIntoParkingSpot(vtype)) return &pspot;
        }
        return nullptr;
    }
    vector<parkingSpot> getSpots(){
        return parkingSpots;
    }
};
class ticketRepository{ // save in database
    public:
    ticket* createTicket(string licenseplate, int spot_id, int entry_time){
        // toDO
        return nullptr;
    }
};
class ticket{
    string id;
    string licensePlate;
    int parkingSpotId;
    int parkingLevelId;
    TimePoint entry_time;
    TimePoint exit_time;
    double fees;
    bool isClosed;
    public:
    string getId(){
        return id;
    }
    bool markedClosed(){
        isClosed = true;
    }
};
class parkingLot{
    int id;
    vector<parkingLevel> parkingLevels;
    public:
    vector<parkingLevel> getParkingLevel(){
        return parkingLevels;
    }
};

class ISpotAssignmentStrategy{
    public:
    virtual parkingSpot* findspot(vector<parkingLevel>&level, vechicleType type) = 0;
};

class lowLevelFirstStrategy : public  ISpotAssignmentStrategy{
    public:
    parkingSpot* findspot(vector<parkingLevel>&level, vechicleType type){
        parkingSpot* spot = level.findSpot(type);
        if(!spot) return spot;
    }
    return nullptr;
};

class IRateCalculationStrategy{
    public:
    virtual double calculateFees(ticket tickett, TimePoint time_point) = 0;
};

class hourlyCalculationStrategy : public IRateCalculationStrategy{
    public:
    double calculateFees(ticket tickett, TimePoint time_point) override{
        // todo
    }
}

// there should be dependency injection on service while applying strategy pattern
class parkingLotService{
    parkingLot parkinglot_;
    ISpotAssignmentStrategy* spotStrategy_;
    IRateCalculationStrategy* feeStrategy_;
    mutex m; // raced condition for multiple entry and exit
    public:
    parkingLotService(parkingLot parkinglot, ISpotAssignmentStrategy* spotStrategy, hourlyCalculationStrategy* feeStrategy): parkinglot_(parkinglot), spotStrategy_(spotstrategy), feeStrategy_(feeStrategy){}
    string parkVehicle(string licensePlate, vechicleType type){ 
     lock_guard<mutex> obj(m);
     // find the spot
     parkingSpot* spot = spotStrategy_->findSpot(parkinglot_.getParkingLevel(),type);
     if(!spot){
        throw runtime_error("no free spot found"); 
     }
     // generate the ticket
     ticket* tickett = ticketRepository.createTicket(licensePlate,spot->id,clock::now());
     // book the ticket
     spot->markedOccupied();
     return ticket->getId();
    }
    void unparkVehicle(string ticket_id){
     lock_guard<mutex> obj(m);
     ticket* tickett = ticketRepository.getTicket(ticket_id);
     if(!tickett){
        throw runtime_error("no such ticket is created");
     }
     if(ticket->isClosed()){
        throw runtime_error("ticket is already closed");
     }
     // do price calculation  
     auto now = clock::now();
     double fee = feeStrategy_->calculateFees(*ticket,now);
     // close the ticket
     ticket->exit_time = now;
     ticket->fees = fee;
     ticket->markedClosed();
     // free the spot
     for(auto& level : parkinglot_.getParkingLevel()){
        for(auto& spot : level.getSpots()){
            if(spot.getId()==tickett->getId())
            {
                spot.markedFree();
            }
        }
     }
     return fee;
    }
    int getAvailabilitySpot(string licensePlate, vechicleType vtype){
        int total = 0;
        for(auto& plevel : parkinglot_.getParkingLevel()){
            total+=plevel.countFreeSpots(vtype);
        }
        return total;
    }
};
