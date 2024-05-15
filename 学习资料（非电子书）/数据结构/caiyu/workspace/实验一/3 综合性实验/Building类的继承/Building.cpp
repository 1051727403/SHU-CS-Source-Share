#include<iostream>
#include<ostream>
#include"Building.h"

void Building::showBuilding()
{
    std::cout<<"floor(s):              "<<this->_floor<<std::endl;
    std::cout<<"room(s):               "<<this->_room<<std::endl;
    std::cout<<"squar(s):              "<<this->_squar<<std::endl;
}

void Housing::show()
{
    std::cout<<"*********** Housing::show() ************      "<<std::endl;
    std::cout<<std::endl;
    Building::showBuilding();
    std::cout<<"bedroom(s):            "<<this->_bedroom<<std::endl;
    std::cout<<"toilet(s):             "<<this->_toilet<<std::endl<<std::endl;
}

void OfficeBuilding::show()
{
    std::cout<<"******* OfficeBuilding::show() *********    "<<std::endl;
    std::cout<<std::endl;
    Building::showBuilding();
    std::cout<<"tel(s):                "<<this->_tel<<std::endl;
    std::cout<<"fire extinguisher(s):  "<<this->_fireExtinguisher<<std::endl<<std::endl;
}
