#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include <stdbool.h>
#include<signal.h>
#include<unistd.h>


int nfaces;
bool RUN=1;
FILE *fptr;

void stopall(int dummy){
	fclose(fptr);
	printf("\n\n<<< STOPALL >>>\n\n");
	RUN=0;
	exit(0);
}

double avg(int d[nfaces]){
	double tot=0;
	for(int c=0; c<nfaces; c++){
		tot+=d[c];
	}
	//printf("\navg %f %d", tot/nfaces, d[0]);
	return tot/nfaces;
}

double stddev(int d[nfaces]){
	double a=avg(d), sd=0, nv=0;
	for(int c=0; c<nfaces; c++){
		//printf("\nNow %f", d[c]-a);
		nv=d[c]-a;
		sd+=nv*nv;
	}
	//printf("\nNOW: %f", nv);
	return sqrt(sd/nfaces);
}

int main(int argc, char *argv []){
	nfaces=6;
	int srate=0;
	int limit=-1;
	if(argc>1){
		nfaces=atoi(argv[1]);
		printf("\nCustom faces: %d", nfaces);
	}
	if(argc>2){
		printf("\nConverting 2");
		srate=atoi(argv[2]);
		printf("\nCustom sample rate: %d", srate);
	}
	if(argc>3){
		printf("\nConverting 2");
		limit=atol(argv[3]);
		printf("\nCustom limit: %d", limit);
	}
	int r, c=1, d[nfaces];
	for(int c=0; c<nfaces; c++){
		 d[c]=0;
	}
	fptr=fopen("stddev.log", "w");
	double sd;
	signal(SIGINT, stopall);
	srand(time(NULL));   // Initialization, should only be called once.
	double sdsum=0, avgsum=0;
	while(RUN && c!=limit){
		if(srate!=0){
			if(c%srate==0&&c>0){
				//printf("\e[1;1H\e[2J");
				//printf("\n[Face %d]: %d, %f \%", cc, d[cc], (int)100*(double)d[cc]/c);
				//printf("\nc: %d STDDEV: %f SD/AVG: %f", c, sd, 100*sd/avg(d));
				fprintf(fptr, "\nC: %d STDDEV: %f SD/AVG: %f", c, sdsum/srate, 100*(sdsum/srate)/(avgsum/srate));
				sdsum=0;
				avgsum=0;
				
			}
		}
		else{
		}
		//printf("\e[1;1H\e[2J");
		r = rand()%nfaces;
		d[r]++;
		//printf("\nC: %d\n", c);
		sd=stddev(d);
		sdsum+=sd;
		avgsum+=avg(d);
		sleep(0.1);
		//system("sleep 0.05 && clear");
		c++;
	}
	printf("Done: %d\n", c);
	fclose(fptr);
}
