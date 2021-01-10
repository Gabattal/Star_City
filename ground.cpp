#include <iostream>
#include "ground.h"
#include "lampadaire.h"

#define MAP_WIDTH 1920
#define MAP_HEIGHT 960

Ground::Ground(Pos unit, Svgfile *svgout, Lampadaire *lamp, std::mt19937 *rand)
{
    this->m_unit = unit;
    this->svgout = svgout;
    this->lampadaire = lamp;
    this->rand = rand;
}

Ground::~Ground() {}

void Ground::makeGround(int multRoad, int multSquare, int seed, int freq)
{
    Couleur mapColor = Couleur{50,50,50};
    Couleur roadColor = Couleur{30,30,30};
    Couleur walkColor = Couleur{40,40,40};
    Couleur dashColor = Couleur{255,255,255};
    Couleur black = Couleur{0,0,0};

    float randRoad = 0.9f;
    float multDash = 8.0f;

    svgout->addRect(Pos{0,0}, Pos{MAP_WIDTH,0}, Pos{MAP_WIDTH,MAP_HEIGHT}, Pos{0,MAP_HEIGHT},mapColor);

    Pos unitx = Pos{m_unit.x, 0.0f};
    Pos unity = Pos{0.0f, m_unit.y};

    Pos uniti = Pos{m_unit.x, -m_unit.y};

    for (int x=0; x<multRoad+1; x++)
    {
        int maxY = ceil(MAP_HEIGHT/(m_unit.y*multSquare));
        for (int y=0; y<maxY+1; y++)
        {
            Pos startPos = unitx*multSquare*x+unity*multSquare*y;
            if ((x+y)%2==1)
            {


                startPos = startPos+unity*multSquare;

                if (util::alea(0.0f, 1.0f, *rand) < randRoad)
                {
                    svgout->addRect(startPos+unitx, startPos-unity, startPos-unity+uniti*(multSquare-1), startPos+unitx+uniti*(multSquare-1),roadColor);
                    svgout->addRect(startPos+unitx, startPos+unitx*2.0f, startPos+unitx+uniti*(multSquare-1)+unity, startPos+unitx+uniti*(multSquare-1),walkColor);
                    svgout->addRect(startPos-unity, startPos-unity*2.0f, startPos-unity+uniti*(multSquare-1)-unitx, startPos-unity+uniti*(multSquare-1),walkColor);

                    for (int i=1; i<multSquare-1; i++)
                    {
                        if(i==0)
                        {
                            lampadaire->lamp(startPos+uniti*i);
                            lampadaire->lamp(startPos-m_unit*1.02f+uniti*i);
                        }
                        else
                        {
                            lampadaire->lamp(startPos+uniti*i-uniti/(multSquare*multSquare));
                            lampadaire->lamp(startPos-m_unit*1.02f+uniti*i-uniti/(multSquare*multSquare));
                        }
                    }

                    for (int i=multDash/2; i<multSquare*multDash-multDash/2-1 ; i++)
                    {
                        if(i%2==1)
                        {
                            float multStart= ((float)i+0.5f)/multDash;
                            float multEnd = ((float)i+1.5f)/multDash;
                            svgout->addRect(startPos+m_unit*0.01+uniti*multStart, startPos-m_unit*0.01+uniti*multStart, startPos-m_unit*0.01+uniti*multEnd, startPos+m_unit*0.01+uniti*multEnd,dashColor);
                        }
                    }

                }
                else
                {
                    svgout->addRect(startPos+unitx, startPos-unity, startPos-unity*2.0f, startPos+unitx*2.0f,walkColor);
                    svgout->addRect(startPos+unitx+uniti*(multSquare-1), startPos-unity+uniti*(multSquare-1), startPos-m_unit+uniti*(multSquare-1), startPos+m_unit+uniti*(multSquare-1),walkColor);

                    lampadaire->lamp(startPos+m_unit);
                }
            }
        }
    }

    for (int x=0; x<multRoad+1; x++)
    {
        int maxY = ceil(MAP_HEIGHT/(m_unit.y*multSquare));
        for (int y=0; y<maxY+1; y++)
        {
            Pos startPos = unitx*multSquare*x+unity*multSquare*y;
            if ((x+y)%2==0)
            {

                svgout->addRect(startPos+unitx, startPos+unity, startPos-unitx, startPos-unity,roadColor); // carré


                if (util::alea(0.0f, 1.0f, *rand) < randRoad)
                {
                    svgout->addRect(startPos+unitx, startPos+unity, startPos+unity+m_unit*(multSquare-1), startPos+unitx+m_unit*(multSquare-1),roadColor);

                    svgout->addRect(startPos+unitx, startPos+unitx*2.0f, startPos+unitx+m_unit*(multSquare-1)-unity, startPos+unitx+m_unit*(multSquare-1),walkColor);
                    svgout->addRect(startPos+unity, startPos+unity*2.0f, startPos+unity+m_unit*(multSquare-1)-unitx, startPos+unity+m_unit*(multSquare-1),walkColor);

                    for (int i=0; i<multSquare; i++)
                    {
                        if(i==0)
                        {
                            lampadaire->lamp(startPos+m_unit*i);
                            lampadaire->lamp(startPos-uniti*1.02f+m_unit*i);
                        }
                        else
                        {
                            lampadaire->lamp(startPos+m_unit*i-m_unit/(multSquare*multSquare));
                            lampadaire->lamp(startPos-uniti*1.02f+m_unit*i-m_unit/(multSquare*multSquare));
                        }
                    }



                    for (int i=multDash/2; i<multSquare*multDash-multDash/2-1 ; i++)
                    {
                        if(i%2==1)
                        {
                            float multStart= ((float)i+0.5f)/multDash;
                            float multEnd = ((float)i+1.5f)/multDash;
                            svgout->addRect(startPos+uniti*0.01+m_unit*multStart, startPos-uniti*0.01+m_unit*multStart, startPos-uniti*0.01+m_unit*multEnd, startPos+uniti*0.01+m_unit*multEnd,dashColor);
                        }

                    }
                }
                else
                {

                    //lamp(startPos-uniti*1.02f+unit*i, unit, svgout, Couleur{0, 0, 0});
                    svgout->addRect(startPos+unitx, startPos+unity, startPos+unity*2.0f, startPos+unitx*2.0f,walkColor);
                    svgout->addRect(startPos+unitx+m_unit*(multSquare-1), startPos+unity+m_unit*(multSquare-1), startPos-uniti+m_unit*(multSquare-1), startPos+uniti+m_unit*(multSquare-1),walkColor);

                    for(int i=0; i<2; i++)
                    {
                        lampadaire->lamp(startPos+m_unit*(multSquare-1)-uniti*i);

                        lampadaire->lamp(startPos-uniti*i);
                    }

                }
            }

        }

    }
}
