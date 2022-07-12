#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <math.h>
#include <string.h>
#include "../include/cencode.h"

struct dirent* dir=NULL;
DIR* rep=NULL;
char* encode(const char* input)
{
	/* set up a destination buffer large enough to hold the encoded data */
	int nbc=0;
	char* output=NULL;
	nbc = strlen(input)+floor(strlen(input)/3.33)+1;
	output = (char*)malloc(nbc*sizeof(char));


	// keep track of our encoded position
	char* c = output;
	// store the number of bytes encoded by a single call
	int cnt = 0;
	// we need an encoder state
	base64_encodestate s;

	//---------- START ENCODING ----------
	// initialise the encoder state
	base64_init_encodestate(&s);
	// gather data from the input and send it to the output
	cnt = base64_encode_block(input, strlen(input), c, &s);
	c += cnt;
	// since we have encoded the entire input string, we know that
	//   there is no more input data; finalise the encoding
	cnt = base64_encode_blockend(c, &s);
	c += cnt;
	//---------- STOP ENCODING  ----------

	// we want to print the encoded data, so null-terminate it:
	*c = 0;
	return output;
}

// char* decode(const char* input)
// {
// 	/* set up a destination buffer large enough to hold the encoded data */
// 	char* output = (char*)malloc(100000);
// 	/* keep track of our decoded position */
// 	char* c = output;
// 	/* store the number of bytes decoded by a single call */
// 	int cnt = 0;
// 	/* we need a decoder state */
// 	base64_decodestate s;
//
// 	/*---------- START DECODING ----------*/
// 	/* initialise the decoder state */
// 	base64_init_decodestate(&s);
// 	/* decode the input data */
// 	cnt = base64_decode_block(input, strlen(input), c, &s);
// 	c += cnt;
// 	/* note: there is no base64_decode_blockend! */
// 	/*---------- STOP DECODING  ----------*/
//
// 	/* we want to print the decoded data, so null-terminate it: */
// 	*c = 0;
//
// 	return output;
// }
char* readfile(char* filedir)
{
	char* data=NULL;
	char* tmpdata=NULL;
	FILE* fic=NULL;
	long int w;
	fic = fopen(filedir,"r");
	fseek(fic,0,SEEK_END);
	w = ftell(fic);
	data = (char*)malloc(w*sizeof(char));
	tmpdata = (char*)malloc(w*sizeof(char));
	fseek(fic,0,SEEK_SET);
	fclose(fic);

	fic = fopen(filedir,"r");
	while(1)
	{
		if(!feof(fic))
		{
			strcpy(tmpdata,"");
			fscanf(fic,"%s",tmpdata);
			strcat(data,tmpdata);
			strcat(data,"\n");
		}
		else break;
	}
	//puts(data);
	fclose(fic);
	free(tmpdata);
	return data;
}
void encodefile(char* filedir,char* data)
{
	// write file
	FILE* fic;
	fic = fopen(filedir,"w");
	//fprintf(fic,"let %s = %c%s%c;",dir->d_name,'"',encode(data),'"');
	fprintf(fic,"%s",encode(data));
	fclose(fic);
}
int main(int narg,char *tchar[])
{
    char* data=NULL;
	char filedir[80];
    rep = opendir("asset");
	//int long w;
     if(rep!=NULL)
     {
         dir=readdir(rep);
         while(dir!=NULL)
         {
             if(strlen(dir->d_name)>2)
             {
                 // read eatch file
				puts(dir->d_name);
				strcpy(filedir,"asset/");
				strcat(filedir,dir->d_name);
				data=readfile(filedir);
				//puts(data);
 				strcpy(filedir,dir->d_name);
 				strcat(filedir,".js");
 				encodefile(filedir,data);
 				free(data);
             }
             dir = readdir(rep);
		}
        closedir(rep);
     }
    return 0;
}
