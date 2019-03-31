#include <stdio.h>
#include <stdlib.h>

int main()
{
  int p[20],bt[20], sup[20], wt[20],tat[20],i, n;
float avg_wt, avg_ta;
//clrscr();
printf("Enter the number of processes ____ ");
scanf("%d",&n);
for(i=0;i<n;i++)
{
p[i] = i;
printf("Enter the Burst Time of Process %d ____", i);
scanf("%d",&bt[i]);
printf("System/User/program Process (0/1/2) ? --- ");
scanf("%d", &sup[i]);
}
for(i=0;i<n;i++)
for(int k=i+1;k<n;k++)
if(sup[i] > sup[k])
{
int temp=p[i];
p[i]=p[k];
p[k]=temp;
temp=bt[i];
bt[i]=bt[k];
bt[k]=temp;
temp=sup[i];
sup[i]=sup[k];
sup[k]=temp;
}
avg_wt = wt[0] = 0;
avg_ta = tat[0] = bt[0];
for(i=1;i<n;i++)
{
wt[i] = wt[i-1] + bt[i-1];
tat[i] = tat[i-1] + bt[i];
avg_wt = avg_wt + wt[i];
avg_ta = avg_ta + tat[i];
}
printf("\nPROCESS\t PRIORITY    BURST_TIME  WAITING_TIME  TURNAROUND_TIME");
for(i=0;i<n;i++)
printf("\n%d  \t   %d    \t   %d  \t\t%d  \t\t%d ",p[i],sup[i],bt[i],wt[i],tat[i]);
printf("\nAverage Waiting Time is ____ %f",avg_wt/n);
printf("\nAverage Turnaround Time is ____ %f",avg_ta/n);
getch();
}
