/* Assignment: Final Project
 * Class: CSC 121
 * Author: Shiza Ahmed
 */

#include <iostream>
#include <cmath>
#include <string>
#include <climits>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "templateInput2.h"

using namespace std;

const int ADD=1;
const int DELETE=2;
const int FIND=3;
const int DISPLAY=4;
const int SORT=5;
const int QUIT=6;

class Planet
{
        private:
                string name;
                double mass, diameter;
        public:
                double Volume();
                double SurfaceArea();
                double Density();
                double Acceleration();
                bool SetMass(double x);
                bool SetDiameter(double x);
                bool SetName(string x);
                double GetMass();
                double GetDiameter();
                string GetName();
                Planet();
                Planet(double m, double d);
};
Planet::Planet() {
        mass=0.0;
        diameter=0.0;
}
Planet::Planet(double m, double d) {
        if (SetMass(m)==false || SetDiameter(d)==false) {
                mass = 0.0;
                diameter = 0.0;
        }
}
double Planet::Volume()
{
        return (4.0/3.0) * M_PI * ((diameter/2) * (diameter/2) * (diameter/2));
}
double Planet::SurfaceArea()
{
        return 4 * M_PI * ((diameter/2) * (diameter/2));
}
double Planet::Density()
{
        return mass / Volume();
}
double Planet::Acceleration()
{
        return (.0000000000667408 * mass) / ((diameter/2) * (diameter/2));
}
bool Planet::SetMass(double x)
{
        bool rv=false;
        if (x>=0.0) {
                mass=x;
                rv=true;
        }
        return rv;
}
bool Planet::SetDiameter(double x)
{
        bool rv=false;
        if (x>=0.0) {
                diameter=x;
                rv=true;
        }
        return rv;
}
bool Planet::SetName(string x)
{
        Planet::name =x;
        return false;
}
double Planet::GetMass()
{
        return mass;
}
double Planet::GetDiameter()
{
        return diameter;
}
string Planet::GetName()
{
        return name;
}
void Input(Planet& p)
{
        while (p.SetMass(ReadValue<double>("Enter mass in grams: ") )==false ) {
                cerr << "Error! Mass must be >=0.0\n";
        }
        while (p.SetDiameter(ReadValue<double>("Enter diameter in centimeters: ") )==false ) {
                cerr << "Error! Diameter must be >=0.0\n";
        }
}
// original vector assignment ^
void ProcessAdd(vector<Planet>& planets);
void ProcessDelete(vector<Planet>& planets);
void ProcessFind(vector<Planet>& planets);
void ProcessDisplay(vector<Planet>& planets);
void ProcessSort(vector<Planet>& planets);
void ProcessQuit(vector<Planet>& planets);

bool Insert(Planet p, int position, vector<Planet>& planets) {
        bool ft=false;
        if (position >=0.0 && position <= planets.size()) {
                ft=true;
                planets.push_back(planets[planets.size() - 1]);
                for (int i=planets.size()-1;i>=position;i--) {
                        planets[i+1]=planets[i];
                }
                planets[position]=p;
        }
        else if (position>planets.size()) {
                planets.resize(position+1);
                planets.push_back(p);
        }
        return ft;
}
bool DoesFileExist(string fileName)
{
        bool rv=false;
        ifstream in(fileName);
        if (in.is_open()==1) {
                rv=true;
                in.close();
        }
        return rv;
}
void ProcessAdd(vector<Planet>& planets)
{
        string name = "";
        double mass, diameter;
        int position;
        bool ft=false;
        cout << "Enter name of planet. ";
        cin >> name;
        Planet p;
        Input(p);
        position = ReadValue<int>("Enter the position of the planet: ",0,100);
        p.SetName(name);
        cout << "Planet was added to list. " << endl;
        cout << "Volume of the planet is: " << p.Volume() << " cubic centimeters.\n";
        cout << "Surface area of the planet is: " << p.SurfaceArea() << " squared centimeters.\n";
        cout << "Density of the planet is: " << p.Density() << " grams per cubic centimeter.\n";
        cout << "Acceleration due to gravity is: " << p.Acceleration() << "m/s^2.\n";
        Insert(p,position,planets);
}
void ProcessDelete(vector<Planet>& planets)
{
        cout << "Enter the planet you wish to delete: ";
        string name = "";
        cin >> name;
        int j=-1;
        for (int i=0;i<planets.size();i++) {
                if (planets[i].GetName() == name)
                {
                        j=i;
                        cout << "Planet was deleted. " << endl;
                        break;
                }
        }
        if (j!=-1){
                planets.erase(planets.begin() + j);
        }
        else {
                cout << "Planet was not found, sorry." << endl;
        }
}
void ProcessFind(vector<Planet>& planets)
{
        string name;
        cout << "Enter the name of the planet: ";
        cin >> name;
        bool isFound = false;
        for (int i=0; i<planets.size(); i++) {
                if (planets[i].GetName() == name) {
                        isFound=true;
                        cout << "Diameter: " << planets[i].GetDiameter() << "\n";
                        cout << "Mass: " << planets[i].GetMass() << "\n";
                        cout << "Surface Area: " << planets[i].SurfaceArea() << "\n";
                        cout << "Volume: " << planets[i].Volume() << "\n";
                        cout << "Density: " << planets[i].Density() << "\n";
                        cout << "Acceleration: " << planets[i].Acceleration() << "\n";
                }
        }
        if (isFound==false) {
                cout << "Sorry. The planet you entered was not found." << endl;
        }
}
void ProcessDisplay(vector<Planet>& planets)
{
        for (Planet i : planets) {
                if (!i.GetName().empty()) {
                        cout << i.GetName() << "\n" << "Volume: " << i.Volume() << "\n" << "Surface Area: " << i.SurfaceArea() << "\n" << "Density: " << i.Density() << "\n" << "Acceleration: " << i.Acceleration() << "\n";
                }
        if (planets.empty()) {
                cout << "Sorry. No planets are in this list.\n" << endl;
        }
}
}
void ProcessSort(vector<Planet>& planets) {
        for (int i = 0; i < planets.size(); i++) {
                for (int j=0; j<planets.size() - 1; j++) {
                        if (!planets[j].GetName().empty()) {
                                if (!planets[j+1].GetName().empty()) {
                                        if(planets[j].GetName().substr(0,1) > planets[j+1].GetName().substr(0,1)) {
                                                swap(planets[j],planets[j+1]);
                                        }
                                        else if (planets[j].GetName().substr(0,1) == planets[j+1].GetName().substr(1,1)) {
                                                swap(planets[j],planets[j+1]);
                                        }
                                }
                        } else {
                                swap(planets[j],planets[j+1]);
                        }
                }
        }
}
void ProcessQuit(vector<Planet>& planets)
{
        ofstream outFile;
        ifstream inFile;
        string fileName;
        cout << "Enter output file name: ";
        cin >> fileName;
        if (DoesFileExist(fileName)) {
                string ans;
                cout << "This file already exists. Do you want to overwrite this file or append to it?"; //added extra function from past assignment to overwrite and append
                cin >> ans;
                if (ans == "overwrite") {
                        outFile.open(fileName);
                }
                else{
                        outFile.open(fileName,ios::app);
                }
        }
        else {
                outFile.open(fileName,ios::app);
                if (outFile.is_open()==1) {
                        for (int i=0; i<10; i++) {
                                outFile.width(10);
                                outFile.setf(ios::fixed | ios::left);
                                if (outFile.fail()==1) {
                                        cerr << "Error writing to file!\n";
                                }
                        }
                }
        }
                for (Planet& i: planets) {
                        if (!i.GetName().empty()) {
                                outFile << i.GetName() << "\n" << "Volume: " << i.Volume() << "\n" << "Surface Area: " << i.SurfaceArea() << "\n" << "Density: " << i.Density() << "\n" << "Acceleration: " << i.Acceleration() << "\n"; //sending to file
                        }
                }
}
int main() {

        int menuChoice=0.0;
        vector<Planet> planets;
        while (menuChoice!=QUIT) {
                cout << endl;
                cout << "1. Add a planet.\n2. Delete a planet.\n3. Find a planet.\n4. Display list of Planets.\n5. Sort list of planets.\n6. Quit.\nEnter a choice: ";
                cin >> menuChoice;
                switch (menuChoice) {
                        case ADD:
                                ProcessAdd(planets);
                                break;
                        case DELETE:
                                ProcessDelete(planets);
                                break;
                        case FIND:
                                ProcessFind(planets);
                                break;
                        case DISPLAY:
                                ProcessDisplay(planets);
                                break;
                        case SORT:
                                ProcessSort(planets);
                                break;
                        case QUIT:
                                ProcessQuit(planets);
                                break;
                        default:
                                break;
                        }
                }
        return 0;
}

s_ahmed75@ares:~/final$ g++ finalwclass.C -o f
s_ahmed75@ares:~/final$ ./f

1. Add a planet.
2. Delete a planet.
3. Find a planet.
4. Display list of Planets.
5. Sort list of planets.
6. Quit.
Enter a choice: 1 // testing add function
Enter name of planet. jupiter
Enter mass in grams: 30
Enter diameter in centimeters: 30
Enter the position of the planet: 5
Planet was added to list.
Volume of the planet is: 14137.2 cubic centimeters.
Surface area of the planet is: 2827.43 squared centimeters.
Density of the planet is: 0.00212207 grams per cubic centimeter.
Acceleration due to gravity is: 8.89877e-12m/s^2.

1. Add a planet.
2. Delete a planet.
3. Find a planet.
4. Display list of Planets.
5. Sort list of planets.
6. Quit.
Enter a choice: 1
Enter name of planet. mars
Enter mass in grams: 60
Enter diameter in centimeters: 60
Enter the position of the planet: 3
Planet was added to list.
Volume of the planet is: 113097 cubic centimeters.
Surface area of the planet is: 11309.7 squared centimeters.
Density of the planet is: 0.000530516 grams per cubic centimeter.
Acceleration due to gravity is: 4.44939e-12m/s^2.

1. Add a planet.
2. Delete a planet.
3. Find a planet.
4. Display list of Planets.
5. Sort list of planets.
6. Quit.
Enter a choice: 4
mars
Volume: 113097
Surface Area: 11309.7
Density: 0.000530516
Acceleration: 4.44939e-12
jupiter //stored position and put jupiter after mars
Volume: 14137.2
Surface Area: 2827.43
Density: 0.00212207
Acceleration: 8.89877e-12

1. Add a planet.
2. Delete a planet.
3. Find a planet.
4. Display list of Planets.
5. Sort list of planets.
6. Quit.
Enter a choice: 2
Enter the planet you wish to delete: mars //testing delete function
Planet was deleted.

1. Add a planet.
2. Delete a planet.
3. Find a planet.
4. Display list of Planets.
5. Sort list of planets.
6. Quit.
Enter a choice: 4 //checking to see if delete function ran properly
jupiter
Volume: 14137.2
Surface Area: 2827.43
Density: 0.00212207
Acceleration: 8.89877e-12

1. Add a planet.
2. Delete a planet.
3. Find a planet.
4. Display list of Planets.
5. Sort list of planets.
6. Quit.
Enter a choice: 1 // adding one more planet
Enter name of planet. pluto
Enter mass in grams: 35
Enter diameter in centimeters: 40
Enter the position of the planet: 1
Planet was added to list.
Volume of the planet is: 33510.3 cubic centimeters.
Surface area of the planet is: 5026.55 squared centimeters.
Density of the planet is: 0.00104445 grams per cubic centimeter.
Acceleration due to gravity is: 5.83982e-12m/s^2.

1. Add a planet.
2. Delete a planet.
3. Find a planet.
4. Display list of Planets.
5. Sort list of planets.
6. Quit.
Enter a choice: 1 //adding one more planet
Enter name of planet. mercury
Enter mass in grams: 40
Enter diameter in centimeters: 40
Enter the position of the planet: 2
Planet was added to list.
Volume of the planet is: 33510.3 cubic centimeters.
Surface area of the planet is: 5026.55 squared centimeters.
Density of the planet is: 0.00119366 grams per cubic centimeter.
Acceleration due to gravity is: 6.67408e-12m/s^2.

1. Add a planet.
2. Delete a planet.
3. Find a planet.
4. Display list of Planets.
5. Sort list of planets.
6. Quit.
Enter a choice: 4 //testing display function again
pluto
Volume: 33510.3
Surface Area: 5026.55
Density: 0.00104445
Acceleration: 5.83982e-12
mercury
Volume: 33510.3
Surface Area: 5026.55
Density: 0.00119366
Acceleration: 6.67408e-12
jupiter
Volume: 14137.2
Surface Area: 2827.43
Density: 0.00212207
Acceleration: 8.89877e-12

1. Add a planet.
2. Delete a planet.
3. Find a planet.
4. Display list of Planets.
5. Sort list of planets.
6. Quit.
Enter a choice: 5 //testing sort

1. Add a planet.
2. Delete a planet.
3. Find a planet.
4. Display list of Planets.
5. Sort list of planets.
6. Quit.
Enter a choice: 4 //displaying to see if sort worked
jupiter
Volume: 14137.2
Surface Area: 2827.43
Density: 0.00212207
Acceleration: 8.89877e-12
mercury
Volume: 33510.3
Surface Area: 5026.55
Density: 0.00119366
Acceleration: 6.67408e-12
pluto
Volume: 33510.3
Surface Area: 5026.55
Density: 0.00104445
Acceleration: 5.83982e-12

1. Add a planet.
2. Delete a planet.
3. Find a planet.
4. Display list of Planets.
5. Sort list of planets.
6. Quit.
Enter a choice: 6 //finally testing quit function
Enter output file name: fitty
This file already exists. Do you want to overwrite this file or append to it?overwrite //choosing to overwrite existing file
s_ahmed75@ares:~/final$ cat fitty //display file to see if it transferred
jupiter //it did!!!
Volume: 14137.2
Surface Area: 2827.43
Density: 0.00212207
Acceleration: 8.89877e-12
mercury
Volume: 33510.3
Surface Area: 5026.55
Density: 0.00119366
Acceleration: 6.67408e-12
pluto
Volume: 33510.3
Surface Area: 5026.55
Density: 0.00104445
Acceleration: 5.83982e-12
s_ahmed75@ares:~/final$ exit
exit
Script done, file is final2.txt

