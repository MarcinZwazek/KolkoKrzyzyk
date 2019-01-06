#include <iostream>
//Kó³ko i krzy¿yk implementacja algorytmu
using namespace std;
//Funkcja odpowiedzialna za rysowanie planszy na ekranie
void RysowaniePlanszy(char tablica[])
{
    for(int i=1;i<=9;i++)
    {
        cout<<" "<<tablica[i]<<" ";
        if(i%3)
        {
            cout<<"|";
        }
        else if(i!=9)
        {
            cout<<"\n---+---+---\n";
        }
        else
        {
            cout<<endl;
        }
    }

}

//Funkcja któta sprawdza kto wygra³
bool KtoWygral(char tablica[], char gracz, bool zwrot)
{

    bool sprawdzWygrana;
    int i;

    sprawdzWygrana=false;

    //sprawdzamy wiersze
    for( i=1;i<=7;i+=3)
    {
        sprawdzWygrana|=((tablica[i]==gracz)&&(tablica[i+1]==gracz)&&(tablica[i+2]==gracz));
    }
    //sprawdz kolumny
    for(i=1;i<=3;i++)
    {
        sprawdzWygrana|=((tablica[i]==gracz)&&(tablica[i+3]==gracz)&&(tablica[i+6]==gracz));
    }
    //przek¹tna
    sprawdzWygrana|=((tablica[1]==gracz)&&(tablica[5]==gracz)&&(tablica[9]==gracz));
    //przek¹tna 2
    sprawdzWygrana|=((tablica[3]==gracz)&&(tablica[5]==gracz)&&(tablica[7]==gracz));

    if(sprawdzWygrana)
    {
        if(!zwrot)
        {
            RysowaniePlanszy(tablica);
            cout<<"\nGracz "<<gracz<< "  Wygrywa !!! Gratuluje \n\n";
        }
        return true;
    }
    return false;
}
//sprawdzanie remisu
bool SprawdzRemis(char tablica[], bool wynik)
{
    for(int i=1;i<=9;i++)
    {
        if(tablica[i]==' ')
        {
            return false;
        }
    }
    if(!wynik)
    {
        RysowaniePlanszy(tablica);
        cout <<"\REMIS !!! \n\n";
    }
    return true;
}
//G³ówny algorytm
int MiniMax(char tablica[], char gracz)
{
    int mini,mmax;

    if(KtoWygral(tablica,gracz,true))
    {
         if(gracz=='X')
            {
             return 1;
            }
         else
            {

            return -1;
            }
    }
    if(SprawdzRemis(tablica,gracz))
    {
        return 0;
    }
    if(gracz=='X')
    {
        gracz='O';
    }
    else
    {
        gracz='X';
    }
    if(gracz=='O')
    {
        mmax=10;
    }
    else
    {
        mmax=-10;
    }

    for(int i=1;i<=9;i++)
    {
        if(tablica[i]==' ')
        {
            tablica[i]=gracz;
            mini=MiniMax(tablica,gracz);
            tablica[i]=' ';
            if(((gracz=='O')&&(mini<mmax))||((gracz=='X') &&(mini>mmax)))
            {
                mmax=mini;
            }
            return mmax;
        }
    }
}
//Wyznaczenie ruchu dla komputera

int RuchKomputera(char tablica[])
{
    int ruch,i,mini,mmax;
    mmax=-10;
    for(i=1;i<=9;i++)
    {
        if(tablica[i]==' ')
        {
            tablica[i]='X';
            mini=MiniMax(tablica,'X');
            tablica[i]=' ';
            if(mini>mmax)
            {
                mmax=mini;
                ruch=i;
            }
        }
    }
    return ruch;
}
//Instrukcje do ruchu gracza
void RuchGracza(char tablica[],char &gracz)
{
    int r;
    RysowaniePlanszy(tablica);
    if(gracz=='O')
    {
        cout<<"\n\nCzlowiek: wybiera Ruch: ";
        cin>>r;
    }
    else
    {
        r=RuchKomputera(tablica);
        cout<<"\nRuch komputera: "<<r<<endl;
    }
    cout<<"---------------------\n\n";
    if((r>=1)&&(r<=9)&&(tablica[r]==' '))
    {
            tablica[r]=gracz;
        if(gracz=='O')
        {
            gracz='X';
        }
        else
        {
            gracz='O';
        }
    }
}
int main()
{
     char t[10],gracz,wybor;

  do
  {
    cout << "Gra w Kolko i Krzyzyk dla gracza i komputera\n"
            "============================================\n\n";
    for(int i = 1; i <= 9; i++) t[i] = ' ';
    {
          gracz = 'O';
    }


    while(!KtoWygral(t,'X',false) && !KtoWygral(t,'O',false) && !SprawdzRemis(t,false))
    {
        RuchGracza(t,gracz);}

    cout << "Jeszcze raz ? (T = TAK) : ";
    cin >> wybor;
    cout << "\n\n\n";

  } while((wybor == 'T') || (wybor == 't'));

}
