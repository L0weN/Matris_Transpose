#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void matrisolustur();
void matrisbelirle();
void matrissirala();
void matrissonuc();
void matristranspose();
void kaprekars();

struct matris{
	int matrissatir;
	int matrissutun;
	int **matris;
};
struct matris dizi;

int main() {
	
	matrisolustur();
	free(dizi.matris);

	return 0;
}

void matrisolustur(){
	printf("matris satir: ");
	scanf("%d",&dizi.matrissatir);
	
	printf("matris sutun: ");
	scanf("%d",&dizi.matrissutun);
	matrisbelirle();
}

void matrisbelirle() {
    srand(time(NULL));
    int i,j;
    dizi.matris = (int**)malloc(dizi.matrissatir*sizeof(int*));
    for(i=0; i<dizi.matrissatir; i++) {
        dizi.matris[i] = (int*)malloc(dizi.matrissutun*sizeof(int));
        for(j=0; j<dizi.matrissutun; j++) {
            dizi.matris[i][j] = (int*)malloc(dizi.matrissutun*sizeof(int));
            dizi.matris[i][j]=5 + rand()%40000;
        }
    }
    matrissirala();
}

void matrissirala(){
	int i,j,k,l,m;
	for(i=0;i<dizi.matrissatir*dizi.matrissutun;i++)
	{
		for(j=0;j<dizi.matrissatir;j++)
		{
			for(k=0;k<dizi.matrissutun-1;k++)
			{
				if(dizi.matris[j][k] > dizi.matris[j][k+1])
				{
					m = dizi.matris[j][k];
					dizi.matris[j][k] = dizi.matris[j][k+1];
					dizi.matris[j][k+1] = m;
				}
			}
		}
		for(l=0;l<dizi.matrissatir-1;l++)
		{
			if(dizi.matris[l][dizi.matrissatir-1] > dizi.matris[l+1][0])
			{
				m = dizi.matris[l][dizi.matrissatir-1];
				dizi.matris[l][dizi.matrissatir-1] = dizi.matris[l+1][0];
				dizi.matris[l+1][0] = m;
			}
		}
	}
	matrissonuc();
}

void matrissonuc(){
	int i,j;
	printf("Matris:\n");
	for(i=0;i<dizi.matrissatir;i++)
	{
		for(j=0;j<dizi.matrissutun;j++)
		{
			printf("%d\t",dizi.matris[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	FILE *fp;

	fp = fopen("transposesiz.txt","w+");
	for(i=0;i<dizi.matrissatir;i++)
	{
		for(j=0;j<dizi.matrissutun;j++)
		{
			fprintf(fp,"%d\t",dizi.matris[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	matristranspose();
}

void matristranspose(){
	int i,j;
	printf("Transposeli Matris:\n");
	for(i=0;i<dizi.matrissutun;i++)
	{
		for(j=0;j<dizi.matrissatir;j++)
		{
			printf("%d\t",dizi.matris[j][i]);
		}
		printf("\n");
	}
	FILE *fp;

	fp = fopen("transposeli.txt","w+");
	for(i=0;i<dizi.matrissutun;i++)
	{
		for(j=0;j<dizi.matrissatir;j++)
		{
			fprintf(fp,"%d\t",dizi.matris[j][i]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	kaprekars();
}
bool kaprekar(int a) {
	int c,z,n;
    if (a == 1) {
        return true;
    }
    int akare = a*a;
    int h = 0;
    while (akare) {
        h++;
        akare /= 10;
    }
    akare = a*a;
    for (c=1; c<h; c++) {
        int z = pow(10, c);
        if (z == a) {
            continue;
        }
        int toplam = ((akare/z) + akare) % z;
        if (toplam == a) {
            return true;
        }
    }
    return false;
}
void kaprekars()
{
	FILE *kp;
	kp = fopen("kaprekar.txt","w+");
	fprintf(kp,"Kaprekar sayilar: ");
	fclose(kp);
	
	int i,j,toplamkaprekar=0;
	printf("Kaprekarlar:\n");
	for(i=0;i<dizi.matrissutun;i++)
	{
		for(j=0;j<dizi.matrissatir;j++)
		{
			if(kaprekar(dizi.matris[j][i]) == true)
			{
				toplamkaprekar++;
				kp = fopen("kaprekar.txt","a+");
				printf("%d\t",dizi.matris[j][i]);
				fprintf(kp,"%d\t",dizi.matris[j][i]);
				fclose(kp);
			}
		}
	}
	if(toplamkaprekar == 0)
	{
		printf("\nHic kaprekar yok");
	}
}