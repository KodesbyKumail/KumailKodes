#include "ACS_61.h"





// Aircraft methods
Aircraft::Aircraft()
{
    identifier="";
    fuel_level=100;
    health=100;
    current_status=AircraftStatus::OnGround;
}

Aircraft:: Aircraft(string identifier, int fuel_levels, int healths, AircraftStatus current_statuses)
{
    this->identifier=identifier;
    if(fuel_levels<0)
    {
        this->fuel_level=0;
    }
    else
    {
        this->fuel_level=fuel_levels;
    }
    if(fuel_levels>100)
    {
        this->fuel_level=100;
    }

    if(healths<=0)
    {
        this->health=0;
    }


    if(healths>=100)
    {
        this->health=100;
    }
    else if(healths<100 && healths>0)
    {
        this->health=healths;
    }
    if(this->health<=0)
    {
        current_statuses=AircraftStatus::Crashed;
    }
    if(fuel_levels==0 && current_statuses==AircraftStatus::Airborne)
    {
        current_statuses=AircraftStatus::Crashed;
        health=0;


    }
    current_status=current_statuses;
}

Aircraft::Aircraft(Aircraft const &other)
{
    this->identifier=other.identifier;
    this->fuel_level=other.fuel_level;
    this->health=other.health;
    this->current_status=other.current_status;
}

void Aircraft::setIdentifier(string identifier)
{
    this->identifier=identifier;

}
string Aircraft::getIdentifier()
{
    return identifier;
}

void Aircraft::setfuellevel(int fuel_level)
{
    this->fuel_level=fuel_level;
}

void Aircraft::setHealth(int health_lev)
{
    health=health_lev;
}
void Aircraft::setcurrentstatus(AircraftStatus current_Status)
{
   current_status=current_Status; 

}
int Aircraft::getFuelLevel()
{
    return fuel_level;

}
int Aircraft::getHealth()
{
    return health;
}
int Aircraft::getFuelCapacity()
{
    return 100;
}
AircraftStatus Aircraft::getCurrentStatus()
{
    return current_status;
}

void Aircraft::takeOff()
{

    if(fuel_level>30 && current_status==AircraftStatus::OnGround)
    {
        this->current_status=AircraftStatus::Airborne;

    }
    else if(current_status==AircraftStatus::Crashed)
    {
        current_status=AircraftStatus::Crashed;

    }
    
}
void Aircraft::land()
{
    if(current_status==AircraftStatus::Airborne)
    {
        current_status=AircraftStatus::OnGround;
    }
    else if(current_status==AircraftStatus::Crashed || fuel_level==0)
    {
        current_status=AircraftStatus::Crashed;

    }
    if(health==0)
    {
        current_status=AircraftStatus::Crashed;
    }
}

ostream& operator<<(ostream &COUT, AircraftStatus const &current_status)
{
    if(current_status==AircraftStatus::OnGround)
    {
        COUT<<"On Ground";
    }
    else if(current_status==AircraftStatus::Airborne)
    {
        COUT<<"Airborne";
    }
    else
    {
        COUT<<"Crashed";
    }
    return COUT;


}

bool Aircraft::operator==(Aircraft const &other)
{
    if(this->fuel_level==other.fuel_level&&this->health==other.health&&this->current_status==other.current_status&&this->identifier==other.identifier)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Aircraft& Aircraft::operator+=(int num)
{
    if(current_status==AircraftStatus::OnGround)
    {
        this->fuel_level+=num;
        if(this->fuel_level>100)
        {
            this->fuel_level=100;
        }
        return *(this);
    }
    else
    {
        return *(this);

    }
    
}

Aircraft& Aircraft::operator-=(int num)
{
    if(current_status==AircraftStatus::OnGround)
    {
        this->fuel_level-=num;
        if(this->fuel_level<0)
        {
            fuel_level=0;
        }
        return *(this);
    }
    else
    {
        return *(this);
    }
}

void Aircraft::print(ostream& COUT)
{
    COUT<<"Identifier: "<<identifier<<"\n";
    COUT<<"Fuel Level: "<<fuel_level<<"%\n";
    COUT<<"Health: "<<health<<"%\n";
    COUT<<"Current Status: "<<current_status<<"\n";

}

ostream& operator<<(ostream &COUT, Aircraft &obj)
{
    obj.print(COUT);
    return COUT;
}

istream &operator>>(istream &IN, Aircraft &obj)
{
    int status;
    string ident;
    int fuel_index;
    int healths;
    cout<<"Enter identifier: "<<endl;
    
    IN>>obj.identifier;
    
    cout<<"Enter Fuel Level(0-100): "<<endl;
    IN>>obj.fuel_level;
    cout<<"Enter Health(0-100): "<<endl;
    IN>>obj.health;
    cout<<"Enter Status(0:OnGround, 1: AIrborne, 2:Crashed): "<<endl;
    IN>>status;
    switch (status)
    {
    case 0:
        obj.current_status=AircraftStatus::OnGround; 
        
        break;
    case 1:
        obj.current_status=AircraftStatus::Airborne;     
    
        break;
    case 2:
        obj.current_status=AircraftStatus::Crashed;  
        break;
    default:
        cout<<"Invalid Integer"<<endl;
        break;
    }
    return IN;
}




// CombatAircraft methods
CombatAircraft::CombatAircraft():Aircraft()
{
    weapon_type="";
    weapon_count=0;
    weapon_strength=0;
}
CombatAircraft::CombatAircraft(string identifier, int fuel_level, int health, AircraftStatus current_status, string weapon_types, int weapon_counts, int weapon_strengths):Aircraft(identifier, fuel_level, health, current_status)
{
    this->weapon_type=weapon_types;
    if(weapon_counts<0)
    {
        this->weapon_count=0;
    }
    else
    {
        this->weapon_count=weapon_counts;
    }
    if(weapon_strengths<0)
    {
        this->weapon_strength=0;
    }
    else if(weapon_strengths>100)
    {
        this->weapon_strength=100;
    }
    else
    {
        this->weapon_strength=weapon_strengths;
    }
}

CombatAircraft CombatAircraft::operator++(int)
{
    CombatAircraft temporary=*this;
    if(getCurrentStatus()==AircraftStatus::OnGround)
    {
        this->weapon_count++;
        return temporary;
    }
    else
    {
        return temporary;
    }
}

CombatAircraft CombatAircraft::operator--()
{
    CombatAircraft temporary=*this;
    if(getCurrentStatus()==AircraftStatus::OnGround&&weapon_count!=0)
    {
        --this->weapon_count;
        return *this;
    }
    else
    {
        return *this;
    }
}

void CombatAircraft::print(ostream& COUT)
{
    Aircraft::print(COUT);
    COUT<<"Weapon Type: "<<weapon_type<<"\n";
    COUT<<"Weapon Count: "<<weapon_count<<"\n";
    COUT<<"Weapon Strength: "<<weapon_strength<<"\n";



}

    


CombatAircraft::CombatAircraft(CombatAircraft const &other):Aircraft(other)
{
    this->weapon_count=other.weapon_count;
    this->weapon_type=other.weapon_type;
    this->weapon_strength=other.weapon_strength;
}

void CombatAircraft::setWeaponCount(int wp)
{
    weapon_count=wp;
}

string CombatAircraft::getWeaponType()
{
    return weapon_type;

}
int CombatAircraft::getWeaponCount()
{
    return weapon_count;
}
int CombatAircraft::getWeaponStrength()
{
    return weapon_strength;
}


// StealthAircraft methods
StealthAircraft::StealthAircraft():Aircraft()
{
    cloak_status=false;
}
StealthAircraft::StealthAircraft(string identifier, int fuel_level, int health, AircraftStatus current_status, bool cloak_Status):Aircraft(identifier, fuel_level, health, current_status)
{
    if(current_status!=AircraftStatus::Airborne)
    {
        cloak_status=false;
    }
    else if (health<=10 || fuel_level<=15)
    {
        cloak_status=false;
    }
    
    else
    {
        cloak_status=cloak_Status;
    }
    if(cloak_status==true)
    {
        health-=10;
        fuel_level-=15;


    }


}
StealthAircraft::StealthAircraft(StealthAircraft const &other):Aircraft(other)
{
    this->cloak_status=other.cloak_status;
}

bool StealthAircraft::getCloakStatus()
{
    return cloak_status;
}

void StealthAircraft::activateCloak()
{ 
    if(cloak_status==true)
    {
        return;
    }
     
    if(getHealth()>=10 && getCurrentStatus() != AircraftStatus::Crashed)
    {
        setHealth(getHealth()-10);
        
        if(getFuelLevel()>=15&&getHealth()!=0)
        {
            cloak_status=true;
            setfuellevel(getFuelLevel()-15);
        }

        if(getHealth()==0)
        {
            setcurrentstatus(AircraftStatus::Crashed);
            cloak_status=false;
        }
        if(getFuelLevel()==0)
        {
            setcurrentstatus(AircraftStatus::Crashed);
            cloak_status=false;
            setHealth(0);
        }

    }
    else
    {
        cloak_status=false;
    }

}
void StealthAircraft::deactivateCloak()
{
    cloak_status=false;
}

void StealthAircraft::takeOff()
{
    Aircraft::takeOff();
    deactivateCloak();
}
void StealthAircraft::land()
{
    Aircraft::land();
    deactivateCloak();
}

StealthAircraft StealthAircraft::operator!()
{
    int initial_fuel=getFuelLevel();
    if(cloak_status==true)
    {
        cloak_status=false;
        return *(this);
    }
    if(getCurrentStatus()==AircraftStatus::Crashed)
    {
        return *(this);
    }
    else if(cloak_status==false && getCurrentStatus()==AircraftStatus::Airborne)
    {
        if(getHealth()>=10 && getFuelLevel()>=15)
        {
            cloak_status=true;
            setHealth(getHealth()-10);
            setfuellevel(getFuelLevel()-15);

        }

    }
    if(getHealth()==0)
    {
        setcurrentstatus(AircraftStatus::Crashed);
        cloak_status=false;
        setfuellevel(initial_fuel);


    }
    if(getFuelLevel()==0 || getFuelLevel()<15)
    {
        setcurrentstatus(AircraftStatus::Crashed);
        setfuellevel(0);
        cloak_status=false;
        setHealth(0);

    }
    return *(this);
}
void StealthAircraft::print(ostream& COUT)
{
    Aircraft::print(COUT);
    if(cloak_status==true)
    {
        COUT<<"Cloak Status: "<<"On"<<"\n";
    }
    else
    {
        COUT<<"Cloak Status: "<<"Off"<<"\n";
    }
}


// AbductorCraft methods
AbductorCraft::AbductorCraft()
{
    abductee_capacity=0;
    abductee_count=0;
}
AbductorCraft::AbductorCraft(string identifier, int fuel_level, int health, AircraftStatus current_status,bool cloak_Status, int abductee_count1, int abductee_cap):Aircraft(identifier,fuel_level,health,current_status),StealthAircraft(identifier,fuel_level,health,current_status,cloak_Status)
{
    if(abductee_count1<0)
    {
        abductee_count1=0;
    }

    
    abductee_count=abductee_count1;
    if(abductee_cap<0)
    {
        abductee_cap=abductee_count;
    }
    abductee_capacity=abductee_cap;


}
AbductorCraft::AbductorCraft(AbductorCraft const &other):Aircraft(other),StealthAircraft(other)
{
    this->abductee_capacity=other.abductee_capacity;
    this->abductee_count=other.abductee_count;
}

int AbductorCraft::getAbducteeCount()
{
    return abductee_count;
}

int AbductorCraft::getAbducteeCapacity()
{
    return abductee_capacity;
}

bool AbductorCraft::operator>(AbductorCraft obj)
{
    double ratioac1=static_cast<double>(this->abductee_count)/static_cast<double>(this->abductee_capacity);
    double ratioac2=static_cast<double>(obj.abductee_count)/static_cast<double>(obj.abductee_capacity);

    if(ratioac1>ratioac2)
    {
        return true;

    }
    else
    {
        return false;
    }

}

AbductorCraft AbductorCraft::operator+=(int num)
{
    if(this->getCurrentStatus()==AircraftStatus::Airborne)
    {

        this->abductee_count+=num;
        if(this->abductee_count>this->abductee_capacity)
        {
            this->abductee_count=abductee_capacity;
        }
        return *(this);
    }
    else
    {
        Aircraft::operator+=(num);
        return *(this);
    }
}

AbductorCraft AbductorCraft::operator-=(int num)
{
    if(this->getCurrentStatus()==AircraftStatus::Airborne)
    {
        this->abductee_count-=num;
        if(this->abductee_count<0)
        {
            this->abductee_count=0;
        }
        return *(this);
    }
    else
    {
        Aircraft::operator-=(num);
        return *(this);
    }
}

AbductorCraft AbductorCraft::operator&(AbductorCraft &obj)
{
    if(this->getCurrentStatus()!=AircraftStatus::Airborne || obj.getCurrentStatus()!=AircraftStatus::Airborne)
    {
        return *(this);

    }
    if(this->getAbducteeCapacity()>obj.getAbducteeCapacity())
    {
        this->setfuellevel(this->getFuelLevel()+obj.getFuelLevel());
        this->setHealth(this->getHealth()+obj.getHealth());
        this->abductee_count+=obj.abductee_count;
        this->abductee_capacity+=obj.abductee_capacity;
        if(this->getHealth()>100)
        {
            this->setHealth(100);
        }
        if(this->getFuelLevel()>100)
        {
            this->setfuellevel(100);
        }
        !obj;
        obj.setfuellevel(0);
        obj.setHealth(0);
        obj.setcurrentstatus(AircraftStatus::Crashed);
        obj.abductee_count=0;
        obj.abductee_capacity=0;
        

        return *(this);

    }
    else
    {
        
        obj.setfuellevel(obj.getFuelLevel()+this->getFuelLevel());
        obj.setHealth(obj.getHealth()+this->getHealth());
        obj.abductee_count+=this->abductee_count;
        obj.abductee_capacity+=this->abductee_capacity;
        if(obj.getHealth()>100)
        {
            obj.setHealth(100);
        }
        if(obj.getFuelLevel()>100)
        {
            obj.setfuellevel(100);
        }

        !*(this);
        this->setfuellevel(0);
        this->setHealth(0);
        this->setcurrentstatus(AircraftStatus::Crashed);
        this->abductee_count=0;
        this->abductee_capacity=0;

        return *(this);

    }




    

    
}

void AbductorCraft::print(ostream &COUT)
{
    StealthAircraft::print(COUT);
    COUT<<"Abductee Count: "<<abductee_count<<endl;
    COUT<<"Abductee Capacity: "<<abductee_capacity<<endl;

}




// GuardianCraft methods

GuardianCraft::GuardianCraft():Aircraft(),StealthAircraft(),CombatAircraft()
{
    kill_count=0;


}
GuardianCraft::GuardianCraft(string identifier, int fuel_level, int health, AircraftStatus current_status,string weapon_type, int weapon_count, int weapon_strength, bool cloak_status, int kill_counts):Aircraft(identifier, fuel_level, health,current_status),CombatAircraft(identifier,fuel_level, health,current_status,weapon_type,weapon_count,weapon_strength),StealthAircraft(identifier,fuel_level,health,current_status,cloak_status)
{
    if(kill_counts<0)
    {
        kill_counts=0;
    }
    kill_count=kill_counts;
}

GuardianCraft::GuardianCraft(GuardianCraft const &other):Aircraft(other), CombatAircraft(other),StealthAircraft(other) 
{
    this->kill_count=other.kill_count;
}

GuardianCraft::GuardianCraft(CombatAircraft const &combat_aircraft):CombatAircraft(combat_aircraft)
{
    this->kill_count=kill_count;
    int num=getWeaponCount();
    setWeaponCount(num);

}



void GuardianCraft::setKillCount(int kc)
{
    kill_count=kc;
}
int GuardianCraft::getKillCount()
{
    return kill_count;

}

bool GuardianCraft::operator*=(AbductorCraft &obj)
{
    bool flag1=false;
    bool flag2=false;
    bool flag3=false;
    if(this->getCurrentStatus()==AircraftStatus::Airborne && obj.getCurrentStatus()==AircraftStatus::Airborne)
    {
        flag1=true;
    }
    if(this->getWeaponCount()>0 && obj.getAbducteeCount()==0)
    {
        flag2=true;

    }
    if(obj.getCloakStatus()!=true)
    {
        flag3=true;
    }
    if(flag1==true && flag2==true && flag3==true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

GuardianCraft GuardianCraft::operator*(AbductorCraft &obj)
{
    if(*(this)*=obj)
    {
        obj.setHealth(obj.getHealth()-this->getWeaponStrength());
        if(obj.getHealth()<0 || obj.getHealth()==0)
        {
            obj.setHealth(0);
            obj.setcurrentstatus(AircraftStatus::Crashed);
            this->kill_count+=1;
            
        }
        int temp_count=this->getWeaponCount()-1;
        this->setWeaponCount(temp_count);
        return *(this);
        
    }
    else
    {
        return *(this);
    }
}



void GuardianCraft::print(ostream& COUT)
{
    CombatAircraft::print(COUT);
    if(getCloakStatus()==true)
    {
        COUT<<"Cloak Status: "<<"On"<<"\n";
    }
    else
    {
        COUT<<"Cloak Status: "<<"Off"<<"\n";
    }
    COUT<<"Kill Count: "<<kill_count<<endl;

   
}




