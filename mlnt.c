#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>

double avg(int d[6]){
	double tot=0;
	for(int c=0; c<6; c++){
		tot+=d[c];
	}
	printf("\navg %f %d", tot/6, d[0]);
	return tot/6;
}

double stddev(int d[6]){
	double a=avg(d), sd=0, nv=0;
	for(int c=0; c<6; c++){
		printf("\nNow %f", d[c]-a);
		nv=d[c]-a;
		sd+=nv*nv;
	}
	printf("\nNOW: %d", nv);
	return sqrt(sd/6);
}

int main(){
	int r, c=1, d[6]={0,0,0,0,0,0};
	double sd;
	srand(time(NULL));   // Initialization, should only be called once.
	while(1){
		r = rand()%6;
		d[r]++;
		for(int cc=0; cc<6; cc++){
			printf("\nDice: %d, %f \%", d[cc], (int)100*(double)d[cc]/c);
		}
		sd=stddev(d);
		printf("\nSTDDEV: %f SD/AVG: %f", sd, 100*sd/avg(d));
		system("sleep 0.05 && clear");
		c++;
	}
	printf("Done: %d", c);
}
