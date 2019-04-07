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
};
void getInput();
void calcwt(struct process *q,int);
void calctat(struct process *q,int);
void printQ(struct process *q,int size);
void RR();
void Prior();
void FCFS();
void printQI(struct process);
void printQ(struct process *,int);
int q1_size=0,q2_size=0,q3_size=0,n=0; //N=Total Process
struct process *q1,*q2,*q3;
int tq = 4;
void getInput(){
	printf("\n Total Number of Process:\t");
	scanf("%d",&n);
	//
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
	calcwt(q,size);
	calctat(q,size);
		printf("\nPId\t\tPriority\t\tBurst_Time\t\tWaiting_Time\t  TurnAround_Time\t   Arrival_Time");
    printf("\n================================================================================\n");
    for(int i=0;i<size;i++){
		printQI(q[i]);
	}
	printf("\n\n");
}
void printQI(struct process p){
	printf("\n%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t\t%d",p.pid,p.priority,p.bt,p.wt,p.tat,p.at);
}
void calcwt(struct process *q,int size){
	q[0].wt = 0;
	for(int i=1;i<size;i++){
		q[i].wt = q[i-1].wt + q[i-1].bt;
	}
}
void calctat(struct process *q,int size){
	q[0].wt = 0;
	for(int i=0;i<size;i++){
		q[i].tat = q[i].wt + q[i].bt;
	}
}
void FCFSq1(struct process *q,int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(q[j].at>q[i].at){
				struct process t = q[i];
				q[i] = q[j];
				q[j] = t;
			}
		}
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
		}
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
			printf("\n%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t \t%d",p.pid,p.priority,p.bt,p.wt,p.tat,p.at);
			wait_time += time -p.at - p.bt;
			tat_time += time -p.at;
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
	}
	printf("\nRR Average Waiting Time= %f\n",wait_time*1.0/n);
	printf("RR Average Turnaround Time = %f\n",tat_time*1.0/n);
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

	printf("\nPId\t\tPriority\t\tBurst_Time\t\tWaiting_Time\t\tTurnAround_Time\t\tArrival_Time");
	printf("\n===============================================================================================================================\n");
	calcwt(q3,q3_size);
	calctat(q3,q3_size);

	RRq3(q3,q3_size);
}
int main(){
	getInput();
	int i=1;
	while(n>0){
		switch(i){
			case 3:
				RR();
				break;
			case 2:
				Prior();
				break;
			case 1:
				FCFS();
				break;
		}
		i++;
		//sleep(10);
	}
	printf("\n\n");
}
