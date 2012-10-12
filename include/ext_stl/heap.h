/*Header-MicMac-eLiSe-25/06/2007

    MicMac : Multi Image Correspondances par Methodes Automatiques de Correlation
    eLiSe  : ELements of an Image Software Environnement

    www.micmac.ign.fr

   
    Copyright : Institut Geographique National
    Author : Marc Pierrot Deseilligny
    Contributors : Gregoire Maillet, Didier Boldo.

[1] M. Pierrot-Deseilligny, N. Paparoditis.
    "A multiresolution and optimization-based image matching approach:
    An application to surface reconstruction from SPOT5-HRS stereo imagery."
    In IAPRS vol XXXVI-1/W41 in ISPRS Workshop On Topographic Mapping From Space
    (With Special Emphasis on Small Satellites), Ankara, Turquie, 02-2006.

[2] M. Pierrot-Deseilligny, "MicMac, un lociel de mise en correspondance
    d'images, adapte au contexte geograhique" to appears in 
    Bulletin d'information de l'Institut Geographique National, 2007.

Francais :

   MicMac est un logiciel de mise en correspondance d'image adapte 
   au contexte de recherche en information geographique. Il s'appuie sur
   la bibliotheque de manipulation d'image eLiSe. Il est distibue sous la
   licences Cecill-B.  Voir en bas de fichier et  http://www.cecill.info.


English :

    MicMac is an open source software specialized in image matching
    for research in geographic information. MicMac is built on the
    eLiSe image library. MicMac is governed by the  "Cecill-B licence".
    See below and http://www.cecill.info.

Header-MicMac-eLiSe-25/06/2007*/



#ifndef _ELISE_EXT_STL_HEAP
#define _ELISE_EXT_STL_HEAP

// #include "ext_stl/fifo.h"


/*************************************************************/
/* SOME UTILS ON TAB                                         */
/*************************************************************/


template <class Type,class Compare> class ElHeap 
{
    public :

        ElHeap(Compare inferior,INT capa = 2) :
           _inferior    (inferior)
        {
		mEls.reserve(capa);
        }

         void  push(const Type & v)
        {
             mEls.push_back(v);
             heap_down(nb()-1);
        }

        bool pop(Type & v)
        {
             if (nb() <= 0) return false;
             v = mEls[0];
             mEls[0] = mEls[nb()-1];
	     mEls.pop_back();
             heap_up(0);
             return true;
        }
        void clear() { mEls.clear();}
        INT nb() {return (int) mEls.size();}
        bool empty() {return mEls.empty();}

   private :

	std::vector<Type> mEls;

        static INT  Fils(INT i) { return   (i+1)/2-1;}
        static INT  Pere1(INT i){ return   i*2+1;}
        static INT  Pere2(INT i){ return   i*2+2;}


        Compare       _inferior;

        // do not exist
        ElHeap(const ElHeap<Type,Compare> &);

        void heap_up(INT KV)
        {
            for(;;)
            {
                INT ind_plus_petit = KV;

                INT p1 = Pere1(KV);
                if ((p1 < nb()) && _inferior(mEls[p1],mEls[ind_plus_petit]))
                    ind_plus_petit = p1;

                INT p2 = Pere2(KV);
                if ((p2 < nb()) && _inferior(mEls[p2],mEls[ind_plus_petit]))
                    ind_plus_petit = p2;

                if (ind_plus_petit == KV)
                   return;
                else
                {
                    ElSwap(mEls[ind_plus_petit],mEls[KV]);
                    KV = ind_plus_petit;
                }
            }
        }

        void heap_down(INT KV)
        {
            while ((KV>0)&& _inferior(mEls[KV],mEls[Fils(KV)]))
            {
                  ElSwap(mEls[KV],mEls[Fils(KV)]);
                  KV = Fils(KV);
            }
        }
};



#endif /* ! _ELISE_EXT_STL_HEAP */


/*


template <class Type,class Compare> class ElHeap : private ElFifo<Type>
{
    public :

        ElHeap(Compare inferior,INT capa = 2) :
           ElFifo<Type> (capa),
           _inferior    (inferior)
        {
        }

        void  push(Type v)
        {
             pushlast(v);
             heap_down(_nb-1);
        }

        bool pop(Type & v)
        {
             if (_nb <= 0) return false;
             v = _tab[0];
             _tab[0] = _tab[_nb-1];
             _nb--;
             heap_up(0);
             return true;
        }
        void clear() { _nb = 0;}
        INT nb() {return _nb;}
        bool empty() {return nb() ==0;}

   private :

        static INT  Fils(INT i) { return   (i+1)/2-1;}
        static INT  Pere1(INT i){ return   i*2+1;}
        static INT  Pere2(INT i){ return   i*2+2;}


        Compare       _inferior;

        // do not exist
        ElHeap(const ElHeap<Type,Compare> &);

        void heap_up(INT KV)
        {
            for(;;)
            {
                INT ind_plus_petit = KV;

                INT p1 = Pere1(KV);
                if ((p1 < _nb) && _inferior(_tab[p1],_tab[ind_plus_petit]))
                    ind_plus_petit = p1;

                INT p2 = Pere2(KV);
                if ((p2 < _nb) && _inferior(_tab[p2],_tab[ind_plus_petit]))
                    ind_plus_petit = p2;

                if (ind_plus_petit == KV)
                   return;
                else
                {
                    ElSwap(_tab[ind_plus_petit],_tab[KV]);
                    KV = ind_plus_petit;
                }
            }
        }

        void heap_down(INT KV)
        {
            while ((KV>0)&& _inferior(_tab[KV],_tab[Fils(KV)]))
            {
                  ElSwap(_tab[KV],_tab[Fils(KV)]);
                  KV = Fils(KV);
            }
        }
};

template <class Type,class Compare> class ElHeap : private ElFifo<Type>
{
    public :

        ElHeap(Compare inferior,INT capa = 2) :
           ElFifo<Type> (capa),
           _inferior    (inferior)
        {
              pushlast(Type());
        }

        void  push(Type v)
        {
             pushlast(v);
             heap_down(_nb-1);
        }

        bool pop(Type & v)
        {
             if (_nb <= 1) return false;
             v = _tab[1];
             _tab[1] = _tab[_nb-1];
             _nb--;
             heap_up(1);
             return true;
        }
        void clear() { _nb = 1;}
        INT nb() {return _nb-1;}
        bool empty() {return nb() ==0;}

   private :

        static INT  Fils(INT i) { return   i/2;}
        static INT  Pere1(INT i){ return   i*2;}
        static INT  Pere2(INT i){ return   i*2+1;}


        Compare       _inferior;

        // do not exist
        ElHeap(const ElHeap<Type,Compare> &);

        void heap_up(INT KV)
        {
            for(;;)
            {
                INT ind_plus_petit = KV;

                INT p1 = Pere1(KV);
                if ((p1 < _nb) && _inferior(_tab[p1],_tab[ind_plus_petit]))
                    ind_plus_petit = p1;

                INT p2 = Pere2(KV);
                if ((p2 < _nb) && _inferior(_tab[p2],_tab[ind_plus_petit]))
                    ind_plus_petit = p2;

                if (ind_plus_petit == KV)
                   return;
                else
                {
                    ElSwap(_tab[ind_plus_petit],_tab[KV]);
                    KV = ind_plus_petit;
                }
            }
        }

        void heap_down(INT KV)
        {
            while ((KV>1)&& _inferior(_tab[KV],_tab[Fils(KV)]))
            {
                  ElSwap(_tab[KV],_tab[Fils(KV)]);
                  KV = Fils(KV);
            }
        }
};

*/





/*Footer-MicMac-eLiSe-25/06/2007

Ce logiciel est un programme informatique servant à la mise en
correspondances d'images pour la reconstruction du relief.

Ce logiciel est régi par la licence CeCILL-B soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL-B telle que diffusée par le CEA, le CNRS et l'INRIA 
sur le site "http://www.cecill.info".

En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme,  le
titulaire des droits patrimoniaux et les concédants successifs.

A cet égard  l'attention de l'utilisateur est attirée sur les risques
associés au chargement,  à l'utilisation,  à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant 
donné sa spécificité de logiciel libre, qui peut le rendre complexe à 
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant  des  connaissances  informatiques approfondies.  Les
utilisateurs sont donc invités à charger  et  tester  l'adéquation  du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement, 
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité. 

Le fait que vous puissiez accéder à cet en-tête signifie que vous avez 
pris connaissance de la licence CeCILL-B, et que vous en avez accepté les
termes.
Footer-MicMac-eLiSe-25/06/2007*/
