#ifndef ACS_61_H
#define ACS_61_H

#include <iostream>
#include <string>
using namespace std;
/* 
Include only ATTRIBUTES and FUNCTION SIGNATURES for each class in this file. 
Code for each method must be in ACS_61.cpp 
i.e.
class Aeroplane {
    private:
        string name;
    public:
        string get_name();
};
*/

enum class AircraftStatus {
    OnGround,
    Airborne,
    Crashed
};

// BASE CLASS
class Aircraft {
    private:
        string identifier;
        int fuel_level;
        int health;
        AircraftStatus current_status;

    public:
            Aircraft();
            Aircraft(string identifier, int fuel_levels, int healths, AircraftStatus current_statuses);
            Aircraft(Aircraft const &other);

            void setIdentifier(string identifier);
            void setfuellevel(int fuel_level);
            void setHealth(int health_lev);
            void setcurrentstatus(AircraftStatus current_Status);
            string getIdentifier();
            int getFuelLevel();
            int getFuelCapacity();
            int getHealth();
            AircraftStatus getCurrentStatus();

            virtual void takeOff();
            virtual void land();

            friend ostream& operator<<(ostream &COUT, AircraftStatus &current_status);

            Aircraft& operator+=(int num);

            Aircraft& operator-=(int num);

            bool operator==(Aircraft const &other);

            friend ostream& operator<<(ostream &COUT, Aircraft &obj);
            virtual void print(ostream &COUT);
            friend istream& operator>>(istream &IN, Aircraft &obj);



            
    //
};

// INHERITED CLASSES -- implement inheritance yourself.
class CombatAircraft : virtual public Aircraft
{
    private:
        string weapon_type;
        int weapon_count;
        int weapon_strength;

    public:
            CombatAircraft();
            CombatAircraft(string identifier, int fuel_level, int health, AircraftStatus current_status,string weapon_types, int weapon_counts, int weapon_strengths);
            CombatAircraft(CombatAircraft const &other);
            string getWeaponType();
            void setWeaponCount(int wp);
            int getWeaponCount();
            int getWeaponStrength();

            CombatAircraft operator++(int);
            CombatAircraft operator--();
            virtual void print(ostream& COUT) override;

            


            

};

class StealthAircraft :virtual public Aircraft
{
    private:
        bool cloak_status;
    public:
        StealthAircraft();
        StealthAircraft(string identifier, int fuel_level, int health, AircraftStatus current_status,bool cloak_Status);
        StealthAircraft(StealthAircraft const &other);
        bool getCloakStatus();
        void activateCloak();
        void deactivateCloak();
        void takeOff() override;
        void land() override;
        StealthAircraft operator!();
        virtual void print(ostream& COUT) override;
};

class AbductorCraft : public StealthAircraft
{
    private:
        int abductee_count;
        int abductee_capacity;   
    public:
        AbductorCraft();
        AbductorCraft(string identifier, int fuel_level, int health, AircraftStatus current_status,bool cloak_status, int aubductee_count1, int abductee_cap);
        AbductorCraft(AbductorCraft const &other);
        int getAbducteeCount();
        int getAbducteeCapacity();
        bool operator>(AbductorCraft obj);
        AbductorCraft operator+=(int num);
        AbductorCraft operator-=(int num);
        AbductorCraft operator&(AbductorCraft &obj);
        void print(ostream &COUT) override;




    //
};

class GuardianCraft : public StealthAircraft, public CombatAircraft
{
    private:
        int kill_count;
    public:
        GuardianCraft();
        GuardianCraft(string identifier, int fuel_level, int health, AircraftStatus current_status,string weapon_types, int weapon_counts, int weapon_strengths, bool cloak_status, int kill_count);
        GuardianCraft(GuardianCraft const &other);
        GuardianCraft(CombatAircraft const &combat_aircraft);
        void setKillCount(int kc);

        int getKillCount();

        bool operator*=(AbductorCraft &obj);

        GuardianCraft operator*(AbductorCraft &obj);
        void print(ostream& COUT) override;


        


};

#endif