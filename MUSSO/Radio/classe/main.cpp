#include "Radio.h"


int main(int argc, char **argv)
{
	double freq;
	int choix;
	char i[5];

	freq = atof(argv[1]);

	Radio radio(argc);
	radio.setradio(freq);
	while(1)
	{
		cout<<"1 = Muer: "<<endl;
		cout<<"2 = deMuer: "<<endl;
		cout<<"3 = frequense: "<<endl;
		cout<<"4 = quiter: "<<endl;
		scanf ("%d", &choix);
	  	while (getchar() != '\n');

	  	switch(choix)
	  	{
	  		case 1: radio.mute(freq);
	  				break;

	  		case 2: radio.setradio(freq);
	  				break;

	  		case 3: cout<<"choix frquens:"<<endl;
	  				scanf ("%s", i);
	  				while (getchar() != '\n');
	  				freq = atof(i);
					radio.setradio(freq);
	  				break;

	  		case 4: exit (0);
	  				break;
	  	}
	}
	
	return 0;
}