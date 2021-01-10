#include <iostream>
#include "lampadaire.h"

Lampadaire::~Lampadaire(){}

Lampadaire::Lampadaire(Pos unitl, Svgfile* svgoutl)
{
    this->m_unit = unitl;
    this->svgout = svgoutl;
}

void Lampadaire::lamp(Pos base)
{
    Pos uniti = m_unit;
    uniti.y = -m_unit.y;

    float lampHeight = 0.5f;
    float lampRayon =0.03f;

    Pos unitx = Pos{m_unit.x, 0.0f};
    Pos unity = Pos{0.0f, m_unit.y};

    Pos VecRayon = unitx*lampRayon;
    Pos vecHeight = unity*-lampHeight;

    svgout->addRect(base+unitx, base+unitx+m_unit*0.02f, base+unitx+m_unit*0.02f+vecHeight, base+unitx+vecHeight,Couleur{0,85,25});
    svgout->addRect(base+unitx+m_unit*0.02f, base+unitx+m_unit*0.02f+uniti*0.02f, base+unitx+m_unit*0.02f+uniti*0.02f+vecHeight, base+unitx+vecHeight+m_unit*0.02f,Couleur{34,120,25});
    svgout->addDisk(base.x+m_unit.x*1.02f,base.y+vecHeight.y,VecRayon.x,Couleur{255,255,255});
    svgout->addDisk(base.x+m_unit.x*1.02f,base.y+vecHeight.y,VecRayon.x*1.5f,Couleur{255,255,150, 0.3f});
    svgout->addDisk(base.x+m_unit.x*1.02f,base.y+vecHeight.y,VecRayon.x*3.0f,Couleur{255,200,100, 0.1f});
    svgout->addDisk(base.x+m_unit.x*1.02f,base.y+vecHeight.y,VecRayon.x*6.0f,Couleur{255,150,0, 0.03f});
}
