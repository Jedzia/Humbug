#include <iostream>
//#include <vector>
#include <string>
#ifdef WIN32
#  include <limits>
#else
#  include <limits.h>
#  include <stdlib.h>
#endif

using namespace std;

#define MAXPRIM 1000

#ifndef LINUX
void maxvals()
{
   std::cout<<INT_MAX<<std::endl;
   std::cout<<INT_MIN<<std::endl;
   std::cout<<DBL_MAX<<std::endl;
   std::cout<<DBL_MIN<<std::endl;
   std::cout<<FLT_MIN<<std::endl;
   std::cout<<FLT_MAX<<std::endl;
   //std::cout<<MAXFLOAT <<std::endl;
   //std::cout<<MAXINT <<std::endl;
   std::cout << std::numeric_limits<int>::max() << '\n';
}
#endif

int main()
{
#ifndef LINUX // TODO: fix this for linux
	//long int primarray[MAXPRIM];
	int limit;
	int lf = 0;
	int anzahl = 0;
	bool prim = true;
	 
	cerr << "Bis zu welcher Zahl? " << endl;
	cin >> limit;
	if (limit == 0)
		limit = std::numeric_limits<int>::max();
		
	for(int i=2; i<=limit; i++)
	{
	   for(int k=2; k<i; k++)
		  {
			 if ((i%k) == 0)
			 {
				prim = false;
			 }
	 
		  } 
	   if(prim == true)
	   {
			   //primarray[anzahl] = i;
			   cout << i << " ";
			   if(++lf > 20)
				{
					cout << endl;
					lf = 0;
				}	
			   //if (anzahl == MAXPRIM-1)
			   //	break;
			   anzahl++;
	 
	   }
	   prim = true;
	   //if (i == limit)
		//	   break;
	}
   cout << endl << "Got " << anzahl << " prime numbers" << endl;
#endif

}
