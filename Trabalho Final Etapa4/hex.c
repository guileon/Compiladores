#include "hex.h"

int atoh(char * val)
{

	int size = strlen(val);
	int i=size-1;
	int result =0;
	char c = val[0];
	while(c!='\0')
	{
	
		if(c=='f' || c=='F')
			result+=15*pow(16,i);
		else if(c=='e'|| c=='E')
			result+=14*pow(16,i);
		else if(c=='d'|| c=='D')
			result+=13*pow(16,i);
		else if(c=='c'|| c=='C')
			result+=12*pow(16,i);
		else if(c=='b'|| c=='B')
			result+=11*pow(16,i);
		else if(c=='a'|| c=='A')
			result+=10*pow(16,i);
		else
			switch(c)
			{
				case '0': result+=0*pow(16,i); break;
				case '1': result+=1*pow(16,i); break;
				case '2': result+=2*pow(16,i); break;
				case '3': result+=3*pow(16,i); break;
				case '4': result+=4*pow(16,i); break;
				case '5': result+=5*pow(16,i); break;
				case '6': result+=6*pow(16,i); break;
				case '7': result+=7*pow(16,i); break;
				case '8': result+=8*pow(16,i); break;
				case '9': result+=9*pow(16,i); break;
			}
		i--;
		c = val[size-1 - i];
	}
	return result;
}

char * htoa(int val)
{
	char * str = (char*)calloc(33,sizeof(char));
	itoa(val,str,16);
	return str;
}