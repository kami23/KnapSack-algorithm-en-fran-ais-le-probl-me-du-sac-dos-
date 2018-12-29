#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<sys/time.h>


int max(int a,int b)
{
	if (a>b) return a;
	else return b;
}
/****Solution r�ccursive****/
int sacADosReccursive(int nbElem,int tabVal[],int tabPd[],int pdMax,int tabVl[],int vlMax){
  int k,v,z;
   if (nbElem == 0 || pdMax == 0||vlMax==0)
        {return 0;}
   else
   {
       if (tabPd[nbElem-1] > pdMax||tabVl[nbElem-1] >vlMax)
       {

         return sacADosReccursive(nbElem-1, tabVal,tabPd,pdMax,tabVl,vlMax);
       }
       else  {
         v= tabVal[nbElem-1] + sacADosReccursive(nbElem-1, tabVal,tabPd,pdMax-tabPd[nbElem-1],tabVl,vlMax-tabVl[nbElem-1]);
         z=sacADosReccursive(nbElem-1, tabVal, tabPd,pdMax,tabVl,vlMax);
         k=max(v,z);
         return k;
        }
}
}
/****Solution avec programmation dynamique****/

int sacADosProgDynamique(int nbElem,int tabVal[],int tabPd[],int pdMax,int tabVl[],int vlMax){
int i,p,v,x,y,z;

int (*tab)[pdMax+1][vlMax+1];

tab = malloc((nbElem+1) * sizeof *tab);

for (i = 0; i <= nbElem; ++i)
{
	for (p = 0; p <= pdMax; ++p)
	{
		for(v=0;v<=vlMax;++v)
            {
		if(i==0||p==0||v==0) {tab[i][p][v]=0;}
		else {
                y=tab[i-1][p][v];
			         if(tabPd[i-1]>p||tabVl[i-1]>v)   {tab[i][p][v]=y;}
		           else{
                       x=tab[i-1][p-tabPd[i-1]][v-tabVl[i-1]]+tabVal[i-1];
                       tab[i][p][v]=max(x,y);
                     }
		      }

        	}
}
} x=tab[nbElem][pdMax][vlMax];
free(tab);
return x;
}


void remplirTab(int nbElem,int tabPd[],int tabVl[],int tabVal[]){
   for(int i=0;i<nbElem;++i)
   {
       tabPd[i]=rand()%100;
       tabVl[i]=rand()%100;
       tabVal[i]=rand()%50;
   }
}
int main()
{  FILE *ptr;
    ptr=fopen("Statisque.txt","w+");
    if(ptr==NULL){printf("File not created");exit(-1);}
    else{
    fprintf(ptr,"nbElement\t    GainOpt\t     TempsRec(ms)\t    TempsDyn(ms)\t\n");

    long t;
    struct timeval tv1, tv2;
    int gainMax;
    /*int tabVal[] = {60, 100, 120};
    int tabPd[] = {10, 20, 30};
    int tabVl[]={20,40,70};
    int tabSelect[]={0,0,0};
    int  pdMax = 30;
    int vlMax=40;*/
   /*int tabVal[]={6,8,14,6,13,17,10,04,05,11,26,35,2,1,2,7,15,17,30,3};
    int tabPd[]  ={20,30,50,20,40,60,30,10,14,36,72,86,05,03,07,23,49,57,69,12};
   int tabVl[]={10,15,25,10,20,30,15,5,7,18,36,43,3,2,4,12,25,29,35,6};*/
     int nbElem =60;
     int tabPd[nbElem];
     int tabVl[nbElem];
     int tabVal[nbElem];
    int  pdMax = 520;
    int vlMax=300;

    int tabSelect[nbElem];int i=10;
   while(i<=nbElem)
    {
    remplirTab(i,tabPd,tabVl,tabVal);
    printf("*******************************\n");
    printf("Nombre d'objets = %d\n",i);
    /***Execution Recursive***/
    gettimeofday(&tv1,NULL);
    gainMax=sacADosReccursive(i,tabVal,tabPd,pdMax,tabVl,vlMax);
    gettimeofday(&tv2,NULL);
    t = (tv2.tv_sec - tv1.tv_sec)*1000000 + (tv2.tv_usec - tv1.tv_usec);
    fprintf(ptr,"\t%d\t    \t%d\t      \t%ld\t    ",i,gainMax,t/1000);
    printf("Execution reccurcive: \n Gain max = %d\n Temps Execution:%ld ms\n", gainMax,t/1000);
    /****************************/
    /****Execution Dynamique****/
    gettimeofday(&tv1,NULL);
    gainMax=sacADosProgDynamique(i,tabVal,tabPd,pdMax,tabVl,vlMax);
    gettimeofday(&tv2,NULL);
    t = (tv2.tv_sec - tv1.tv_sec)*1000000 + (tv2.tv_usec - tv1.tv_usec);
    fprintf(ptr,"\t%d\t\n",t/1000);
    printf("Execution programmation dynamique: \n Gain max = %d\n Temps Execution:%ld ms\n", gainMax,t/1000);
    /*************************/
    i=i+10;
    }
    fclose(ptr);
    return 0;
    }
}


