#include <iostream>
#include <fstream>
#include <algorithm>  // Add this at the top of your file

using namespace std;

struct Iebraucejs
{
    char tips;
    int id;
    int izejasLaiks;
    int muitniekaKartasNumurs;
};

struct Muitnieks{
    char tips;
    int darbaAtrums;
    int kartasNumurs;
    int kadBrivs;
};

void iebraucejuApstrade(Muitnieks pMuitnieki[], int p_muitnieki_sk, Muitnieks nMuitnieki[], int n_muitnieki_sk, Iebraucejs* iebrauceji, int iebraucejuSkaits){
    
    for (int i=0 ; i<iebraucejuSkaits; i++){
        if(iebrauceji[i].tips == 'P'){

            int atlasitaisMuitnieks = -1; 

            for (int j=0; j<p_muitnieki_sk; j++){
    
                //Pārbauda vai muitnieks ir brīvs
                if (pMuitnieki[j].kadBrivs <= iebrauceji[i].id) {
    
                    //Ja muitnieks ir bīvs, tad pārbauda, vai viņam ir mazākais kartas numurs
                    if (atlasitaisMuitnieks == -1 || pMuitnieki[j].kartasNumurs < pMuitnieki[atlasitaisMuitnieks].kartasNumurs) {
                        atlasitaisMuitnieks = j;
                    }
                }
            }
            
            //Ja neviens muitnieks nav briivs, tad atrod to, kas ir briivs pirmais.
            if(atlasitaisMuitnieks == -1){
                int agrakaisLaiks = 1000000;
                for(int j=0; j < p_muitnieki_sk; j++){
                    if(pMuitnieki[j].kadBrivs < agrakaisLaiks){
                        agrakaisLaiks = pMuitnieki[j].kadBrivs;
                        atlasitaisMuitnieks = j;
                    }else if(pMuitnieki[j].kadBrivs == agrakaisLaiks && 
                            pMuitnieki[j].kartasNumurs < pMuitnieki[atlasitaisMuitnieks].kartasNumurs){
                        atlasitaisMuitnieks = j;
                    }
                }
            } 
    
            //Pārbauda vai ir atrasts muitnieks, kas var apkalpot iebrauceju
            if(atlasitaisMuitnieks != -1){
                int sakumaLaiks;
                //parbuda, kad sākas apkalpošana
                //ja mutinieks uzreiz bija brīvs
                if(iebrauceji[i].id > pMuitnieki[atlasitaisMuitnieks].kadBrivs){
                    sakumaLaiks = iebrauceji[i].id;
                }else{
                    //vai arī, kad muitnieks beidz apkalpot iepriekšējo iebrauceju
                    sakumaLaiks = pMuitnieki[atlasitaisMuitnieks].kadBrivs;
                }
    
                iebrauceji[i].izejasLaiks = sakumaLaiks + pMuitnieki[atlasitaisMuitnieks].darbaAtrums;
                iebrauceji[i].muitniekaKartasNumurs = pMuitnieki[atlasitaisMuitnieks].kartasNumurs;
    
                pMuitnieki[atlasitaisMuitnieks].kadBrivs = iebrauceji[i].izejasLaiks; 
            }

        }
        if(iebrauceji[i].tips == 'N'){

            int atlasitaisMuitnieks = -1; 

            for (int j=0;j<n_muitnieki_sk; j++){
    
                //Pārbauda vai muitnieks ir brīvs
                if (nMuitnieki[j].kadBrivs <= iebrauceji[i].id) {
    
                    //Ja muitnieks ir bīvs, tad pārbauda, vai viņam ir mazākais kartas numurs
                    if (atlasitaisMuitnieks == -1 || nMuitnieki[j].kartasNumurs < nMuitnieki[atlasitaisMuitnieks].kartasNumurs) {
                        
                        atlasitaisMuitnieks = j;
                    }
                    
                   
                }
            }
            //Ja neviens muitnieks nav briivs, tad atrod to, kas ir briivs pirmais.
            if(atlasitaisMuitnieks == -1){
                int agrakaisLaiks = 1000000;
                for(int j=0; j < n_muitnieki_sk; j++){
                    if(nMuitnieki[j].kadBrivs < agrakaisLaiks){
                        agrakaisLaiks = nMuitnieki[j].kadBrivs;
                        atlasitaisMuitnieks = j;
                    }else if(nMuitnieki[j].kadBrivs == agrakaisLaiks && nMuitnieki[j].kartasNumurs < nMuitnieki[atlasitaisMuitnieks].kartasNumurs){
                        atlasitaisMuitnieks = j;
                    }
                }
            } 
    
            //Pārbauda vai ir atrasts muitnieks, kas var apkalpot iebrauceju
            if(atlasitaisMuitnieks != -1){
                int sakumaLaiks;
                //parbuda, kad sākas apkalpošana
                //ja mutinieks uzreiz bija brīvs
                if(iebrauceji[i].id > nMuitnieki[atlasitaisMuitnieks].kadBrivs){
                    sakumaLaiks = iebrauceji[i].id;
                }else{
                    //vai arī, kad muitnieks beidz apkalpot iepriekšējo iebrauceju
                    sakumaLaiks = nMuitnieki[atlasitaisMuitnieks].kadBrivs;
                }
    
                iebrauceji[i].izejasLaiks = sakumaLaiks + nMuitnieki[atlasitaisMuitnieks].darbaAtrums;
                iebrauceji[i].muitniekaKartasNumurs = nMuitnieki[atlasitaisMuitnieks].kartasNumurs;
    
                nMuitnieki[atlasitaisMuitnieks].kadBrivs = iebrauceji[i].izejasLaiks; 
            }
        
        }
    }
}

bool salidzinaIebrauceji(const Iebraucejs& a, const Iebraucejs& b) {
    // First sort by exit time
    if (a.izejasLaiks != b.izejasLaiks) {
        return a.izejasLaiks < b.izejasLaiks;
    }
    
    // If exit times are the same, prioritize 'P' type
    if (a.tips != b.tips) {
        return a.tips == 'P';
    }
    
    return a.muitniekaKartasNumurs < b.muitniekaKartasNumurs;
}
void sortIebrauceji(Iebraucejs arr[], int n) {
    // Simple bubble sort - you can use more efficient sorts for larger data
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (!salidzinaIebrauceji(arr[j], arr[j+1])) {
                // Swap
                Iebraucejs temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}


int main() {
    ifstream input("customs.in");

    int p_muitnieki_sk, n_muitnieki_sk, P_Laiks, N_Laiks;
    input >> p_muitnieki_sk >> n_muitnieki_sk >> P_Laiks >> N_Laiks;  


    Muitnieks* pMuitnieki = new Muitnieks[p_muitnieki_sk];  
    Muitnieks* nMuitnieki = new Muitnieks[n_muitnieki_sk];

    
    for (int i = 0; i < p_muitnieki_sk; i++)
    {
        pMuitnieki[i].tips = 'P';
        pMuitnieki[i].darbaAtrums = P_Laiks;
        pMuitnieki[i].kartasNumurs = i + 1;
        pMuitnieki[i].kadBrivs = 0;
    }

    for (int i = 0; i < n_muitnieki_sk; i++)
    {
        nMuitnieki[i].tips = 'N';
        nMuitnieki[i].darbaAtrums = N_Laiks;
        nMuitnieki[i].kartasNumurs = i + 1;
        nMuitnieki[i].kadBrivs = 0;
    }


    char burts, muitniekaTips;

    input >> burts;
    
    int muitniekaNumurs, muitniekaLaiks;


    int maxIebrauceji = 200; // Set a reasonable maximum
    int iebraucejuSkaits = 0;
    Iebraucejs* iebrauceji = new Iebraucejs[maxIebrauceji];

    while(burts != 'X'){

        if(burts == 'T'){
            input >> muitniekaTips >> muitniekaNumurs >> muitniekaLaiks;

            if(muitniekaTips == 'P'){
                for (int i = 0; i < p_muitnieki_sk; i++)
                {
                    if(pMuitnieki[i].kartasNumurs == muitniekaNumurs){
                        pMuitnieki[i].darbaAtrums = muitniekaLaiks;
                        pMuitnieki[i].kadBrivs = 0;
                    }
                }
            }else{
                for (int i = 0; i < n_muitnieki_sk; i++)
                {
                    if(nMuitnieki[i].kartasNumurs == muitniekaNumurs){
                        nMuitnieki[i].darbaAtrums = muitniekaLaiks;
                        nMuitnieki[i].kadBrivs = 0;
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
                // Resize the array if needed
                Iebraucejs* newIebrauceji = new Iebraucejs[maxIebrauceji * 2];
                for (int i = 0; i < maxIebrauceji; i++) {
                    newIebrauceji[i] = iebrauceji[i];
                }
                delete[] iebrauceji;
                iebrauceji = newIebrauceji;
                maxIebrauceji *= 2;

                // Add the new Iebraucejs
                iebrauceji[iebraucejuSkaits] = jaunsIebraucejs;
                iebraucejuSkaits++;
            }
        }

        input >> burts;

    }


    iebraucejuApstrade(pMuitnieki, p_muitnieki_sk, nMuitnieki, n_muitnieki_sk, iebrauceji, iebraucejuSkaits);

    sortIebrauceji(iebrauceji, iebraucejuSkaits);

    // Output the results
    ofstream output("customs.out");
    if (iebraucejuSkaits == 0) {
        output << "nothing" << endl;
    }else{
        for (int i = 0; i < iebraucejuSkaits; i++) {
            output << iebrauceji[i].id << " " << iebrauceji[i].izejasLaiks << endl;
        }
    }
    output.close();

    // Or if you want to output to console instead:
    for (int i = 0; i < iebraucejuSkaits; i++) {
        cout << iebrauceji[i].id << " " << iebrauceji[i].izejasLaiks << endl;
    }

    delete[] iebrauceji;
    delete[] pMuitnieki;
    delete[] nMuitnieki;
}

// 1. janoskaidroo kaads ir muitniekiem min apstraades laiks.

// 2. saglabaa iebraucejus linked listaa. vajag lai pirmais iebraucejs ir tas, kuram ir vismazakais

