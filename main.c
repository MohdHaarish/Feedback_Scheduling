#include <stdio.h>
#include<conio.h>
#include <stdbool.h>
#include <stdlib.h>
struct Process{
    int PID;
    int burst_time;
    int arrival_time;
    int tempburst;
    int intime;
    int outetime;
    int queue;
    int response_time;
    int priority;
};
void priority(struct Process array[], int n);
void roundRobin();
struct Process queue2[200];
int queue2size=0;
int timequantum=4;
bool check(){
    for(int i=0;i<queue2size;i++)if(queue2[i].tempburst!=0)return false;
    return true;
}
void roundRobin(int cpuTime){
    printf("------------Round Robin execution started with Time Quantum of %d -----------\n",timequantum);
    int x=0;
    //printf("In round robin\n");
    while(x<queue2size){
        int remaining=queue2[x].tempburst;
        int initialcpu=cpuTime;
        if(remaining<timequantum) {
            for (int i = initialcpu ; i < initialcpu + remaining; i++){
                printf("========>  Process ID: P%d , Current CPU time: %d  <========\n",queue2[x].PID, ++cpuTime);
                --queue2[x].tempburst;
            }
            ++x;
            x%=queue2size;
        }
        else if(remaining>=timequantum){
            for(int i=initialcpu +1; i<initialcpu+timequantum; i++){
                printf("========>  Process ID: P%d , Current CPU time: %d  <========\n",queue2[x].PID, ++cpuTime);
                --queue2[x].tempburst;
            }
            ++x;
            x%=queue2size;
        }
        else {
            ++x;
            x%=queue2size;
        }
        if(check())break;

    }
}


bool checkhighestpriority(struct Process queue1[], struct Process curPrcs, int *queuesize){
    for(int i=0;i<*queuesize;i++){
        if(curPrcs.priority>queue1[i].priority)return false;
    }
    return true;
}

void putinQueue(struct Process queue1[], struct Process curPrcs, int *queuesize, int *cpuTime){
    if(*queuesize==0){
        queue1[*queuesize]=curPrcs;
        ++*queuesize;
    }
    else {
        if(queue1[0].tempburst<queue1[0].burst_time && queue1[0].priority>curPrcs.priority){
            //printf("Deleting element ********\n");
            for(int i=0;i<*queuesize;i++){
                struct Process temp=queue1[i];
                queue1[i]=queue1[i+1];
                queue1[i+1]=temp;

                //printf("deleting for loop: %d, %d",queue1[i+1].PID, queue1[i].PID);
                //printf("Copied element is : %d\n",queue1[*queuesize].PID);
            }
            queue2[queue2size]=queue1[*queuesize];
            //printf("\n-----------Entered element to q2: %d, size of q2: %d\n",queue2[queue2size].PID, queue2size);
            ++queue2size;
            --*queuesize;
        }
        if (curPrcs.burst_time == curPrcs.tempburst) {
            //printf("Entered into burst if: with pid: %d\n", curPrcs.PID);
            int first = *queuesize;
            queue1[*queuesize] = curPrcs;
            if (queue1[*queuesize].intime == -1)queue1[*queuesize].intime = *cpuTime;
            ++*queuesize;
            while (first != 0 && queue1[(first - 1) / 2].priority > queue1[first].priority) {
                struct Process temp = queue1[(first - 1) / 2];
                queue1[(first - 1) / 2] = queue1[first];
                queue1[first] = temp;
                // checking whether the process is be added into roundRobin queue


                first = (first - 1) / 2;
            }
        } else if (checkhighestpriority(queue1, curPrcs, queuesize)) {
            //printf("Entered into priority if:with pid: %d \n", curPrcs.PID);
            int first = *queuesize;
            queue1[*queuesize] = curPrcs;
            if (queue1[*queuesize].intime == -1)queue1[*queuesize].intime = *cpuTime;
            ++*queuesize;
            while (first != 0 && queue1[(first - 1) / 2].priority > queue1[first].priority) {
                struct Process temp = queue1[(first - 1) / 2];
                queue1[(first - 1) / 2] = queue1[first];
                queue1[first] = temp;
                first = (first - 1) / 2;
            }
        }
    }
}
void rearrangethequeue(struct Process queue1[], int *queuesize, int first){
    //printf("In rearrangement function: \n");
    int initial= *queuesize;
    int before= 2*first+1;
    int after= 2* first+2;
    if(before<*queuesize && queue1[before].priority < queue1[initial].priority)initial=before;
    if(after<*queuesize && queue1[after].priority < queue1[initial].priority)initial=after;
    if(initial != first){
        struct Process temp=queue1[first];
        queue1[first]=queue1[initial];
        queue1[initial]=temp;
        rearrangethequeue(queue1, queuesize, initial);
    }
}

struct Process find_highest_priority(struct Process queue1[], int *queuesize, int *cpuTime){
    struct Process highestprcs=queue1[0];
    if(highestprcs.response_time==-1)highestprcs.response_time = *cpuTime-highestprcs.arrival_time;
    --(*queuesize);
    if(*queuesize>=1){
        queue1[0]=queue1[*queuesize];
        rearrangethequeue(queue1, queuesize, 0);
    }
    return highestprcs;
}

void priority(struct Process array[], int n){
    //sorting using arrival time first
    //printf("In Priority function\n");
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            if(array[i].arrival_time>array[j].arrival_time){
                struct Process temp= array[j];
                array[j]=array[i];
                array[i]=temp;
                array[i].queue=1;
            }
        }
    }
    printf("Processes according to the arrival time: \n");
    for(int i=0;i<n;i++)printf("%d || %d || %d || %d\n",array[i].PID, array[i].arrival_time, array[i].burst_time, array[i].priority);
    printf("\n\n------------Priority Queue execution started from here -----------\n");
    //printf("After sorting: \n");
    int q1process = 0, queuesize = 0, cpuTime = array[0].arrival_time, totalbursttime=0;
    struct Process queue1[4*n];
    for(int i=0;i<n;i++){
        totalbursttime+=array[i].burst_time;
        array[i].tempburst=array[i].burst_time;
    }
    //printf("After finding burst time: \n");
    while(true){
        //printf("In while loop: %d\n",q1process);
        if(q1process!=n){
            //printf("Entered into if: ");
            for(int i=0;i<n;i++){
                //printf("CHecking which is to be inserted: %d : %d\n",array[i].arrival_time,cpuTime);
                if(array[i].arrival_time==cpuTime){
                    ++q1process;
                    array[i].intime=-1;
                    array[i].response_time=-1;
                    //printf("Putting into queue: \n");
                    putinQueue(queue1,array[i],&queuesize, &cpuTime);
                }

            }
        }
        //printf("Size of queue: %d\n",queuesize);
        if(queuesize!=0){
            int x=0;
            //printf("value of x: %d",x);
            while(x<1) {
               // printf("In scheduling: \n");
                struct Process highestprcs = find_highest_priority(queue1, &queuesize, &cpuTime);
                highestprcs.outetime = cpuTime + 1;
                --highestprcs.tempburst;
                printf("========>  Process ID: P%d , Current CPU time: %d  <========\n", highestprcs.PID, cpuTime);
                    //Checking if burst time is remaining:
                if (highestprcs.tempburst > 0) {
                    putinQueue(queue1, highestprcs, &queuesize, &cpuTime);
                    break;
                }
                //printf("After burst check\n");
                for (int i = 0; i < n; i++) {
                    //printf("In for loop\n");
                    if (array[i].PID == highestprcs.PID)array[i] = highestprcs;
                    //printf("After if\n");
                    break;
                }
                x++;
            }
            //printf("Outside internal while\n");
        }
        //printf("At external while: \n");
        ++cpuTime;
        if( q1process==n && queuesize==0 ) break;
    }
    roundRobin(cpuTime);

}
int main() {
    int n=0;
    printf("---------------------------------------  MULTILEVEL FEEDBACK SCHEDULING  ---------------------------------------\n");
    printf("==========> QUEUE 1: FIXED PRIORITY SCHEDULING |||||||||| QUEUE 2: ROUND ROBIN SCHEDULING <==========\n");
    printf("Enter Number of Process: ");
    scanf("%d",&n);
    printf("\nEnter Time quantum: ");
    scanf("%d",&timequantum);
    printf("\nprocesses are: %d",n);
     struct Process array[n];
    printf("\nEnter: \nPID\t Arrival time\t Burst Time\t Priority respectively:\n");
    for(int i=0;i<n;i++){
        scanf("%d %d %d %d",&array[i].PID, &array[i].arrival_time, &array[i].burst_time, &array[i].priority);
    }
    priority(array,5);
    return 0;
}

