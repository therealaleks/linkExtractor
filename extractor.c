
#include <stdio.h>
#include <string.h>

void main(int argc, char *argv[]){

	FILE * fp = fopen(argv[1], "r");
	size_t sz;
	fseek(fp, 0L, SEEK_END);
	sz = ftell(fp);
	rewind(fp);
	char Stringy[sz + 1];
	fread(Stringy, 1, sz + 1, fp);

	char *pos = Stringy;

	char *keyword1 ="a href=\"/wiki/";
	char *keyword2 = "title=";
	int counter=0;
	char *ahrefLocation = strstr(pos, keyword1);
	
	while (pos < pos+sz) {     //while loop making sure that pos never goes out of bounds
		
		ahrefLocation = strstr(pos, keyword1);    //ahrefLocacion here takes on the index of "a" in "a href="/wiki/"
		
		if(ahrefLocation != NULL){		// if ever strstr cannot find the keyword, the loop breaks

			char *quotation1 = strstr(ahrefLocation+14, "\"");  //we find the " at the right end of the title after "a href="/wiki/"
			char title1[200];
			int titleLength = quotation1-ahrefLocation-14;	//exact length of title1 by computing the difference between the first letter of the title (ahrefLocation+14) and the right side "
			strncpy(title1, (ahrefLocation+15), 6);			//a copy of 6 characters of the title is made (it would only let me do 6 or 7, nothing more, nothing less, weird)

			char *titleTagLocation = strstr(ahrefLocation, keyword2); //now we repeat the process for the title after 'title="'
			char title2[200];
			char *quotation2 = strstr(titleTagLocation+7, "\"");
			int titleLength2 = quotation2 - titleTagLocation - 7; //exact length of title (title begins at titleTagLocation+7)
			strncpy(title2, (titleTagLocation+8), 6);  		
		
			char *endOfTag = strstr(ahrefLocation, ">");	//we find the location of the close of the <a href...> tag
		
			size_t compare = strncmp(title1, title2, 1);	//we compare, for security, if both titles have the same first letter. we wont go deeper due to title2 having '_' instead of spaces
			
			/* now, we know that a tag <> must have both 'a href="/wiki/' and 'title="' to contain a title we are looking for. If the above code line is returns 0, then we know that that
			is true. In the if() function below, we verify that, as well as if the titles have the same first letter and same first length. If all that is true, then we proceed to printing the title*/


			if (titleLength == titleLength2 && endOfTag > titleTagLocation && compare == 0){
				//printf("%d %d ", counter, compare );
				//printf("%d %u %u %s ", bub, bub2, title2);
				//printf("%c %c ", *(locacion+14), *(locacion+15));
				//printf("%s \n",title);
				
				for(int z = 1; z <= titleLength; z++){					//each iteration of the loop prints the next letter from the start of title1, which sits at ahrefLocation+14
					printf("%c", *(ahrefLocation+13+z));
				}
				printf("\n");
				
				//counter++; 
			}
			//printf("%u %u %s %d \n", bub, bub2, title, counter);
			ahrefLocation++;
			pos = ahrefLocation;    //we move up locacion and pos by one so that we may find the next keyword
		}else{
			break;
		}
	}

}
