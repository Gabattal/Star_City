#ifndef GROUND_H_INCLUDED
#define GROUND_H_INCLUDED

#include "couleur.h"
#include "util.h"
#include "svgfile.h"
#include "lampadaire.h"

class Ground
{
    private:

        Pos m_unit;
        Svgfile *svgout;
        Lampadaire *lampadaire;
        std::mt19937 *rand;

    public:
        Ground(Pos unit, Svgfile *svgout, Lampadaire *lamp, std::mt19937 *rand);
        virtual ~Ground();

        void makeGround(int multRoad, int multSquare, int seed, int freq);

};

#endif // GROUND_H_INCLUDED
