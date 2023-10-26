// C++ program for implementation of RR scheduling
#include<iostream>
using namespace std;

// IMPROVED ROUND ROBIN
void findWaitingTime2(int processes[], int n,
			int bt[], int wt[], int quantum)
{
	
	int rem_bt[n];
	for (int i = 0 ; i < n ; i++)
		rem_bt[i] = bt[i];

	int t = 0;

	while (1)
	{
		bool done = true;

		
		for (int i = 0 ; i < n; i++)
		{
			if (rem_bt[i] > 0)
			{
				done = false; 

				if (rem_bt[i] > quantum)
				{
					t += quantum;
					rem_bt[i] -= quantum;
                     
                    if(rem_bt[i] <= quantum)
                    {
                        t+=rem_bt[i];
                        wt[i]=t-bt[i];
                        rem_bt[i]=0;

                    }
				}
			}
		}
		if (done == true)
		break;
	}
}
// Round Robin
void findWaitingTime1(int processes[], int n,
			int bt[], int wt[], int quantum)
{
	int rem_bt[n];
	for (int i = 0 ; i < n ; i++)
		rem_bt[i] = bt[i];

	int t = 0; 
	while (1)
	{
		bool done = true;

	
		for (int i = 0 ; i < n; i++)
		{
			if (rem_bt[i] > 0)
			{
				done = false; 

				if (rem_bt[i] > quantum)
				{
					t += quantum;
					rem_bt[i] -= quantum;
                     
				}
			
				else
				{
				t = t + rem_bt[i];
                wt[i] = t - bt[i];
                rem_bt[i] = 0;
				}
			}
		}


		if (done == true)
		break;
	}
}


void findTurnAroundTime(int processes[], int n,
						int bt[], int wt[], int tat[])
{
	
	for (int i = 0; i < n ; i++)
		tat[i] = bt[i] + wt[i];
}


void find_avgs(int processes[], int n, int bt[],
									int quantum)
{
	int wt[n], tat[n], total_wt = 0, total_tat = 0;

	
	findWaitingTime1(processes, n, bt, wt, quantum);

	
	findTurnAroundTime(processes, n, bt, wt, tat);

	
     cout<<"\n\n Results of Normal Round Robin \n\n";
	cout << "PN\t "<< " \tBT "
		<< " WT " << " \tTAT\n";

	
	for (int i=0; i<n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		cout << " " << i+1 << "\t\t" << bt[i] <<"\t "
			<< wt[i] <<"\t\t " << tat[i] <<endl;
	}

	cout << "Average waiting time = "
		<< (float)total_wt / (float)n;
	cout << "\nAverage turn around time = "
		<< (float)total_tat / (float)n;


   int iwt[n], itat[n], itotal_wt = 0, itotal_tat = 0;
     findWaitingTime2(processes, n, bt, iwt, quantum);
       
	findTurnAroundTime(processes, n, bt, iwt, itat);
         cout<<"\n\n Results of Improved Round Robin \n\n";
	
	cout << "PN\t "<< " \tBT "
		<< " WT " << " \tTAT\n";

	for (int i=0; i<n; i++)
	{
		itotal_wt = itotal_wt + iwt[i];
		itotal_tat = itotal_tat + itat[i];
		cout << " " << i+1 << "\t\t" << bt[i] <<"\t "
			<< iwt[i] <<"\t\t " << itat[i] <<endl;
	}

	cout << "Average waiting time = "
		<< (float)itotal_wt / (float)n;
	cout << "\nAverage turn around time = "
		<< (float)itotal_tat / (float)n;
}

// Driver code
int main()
{
	// process id's
    
	int n;
    cout<<"Enter the number of process \n";
    cin>>n;
    int processes[n],burst_time[n];
    for(int i=0;i<n;i++)
    {
        cout<<"Enter the Process Number and it's Burst time:";
        cin>>processes[i]>>burst_time[i];
        cout<<"\n";
    }

	int quantum;
    cout<<"Enter the time Quantaum:";
    cin>>quantum;	

	find_avgs(processes, n, burst_time, quantum);
   


	return 0;
}
