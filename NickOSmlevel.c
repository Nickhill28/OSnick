#include <stdio.h>
#include <stdlib.h>
struct process{
	int priority;
	int bt;
	int pid;
	int wt;
	int tat;
	int rt;
	int at;
	int ct;
};//made a structure so that it would be easy to take the record of process
int Total=0,t1=0,t2=0,t3=0;
double totalwait=0,totaltat=0,totalCT=0;
void getInput();//to get input
void calcwt(struct process *q,int);//calculate waiting time
void calcCT(struct process *q,int);
void calctat(struct process *q,int);//calculating turnaround
void printQ(struct process *q,int size);//print process details for each queue
void RR();//round robin
void Prior();//priority scheduling
void FCFS();//first come first serve
void printQI(struct process);//print particular process details
void printQ(struct process *,int);//process details for all processes
int q1_size=0,q2_size=0,q3_size=0,n=0; //n=Total Process
struct process *q1,*q2,*q3;
int tq = 4;//time quantum given for RR
void getInput(){
	printf("\n Total Number of Process:\t");
	scanf("%d",&n);
	//memory allocation to the queues so that the data of process does not scatter
	q1 = (struct process *)malloc(n*sizeof(struct process));
	q2 = (struct process *)malloc(n*sizeof(struct process));
	q3 = (struct process *)malloc(n*sizeof(struct process));
	for(int i=0;i<n;i++){
		struct process p;
		printf("\n\t\tProcess %d\n=============================================\n\n",i+1);

		printf("PId:\t");
		scanf("%d",&p.pid);
		printf("Arrival time:\t");
		scanf("%d",&p.at);
		printf("Priority :\t");
		scanf("%d",&p.priority);
		printf("\nBurst Time: \t");
		scanf("%d",&p.bt);
		p.rt = p.bt;
        switch(p.priority){
			case 3:
				q3[q3_size++] = p;
				break;
			case 2:
				q2[q2_size++] = p;
				break;
			case 1:
				q1[q1_size++]  = p;
				break;
			default:
                printf("\npriority can only be 1/2/3 nothing else\n");
		}
	}
}
void printQ(struct process *q,int size){
	calcCT(q,size);
	calctat(q,size);

	calcwt(q,size);
		printf("\nPId| Priority| Burst_Time| Waiting_Time| TurnAround_Time| Arrival_Time| Completion_time|");
    printf("\n================================================================================\n");
    for(int i=0;i<size;i++){
		printQI(q[i]);
	}
	printf("\n\n");
}
void printQI(struct process p){
	printf("\n%d\t%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d",p.pid,p.priority,p.bt,p.wt,p.tat,p.at,p.ct);
}
void calcwt(struct process *q,int size){
	q[0].wt = 0;
	for(int i=1;i<size;i++){
		q[i].wt = q[i].tat - q[i].bt;
		totalwait+=q[i].wt;
	}
	//printf(q.wt);
}
void calcCT(struct process *q,int size){
	q[0].ct = q[0].bt +q[0].at;
	for(int i=1;i<size;i++){
		q[i].ct = q[i-1].ct + q[i].bt;
		totalCT+=q[i].ct;
	}
}
void calctat(struct process *q,int size){
	q[0].tat = q[0].bt;
	for(int i=0;i<size;i++){
		q[i].tat = q[i].ct - q[i].at;
		totaltat+=q[i].tat;
	}
	//printf("the total turnaround tiq.tat);
}
void FCFSq1(struct process *q,int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(q[j].at>q[i].at){
				struct process t = q[i];
				q[i] = q[j];
				q[j] = t;

			}
		}t3+=q[i].ct;
	}
}
void Priorq2(struct process *q,int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(q[j].priority>q[i].priority){
				struct process t = q[i];
				q[i] = q[j];
				q[j] = t;
			}
		}t2+=q[i].ct;
	}
}
void RRq3(struct process *q,int size){
		int time=0,i=0,remain=size,flag=0,wait_time=0,tat_time=0,total_times=0;
	for(time=0,i=0;remain!=0;){
		struct process p = q[i];
		if(p.rt<=tq && p.rt>0){
			time += p.rt;
			p.rt = 0;
			flag = 1;
		}else if(p.rt>tq){
			p.rt -= tq;
			time += tq;
		}
		if(p.rt==0 && flag==1){
			remain--;
			printf("\n%d\t%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d",p.pid,p.priority,p.bt,p.wt,p.tat,p.at,p.ct);
			wait_time += time -p.at - p.bt;
			totalwait+=wait_time;
			//printf("wait test: %f\n",totalwait);
			tat_time += time -p.at;
			totaltat+=tat_time;
			flag = 0;
		}

		if(i==remain-1){
			i=0;
		}else if(q[i+1].at<time){
			i++;
		}else{
			i=0;
		}

		q[i] = p;
	}t1+=q[i].ct;
	//p.wt+=wait_time;
	//p.tat+=tat_time;

}
void FCFS(){
	printf("\n\n===========================================================================");
	printf("\n\t\tFirst Come First Serve\t");
	printf("\n===========================================================================\n\n");
	FCFSq1(q1,q1_size);
	printQ(q1,q1_size);
}
void Prior(){
	printf("\n\n===========================================================================");
	printf("\n\t\tPriority Scheduling\t");
	printf("\n===========================================================================\n\n");
	Priorq2(q2,q2_size);
	printQ(q2,q2_size);
}
void RR(){
	printf("\n\n===========================================================================");
	printf("\n\t\tRound Robin\t");
	printf("\n===========================================================================\n\n");

	printf("\nPId| Priority| Burst_Time| Waiting_Time| TurnAround_Time| Arrival_Time| Completion_time|");
	printf("\n======================================================================================\n");
    calcCT(q3,q3_size);

	calctat(q3,q3_size);
	calcwt(q3,q3_size);
	RRq3(q3,q3_size);


}
void round_robin1()
{
	printf("Time Quantum between the 3 queues is 10\n");
	for(int i=1;i<Total;i=i+10)
	{
		if(t1>10)
		{
			printf("Queue1 is running for 10 units\n");
			t1=t1-10;
		}
		else if(t1<=10&&t1!=0)
		{
			printf("Queue1 is running for %d units\n",t1);
			t1=0;
		}
		if(t2>10)
		{
			printf("Queue2 is running for 10 units\n");
			t2=t2-10;
		}
		else if(t2<=10&&t2!=0)
		{
			printf("Queue2 is running for %d units\n",t2);
			t2=0;
		}
		if(t3>10)
		{
			printf("Queue3 is running for 10 units\n");
			t3=t3-10;
		}
		else if(t3<=10&&t3!=0)
		{
			printf("Queue3 is running for %d units\n",t3);
			t3=0;
		}
	}
}
int main(){
	getInput();
	int i=1;
	round_robin1();
	RR();
    Prior();
    FCFS();
	printf("\n\n");
	double p= totalwait/n;
	if(p<0)
        p=0;
	printf("\n Average Waiting Time= %f\n",p);
	printf(" Average Turnaround Time = %f\n",totaltat/n);
}
