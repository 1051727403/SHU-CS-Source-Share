#include <iostream>
#include"Building.h"

using namespace std;

int main()
{
    Housing house(5,7,200,0,2);
    OfficeBuilding office(8,12,800,12);

    house.show();
    office.show();

    return 0;
}
