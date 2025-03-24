#include <iostream>
#include <fstream>

using namespace std;

struct Iebraucejs
{
    char tips;
    int id;
    int izejasLaiks; 
};

struct Muitnieks{
    char tips;
    int darbaAtrums;
    int kartasNumurs;
    int kadBrivs;
};


int main() {
    ifstream input("customs.in");

    int P_Muitnieki, N_Muitnieki, P_Laiks, N_Laiks;
    input >> P_Muitnieki >> N_Muitnieki >> P_Laiks >> N_Laiks;  


    Muitnieks pMuitnieki[P_Muitnieki];  
    Muitnieks nMuitnieki[N_Muitnieki];

    
    for (int i = 0; i < P_Muitnieki; i++)
    {
        pMuitnieki[i].tips = 'P';
        pMuitnieki[i].darbaAtrums = P_Laiks;
        pMuitnieki[i].kartasNumurs = i + 1;
        pMuitnieki[i].kadBrivs = 0;
    }

    for (int i = 0; i < N_Muitnieki; i++)
    {
        nMuitnieki[i].tips = 'N';
        nMuitnieki[i].darbaAtrums = P_Laiks;
        nMuitnieki[i].kartasNumurs = i + 1;
        nMuitnieki[i].kadBrivs = 0;
    }


    char burts, muitniekaTips;
    int muitniekaNumurs, muitniekaLaiks;


    int maxIebrauceji = 1000; // Set a reasonable maximum
    int iebraucejuSkaits = 0;
    Iebraucejs* iebrauceji = new Iebraucejs[maxIebrauceji];

    while(burts != 'X'){

        if(burts == 'T'){
            input >> muitniekaTips >> muitniekaNumurs >> muitniekaLaiks;

            if(muitniekaTips == 'P'){
                for (int i = 0; i < P_Muitnieki; i++)
                {
                    if(pMuitnieki[i].kartasNumurs == muitniekaNumurs){
                        pMuitnieki[i].darbaAtrums = muitniekaLaiks;
                        pMuitnieki[i].kadBrivs = muitniekaLaiks;
                    }
                }
            }else{
                for (int i = 0; i < N_Muitnieki; i++)
                {
                    if(nMuitnieki[i].kartasNumurs == muitniekaNumurs){
                        nMuitnieki[i].darbaAtrums = muitniekaLaiks;
                        nMuitnieki[i].kadBrivs = muitniekaLaiks;
                    }
                }
            }
        }else if(burts == 'P' || burts == 'N'){

            int ierasnasLaiks;

            input >> ierasnasLaiks;

            Iebraucejs jaunsIebraucejs;
            jaunsIebraucejs.tips = burts;
            jaunsIebraucejs.id = ierasnasLaiks;
            jaunsIebraucejs.izejasLaiks = 0;

            if(iebraucejuSkaits < maxIebrauceji){
                iebrauceji[iebraucejuSkaits] = jaunsIebraucejs;
                iebraucejuSkaits++;
            }else{
                cout << "Pārāk daudz iebraucēju" << endl;
            }

        }else{
            cout << "nothing" << endl;
        }
    }
    
    
    delete[] iebrauceji;
}
