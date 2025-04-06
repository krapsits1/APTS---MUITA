#include <iostream>
#include <fstream>




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
// Min Heap-based Priority Queue for travelers
struct PriorityQueue {
    Iebraucejs* travelers;
    int capacity;
    int size;
    
    // Constructor
    PriorityQueue(int initialCapacity) {
        travelers = new Iebraucejs[initialCapacity];
        capacity = initialCapacity;
        size = 0;
    }
    
    // Destructor
    ~PriorityQueue() {
        delete[] travelers;
    }

    // Helper: Compare two travelers (returns true if a should come before b)
    bool compare(const Iebraucejs& a, const Iebraucejs& b) {
        // First sort by exit time
        if (a.izejasLaiks != b.izejasLaiks) {
            return a.izejasLaiks < b.izejasLaiks;
        }
        
        // If exit times are the same, prioritize 'P' type
        if (a.tips != b.tips) {
            return a.tips == 'P';
        }
        
        // If both have same exit time and type, sort by officer number
        return a.muitniekaKartasNumurs < b.muitniekaKartasNumurs;
    }
    
    // Helper: Get parent index of a node
    int parent(int index) {
        return (index - 1) / 2;
    }
    
    int leftChild(int index) {
        return 2 * index + 1;
    }
    
    int rightChild(int index) {
        return 2 * index + 2;
    }
    
    void swap(int i, int j) {
        Iebraucejs temp = travelers[i];
        travelers[i] = travelers[j];
        travelers[j] = temp;
    }
    
    void bubbleUp(int index) {
        while (index > 0) {
            int p = parent(index);
            if (compare(travelers[index], travelers[p])) {
                swap(index, p);
                index = p;
            } else {
                break;
            }
        }
    }
    
    void bubbleDown(int index) {
        int minIndex = index;
        
        int left = leftChild(index);
        if (left < size && compare(travelers[left], travelers[minIndex])) {
            minIndex = left;
        }
        
        int right = rightChild(index);
        if (right < size && compare(travelers[right], travelers[minIndex])) {
            minIndex = right;
        }
        
        if (minIndex != index) {
            swap(index, minIndex);
            bubbleDown(minIndex);
        }
    }
    
    void insert(Iebraucejs traveler) {
        if (size >= capacity) {
            int newCapacity = capacity * 2;
            Iebraucejs* newTravelers = new Iebraucejs[newCapacity];
            for (int i = 0; i < size; i++) {
                newTravelers[i] = travelers[i];
            }
            delete[] travelers;
            travelers = newTravelers;
            capacity = newCapacity;
        }
        
        travelers[size] = traveler;
        
        bubbleUp(size);
        
        size++;
    }
    
    Iebraucejs extractMin() {
        if (size <= 0) {
            Iebraucejs empty;
            empty.tips = '?';
            empty.id = -1;
            empty.izejasLaiks = -1;
            empty.muitniekaKartasNumurs = -1;
            return empty;
        }
        
        Iebraucejs result = travelers[0];
        
        travelers[0] = travelers[size - 1];
        size--;
        
        if (size > 0) {
            bubbleDown(0);
        }
        
        return result;
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    Iebraucejs peek() {
        if (size <= 0) {
            Iebraucejs empty;
            empty.tips = '?';
            empty.id = -1;
            empty.izejasLaiks = -1;
            empty.muitniekaKartasNumurs = -1;
            return empty;
        }
        return travelers[0];
    }
};

int main() {


    std::ifstream input("customs.in");
    std::ofstream output("customs.out");

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

    PriorityQueue pq(200);

    int latestArrivalTime = 0;
    int travelersCount = 0;

    char burts, muitniekaTips;

    input >> burts;
    
    int muitniekaNumurs, muitniekaLaiks;

    int minPLaiks = P_Laiks;
    int minNLaiks = N_Laiks;


    while(burts != 'X'){

        if(burts == 'T'){
            input >> muitniekaTips >> muitniekaNumurs >> muitniekaLaiks;

            if(muitniekaTips == 'P'){
                for (int i = 0; i < p_muitnieki_sk; i++)
                {
                    if(pMuitnieki[i].kartasNumurs == muitniekaNumurs){
                        pMuitnieki[i].darbaAtrums = muitniekaLaiks;

                        if (muitniekaLaiks < minPLaiks) {
                            minPLaiks = muitniekaLaiks;
                        }
                    }
                }
            }else{
                for (int i = 0; i < n_muitnieki_sk; i++)
                {
                    if(nMuitnieki[i].kartasNumurs == muitniekaNumurs){
                        nMuitnieki[i].darbaAtrums = muitniekaLaiks;

                        if (muitniekaLaiks < minNLaiks) {
                            minNLaiks = muitniekaLaiks;
                        }
                    }
                }
            }
        }else if(burts == 'P' || burts == 'N'){

            int ierasnasLaiks;

            input >> ierasnasLaiks;

            if(ierasnasLaiks > latestArrivalTime) {
                latestArrivalTime = ierasnasLaiks;
            }

            Iebraucejs jaunsIebraucejs;
            jaunsIebraucejs.tips = burts;
            jaunsIebraucejs.id = ierasnasLaiks;
            jaunsIebraucejs.izejasLaiks = 0;
            jaunsIebraucejs.muitniekaKartasNumurs = 0; 

            int atlasitasisMuitnieks = -1;

            if(burts == 'P'){
                for(int j = 0; j < p_muitnieki_sk; j++){
                    if(pMuitnieki[j].kadBrivs <= jaunsIebraucejs.id){
                        if (atlasitasisMuitnieks == -1 || 
                            pMuitnieki[j].kartasNumurs < pMuitnieki[atlasitasisMuitnieks].kartasNumurs) {
                            atlasitasisMuitnieks = j;
                        }
                    }
                }

                if(atlasitasisMuitnieks == -1){
                    int agrakaisLaiks = 1000000;
                    for(int j =0; j <p_muitnieki_sk; j++){
                        if(pMuitnieki[j].kadBrivs < agrakaisLaiks){
                            agrakaisLaiks = pMuitnieki[j].kadBrivs;
                            atlasitasisMuitnieks = j;
                        }else if (pMuitnieki[j].kadBrivs == agrakaisLaiks && 
                                pMuitnieki[j].kartasNumurs < pMuitnieki[atlasitasisMuitnieks].kartasNumurs){
                            atlasitasisMuitnieks = j;
                        }
                    }
                }

                if(atlasitasisMuitnieks != -1){
                    int sakumaLaiks;
                    if (jaunsIebraucejs.id > pMuitnieki[atlasitasisMuitnieks].kadBrivs) {
                        sakumaLaiks = jaunsIebraucejs.id;
                    } else {
                        sakumaLaiks = pMuitnieki[atlasitasisMuitnieks].kadBrivs;
                    }
                    jaunsIebraucejs.izejasLaiks = sakumaLaiks + pMuitnieki[atlasitasisMuitnieks].darbaAtrums;
                    jaunsIebraucejs.muitniekaKartasNumurs = pMuitnieki[atlasitasisMuitnieks].kartasNumurs;
                    pMuitnieki[atlasitasisMuitnieks].kadBrivs = jaunsIebraucejs.izejasLaiks;
                }
            }else{
                for(int j = 0; j < n_muitnieki_sk; j++){
                    if(nMuitnieki[j].kadBrivs <= jaunsIebraucejs.id){
                        if (atlasitasisMuitnieks == -1 || 
                            nMuitnieki[j].kartasNumurs < nMuitnieki[atlasitasisMuitnieks].kartasNumurs) {
                            atlasitasisMuitnieks = j;
                        }
                    }
                }

                if(atlasitasisMuitnieks == -1){
                    int agrakaisLaiks = 1000000;
                    for(int j =0; j <n_muitnieki_sk; j++){
                        if(nMuitnieki[j].kadBrivs < agrakaisLaiks){
                            agrakaisLaiks = nMuitnieki[j].kadBrivs;
                            atlasitasisMuitnieks = j;
                        }else if (nMuitnieki[j].kadBrivs == agrakaisLaiks && 
                                nMuitnieki[j].kartasNumurs < nMuitnieki[atlasitasisMuitnieks].kartasNumurs){
                            atlasitasisMuitnieks = j;
                        }
                    }
                }

                if(atlasitasisMuitnieks != -1){
                    int sakumaLaiks;
                    if (jaunsIebraucejs.id > nMuitnieki[atlasitasisMuitnieks].kadBrivs) {
                        sakumaLaiks = jaunsIebraucejs.id;
                    } else {
                        sakumaLaiks = nMuitnieki[atlasitasisMuitnieks].kadBrivs;
                    }
                    jaunsIebraucejs.izejasLaiks = sakumaLaiks + nMuitnieki[atlasitasisMuitnieks].darbaAtrums;
                    jaunsIebraucejs.muitniekaKartasNumurs = nMuitnieki[atlasitasisMuitnieks].kartasNumurs;
                    nMuitnieki[atlasitasisMuitnieks].kadBrivs = jaunsIebraucejs.izejasLaiks;
                }

            }

            pq.insert(jaunsIebraucejs);
            travelersCount++;

            // Find the absolute minimum processing time
            int absoluteMinProcessingTime = (minPLaiks < minNLaiks) ? minPLaiks : minNLaiks;

            // Calculate safe extraction threshold
            int safeCutoffTime = latestArrivalTime - absoluteMinProcessingTime;

            // Extract travelers who can't possibly be overtaken
            while(!pq.isEmpty() && pq.peek().izejasLaiks <= safeCutoffTime){
                Iebraucejs toOutput = pq.extractMin();
                output << toOutput.id << " " << toOutput.izejasLaiks << std::endl;
            }

        }

        input >> burts;

    }

    while(!pq.isEmpty()){
        Iebraucejs toOutput = pq.extractMin();
        output << toOutput.id << " " << toOutput.izejasLaiks << std::endl;
    }

    if(travelersCount == 0) {
        output << "nothing" << std::endl;
    }

    

    delete[] pMuitnieki;
    delete[] nMuitnieki;
    input.close();
    output.close();
    return 0;
}

