#include "headersafestate.hpp"

void init(System *s) {

        std::fstream in("./data.txt");
        if (!in.is_open()) {
                std::cout << "Error: Cannot open data.txt" << std::endl;
                exit(-1);
        }

        //Get data from data.txt and input into Allocation, Max, and Available
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                        char ch;
                        in >> ch;
                        int inp = atoi(&ch);
                        s->Allocation[i][j] = inp;
                }
        }
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                        char ch;
                        in >> ch;
                        int inp = atoi(&ch);
                        s->Max[i][j] = inp;
                }
        }
        for (int i = 0; i < m; i++) {
                char ch;
                in >> ch;
                int inp = atoi(&ch);
                s->Available[i] = inp;
        }
        //Need = Max - Allocation
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                        s->Need[i][j] = s->Max[i][j] - s->Allocation[i][j];
                }
        }
}

int main() {

        System s1;

        init(&s1);     //Initialize new System

        int safeSequence[n] = {-1,-1,-1,-1,-1};      //Starting position for safe sequence 
        int SSIndex = 0;     //Safe sequence index -- keeps track of processes in safe sequence
        //Work = Avaialable
        int Work[m];
        for (int i = 0; i < m; i++) {
                Work[i] = s1.Available[i];
        }

        //Finish[n] = false for all n
        //Keeps track of all processes already in safe sequence
        bool Finish[n];
        for (int i = 0; i < n; i++) {
                Finish[i] = false;
        }

        bool lessThanFlag = false;     //True if Need <= Work
        int i = 0;     //Index for while loop
        int loopCheck = 0;     //Keeps track of iterations of while loop

        //Loop continues while safe sequence array is not full
        while (SSIndex < 5) {

                //If process is not already in safe sequence, enter loop        
                if (Finish[i] == false) {

                        //Check if Need <= Work (a neccesity to enter safe sequence)
                        for (int j = 0; j < m; j++) {
                                if (s1.Need[i][j] <= Work[j]) {
                                        lessThanFlag = true;
                                }
                                else {
                                        lessThanFlag = false;
                                        break;
                                }
                        }

                        //If Need <= Work
                        if (lessThanFlag == true) {
                                //Work = Work + Allocation
                                for (int j = 0; j < m; j++) {
                                        Work[j] = Work[j] + s1.Allocation[i][j];
                                }
                                safeSequence[SSIndex] = i;     //Process enters safe sequence
                                SSIndex++;
                                Finish[i] = true;     //Indicate that process is now in safe sequence, and should not be checked again 
                        }
                }

                i = (i + 1) % n;     //i cycles through 0-n processes
                lessThanFlag = false;     //Reset flag

                //If while loop has iterated 50 times, sequence is not safe; break loop
                loopCheck++;
                if (loopCheck > 50) {
                        break;
                }
        }

        //If any processes did not enter safe sequence, sequence not safe - Terminate
        for (int i = 0; i < n; i++) {
                if (Finish[i] == false) {
                        std::cout << "The sequence is not safe." << std::endl;
                        return 1;
                }
        }

        //If sequence is safe, print sequence
        std::cout << "The sequence is safe. The Safe sequence = " << std::endl;
        for (int k = 0; k < n; k++) {
                std::cout << "P" <<  safeSequence[k] << " ";
        }

        return 0;
}

          
"safestate.cpp" 131L, 2979B
