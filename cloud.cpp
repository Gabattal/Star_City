#include <iostream>
#include <math.h>
#include "cloud.h"

#define MAP_WIDTH 1920
#define MAP_HEIGHT 960

#define M_PI 3.14159265358979323846

Cloud::~Cloud(){}

Cloud::Cloud(Svgfile *svgout, std::mt19937 *rand)
{
    this->m_svgout = svgout;
    this->m_rand = rand;
}

void Cloud::makeCloud(int nbcloud, int heightCloud, int widthCloud)
{
    float x;
    float vx;
    int sx;
    float y;
    float vy;
    int sy;
    int largeur;
    int hauteur;

    float angle;
    float distance;

    float maxDist = sqrt(MAP_WIDTH*MAP_WIDTH/4.0f+MAP_HEIGHT*MAP_HEIGHT/4.0f);

    Couleur black = Couleur{20,20,20,0.3f};

    for (int i=0;i<nbcloud;i++)
    {

        //x = util::alea(-1.0f, 1.0f, *m_rand);
        //y = util::alea(-1.0f, 1.0f, *m_rand);

        angle = util::alea(0.0, 2*M_PI, *m_rand);
        distance = 0.2f+util::alea(0.0f, 10.0f, *m_rand);
        distance = pow(distance, 0.15f)/2.0f;

        Pos cloudCenter = Pos{MAP_WIDTH/2, MAP_HEIGHT/2} + Pos{cos(angle)*MAP_WIDTH, sin(angle)*MAP_HEIGHT}*distance;
        /*

        sx=(x>0) - (x<0);
        sy=(y>0) - (y<0);

        vx=pow(x*sx, 0.2f)*sx;
        vy=pow(y*sy, 0.2f)*sy;

        Pos cloudCenter = Pos{vx, vy};
        Pos mapSize = {WIDTH, HEIGHT};

        cloudCenter = cloudCenter*0.5f*mapSize+mapSize*0.5f,;
*/


        hauteur = util::alea(5, heightCloud, *m_rand);
        largeur = util::alea(100, widthCloud, *m_rand);
        //std::cout<<a<<std::endl;

         m_svgout->addEllipse(cloudCenter.x,cloudCenter.y,largeur,hauteur,black);
         //m_svgout->addEllipse(cloudCenter.x,cloudCenter.y,10,10,Couleur{255,255,255});
    }
}
