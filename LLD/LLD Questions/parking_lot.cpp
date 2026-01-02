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
};
class ticket{
    string id;
    string licensePlate;
    int parkingSpotId;
    int parkingLevelId;
    TimePoint entry_time;
    TimePoint exit_time;
    double fees;
};
class parkingLot{
    int id;
    vector<parkingLevel> parkingLevels;
    public:
    vector<parkingLevel> getParkingLevel(){
        return parkingLevels;
    }
};

class parkingLotService{
    parkingLot parkinglot;
    public:
    void parkVehicle(){ // return ticket
     
    }
    int getAvailabilitySpot(string licensePlate, vechicleType vtype){
        int total = 0;
        for(auto& plevel : parkinglot.getParkingLevel()){
            total+=plevel.countFreeSpots(vtype);
        }
        return total;
    }
    void unparkVehicle(){

    }

};

int main(){

}