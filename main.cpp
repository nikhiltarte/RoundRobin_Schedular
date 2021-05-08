
#include <iostream>
#include <queue>
#include <unistd.h>

using namespace std;

int main()
{
    int Num_Processes,QuantumTime;
    cout << "Number of Processes:\t";
    cin >> Num_Processes;
    
    cout << "Quantum Time:\t";
    cin >> QuantumTime;
    
    int ProcessData[Num_Processes][3];
    
    for(int i = 0; i < Num_Processes; i++){
        cout << "Process P" << i << ":\t" << endl;
        ProcessData[i][0] = i;
        cout << "Arrival Time:\t";
        cin >> ProcessData[i][1];
        cout << "Burst Time:\t";
        cin >> ProcessData[i][2];
    }
    
    cout  << endl << endl;
    cout << "==============================================================" << endl;
    cout << "Process Id              Arrival Time       Burst Time" << endl;
    cout << "==============================================================" << endl;

    for(int i = 0; i < Num_Processes; i++){
        cout << "   P" << ProcessData[i][0] << "                      " << ProcessData[i][1] << "                        " << ProcessData[i][2] << endl;
    }

    cout << "==============================================================" << endl;
    cout  << endl << endl;
    
    cout << "##############################################################" << endl;
    
    cout << "Starting Execution:" << endl << endl;
    
    sleep(2);
    
    //---------Schedular Implementation Start----------------------------------------------------------
    
    queue<int> ReadyQ;
    int CurrentTime = 0;
    int QuantumCounter = 0;
    int ProcessInExcution;
    bool ProcessBreaked = false;    // HERE
    bool ProcessIsInExcution = false;
    
    while(true){
        // Checking If all Process Burst Time is Ended or Not
        bool all_process_excuted = true;
        for(int i = 0; i < Num_Processes; i++)
            if(ProcessData[i][2] > 0)
                all_process_excuted = false;
        
        if(all_process_excuted)
            break; // Break Loop as All Process Excution Complete
        cout << "$$$ Time:\t " <<  CurrentTime << endl;
        
        //Checking Arrival Time of Each Process and if Arrival Time Matches Put in queue
        for(int i = 0; i < Num_Processes; i++)
            if(CurrentTime == ProcessData[i][1]){
                ReadyQ.push(ProcessData[i][0]);
                cout << "Added Process P" << ProcessData[i][0] << " Ready Queue" << endl;
            }
            
        if(ProcessBreaked){
            ReadyQ.push(ProcessInExcution);
            cout << "Added Process #P" << ProcessData[ProcessInExcution][0] << " Ready Queue" << endl;   // HERE
            ProcessBreaked = false;
        }
        if(!ReadyQ.empty() || ProcessIsInExcution){
            //Getting Latest Process to Excute when Time QuantumCounter is Zero, and Recharging QuantumTime
            if(QuantumCounter == 0){
                ProcessInExcution = ReadyQ.front();
                ReadyQ.pop();
                QuantumCounter = QuantumTime;
                ProcessIsInExcution = true;
            }
            
            //Exuting Process -> Burst Time -1
            ProcessData[ProcessInExcution][2] = ProcessData[ProcessInExcution][2] - 1;
            QuantumCounter--;
            
            cout << "#$# Process in Excution:\t P" << ProcessInExcution <<endl;
            
            if(QuantumCounter == 0 && ProcessData[ProcessInExcution][2] > 0){
                ProcessBreaked = true;
                ProcessIsInExcution = false;
            }
            
            if(ProcessData[ProcessInExcution][2] == 0){
                cout << ">> Process P" << ProcessInExcution << " Completed." << endl;
                QuantumCounter = 0;
                ProcessIsInExcution = false;
            }
        }
        
        cout  << endl;
        cout << "======================== READY QUEUE =========================" << endl;
        cout << "Process Id              Arrival Time       Burst Time" << endl;
        cout << "==============================================================" << endl;
    
        for(int i = 0; i < Num_Processes; i++){
            if(ProcessData[i][2] > 0 && ProcessData[i][1] <= CurrentTime)
            cout << "   P" << ProcessData[i][0] << "                      " << ProcessData[i][1] << "                        " << ProcessData[i][2] << endl;
        }
        cout << "==============================================================" << endl;
        cout  << endl << endl;
        CurrentTime++;
        sleep(1);
    }
    
    cout << endl << "Total Turn Around Time:\t" << CurrentTime;
    
    return 0;
}
