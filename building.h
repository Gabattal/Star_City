#ifndef BUILDING_H
#define BUILDING_H

#include "couleur.h"
#include "util.h"
#include "svgfile.h"

class Building
{
    public:
        Building(Pos unit, Svgfile *svgout, std::mt19937 *rand);
        virtual ~Building();

        void generateSvg(Pos base, Couleur color, int multRoad, int multSquare, float light);

    protected:
        Pos unitD;
        Svgfile *svgout;
        std::mt19937 *rand;
};

#endif // BUILDING_H
