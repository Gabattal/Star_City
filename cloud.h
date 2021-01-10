#ifndef CLOUD_H_INCLUDED
#define CLOUD_H_INCLUDED

#include "couleur.h"
#include "util.h"
#include "svgfile.h"

class Cloud
{
    private:
        Svgfile *m_svgout;
        std::mt19937 *m_rand;
    public:
        Cloud(Svgfile *svgout, std::mt19937 *rand);
        virtual ~Cloud();

        void makeCloud(int nbcloud,int heightCloud, int widthCloud);

};

#endif // CLOUD_H_INCLUDED
