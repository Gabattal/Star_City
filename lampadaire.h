#ifndef LAMPADAIRE_H_INCLUDED
#define LAMPADAIRE_H_INCLUDED

#include "couleur.h"
#include "util.h"
#include "svgfile.h"

class Lampadaire
{
    public:

        Lampadaire(Pos unitl, Svgfile *svgoutl);
        virtual ~Lampadaire();

        void lamp(Pos base);

    private:

        Pos m_unit;
        Svgfile *svgout;

};

#endif // LAMPADAIRE_H_INCLUDED
