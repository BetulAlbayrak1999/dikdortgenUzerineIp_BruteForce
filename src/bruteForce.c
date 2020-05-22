//Brute Force

#include <stdio.h>
#include <stdlib.h>
#include <String.h>

#define size 50
struct shape{
	int start;
	int width;
	int height;
}b[size], temp;


void selectionSort(struct shape a[], int n){
	int min_idx;
	for(int i = 0; i < n; i++){
		min_idx = i;
		for(int j = i + 1; j < n; j++){
			if(a[j].start < a[min_idx].start)
				min_idx = j;
			temp = a[min_idx];
			a[min_idx] = a[i];
			a[i] = temp;
		}
	}
}
int main(void) {
	int shape_count = 0;
	int ipUzunlugu = 0, backHeight = 0, yatayUzunlugu = 0;
	FILE *f = fopen("data.csv", "r");
		if(f != NULL){
			 char buf[1024];
			 printf("veriniz\n");
			 while (fgets(buf, 1024, f)) {
				 b[shape_count].start = atoi(strtok(buf, ","));
				 b[shape_count].height = atoi(strtok(NULL, ","));
				 b[shape_count].width = atoi(strtok(NULL, ","));
			     printf("%d\t%d\t%d\n", b[shape_count].start, b[shape_count].height, b[shape_count].width);
			     shape_count++;
		     }
			 fclose(f);
		}
		else{
			printf("file was not opend\n");
		}
	printf("\n\n");

	//sort edilen sekillleri bastirma
	selectionSort(b, shape_count);
	printf("veriniz sirali bir sekilde baslangic degerlerine gore\n");
	for(int i = 0; i < shape_count; i++){
	     printf("%d\t%d\t%d\n", b[i].start, b[i].height, b[i].width);
		}

	//bitis noktasi belirleme ve width index'inde bitis noktasini sakliyoruz

	for(int k = 0; k < shape_count; k++){
		b[k].width = b[k].width + b[k].start;
	}

	//ip uzunlugu hesaplama

	int j = 0;
	for(int i = 0; i < shape_count; i++){
		j = i + 1;
			//bitis noktalari esit degilse ve iki sekil arasinda bosluk yoksa

			if(b[i].width != b[j].width && !(b[j].start - b[i].width > 0)){

				//ve 1.seklin hem bitis noktalari hem de yuksekligi 2.sekilden buyuk degilse

				if(!(b[i].width > b[j].width && (b[i].height > b[j].height || b[i].height == b[j].height))){
					if(b[i].height - b[j].height > 0)
						  backHeight = backHeight + (b[i].height - b[j].height);
					 else if(b[j].height - b[i].height > 0)
					      backHeight = backHeight + (b[j].height - b[i].height);
				}

				//ve 1.seklin hem bitis noktalari hem de yuksekligi 2.sekilden buyuk,
				//1.sekil ile 3.sekil arasinda islem yapsin

				else if(b[i].width > b[j].width && (b[i].height > b[j].height || b[i].height == b[j].height)){
					j++;
					if(b[i].height - b[j].height > 0 && !(b[j].start - b[i].width > 0))
						  backHeight = backHeight + b[i].height - b[j].height;
			        else if(b[j].height - b[i].height > 0 && !(b[j].start - b[i].width > 0))
						  backHeight = backHeight + b[j].height - b[i].height;
				}
		    }
			else if(b[i].width == b[j].width && b[i].height != b[j].height) {
				if(b[i].height - b[j].height > 0)
					backHeight = backHeight + (b[i].height - b[j].height);
				else if(b[j].height - b[i].height > 0){
					backHeight = backHeight + (b[j].height - b[i].height);
				}
		   }
			//ayri bir sekil varsa
			else if((b[j].start - b[i].width > 0)){
				backHeight = backHeight + b[j].height;
			}
	}

	yatayUzunlugu = b[shape_count - 1].width - b[0].start;
	ipUzunlugu = backHeight + yatayUzunlugu + b[0].height + b[shape_count - 1].height;



	printf("\n\nBeklene sonuc : ip uzunlugu = %d", ipUzunlugu);


	return 0;
}
