#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include "svgfile.h"
#include "couleur.h"
#include "util.h"
#include "coords.h"
#include "building.h"
#include "lampadaire.h"
#include "ground.h"
#include "cloud.h"

#define UNIT 76.0f

#define MAP_WIDTH 1920
#define MAP_HEIGHT 960


void debug(Pos base, Pos unit,Svgfile &svgout)
{
    Pos uniti = unit;
    uniti.y = -unit.y;

    float debugSize = 0.8f;

    base = base + Pos{0.0f, (unit.y*debugSize-unit.y)};

    svgout.addRect(base, base-unit*debugSize, base+(unit*-1+uniti)*debugSize, base+uniti*debugSize, Couleur{0,255,0});
}



int main()
{

    int modifScene = 0;
    int multRoad = 0 ;
    int multSquare = 0;
    float light = 0;
    int time = 0;
    int nbcloud = 0;
    int heightCloud=0;
    int widthCloud=0;
    float freq;
    int seed1;
    int seed2;
    int seed3;
    int choix=0;
    int choix2=0;

    do
    {
        std::cout << "1 : Create new scene " << std::endl;
        std::cout << "2 : Modify scene " << std::endl;
        std::cout << "3 : Exit " << std::endl;
        std::cin>>(choix);

        switch(choix)
        {

        case 1:
        {


            std::cout << "Seed ground: " << std::endl;
            std::cin>>seed1;
            std::mt19937 rand{seed1};

            do
            {
                std::cout << "Size city: (between 4 and 10) " << std::endl;
                std::cin>>multRoad;
            }
            while (multRoad<4 || multRoad>10);

            do
            {
                std::cout << "Number of buildings in a block: (between 4 and 7) " << std::endl;
                std::cin>>multSquare;
            }
            while (multSquare<4 || multSquare>7);




            std::cout << "Seed building: " << std::endl;
            std::cin>>seed1;
            std::mt19937 rand2{seed2};
            do
            {
                std::cout << "Frequence of buildings: (between 0 and 1) " << std::endl;
                std::cin>>freq;
            }
            while (freq<0 || freq>1);

            do
            {
                std::cout << "Time: (press '1' for evening or '2' for night) " << std::endl;
                std::cin>>time;
                if (time==1)
                {
                    light = 0.3f;
                }
                if (time==2)
                {
                    light = 0.05f;
                }
            }
            while (time!=1 && time!=2);



            std::cout << "Seed cloud: " << std::endl;
            std::cin>>seed1;
            std::mt19937 rand3{seed3};

            do
            {
                std::cout << "Frequence of clouds: (between 0 and 1000) " << std::endl;
                std::cin>>nbcloud;
            }
            while (nbcloud<0 || nbcloud>1000);

            do
            {
                std::cout << "Width clouds MAX: (between 250 and 1000) " << std::endl;
                std::cin>>widthCloud;
            }
            while (widthCloud<250 || widthCloud>1000);

            do
            {
                std::cout << "Height clouds MAX: (between 10 and 30) " << std::endl;
                std::cin>>heightCloud;
            }
            while (heightCloud<10 || heightCloud>30);


            Svgfile svgout("output.svg", MAP_WIDTH, MAP_HEIGHT);

            /* ----- [ Configuration ] ----- */


            Couleur black = Couleur{20,20,20,0.9f};




            /* ----- [ End of configuration ] ----- */


            Pos unit;
            unit.x = (double)MAP_WIDTH/multRoad/multSquare;
            unit.y = unit.x/2.0f;

            Pos unitx = Pos{unit.x, 0.0f};
            Pos unity = Pos{0.0f, unit.y};



            Building building(unit, &svgout, &rand2);

            Lampadaire lampadaire(unit, &svgout);

            Ground ground(unit, &svgout, &lampadaire, &rand);

            ground.makeGround( multRoad, multSquare, seed1, freq);

            Cloud cloud(&svgout, &rand3);



            int maxY = ceil(MAP_HEIGHT/unit.y);

            for (int y=2; y<maxY+5; y++)
            {
                for (int x=0; x<multRoad*multSquare/2+1; x++)
                {

                    Pos startPos;
                    if (y%2 == 0)
                    {
                        startPos = unitx*x*2 - unity + unity*y ;
                    }
                    else
                    {
                        startPos = unitx*x*2 - unity + unity*y + unitx;
                    }

                    if ((0 == (y/2 - 1 - x)%multSquare) || (0 == ((y-1)/2 + x)%multSquare))
                    {
                        continue;
                    }

                    if ((0 == (y/2 - 2 - x)%multSquare) || (0 == ((y-3)/2 + x)%multSquare))
                    {
                        continue;
                    }

                    //
                    if (util::alea(0.0f, 1.0f, rand) < freq)
                    {
                        int colorInt = (float)y/maxY*120+30;
                        building.generateSvg(startPos-unity, Couleur{colorInt, colorInt, colorInt}, multRoad, multSquare, light);
                    }
                }
            }
            cloud.makeCloud(nbcloud,heightCloud, widthCloud);
            modifScene = 1;
            break;
        }
        case 2:
            if(modifScene == 0)
            {
                std::cout<<"Vous n avez pas de scene a modifier"<<std::endl;
            }
            else
            {


                do
                {
                std::cout<<"1 Modify seed ground"<<std::endl;
                std::cout<<"2 Modify size city"<<std::endl;
                std::cout<<"3 Modify number of buildings in a block"<<std::endl;

                std::cout<<"4 Modify seed building"<<std::endl;
                std::cout<<"5 Modify buildings frequency"<<std::endl;
                std::cout<<"6 Modify time"<<std::endl;

                std::cout<<"7 Modify seed cloud"<<std::endl;
                std::cout<<"8 Modify clouds frequency"<<std::endl;
                std::cout<<"9 Modify clouds width MAX"<<std::endl;
                std::cout<<"10 Modify clouds height MAX"<<std::endl;

                std::cout<<"11 Apply modifications"<<std::endl;
                std::cout<<"12 Stop modifications"<<std::endl;
                std::cin>>(choix2);


                switch(choix2)
                {
                case 1:
                {
                    std::cout << "Seed ground: " << std::endl;
                    std::cin>>seed1;
                    std::mt19937 rand{seed1};
                    break;
                }
                case 2:
                    do
                    {
                        std::cout << "Size city: (between 4 and 10) " << std::endl;
                        std::cin>>multRoad;
                    }
                    while (multRoad<4 || multRoad>10);
                    break;

                case 3:
                    do
                    {
                        std::cout << "Number of buildings in a block: (between 4 and 7) " << std::endl;
                        std::cin>>multSquare;
                    }
                    while (multSquare<4 || multSquare>7);
                    break;

                case 4:
                {
                    std::cout << "Seed building: " << std::endl;
                    std::cin>>seed2;
                    std::mt19937 rand{seed2};
                    break;
                }

                case 5:
                    do
                    {
                        std::cout << "Frequence of buildings: (between 0 and 1) " << std::endl;
                        std::cin>>freq;
                    }
                    while (freq<0 || freq>1);
                    break;

                case 6:

                    do
                    {
                        std::cout << "Time: (press '1' for evening or '2' for night) " << std::endl;
                        std::cin>>time;
                        if (time==1)
                        {
                            light = 0.3f;
                        }
                        if (time==2)
                        {
                            light = 0.05f;
                        }
                    }
                    while (time!=1 && time!=2);
                    break;

                case 7:
                {
                    std::cout << "Seed cloud: " << std::endl;
                    std::cin>>seed3;
                    std::mt19937 rand{seed3};
                    break;
                }

                case 8:
                    do
                    {
                        std::cout << "Frequence of clouds: (between 0 and 1000) " << std::endl;
                        std::cin>>nbcloud;
                    }
                    while (nbcloud<0 || nbcloud>1000);
                    break;

                case 9:
                    do
                    {
                        std::cout << "Width clouds MAX: (between 250 and 1000) " << std::endl;
                        std::cin>>widthCloud;
                    }
                    while (widthCloud<250 || widthCloud>1000);
                    break;

                case 10:
                    do
                    {
                        std::cout << "Height clouds MAX: (between 10 and 30) " << std::endl;
                        std::cin>>heightCloud;
                    }
                    while (heightCloud<10 || heightCloud>30);
                    break;

                case 11:
                    {


                    std::mt19937 rand{seed1};
                    std::mt19937 rand2{seed2};
                    std::mt19937 rand3{seed3};

                    Svgfile svgout("output.svg", MAP_WIDTH, MAP_HEIGHT);

                    /* ----- [ Configuration ] ----- */


                    Couleur black = Couleur{20,20,20,0.9f};




                    /* ----- [ End of configuration ] ----- */


                    Pos unit;
                    unit.x = (double)MAP_WIDTH/multRoad/multSquare;
                    unit.y = unit.x/2.0f;

                    Pos unitx = Pos{unit.x, 0.0f};
                    Pos unity = Pos{0.0f, unit.y};

                    Building building(unit, &svgout, &rand2);

                    Lampadaire lampadaire(unit, &svgout);

                    Ground ground(unit, &svgout, &lampadaire, &rand);

                    ground.makeGround( multRoad, multSquare, seed1, freq);

                    Cloud cloud(&svgout, &rand3);



                    int maxY = ceil(MAP_HEIGHT/unit.y);

                    for (int y=2; y<maxY+5; y++)
                    {
                        for (int x=0; x<multRoad*multSquare/2+1; x++)
                        {

                            Pos startPos;
                            if (y%2 == 0)
                            {
                                startPos = unitx*x*2 - unity + unity*y ;
                            }
                            else
                            {
                                startPos = unitx*x*2 - unity + unity*y + unitx;
                            }

                            if ((0 == (y/2 - 1 - x)%multSquare) || (0 == ((y-1)/2 + x)%multSquare))
                            {
                                continue;
                            }

                            if ((0 == (y/2 - 2 - x)%multSquare) || (0 == ((y-3)/2 + x)%multSquare))
                            {
                                continue;
                            }

                            //
                            if (util::alea(0.0f, 1.0f, rand) < freq)
                            {
                                int colorInt = (float)y/maxY*120+30;
                                building.generateSvg(startPos-unity, Couleur{colorInt, colorInt, colorInt}, multRoad, multSquare, light);
                            }
                        }
                    }
                    cloud.makeCloud(nbcloud,heightCloud, widthCloud);
                    modifScene = 1;
                    break;
                }
                case 12:
                   break ;
                }
                }while(choix2 !=12);


            case 3:
                break;

            }

        }
    }
        while(choix !=3);
    }




