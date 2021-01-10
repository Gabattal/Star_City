#include "building.h"
#define MAP_WIDTH 1920

Building::Building(Pos unit, Svgfile *svgout, std::mt19937 *rand)
{
    this->unitD = unit;
    this->svgout = svgout;
    this->rand = rand;
}

Building::~Building()
{
    //dtor
}

void Building::generateSvg(Pos base, Couleur color, int multRoad, int multSquare, float light)
{

    int h=0;
    Pos uniti = unitD;
    uniti.y = -unitD.y;

    Pos unitx = Pos{unitD.x, 0.0f};
    Pos unity = Pos{0.0f, unitD.y};
    float constante =0.4f;

    float buildingHeight = util::alea(0.0f, 1.4f, *rand);
    buildingHeight = 2.5f + pow(buildingHeight,7.0f);
    float buildingWidth = util::alea(0.4f, 0.9f, *rand);
    //float buildingWidth = 0.6f;
    float windowHeight = 0.25f;
    float entreeHeight = 0.6f;
    float espaceHeight = 0.04f;
    float hauteurAntenne = 2.0f;
    float largeurAntenne = 0.2f;

    Pos vecHauteurAntenne = unity*-hauteurAntenne;


    base = base + Pos{0.0f, (unitD.y*buildingWidth-unitD.y)};

    Pos vecHeight = unity*-buildingHeight;
    Pos vecWindowHeight = unity*-windowHeight;
    Pos vecEntreeHeight = unity*-entreeHeight;
    Pos vecEspaceHeight = unity*-espaceHeight;
    Pos vecConst = unity*-constante;

    Pos vechauteurAntenne = Pos{0.0f, -(double)MAP_WIDTH/multRoad/multSquare*0.25};
    Pos vecLargeurAntenne = Pos{(double)MAP_WIDTH/multRoad/multSquare*0.02f, -(double)MAP_WIDTH/multRoad/multSquare*0.02f/2};
    Pos vecLargeurAntenne2 = Pos{-(double)MAP_WIDTH/multRoad/multSquare*0.02f, -(double)MAP_WIDTH/multRoad/multSquare*0.02f/2};

    Pos unit = unitD*buildingWidth;
    uniti = uniti*buildingWidth;

    svgout->addRect(base, base+uniti, base+uniti+vecHeight,base+vecHeight, color+Couleur{80,40,0});
    svgout->addRect(base, base-unit, base-unit+vecHeight,base+vecHeight, color-Couleur{30,30,10});


    // fenêtres

    svgout->addRect(base-unit*0.1f+vecEntreeHeight, base-unit*0.9f+vecEntreeHeight, base-unit*0.9f+vecEntreeHeight-vecEspaceHeight, base-unit*0.1f+vecEntreeHeight-vecEspaceHeight, Couleur(0,0,0));
    svgout->addRect(base+uniti*0.1f+vecEntreeHeight, base+uniti*0.9f+vecEntreeHeight, base+uniti*0.9f+vecEntreeHeight-vecEspaceHeight, base+uniti*0.1f+vecEntreeHeight-vecEspaceHeight, Couleur(0,0,0));

    do
    {
        int windowNum = round(buildingWidth/0.1f);
        float windowSize = 0.0975f*8.0f/windowNum;
        float windowWidth = 0.12f+0.0875f*8.0f/windowNum;

        for (int i=0; i<windowNum ; i++)
        {
            if (util::alea(0.0f, 1.0f, *rand) < light)
            {
                svgout->addRect(base-unit*(0.12f+windowSize*i)+vecEntreeHeight, base-unit*(windowWidth+windowSize*i)+vecEntreeHeight,
                                base-unit*(windowWidth+windowSize*i)+vecWindowHeight+vecEntreeHeight, base-unit*(0.12f+windowSize*i)+vecWindowHeight+vecEntreeHeight, Couleur(190,150,0));


            }
            else
            {
                svgout->addRect(base-unit*(0.12f+windowSize*i)+vecEntreeHeight, base-unit*(windowWidth+windowSize*i)+vecEntreeHeight,
                                base-unit*(windowWidth+windowSize*i)+vecWindowHeight+vecEntreeHeight, base-unit*(0.12f+windowSize*i)+vecWindowHeight+vecEntreeHeight, Couleur(40,20,4));


            }
        }


        for(int i=0; i<windowNum ; i++)

        {
            if (util::alea(0.0f, 1.0f, *rand) < light)
            {


                svgout->addRect(base+uniti*(0.12f+windowSize*i)+vecEntreeHeight, base+uniti*(windowWidth+windowSize*i)+vecEntreeHeight,
                                base+uniti*(windowWidth+windowSize*i)+vecWindowHeight+vecEntreeHeight, base+uniti*(0.12+windowSize*i)+vecWindowHeight+vecEntreeHeight, Couleur(240,195,0));
            }
            else
            {


                svgout->addRect(base+uniti*(0.12f+windowSize*i)+vecEntreeHeight, base+uniti*(windowWidth+windowSize*i)+vecEntreeHeight,
                                base+uniti*(windowWidth+windowSize*i)+vecWindowHeight+vecEntreeHeight, base+uniti*(0.12+windowSize*i)+vecWindowHeight+vecEntreeHeight, Couleur(63,40,4));
            }
        }
        for (int i=0; i<windowNum+1 ; i++)
        {
            svgout->addRect(base-unit*(0.1f+windowSize*i)+vecEntreeHeight, base-unit*(0.12f+windowSize*i)+vecEntreeHeight,
                            base-unit*(0.12f+windowSize*i)+vecWindowHeight+vecEntreeHeight, base-unit*(0.1f+windowSize*i)+vecWindowHeight+vecEntreeHeight, Couleur(0,0,0));

            svgout->addRect(base+uniti*(0.1f+windowSize*i)+vecEntreeHeight, base+uniti*(0.12f+windowSize*i)+vecEntreeHeight,
                            base+uniti*(0.12f+windowSize*i)+vecWindowHeight+vecEntreeHeight, base+uniti*(0.1f+windowSize*i)+vecWindowHeight+vecEntreeHeight, Couleur(0,0,0));
        }

        svgout->addRect(base-unit*0.1f+vecEntreeHeight+vecWindowHeight, base-unit*0.90f+vecEntreeHeight+vecWindowHeight,
                        base-unit*0.90f+vecWindowHeight+vecEntreeHeight+vecEspaceHeight, base-unit*0.1f+vecWindowHeight+vecEntreeHeight+vecEspaceHeight, Couleur(0,0,0));

        svgout->addRect(base+uniti*0.1f+vecEntreeHeight+vecWindowHeight, base+uniti*0.90f+vecEntreeHeight+vecWindowHeight,
                        base+uniti*0.90f+vecWindowHeight+vecEntreeHeight+vecEspaceHeight, base+uniti*0.1f+vecWindowHeight+vecEntreeHeight+vecEspaceHeight, Couleur(0,0,0));

        vecEntreeHeight = vecEntreeHeight + vecWindowHeight + vecEspaceHeight;
        entreeHeight = entreeHeight + windowHeight + espaceHeight;

    }
    while (entreeHeight < (buildingHeight-windowHeight-espaceHeight));

    //svgout.addRect(base, base+uniti, base+uniti+vecHeight,base+vecHeight, color+Couleur{0,0,0});

    //svgout.addRect(base+uniti/4,unity/4+uniti/4,unity/4+base+uniti/2,uniti/2,Couleur{0,0,0});

    Pos ceilBase = base + vecHeight;

    svgout->addRect(ceilBase, ceilBase-unit, ceilBase-unit+uniti, ceilBase+uniti, color);


    if(buildingHeight>8.0f)
    {

        svgout->addRect(ceilBase-unity*buildingWidth*0.5f, ceilBase-unity*buildingWidth*0.5f-unity*0.5*buildingWidth+unitx*0.5*buildingWidth,
                        ceilBase+vecConst-unity*buildingWidth-unity*0.5*buildingWidth+unitx*0.5*buildingWidth,
                        ceilBase+vecConst-unity*buildingWidth, color+Couleur{80,40,0});

        svgout->addRect(ceilBase-unity*buildingWidth*0.5f, ceilBase-unity*buildingWidth*0.5f-unity*0.5*buildingWidth-unitx*0.5*buildingWidth,
                        ceilBase+vecConst-unity*buildingWidth-unity*0.5*buildingWidth-unitx*0.5*buildingWidth,
                        ceilBase+vecConst-unity*buildingWidth, color-Couleur{30,30,10});

        svgout->addRect(ceilBase+vecConst-unity*buildingWidth, ceilBase+vecConst-unity*buildingWidth-unity*0.5*buildingWidth+unitx*0.5*buildingWidth,
                        ceilBase+vecConst-unity*buildingWidth*2, ceilBase+vecConst-unity*buildingWidth-unity*0.5*buildingWidth-unitx*0.5*buildingWidth, color);



        svgout->addRect(ceilBase+vecConst-unity*buildingWidth-unity*buildingWidth*0.5,ceilBase+uniti*0.1f+vecConst-unity*buildingWidth-unity*buildingWidth*0.5,
                        ceilBase+vecHauteurAntenne+vecConst-unity*buildingWidth-unity*buildingWidth*0.5,
                        ceilBase+vecHauteurAntenne+vecConst-unity*buildingWidth-unity*buildingWidth*0.5, color+Couleur{80,40,0});

        svgout->addRect(ceilBase+vecConst-unity*buildingWidth-unity*buildingWidth*0.5,ceilBase-unit*0.1f+vecConst-unity*buildingWidth-unity*buildingWidth*0.5,
                        ceilBase+vecHauteurAntenne+vecConst-unity*buildingWidth-unity*buildingWidth*0.5,
                        ceilBase+vecHauteurAntenne+vecConst-unity*buildingWidth-unity*buildingWidth*0.5, color-Couleur{30,30,10});

    }

    else
    {

        if (util::alea(0.0f, 1.0f, *rand) < 0.2)
        {

            Pos ceilBase2 = base + vecHeight -unit*(util::alea(0.0f,0.96f, *rand)) + uniti*(util::alea(0.0f,0.96f, *rand));

            svgout->addRect(ceilBase2,ceilBase2+vecLargeurAntenne, ceilBase2+vecLargeurAntenne+vechauteurAntenne, ceilBase2+vechauteurAntenne, Couleur(180,180,180));
            svgout->addRect(ceilBase2,ceilBase2+vecLargeurAntenne2, ceilBase2+vecLargeurAntenne2+vechauteurAntenne, ceilBase2+vechauteurAntenne, Couleur(180,180,180));

            Pos ceilBaseAntenne = ceilBase2 + vechauteurAntenne;

            svgout->addRect(ceilBaseAntenne, ceilBaseAntenne+vecLargeurAntenne,
                            ceilBaseAntenne+vecLargeurAntenne2+vecLargeurAntenne, ceilBaseAntenne+vecLargeurAntenne2,
                            Couleur(180,180,180));

            Pos antBase = ceilBase2 + Pos{0.0f, vechauteurAntenne.y*0.5};

            svgout->addRect(antBase, antBase+vecLargeurAntenne2*4, antBase+vecLargeurAntenne2*4+vecLargeurAntenne,
                            antBase+vecLargeurAntenne2+vecLargeurAntenne, Couleur(180,180,180));
            svgout->addRect(antBase, antBase-vecLargeurAntenne2*4, antBase-vecLargeurAntenne2*4+vecLargeurAntenne,
                            antBase+vecLargeurAntenne2+vecLargeurAntenne, Couleur(180,180,180));

            Pos antBase2 = ceilBase2 + Pos{0.0f, vechauteurAntenne.y*0.75};

            svgout->addRect(antBase2, antBase2+vecLargeurAntenne2*4, antBase2+vecLargeurAntenne2*4+vecLargeurAntenne,
                            antBase2+vecLargeurAntenne2+vecLargeurAntenne, Couleur(180,180,180));
            svgout->addRect(antBase2, antBase2-vecLargeurAntenne2*4, antBase2-vecLargeurAntenne2*4
                            +vecLargeurAntenne, antBase2+vecLargeurAntenne2+vecLargeurAntenne, Couleur(180,180,180));
        }

    }

}
