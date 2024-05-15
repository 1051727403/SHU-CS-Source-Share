#ifndef BUILDING_H
#define BUILDING_H
#include<iostream>
class Building
{
protected:
    int _floor;
    int _room;
    double _squar;
    void showBuilding();
public:
    Building():_floor(0),_room(0),_squar(0) {}
    Building(int floor,int room, double squar):_floor(floor),_room(room),_squar(squar) {}
};

class Housing:public Building
{
private:
    int _bedroom;
    int _toilet;
public:
    Housing():Building(),_bedroom(0),_toilet(0) {}
    Housing(int floor = 0,int room = 0,double squar = 0,int bedroom = 0,int toilet = 0):Building(floor,room,squar),_bedroom(bedroom),_toilet(toilet) {}
    void show();
};

class OfficeBuilding:public Building
{
private:
    int _tel;
    int _fireExtinguisher;
public:
    OfficeBuilding():Building(),_tel(0),_fireExtinguisher(0) {}
    OfficeBuilding(int floor = 0,int room = 0,double squar = 0,int tel = 0,int fireExtinguisher = 0):Building(floor,room,squar),_tel(tel),_fireExtinguisher(fireExtinguisher) {}
    void show();
};

#endif // BUILDING_H
