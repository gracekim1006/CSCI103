#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include "bmplib.h"

using namespace std;

//============================Add function prototypes here======================
void dummy(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB]);
void convolve(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB], 
	      int N, double kernel[][11]);
void sobel(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB]);
void gaussian_filter(unsigned char output [][SIZE][3],
 unsigned char input[][SIZE][3],int N, double sigma);
void unsharp(unsigned char output[][SIZE][3], unsigned char input[][SIZE][3], 
			int N, double sigma, double alpha);


//============================Do not change code in main()======================

#ifndef AUTOTEST

int main(int argc, char* argv[])
{
   //First check argc
  if(argc < 3)
    {
      //we need at least ./filter <input file> <filter name> to continue
      cout << "usage: ./filter <input file> <filter name> <filter parameters>";
      cout << " <output file name>" << endl;
      return -1;
    }
   //then check to see if we can open the input file
   unsigned char input[SIZE][SIZE][RGB];
   unsigned char output[SIZE][SIZE][RGB];
   char* outfile;
   int N;
   double sigma, alpha;
   //double kernel[11][11];

   // read file contents into input array
   int status = readRGBBMP(argv[1], input); 
   if(status != 0)
   {
      cout << "unable to open " << argv[1] << " for input." << endl;
      return -1;
   }
   //Input file is good, now look at next argument
   if( strcmp("sobel", argv[2]) == 0)
   {
     sobel(output, input);
     outfile = argv[3];
   }
   else if( strcmp("blur", argv[2]) == 0)
   {
     if(argc < 6)
       {
	 cout << "not enough arguments for blur." << endl;
	 return -1;
       }
     N = atoi(argv[3]);
     sigma = atof(argv[4]);
     outfile = argv[5];
     gaussian_filter(output, input, N, sigma);
   }
   else if( strcmp("unsharp", argv[2]) == 0)
   {
     if(argc < 7)
       {
	 cout << "not enough arguments for unsharp." << endl;
	 return -1;
       }
     N = atoi(argv[3]);
     sigma = atof(argv[4]);
     alpha = atof(argv[5]);
     outfile = argv[6];
     unsharp(output, input, N, sigma, alpha);

   }
   else if( strcmp("dummy", argv[2]) == 0)
   {
     //do dummy
     dummy(output, input);
     outfile = argv[3];
   }
   else
   {
      cout << "unknown filter type." << endl;
      return -1;
   }

   if(writeRGBBMP(outfile, output) != 0)
   {
      cout << "error writing file " << argv[3] << endl;
   }

}   

#endif 

//=========================End Do not change code in main()=====================


// Creates an identity kernel (dummy kernel) that will simply
// copy input to output image and applies it via convolve()
//
// ** This function is complete and need not be changed.
// Use this as an example of how to create a kernel array, fill it in
// appropriately and then use it in a call to convolve.
void dummy(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB])
{
   double k[11][11];
   for (int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         k[i][j] = 0;
      }
   }
   k[1][1] = 1;
   convolve(out, in, 3, k);
}


// Convolves an input image with an NxN kernel to produce the output kernel
// You will need to complete this function by following the 
//  instructions in the comments
void convolve(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB], 
	      int N, double kernel[][11])
{
 
   int padded[SIZE+11][SIZE+11][RGB];  // Use for input image with appropriate 
    //Took out temp for precision purposes                        // padding
   //int temp[SIZE][SIZE][RGB];          // Use for the unclamped output pixel 
                                       // values then copy from temp to out, 
                                       // applying clamping 

   //first set all of padded to 0 (black)
   for(int color = 0; color < RGB; color++)
   {
      for(int row = 0; row < SIZE+11; row++)
      {
      	for(int column = 0; column < SIZE+11; column++)
      	{
      		padded[row][column][color] = 0;
      	}
      }
   }


   //now copy input into padding to appropriate locations
   for(int color = 0; color < RGB; color++)
   {
   	   for(int row = 0; row < SIZE; row++)
   	   {
   	   	   for(int column = 0; column < SIZE; column++)
   	   	   {
   	   	       padded[row+N/2][column+N/2][color] = in[row][column][color];
   	   	   }
   	   }
   }


   //initialize temp pixels to 0 (black)
/*
  Taking out temp allowed me to become more precise
  and it eliminated some pixel errors I was receiving before.
   for(int color = 0; color < RGB; color++)
   {
       for(int row = 0; row < SIZE; row++)
       {
       	   for(int column = 0; column < SIZE; column++)
       	   {
       	       temp[row][column][color] = 0; 
       	   }
       }
   }
   */


   //now perform convolve (using convolution equation on each pixel of the 
   // actual image) placing the results in temp (i.e. unclamped result)
   
   for(int color = 0; color < RGB; color++)
   {
       for(int row = N/2; row < SIZE + N/2; row++)
       {
           for(int column = N/2; column < SIZE + N/2; column++)
           {
              double sum = 0;
           		for(int i = -N/2; i <= N/2; i++)
           		{
           			for(int j = -N/2; j <= N/2; j++)
           			{
           				sum += 
                  padded[row+i][column+j][color]*kernel[(N/2)+i][(N/2)+j];
           			}
           		}
              if(sum > 255)
                  sum = 255;
               if(sum < 0)
                  sum = 0;
              out[row - N/2][column - N/2][color] = (unsigned char) sum;
           }
       }
   }
}

// You will need to complete thisout function by following the 
//  instructions in the comments
void sobel(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB])
{
   double k[11][11];
   double s_h1[3][3] = { {-1, 0, 1}, 
                         {-2, 0, 2}, 
                         {-1, 0, 1} };
   double s_h2[3][3] = { {1, 0, -1}, 
                         {2, 0, -2}, 
                         {1, 0, -1} };
   
   unsigned char h1_soble[SIZE][SIZE][RGB]; //hold intemediate images
   unsigned char h2_soble[SIZE][SIZE][RGB]; 

   for (int i = 0; i < 11; i++)
   {
      for(int j=0; j < 11; j++)
      {
         k[i][j] = 0;
      }
   }


   // Copy in 1st 3x3 horizontal sobel kernel (i.e. copy s_h1 into k)
   for(int row = 0; row < 3; row++)
   {
   	   for(int column = 0; column < 3; column++)
   	   {
   	   	  //Copying whatever values in s_h1 into a bigger k
   	   	  //but limits in loop account for bigger size. 
   	   	  k[row][column] = s_h1[row][column];
   	   }
   }


   // Call convolve to apply horizontal sobel kernel with result in h1_soble
   convolve(h1_soble, in, 3, k);


   // Copy in 2nd 3x3 horizontal sobel kernel (i.e. copy s_h2 into k)
   for(int row = 0; row < 3; row++)
   {
   	   for(int column = 0; column < 3; column++)
   	   {
   	   	  //Copying whatever values in s_h1 into a bigger k
   	   	  //but limits in loop account for bigger size. 
   	   	  k[row][column] = s_h2[row][column];
   	   }
   }


   // Call convolve to apply horizontal sobel kernel with result in h2_soble
   convolve(h2_soble, in, 3, k);


   // Add the two results (applying clamping) to produce the final output 
   for(int color = 0; color < RGB; color++)
   {
       for(int row = 0; row < SIZE; row++)
       {
       	   for(int column = 0; column < SIZE; column++)
       	   {
       	   	   //Clamping 
       	       if(h1_soble[row][column][color] + 
       	       	h2_soble[row][column][color] > 255){	
       	           out[row][column][color] = 255;
       	       }
       	       else if(h1_soble[row][column][color] + 
       	       	h2_soble[row][column][color] < 0){
       	           out[row][column][color] = 0;
       	       }
       	       else{
       	       	   out[row][column][color] = 
       	       	   h1_soble[row][column][color] + h2_soble[row][column][color];
       	       }
       	   }
       }
   } 


}


// Add the rest of your functions here (i.e. gaussian, gaussian_filter, unsharp)
void gaussian(double k[][11], int n, double sigma)
{
	//Creating raw numbers for Gaussian
	double sum = 0.0;
	for(int row = 0; row < n; row++)
	{
		for(int column = 0; column < n; column++)
		{
      /*
			//(x-x0)^2 and (y-y0)^2
			//Calculations for the Gaussian Number
			//n/2 would be the middle point. For x and y.
			//(x - x0)^2
			int xdistsqrd = (row - n/2)*(row - n/2);
			//(y - y0)^2
			int ydistsqrd = (column - n/2)*(column - n/2);
			//Power to be taken to the e
			double epower = -1* ((xdistsqrd + ydistsqrd)/(2*sigma*sigma));
			//e to the power
			double result = exp(epower);
			//put result into kernel 
			k[row][column] = result;
			//Add kernel value to a running sum for normalization
			//purposes.
			sum += result;
      */

      double rsqr = pow(row-(n/2), 2);
      double csqr = pow(column-(n/2), 2);
      double power = (rsqr + csqr) / (2 * pow(sigma, 2));
      double result = exp(power * -1.0);
      k[row][column] = result;
      sum += result;
		}
	}
	//Making each number normalized
	for(int row = 0; row < n; row++)
	{
		for(int column = 0; column < n; column++)
		{
			k[row][column] /= sum;
		}
	}
	

}
void gaussian_filter(unsigned char output [][SIZE][3],
 unsigned char input[][SIZE][3], int N, double sigma)
{
	double k[11][11] = {};
	gaussian(k, N, sigma);
	convolve(output, input, N, k);
}
void unsharp(unsigned char output[][SIZE][3], unsigned char input[][SIZE][3], 
	int N, double sigma, double alpha)
{
	//Storing blurred image into another unsigned character array
	unsigned char blur[SIZE][SIZE][RGB];
	gaussian_filter(blur,input, N, sigma);
	
	for(int color = 0; color < RGB; color++)
	{
		for(int row = 0; row < SIZE; row++)
		{
			for(int column = 0; column < SIZE; column++)
			{
				//S = IM + sigma*D
				//Clamping
        double detail = input[row][column][color] - blur[row][column][color];
        double sharp = input[row][column][color] + (alpha * detail);
				if(sharp < 0)
					sharp = 0;
				else if(sharp > 255)
					sharp = 255; 
				
				output[row][column][color] = (unsigned char) sharp;
			}
		}
	}

}

