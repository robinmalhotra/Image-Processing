/*******************************************************************************
*       visualimage01.cpp - Program for Image Negation. Contrast Stretching and
*                           Histogram Equalization is performed for gray scale 
*                           and color images.
*
*       Note : Histogram Equalization in RGB color space does not provide satisfactory
*              results. Use HSI color space for Histogram Eqalization for color images. 
*_______________________________________________________________________________ 
*               The program reads the TIFF file,interprets,processes and writes
*               the processed image to an output file.
*_______________________________________________________________________________
*               Program tested for e32.tif, wom1.tif, beans.tif, color.tif,
*               family.tif and lilli.tif files.
*                
*_______________________________________________________________________________
*      Notes: 1) Program has been implemented in Microsoft's Visual C++6.0 under 
*                Windows environment and can be execetued under "Build" menu 
*                item of Visual C++6.0 or through "command line". It may not run 
*                purely under DOS environment because the memory requirement is
*                high.
*             2) This is not a product. This serves a demo for zooming operation 
*_______________________________________________________________________________
*	Developed By: Dr. Chandan Singh,
*		      Professor and Head,
*		      Department of Computer Science,
*		      Punjabi University, Patiala, India - 147 002
*             Phones : +91-175-3046316(O), 3046313(O), 2283209(R)
*             FAX :    +91-175-3046313.
*     	Date : January 15,2005.
*	Reference : 1) TIFF, Revision 6.0, (June 1992). Adobe Developers Association.
*	               www.adobe.com/Support/TechNotes.html 
*                  and ftp://ftp.adobe.com/pub/adobe/DeveloperSupport/TechNotes/PDFfiles
*               2) Digital Image Processing by Rafael C. Ganzalez and
*                  Richard E. Woods, Third Edition, Pearson Education, India, (for image
*                  processing operations)
**************************************************************************
*/

#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <process.h>
#include <math.h>

#define MAXSIZE 1024

void  Read_Tiff_File(void);
void copy_array_to_file(unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE], FILE *outfile_ptr);
void copy_to_array(unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char *IB, unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void copy_array_to_file_binary(unsigned long ImageLength, unsigned long ImageWidth, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE], FILE *outfile_ptr);
void copy_to_text_file(unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE]);
void display_error( char *message);




void Negation(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Log_Transformation(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void PowerLaw_Transformation(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Contrast_Stretch(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Intensity_Level(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Bit_Plane(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Histogram_Eq(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Filtering_mask(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Filtering_Gaussian(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Filtering_Order_Stat(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Filtering_Laplacian(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);

int round(double dd);
void logical_op(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Filtering_Sobel(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Filtering_Robercross(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Laplacian_Image(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Laplacian_Sign(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Unsharp_Mask(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void xy_Sobel(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void F_T(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Power_Spectrum(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Mean_Filters(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Notch_Filter(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Negation_RGB(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Order_Stat(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Adaptive_LNR( unsigned long ImageLength, unsigned long ImageWidthByte, unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] );
void Adaptive_Median( unsigned long ImageLength, unsigned long ImageWidthByte, unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] );

void pseudo_RGB(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void HE_RGB( unsigned long ImageLength, unsigned long ImageWidthByte, unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] );

void Power_Spectrum(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void ideal_filter(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Butterworth_Filter(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Gaussian_Filter(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);
void Laplacian_Filter(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE]);




//  This following function may be used later

unsigned long ImageWidth, ImageLength, StripOffsets, RowsPerStrip,
StripsPerImage, ImageWidthByte, ImageSize, StripByteCounts;

short int BitWhite;
short int ResolutionUnit, BitsPerSample;
unsigned long XResolution, YResolution, NoOfStrips;
void *ImageBuffer;
main()
{
	Read_Tiff_File();
	return(0);
}

void  Read_Tiff_File()
{
	long int n, sumR, sumG, sumB, nkR[256], sR[256], nkG[256], 
		sG[256], nkB[256], sB[256];
	short unsigned int i, j, reply, reply2=0;
	short unsigned int byte_order, TIFF_identifier;
	unsigned short int no_of_entries, tag, field_type, temp;
	unsigned long offset_address, count, value, so, sbc, StripAddress,
		StripSize;
	unsigned long file_position;
	unsigned char *IB, item;
	unsigned char *ib, fxy[MAXSIZE][3*MAXSIZE], fxyout[MAXSIZE][3*MAXSIZE];  // for RGB
	unsigned char in_filename[14], out_filename[14], pic_byteR, pic_byteG, pic_byteB; 
	FILE *infile_ptr, *outfile_ptr;
	
	// Open the input file for processing
	printf("Input TIFF File ? : ");
	scanf( "%s", in_filename);
	if((infile_ptr = fopen((const char *)in_filename, "rb+")) ==NULL)
	{
		printf("can't open file - %s - either the filename is wrong or the"
			" file does not exist\n", in_filename);
		exit(0);
	}
	
	// Open a new file for storing the processed image
	printf("Output TIFF File ? : ");
	scanf( "%s", out_filename);
	if((outfile_ptr = fopen((const char *)out_filename, "wb")) ==NULL)
	{
		printf("Error in opening file - %s - the filename may be wrong"
			, out_filename);
		exit(0);
	}
	/*---- Copy the existing file to the new file  */
	while( fread((void *)&item, (size_t)1, (size_t)1, infile_ptr) !=0)
	{
		fwrite((void *)&item, (size_t)1, (size_t)1, outfile_ptr);
	}
	//     bring the file pointer to the beginning of the input file
	rewind(infile_ptr);
	//     Close the output file and reopen it in read & write modes
	fclose(outfile_ptr);
	if((outfile_ptr = fopen((const char *)out_filename, "rb+")) ==NULL)
	{
		printf("Error in opening file - %s - the filename may be wrong"
			, out_filename);
		exit(0);
	}
	 printf("Enter 1 for Image Negation: \nEnter 2 for Enhancement: \nEnter 3 for log transformation:\nEnter 4 for power Law transformation: \nEnter 5 for Contrast Stretching: \nEnter 6 for Intesity Level Slicing:\nEnter 7 for Bit Plane Slicing:\nEnter 8 for Histogram Equalization:\nEnter 9 for Histogram Matching:\n Enter 10 for fitering:\n Enter 11 for Gaussian fitering:\n Enter 12 for Order statistics fitering:\n Enter 13 for laplacian :\n Enter 14 for logical operations :\nEnter 15 for filtering using Sobel: \nEnter 16 for filtering using Robert cross: \nEnter 17 for laplacian Image:\nEnter 18 for laplacian Sign: \nEnter 19 for unsharp masking :\nEnter 20 for sobels:\nEnter 21 for fourier transform:\nEnter 22 for spectrum:\nEnter 23 for Mean Filter:\nEnter 24 for notch Filter:\nEnter 25 for negation RGB:\nEnter 26 for Order Stat:\nEnter 27 for adaptive LNR filter:\nEnter 28 for adaptive MEDIAN filter:\nEnter 29 for pseudo RGB:\nEnter 30 for ideal filter:\nEnter 31 for Histogram Eql of RGB:\nEnter 32 for Power Spectrum:\nEnter 33 for Butterworth:\nEnter 34 for Gaussian:\nEnter 35 for Laplacian Filter:");
   scanf("%d", &reply);
   if(reply<1||reply>50) display_error("Choice no. wrong");

		
	/*---- Read byte_order, TIFF_identifier and offset to the first image file
	   directory(IFD).
	*/
	//   byte_order = getw(infile_ptr);
	fread((void *)&byte_order, (size_t)2, (size_t)1, infile_ptr);
	
	//   TIFF_identifier = getw(infile_ptr);
	fread((void *)&TIFF_identifier, (size_t)2, (size_t)1, infile_ptr);
	if(byte_order != 0x4949)  display_error("Byte Order not Intel Processor"
		" Compatible");
	if(TIFF_identifier != 0x002A)  display_error("File is not a valid TIFF file");
	fread((void *)&offset_address, (size_t)4, (size_t)1, infile_ptr);
	//   printf("offset address=%lu\n", offset_address);
	fseek(infile_ptr, offset_address, SEEK_SET);
	
	/*---- Read the total number of entries and the contents of the entries
	   themselves.
	*/
	//   no_of_entries = getw(infile_ptr);
	fread((void *)&no_of_entries, (size_t)2, (size_t)1, infile_ptr);
	//   printf("no_of_entries=%u\n", no_of_entries);
	/*---- Read Tag identifying the field, Field type, Number of values or count
	   of the type, Offset into the file where the value begins.
	*/
	for(i=0; i<no_of_entries; i++)
	{
		//      tag = getw(infile_ptr);
		fread((void *)&tag, (size_t)2, (size_t)1, infile_ptr);
		//      field_type = getw(infile_ptr);
		fread((void *)&field_type, (size_t)2, (size_t)1, infile_ptr);
		fread((void *)&count, (size_t)4, (size_t)1, infile_ptr);
		fread((void *)&value, (size_t)4, (size_t)1, infile_ptr);
		//      printf("tag =%u, field_type=%u, count=%lu, value=%lu\n",
		//		   tag, field_type, count, value);
		/*	  getch(); */
		/* Only a few tag information are required for a bilevel/gray scale scanned
		image. Other tags are skipped.  */
		switch(tag)
		{
		case 256 : /* Image Width. Number of columns in the image(pixels
				   per row. Only one bit per pixel is required for a
			bilevel system.  */
			ImageWidth = value;
			break;
		case 257 : /* Image Length. Number of rows of pixels in the image. */
			ImageLength = value;
			break;
		case 258 : /* BitsPerSample. The number of bits per component. */
			BitsPerSample = (short)value;
			//		     printf("Bits per sample=%d\n", BitsPerSample);
			//		     getch(); exit(0);
			break;
		case 259 : /* Compression. If the count =1, then there is no
			compression. */
			if(value !=1) display_error("Image is compressed. "
			"Can't process");
			break;
			case 262 : /* Photometric Interpretation. Determines the meaning
			of a bit.  */
			if(value<0 || value >3)
			display_error("The Image is not binary/8-bit gray"
				"/8-bit coloured/24-bit colour");
			BitWhite =0;
			if(value ==1) BitWhite =1;
			//printf("count=%lu, value=%lu,  BitWhite=%d\n", count, value, BitWhite); getch();
			break;
					
		case 273 : /* Strip Offsets. Byte offset for each strip. Specifies
				   the location of a strip with respect to the beginning
				of a tiff file. */
			NoOfStrips = count;
			StripOffsets= value;
			break;
		case 278 : /* Rows Per Strip. Number of rows per strip.  */
			RowsPerStrip = value;
			StripsPerImage =(ImageLength + RowsPerStrip -1)/RowsPerStrip;
			break;
		case 279 : /* Strip Byte Counts. For each strip, the number of bytes
					in it after compression. */
			StripByteCounts = value;
			break;
		case 282 : /* X-Resolution. Number of pixels per ResolutionUnit
					in the ImageWidth direction.  */
			XResolution = (short)value;
			break;
		case 283 : /* Y-Resolution. Number of pixels per ResolutionUnit
				in the ImageLength direction.  */
		    YResolution = (short)value;
			break;
		case 296 : /* Resolution Unit. Unit of measurement for X-Resolution
									   and Y-Resolution.
				   per row. Only one bit per pixel is required for a
				bilevel system.  */
			ResolutionUnit= (short)value;
			break;
		default :   break;
		}
	}
	/*   printf("ImageWidth, ImageLength, StripOffsets, RowsPerStrip,"
	" StripsPerImage, No. of Strips=%lu, %lu, %lu, %lu, %lu, %lu\n",
	   ImageWidth, ImageLength, StripOffsets, RowsPerStrip,
	   StripsPerImage, NoOfStrips);
	   printf("BitWhite, XResolution, YResolution, ResolutionUnit=%d, "
	   "%d, %d, %d\n", BitWhite, XResolution,
			 YResolution, ResolutionUnit);  */
	
	/*  Store the image in a buffer pointed to by ImageBuffer.  */
	
	if(BitsPerSample == 1) ImageWidthByte = (ImageWidth + 7)/8;
    else  if(BitsPerSample == 8) ImageWidthByte = ImageWidth;
    else  if(BitsPerSample == 24) ImageWidthByte = 3*ImageWidth;
	ImageSize = ImageWidthByte*ImageLength;
	n=ImageSize;
	//  printf("ImageSize=%lu\n", ImageSize);
	ImageBuffer =  malloc(ImageSize);
	if(ImageBuffer == NULL)
		display_error("Unable to allocate memory for storing the image"
		" in memory");
	
	/*  Zeroize the contents of the Image Buffer  */
	IB = (unsigned char *)ImageBuffer;
	for(i=0; i<ImageLength; i++)
		for(j=0; j<ImageWidthByte; j++)
		{
			(*IB) =0;
			IB++;
		}
		
		
		/*  Read the image data stored in strips in the TIFF format and build up
		a memory block where the whole data is stored.  */
		
		so = StripOffsets;  sbc = StripByteCounts;  ib = (unsigned char *)ImageBuffer;
		/*   printf("ImageSize=%lu\n", ImageSize);
		printf("NoOfStrips=%lu\n", NoOfStrips);
		printf("Strip offset=%lu\n", so);
		printf("Strip Byte Counts=%lu\n", StripByteCounts);
		getch();  */
		if(NoOfStrips ==1)
		{
			fseek(infile_ptr, so, SEEK_SET);
			/*  The location of the input file pointer is required to position the file
			pointer of the output file at the place from where the processed data in
			the output file is to be stored.
			*/
			file_position = (unsigned long)ftell(infile_ptr);
			//      printf("Position of input file pointer before storing the image=%d\n",
			//	       file_position);  getch();
			temp =fread(ImageBuffer, (size_t)1, (size_t)ImageSize, infile_ptr);
			//     printf("No of bytes read=%lu\n", temp);
			//     getch();
		}
		else
		{
			for(i=0; i<NoOfStrips; i++)
			{
				fseek(infile_ptr, so, SEEK_SET);
				fread(&StripAddress, 4, 1, infile_ptr);
				//       printf("StripAddress for %d strip = %lu\n", (i+1), StripAddress);
				so = so + 4;
				fseek(infile_ptr, sbc, SEEK_SET);
				sbc = sbc +4;
				fread(&StripSize, 4, 1, infile_ptr);
				//   printf("StripSize = %lu\n", StripSize);
				//     getch();
				fseek(infile_ptr, StripAddress, SEEK_SET);
				/*  The location of the input file pointer is required to position the file
				pointer of the output file at the place from where the processed data in
				the output file is to be stored.
				*/
				if(i==0)
				{
					file_position = (unsigned long) ftell(infile_ptr);
					//	 printf("Position of input file pointer before storing"
					//	   "a strip=%lu\n", file_position);  getch();
					
				}
				fread(ib, (size_t)StripSize, (size_t)1, infile_ptr);
				(unsigned char *)ib = (unsigned char *)ib + StripSize;
			}
		}

		IB = (unsigned char *)ImageBuffer;
        copy_to_array(ImageLength, ImageWidthByte, IB, fxy);




		if(reply ==1)
		{
			//Image Negation	
			Negation(ImageLength, ImageWidthByte, fxyout, fxy);
			
		} 
		

		if(reply ==3)
		{
			// Log Transformation
			Log_Transformation(ImageLength, ImageWidthByte, fxyout, fxy);
		} 
		
		

		if(reply ==4)
		{
			// Power Law Transformation
			PowerLaw_Transformation(ImageLength, ImageWidthByte, fxyout, fxy);
		}
		

		
		if(reply ==5)
		{
			// Contrast Stretching
				Contrast_Stretch(ImageLength, ImageWidthByte, fxyout, fxy);
				
		} 
		
		
		if(reply ==6)
		{
			// Intensity Level Slicing
			Intensity_Level(ImageLength, ImageWidthByte, fxyout, fxy);
		} 


		if(reply ==7)
		{
			// Bit Plane Slicing
			Bit_Plane(ImageLength, ImageWidthByte, fxyout, fxy);


		}


		if(reply ==8)
		{
			// Bit Plane Slicing
			Histogram_Eq(ImageLength, ImageWidthByte, fxyout, fxy);


		}


		if(reply ==10)
		{
				// Image Filtering un-weighted (1,1,1,1,1,1,1,1,1) and weighted( we can assign any weight) filter.

				Filtering_mask(ImageLength, ImageWidthByte, fxyout, fxy);
		}


		if(reply ==11)
		{
				// Image filtering using Gaussian Filter
				Filtering_Gaussian(ImageLength, ImageWidthByte, fxyout, fxy);	
  
		}




		if(reply ==12)
		{
			//  Order statistics filtering (Median, max, min ,mean filter)
				Filtering_Order_Stat(ImageLength, ImageWidthByte, fxyout, fxy);
		}




		if(reply ==13)
		{
				// Laplacian Filter (Addition OR Subtraction Depend upon the sign of the center)
				Filtering_Laplacian(ImageLength, ImageWidthByte, fxyout, fxy);
		}	
		
	
	
	
	
	if(reply==14)
		{
			// Logical operation(AND,OR,NOT,XOR)

			logical_op(ImageLength, ImageWidthByte, fxyout, fxy);
			
		}

	if(reply==15)
		{
			

			Filtering_Sobel(ImageLength, ImageWidthByte, fxyout, fxy);
			
		}

	
	if(reply==16)
		{
			// Logical operation(AND,OR,NOT,XOR)

			Filtering_Robercross(ImageLength, ImageWidthByte, fxyout, fxy);
			
		}

	if(reply==17)
	{
			 Laplacian_Image(ImageLength, ImageWidthByte, fxyout, fxy);
			
			
	}
	if(reply==18)
	{
			 Laplacian_Sign(ImageLength, ImageWidthByte, fxyout, fxy);
			
	}

	if(reply==19)
	{
			 Unsharp_Mask(ImageLength, ImageWidthByte, fxyout, fxy);
			
	}
	if (reply==20)
	{

		xy_Sobel(ImageLength,ImageWidthByte,fxyout,fxy);
	}

	if(reply==21)
	{
			F_T(ImageLength,ImageWidthByte,fxyout,fxy);
	}

/*	if(reply==22)
	{
			Power_Spectrum(ImageLength,ImageWidthByte,fxyout,fxy);
	}*/
	
	if(reply==23)
	{
			Mean_Filters(ImageLength,ImageWidthByte,fxyout,fxy);
	}
	
	/*if(reply==24)
	{
			Notch_Filter(ImageLength,ImageWidthByte,fxyout,fxy);
	}*/
	if(reply==25)
	{
		Negation_RGB(ImageLength,ImageWidthByte,fxyout,fxy);
	}
	if(reply==26)
	{
		Order_Stat(ImageLength,ImageWidthByte,fxyout,fxy);
	}

	if(reply==27)
	{
		Adaptive_LNR(ImageLength,ImageWidthByte,fxyout,fxy);
	}


	if(reply==29)
	{
		pseudo_RGB(ImageLength,ImageWidthByte,fxyout,fxy);
	}

	if(reply==30)
	{
		ideal_filter(ImageLength,ImageWidthByte,fxyout,fxy);
	}
	if(reply==31)
	{
		HE_RGB(ImageLength,ImageWidthByte,fxyout,fxy);
	}
	if(reply==32)
	{
		Power_Spectrum(ImageLength,ImageWidthByte,fxyout,fxy);
	}
	
	if(reply==33)
	{
		Butterworth_Filter(ImageLength,ImageWidthByte,fxyout,fxy);
	}
	if(reply==34)
	{
		Gaussian_Filter(ImageLength,ImageWidthByte,fxyout,fxy);
	}
	if(reply==35)
	{
		Laplacian_Filter(ImageLength,ImageWidthByte,fxyout,fxy);
	}
	

	


	



	

	

	




	

	

	


















		 







		fseek(outfile_ptr, file_position, SEEK_SET);
        
		copy_array_to_file(ImageLength, ImageWidthByte, fxyout, outfile_ptr);
		fclose(infile_ptr);  
		fclose(outfile_ptr);
	
		copy_to_text_file(ImageLength, ImageWidthByte,  fxyout);
		getch();
		
		/*  Operation on the input image file is over  */
}





void Negation(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{

		// Image Negation
			int i,j;
			for(i=0; i<ImageLength; i++)
			{
				for(j=0; j<ImageWidthByte; j++)
				{
					fxyout[i][j]=255-fxy[i][j];
				}
			}	

}





void Log_Transformation(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{

			double max=0,min=255,temp;
			int i,j;
			
			for(i=0; i<ImageLength; i++)
			{
				for(j=0; j<ImageWidthByte; j++)
				{
					temp=log(fxy[i][j]+1);

					if(min>temp)
						 min=temp;
					if(max<temp)
						 max=temp;
					
				}
			}

			printf("Min:%f Max:%f",min,max);
			getch();

		//Linear Transformation			
			for(i=0; i<ImageLength; i++)
			{
				for(j=0; j<ImageWidthByte; j++)
				{
					temp=log(fxy[i][j]+1);
					fxyout[i][j]=(double)((255-0)/(max-min)*(temp-min));
					
				}
			}


}


void PowerLaw_Transformation(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{

			double max=0,min=255,temp;
			int i,j;
			
			for(i=0; i<ImageLength; i++)
			{
				for(j=0; j<ImageWidthByte; j++)
				{
					temp=pow(fxy[i][j],0.5);

					if(min>temp)
						 min=temp;
					if(max<temp)
						 max=temp;
					
				}
			}

			printf("Min:%f Max:%f",min,max);
			getch();

			//Linear Transformation
			for(i=0; i<ImageLength; i++)
			{
				for(j=0; j<ImageWidthByte; j++)
				{
					temp=pow(fxy[i][j],0.5);
					fxyout[i][j]=(double)((255-0)/(max-min)*(temp-min));
						
				}
			}
		



}



void Contrast_Stretch(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
		
			unsigned int r1,r2,s1,s2;
			int x,y;

			printf("Enter values of r1,r2,s1,s2");
			scanf("%d%d%d%d",&r1,&r2,&s1,&s2);
			
				for(x=0; x<ImageLength; x++)
				{
					for(y=0; y<ImageWidthByte; y++)
					{
						if(fxy[x][y]<=r1)
							fxyout[x][y]=0+(double)((s1-0)/(double)(r1-0))*(fxy[x][y]-0);
						if(fxy[x][y]>=r1 && fxy[x][y]<=r2)
							fxyout[x][y]=s1+(double)((s2-s1)/(double)(r2-r1))*(fxy[x][y]-r1);
						if(fxy[x][y]>r2)	
							fxyout[x][y]=s2+(double)((255-s2)/(double)(255-r2))*(fxy[x][y]-r2);
					}
				}

}



void Intensity_Level(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
			unsigned int r1,r2;
			int i,j;

			printf("Enter value of r1 and r2");
			scanf("%d%d",&r1,&r2);

			for(i=0;i<ImageLength;i++)
			{
				for(j=0;j<ImageWidthByte;j++)
				{
					

					if((fxy[i][j]>=r1)&&(fxy[i][j]<=r2))
						
						fxyout[i][j]=200;
					else 
						fxyout[i][j]=50;

				}
			}


}



void Bit_Plane(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{

			unsigned int temp,plane,k;
			int i,j;
			printf("Enter the plane");
			scanf("%d",&plane);
			k=pow(2.0,plane-1);
			// position the file pointer of the output file from where the processed data
			// is to be written.
   
			for(i=0; i<ImageLength; i++)
			{
				for(j=0; j<ImageWidthByte; j++)
				{
					if((fxy[i][j] & k)>0)
						fxyout[i][j]=255;
					else
						fxyout[i][j]=0;
				}
			}
}


void Histogram_Eq(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{

		int arr[256],temp,i,j,k;
		float fltarr[256];

	//Initializing array

		for(k=0;k<=255;k++)
		{
			fltarr[k]=arr[k]=0;
		
		}

   // Calculating the frequency

		for(i=0; i<ImageLength; i++)
		{
			for(j=0; j<ImageWidthByte; j++)
			{
		
				arr[fxy[i][j]]++;
				
			}
		}
		/*
		for(k=0;k<=255;k++)
		{
			printf("\n%d : %d",k,arr[k]);
		}
		getch(); */
        
		for(k=0;k<=255;k++)
		{
			fltarr[k]=(float(arr[k])/(ImageLength*ImageWidthByte));
			printf("\n%d : %f",k,fltarr[k]);
		}

		for(k=0;k<=255;k++)
		{
			fltarr[k+1]=fltarr[k+1]+fltarr[k];
//			printf("comm frq:%f",fltarr[k+1]);
//			getch();
		}
		for(k=0;k<=255;k++)
		{
				arr[k]=int(fltarr[k]*255);
				printf("\n%d : %d",k,arr[k]);
//				getch();
		}
		
		for(i=0; i<ImageLength; i++)
		{
			for(j=0; j<ImageWidthByte; j++)
			{

				fxyout[i][j]=arr[fxy[i][j]];

			}
		}


		
		




}





void Filtering_mask(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
			int M,N;
			M=ImageLength;
			N=ImageWidthByte;
			float sum;
			int m,n,a,b,x,y,xps,ypt,totalsum=0,s,t;
			int w[MAXSIZE][MAXSIZE];
			printf("Enter the filter size :");

			scanf("%d%d",&m,&n);
			a=(m-1)/2;
			b=(n-1)/2;

			printf("\nEnter the filter coefficients :");

			for(x=-a;x<=a;x++)
			{	
				for(y=-b;y<=b;y++)
				{	
					scanf("%d",&w[x+a][y+b]);
					totalsum=totalsum+w[x+a][y+b];
				}
			}
				for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						sum=0;
						for(s=-a;s<=a;s++)
						{
							xps=x+s;
							if(xps<0)
								xps=0;
							if(xps>=M)
								xps=M-1;
						for(t=-b;t<=b;t++)
						{
								ypt=y+t;
								if(ypt<0)
									ypt=0;
								if(ypt>=N)
									ypt=N-1;
							sum=sum+(w[a+s][b+t]*fxy[xps][ypt]);
						}
					}
						fxyout[x][y]=sum/totalsum;
				}
			}
		
}




void Filtering_Gaussian(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
			int M,N;
			M=ImageLength;
			N=ImageWidthByte;
			float sum,g[MAXSIZE][MAXSIZE],totalsum=0;
			int m,n,a,b,xps,ypt,s,t,x,y;
		//	int w[MAXSIZE][MAXSIZE];
		//	double min;
			printf("Enter the filter size :");

			scanf("%d%d",&m,&n);
			a=(m-1)/2;
			b=(n-1)/2;


			for(x=-a;x<=a;x++)
			{	
				for(y=-b;y<=b;y++)
				{	
					g[x+a][y+b]=pow(2.71828183,-((float)(x*x+y*y)/(float)2));
					totalsum=totalsum+g[x+a][y+b];
				}
			}


		

 
				for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						sum=0;
						for(s=-a;s<=a;s++)
						{
							xps=x+s;
							if(xps<0)
								xps=0;
							if(xps>=M)
								xps=M-1;
							for(t=-b;t<=b;t++)
							{
								ypt=y+t;
								if(ypt<0)
									ypt=0;
								if(ypt>=N)
									ypt=N-1;
								sum=sum + g[a+s][b+t]*(float)fxy[xps][ypt];
							}
						}
							fxyout[x][y]=sum/totalsum;
					}
				}
		
}



void Filtering_Order_Stat(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
			
			int M,N,i,j;
			M=ImageLength;
			N=ImageWidthByte;
//			float sum;
			int m,n,a,b,x,y,xps,ypt,s,t,choice,sum;
			int arr[9];   //by default 3*3 filter
			printf("Enter the filter size");
			scanf("%d%d",&m,&n);
			a=(m-1)/2;
			b=(n-1)/2;
			printf("\nEnter the choice: \nEnter 1 for Median filter: \n\nEnter 2 for Max filter: \nEnter 3 for Min filter: \nEnter 4 for Mean filter:");
			scanf("%d",&choice);
						

			for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						sum=0;
				
						for(s=-a;s<=a;s++)
						{
							for(t=-b;t<=b;t++)
							{
									xps=x+s;
									if(xps<0)
									xps=0;
									if(xps>=M)
									xps=M-1;
								
									ypt=y+t;
									if(ypt<0)
									ypt=0;
									if(ypt>=N)
									ypt=N-1;
									arr[sum++]=fxy[xps][ypt];
								}
						}
					
			
						int min=arr[0];
						int max=arr[0];
					

						switch(choice)
						{
							case 1:
								
								for(m=0;m<8;m++)
								{
									for(n=m+1;n<9;n++)
									{
										if(arr[m]>arr[n])
										{
											int temp;
											temp=arr[m];
											arr[m]=arr[n];
											arr[n]=temp;
										}
									}
								}
								fxyout[x][y]=arr[4];
								break;
							case 2:
								
								for(m=0;m<9;m++)
								{
										if(arr[m]>max)
										{
											max=arr[m];
										}
								}
								fxyout[x][y]=max;
								break;
							case 3:
								for(m=0;m<9;m++)
								{
										if(arr[m]<min)
										{
											min=arr[m];
										}
								}
								fxyout[x][y]=min;
								break;

							case 4:
								for(m=0;m<9;m++)
								{
									if(arr[m]>max)
										{
											max=arr[m];
										}

									if(arr[m]<min)
										{
											min=arr[m];
										}
								
								}
								fxyout[x][y]=(max+min)/2;
								break;

						}
					}
			}
		
}




void Filtering_Laplacian(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
			int M,N;
			M=ImageLength;
			N=ImageWidthByte;
			int sum;
			int x,y,xps,ypt,totalsum=0,s,t;
			int delta[MAXSIZE][MAXSIZE];
			int w[3][3]={0,1,0,1,-4,1,0,1,0};
			
			
				for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						sum=0;
						for(s=-1;s<=1;s++)
						{
							xps=x+s;
							if(xps<0)
								xps=0;
							if(xps>=M)
								xps=M-1;
						for(t=-1;t<=1;t++)
						{
								ypt=y+t;
								if(ypt<0)
									ypt=0;
								if(ypt>=N)
									ypt=N-1;
							sum=sum+(w[1+s][1+t]*(int)fxy[xps][ypt]);
						}
					}
						delta[x][y]=sum;
				}
			}



			//verifying the laplacian image..the sum should be zero.
		/*	for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						if(delta[x][y]<0)
							neg=neg+delta[x][y];
						if(delta[x][y]>0)
							pos=pos+delta[x][y];
					}
			}
			printf("%ld %ld",pos,neg);
			getch();
		*/

// laplacian Image
			/*	for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						if(delta[x][y]<0)
							fxyout[x][y]=0;
						else if(delta[x][y]>255)
							fxyout[x][y]=255;
						else
							fxyout[x][y]=delta[x][y];
					}
				}
*/
  
// final Image				
				for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						
						delta[x][y]=(int)fxy[x][y]-delta[x][y];

						if(delta[x][y]<0)
							fxyout[x][y]=0;
						else if(delta[x][y]>255)
							fxyout[x][y]=255;
						else
							fxyout[x][y]=delta[x][y];

					}
				}






		/*	double max,min,temp;
			min=max=fxyout[0][0];
			
			for(i=0; i<ImageLength; i++)
			{
				for(j=0; j<ImageWidthByte; j++)
				{
					
					if(min>fxyout[i][j])
						 min=fxyout[i][j];
					if(max<fxyout[i][j])
						 max=fxyout[i][j];
					
				}
			}

			printf("Min:%f Max:%f",min,max);
			getch();

		
			for(i=0; i<ImageLength; i++)
			{
				for(j=0; j<ImageWidthByte; j++)
				{
					fxyout[i][j]=(double)((255-0)/(max-min)*(fxyout[i][j]-min));
						
				}
			}
			*/		
}



/*************************************************************************
*                                                                        *
*  Logical operations on Image (OR, AND, NOT, XOR)                                  *
*                                                                        *
**************************************************************************/

void logical_op(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])

{

			int M,N,x,y,choice;
			M=ImageLength;
			N=ImageWidthByte;

			printf("length : %d width : %d",M,N);
			unsigned char delta[MAXSIZE][MAXSIZE];
			
			printf("\nEnter 1 for ORing: \nEnter 2 for ANDing: \nEnter 3 for XORing: \nEnter 4 for NOTing: ");
			scanf("%d",&choice);

			switch(choice)
			{
				case 1:
						// ORing
					for(x=0; x<M; x++)
					{	
						for(y=0; y<N; y++)
						{
							delta[x][y]=255;
						
						}
					}




					for(x=0; x<200; x++)
					{	
						for(y=(N/2)-50; y<(N/2)+50; y++)
						{
							delta[x][y]=0;
						
						}
					}

				
					for(x=0; x<M; x++)
					{	
						for(y=0; y<N; y++)
						{
							fxyout[x][y]=fxy[x][y]|delta[x][y];
						
						}
					}
					break;


				case 2:
					
						// ANDing
					for(x=0; x<M; x++)
					{	
						for(y=0; y<N; y++)
						{
							delta[x][y]=0;
						
						}
					}




					for(x=0; x<200; x++)
					{	
						for(y=(N/2)-50; y<(N/2)+50; y++)
						{
							delta[x][y]=255;
						
						}
					}

				
					for(x=0; x<M; x++)
					{	
						for(y=0; y<N; y++)
						{
							fxyout[x][y]=fxy[x][y]&delta[x][y];
						
						}
					}

					break;

					case 3:
						// XORing
						for(x=0; x<M; x++)
						{	
							for(y=0; y<N; y++)
							{
								delta[x][y]=255;
								// if we assign 255, we ll get the negation of an image.
								// if we assign 0 , then we ll get the same image.
						
							}
						}

				
						for(x=0; x<M; x++)
						{	
							for(y=0; y<N; y++)
							{
								fxyout[x][y]=fxy[x][y]^delta[x][y];
						
							}	
						}
						break;

					case 4:
						//NOT
						for(x=0; x<M; x++)
						{	
							for(y=0; y<N; y++)
							{
								fxyout[x][y]=~fxy[x][y];
						
							}	
						}
						break;
			}



}



void Filtering_Sobel(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
		
			int M,N;
			M=ImageLength;
			N=ImageWidthByte;
			int sum1,sum2;
			int x,y,xps,ypt,totalsum=0,s,t;
			int delta1[MAXSIZE][MAXSIZE];
			int delta2[MAXSIZE][MAXSIZE];
			int w1[3][3]={-1,-2,-1,0,0,0,1,2,1};
			int w2[3][3]={-1,0,1,-2,0,2,-1,0,1};
		

			
				for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						sum1=0;
						sum2=0;
						for(s=-1;s<=1;s++)
						{
							xps=x+s;
							if(xps<0)
								xps=0;
							if(xps>=M)
								xps=M-1;
						for(t=-1;t<=1;t++)
						{
								ypt=y+t;
								if(ypt<0)
									ypt=0;
								if(ypt>=N)
									ypt=N-1;
							sum1=sum1+(w1[1+s][1+t]*(int)fxy[xps][ypt]);
							sum2=sum2+(w2[1+s][1+t]*(int)fxy[xps][ypt]);
						}
					}
						delta1[x][y]=sum1;
						delta2[x][y]=sum2;
				}
			}


			

				for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						fxyout[x][y]=(abs(delta1[x][y]))+(abs(delta2[x][y]));
					}
				}


}




void Filtering_Robercross(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{


			int M,N;
			M=ImageLength;
			N=ImageWidthByte;
			int sum1,sum2;
			int x,y,xps,ypt,totalsum=0,s,t;
			int delta1[MAXSIZE][MAXSIZE];
			int delta2[MAXSIZE][MAXSIZE];
			int w1[2][2]={-1,0,0,1};
			int w2[2][2]={0,-1,1,0};
		

			
				for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						sum1=0;
						sum2=0;
						for(s=0;s<=1;s++)
						{
							xps=x+s;
							if(xps<0)
								xps=0;
							if(xps>=M)
								xps=M-1;
						for(t=0;t<=1;t++)
						{
								ypt=y+t;
								if(ypt<0)
									ypt=0;
								if(ypt>=N)
									ypt=N-1;
							sum1=sum1+(w1[s][t]*(int)fxy[xps][ypt]);
							sum2=sum2+(w2[s][t]*(int)fxy[xps][ypt]);
						}
					}
						delta1[x][y]=sum1;
						delta2[x][y]=sum2;
				}
			}


			
				for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						fxyout[x][y]=(abs(delta1[x][y]))+(abs(delta2[x][y]));
					}
				}


		
}



void Laplacian_Image(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
			int M,N;
			M=ImageLength;
			N=ImageWidthByte;
			int sum;
			int x,y,xps,ypt,totalsum=0,s,t;
			int delta[MAXSIZE][MAXSIZE];
			int w[3][3]={0,1,0,1,-4,1,0,1,0};
			long pos=0,neg=0;

			
				for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						sum=0;
						for(s=-1;s<=1;s++)
						{
							xps=x+s;
							if(xps<0)
								xps=0;
							if(xps>=M)
								xps=M-1;
						for(t=-1;t<=1;t++)
						{
								ypt=y+t;
								if(ypt<0)
									ypt=0;
								if(ypt>=N)
									ypt=N-1;
							sum=sum+(w[1+s][1+t]*(int)fxy[xps][ypt]);
						}
					}
							fxyout[x][y]=sum;
				}
			}



			//verifying the laplacian image..the sum should be zero.
		/*	for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						if(delta[x][y]<0)
							neg=neg+delta[x][y];
						if(delta[x][y]>0)
							pos=pos+delta[x][y];
					}
			}
			printf("%ld %ld",pos,neg);
			getch();
		*/
		
}


void Laplacian_Sign(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
			int M,N;
			M=ImageLength;
			N=ImageWidthByte;
			int sum;
			int x,y,xps,ypt,totalsum=0,s,t,a,b,m,n;
			int delta[MAXSIZE][MAXSIZE];
			int w[3][3];
			long pos=0,neg=0;

			printf("Enter the filter size :");

			scanf("%d%d",&m,&n);
			a=(m-1)/2;
			b=(n-1)/2;

			printf("\nEnter the filter coefficients :");

			for(x=-a;x<=a;x++)
			{	
				for(y=-b;y<=b;y++)
				{	
					scanf("%d",&w[x+a][y+b]);
				}
			}

			
				for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						sum=0;
						for(s=-a;s<=a;s++)
						{
							xps=x+s;
							if(xps<0)
								xps=0;
							if(xps>=M)
								xps=M-1;
						for(t=-a;t<=a;t++)
						{
								ypt=y+t;
								if(ypt<0)
									ypt=0;
								if(ypt>=N)
									ypt=N-1;
							sum=sum+(w[1+s][1+t]*(int)fxy[xps][ypt]);
						}
					}
						delta[x][y]=sum;
				}
			}


// final Image			
				
				//	printf("Sign of center coefficient is Negtive..!");
					for(x=0; x<M; x++)
					{	
						for(y=0; y<N; y++)
						{
							if(w[5]<0)            // checking sign of center coefficient.
								delta[x][y]=(int)fxy[x][y]-delta[x][y];
							else
								delta[x][y]=(int)fxy[x][y]+delta[x][y];

							if(delta[x][y]<0)
								fxyout[x][y]=0;
							else if(delta[x][y]>255)
								fxyout[x][y]=255;
							else
								fxyout[x][y]=delta[x][y];

						}
					}
				

			





	
}



void Unsharp_Mask(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
		
			int M,N;
			M=ImageLength;
			N=ImageWidthByte;
			float sum,g[MAXSIZE][MAXSIZE],totalsum=0;
			int delta[MAXSIZE][MAXSIZE],gmask[MAXSIZE][MAXSIZE];
			int m,n,a,b,xps,ypt,s,t,x,y;
			printf("Enter the Gaussian filter size for blurring an image :");

			scanf("%d%d",&m,&n);
			a=(m-1)/2;
			b=(n-1)/2;


			for(x=-a;x<=a;x++)
			{	
				for(y=-b;y<=b;y++)
				{	
					g[x+a][y+b]=pow(2.71828183,-((float)(x*x+y*y)/(float)2));
					totalsum=totalsum+g[x+a][y+b];
				}
			}
 
				for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						sum=0;
						for(s=-a;s<=a;s++)
						{
							xps=x+s;
							if(xps<0)
								xps=0;
							if(xps>=M)
								xps=M-1;
							for(t=-b;t<=b;t++)
							{
								ypt=y+t;
								if(ypt<0)
									ypt=0;
								if(ypt>=N)
									ypt=N-1;
								sum=sum + g[a+s][b+t]*(float)fxy[xps][ypt];
							}
						}
							delta[x][y]=sum/totalsum;
					}
				}

				for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						gmask[x][y]=fxy[x][y]-delta[x][y];
						fxyout[x][y]=fxy[x][y]+(gmask[x][y]);  // here k=1, unsharp masking
																// if k>1, highboost filtering
																//which gives more clear image.
		
					}
				}





}


void xy_Sobel(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
			int M,N;
			M=ImageLength;
			N=ImageWidthByte;
			int sum1,sum2,choice;
			int x,y,xps,ypt,totalsum=0,s,t;
			int delta1[MAXSIZE][MAXSIZE];
			int delta2[MAXSIZE][MAXSIZE];
			int w1[3][3]={-1,-2,-1,0,0,0,1,2,1};
			int w2[3][3]={-1,0,1,-2,0,2,-1,0,1};
		
			printf("Enter the choice: \n enter 1 for x gradient:\nenter 2 for y gradient:\nenter 3 for absolute image:\n Enter 4 for sqrt(gx+gy):\nEnter 5 for tan image:");
			scanf("%d",&choice);
				for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						sum1=0;
						sum2=0;
						for(s=-1;s<=1;s++)
						{
							xps=x+s;
							if(xps<0)
								xps=0;
							if(xps>=M)
								xps=M-1;
						for(t=-1;t<=1;t++)
						{
								ypt=y+t;
								if(ypt<0)
									ypt=0;
								if(ypt>=N)
									ypt=N-1;
							sum1=sum1+(w1[1+s][1+t]*(int)fxy[xps][ypt]);
							sum2=sum2+(w2[1+s][1+t]*(int)fxy[xps][ypt]);
						}
					}
						delta1[x][y]=sum1;
						delta2[x][y]=sum2;
				}
			}


				switch(choice)
				{
					case 1:
						for(x=0; x<M; x++)
						{	
							for(y=0; y<N; y++)
							{
								fxyout[x][y]=abs(delta1[x][y]);
							}
						}
						break;

					case 2:
						for(x=0; x<M; x++)
						{	
							for(y=0; y<N; y++)
							{
								fxyout[x][y]=abs(delta2[x][y]);
							}
						}
						break;


					case 3:

						for(x=0; x<M; x++)
						{	
							for(y=0; y<N; y++)
							{
								fxyout[x][y]=(abs(delta1[x][y]))+(abs(delta2[x][y]));
							}
						}
						break;
					case 4:
						for(x=0; x<M; x++)
						{	
							for(y=0; y<N; y++)
							{
								fxyout[x][y]=sqrt((delta1[x][y]*delta1[x][y])+(delta2[x][y]*delta2[x][y]));
							}
						}

					break;

					case 5:
						for(x=0; x<M; x++)
						{	
							for(y=0; y<N; y++)
							{
								fxyout[x][y]=atan2((delta2[x][y]),(delta1[x][y]));
							}
						}

					break;
				}


		
}


void F_T( unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
	//Fourier transform
	int u,v,x,y,M=ImageLength,N=ImageWidthByte;
	double pi=4.0*atan(1.0);
	pi = 2*pi;
	int MN = ImageLength * ImageWidthByte;
	double fr[1000][1000],fi[1000][1000],Fr[1000][1000],Fi[1000][1000],sumr,sumi;
	printf("Loop Starts : ");
	//Forward FT
	for(u=0;u<M;u++)
	{
		for(v=0;v<N;v++)
		{
			sumr = 0.0;
			sumi = 0.0;
			for(x=0;x<M;x++)
			{
				for(y=0;y<N;y++)
				{
					//sumr = sumr+(fxy[x][y] * cos(2*pi*((double)(u*x)/30+(double)(v*y)/30)));
					//sumi = sumi-(fxy[x][y] * sin(2*pi*((double)(u*x)/30+(double)(v*y)/30)));
					sumr = sumr+(fxy[x][y] * cos(pi*((double)(u*x)/M+(double)(v*y)/N)));
					sumi = sumi-(fxy[x][y] * sin(pi*((double)(u*x)/M+(double)(v*y)/N)));
				}
			}
			Fr[u][v] = sumr/(double)(MN);
			Fi[u][v] = sumi/(double)(MN);
			//fxyout[u][v] = Fr[u][v] + Fi[u][v];
			
		}
		printf("F");
		
	}
	cout<<"\n done";
	//Inverse FT
	for(x=0;x<M;x++)
	{
		for(y=0;y<N;y++)
		{
			sumr = 0.0;
			sumi = 0.0;
			for(u=0;u<M;u++)
			{
				for(v=0;v<N;v++)
				{
					
					//sumr = sumr + (Fr[u][v] * cos(2*pi*((double)(u*x)/30+(double)(v*y)/30)))-(Fi[u][v] * sin(2*pi*((double)(u*x)/30+(double)(v*y)/30)));
					//sumi = sumi + (Fr[u][v] * sin(2*pi*((double)(u*x)/30+(double)(v*y)/30)))+(Fi[u][v] * cos(2*pi*((double)(u*x)/30+(double)(v*y)/30)));

					sumr = sumr + (Fr[u][v] * cos(pi*((double)(u*x)/M+(double)(v*y)/N)))-(Fi[u][v] * sin(pi*((double)(u*x)/M+(double)(v*y)/N)));
					sumi = sumi + (Fr[u][v] * sin(pi*((double)(u*x)/M+(double)(v*y)/N)))+(Fi[u][v] * cos(pi*((double)(u*x)/M+(double)(v*y)/N)));
				}
			}
			fr[x][y] = sumr;
			fi[x][y] = sumi;
			fxyout[x][y] = fr[x][y];
			
		
		}
		printf("I");
			
	}
	cout<<"inverse is done";
}





void Mean_Filters(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{


			int m,n,a,b,x,y,xps,ypt,s,t;
			double sum,sum1,sum2,sum3,sum4;
			int M,N,choice;
			M=ImageLength;
			N=ImageWidthByte;
			m=3;
			n=3;
			float q;
			double denom=9;
			double pw=1/denom;
			a=(m-1)/2;
			b=(n-1)/2;
			printf("Enter the choice \n Enter 1 for Arithmetic Mean\n  Enter 2 for Geometric Mean:\n  Enter 3 for harmonic Mean:\n  Enter 4 for Contraharmonic Mean:");
			scanf("%d",&choice);
			printf("Enter q for contraharmonic:");
			scanf("%f",&q);
			for(x=0; x<M; x++)
			{	
				for(y=0; y<N; y++)
				{
					sum=0;
					sum1=1;
					sum2=0;
					sum3=0;
					sum4=0;
					for(s=-a;s<=a;s++)
					{
						xps=x+s;
						if(xps<0)
							xps=0;
						if(xps>=M)
							xps=M-1;
						for(t=-b;t<=b;t++)
						{
							ypt=y+t;
							if(ypt<0)
								ypt=0;
							if(ypt>=N)
								ypt=N-1;
						    sum=sum+fxy[xps][ypt];
							sum1=sum1*fxy[xps][ypt];
							sum2=sum2+(1.0/fxy[xps][ypt]);
							sum3=sum3+pow(fxy[xps][ypt],q+1.0);
							sum4=sum4+pow(fxy[xps][ypt],q);
						}
					}
							if(choice==1)				
							fxyout[x][y]=(unsigned char)(sum/denom);    //Arithmatic Mean
							else if(choice==2)				
							fxyout[x][y]=(unsigned char)(pow(sum1,pw));  //Geometric Mean
							else if(choice==3)
							fxyout[x][y]=(unsigned char)(denom/sum2);    //Harmonic Mean
							else if(choice==4)
							fxyout[x][y]=(unsigned char)(sum3/sum4);    //ContraHarmonic Mean


							
					}			
				}
			

}


void Negation_RGB(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{

		// Image Negation
			int i,j;
			unsigned char r,g,b;
			for(i=0; i<ImageLength; i++)
			{
				for(j=0; j<ImageWidthByte; j++)
				{
					
					r=fxy[i][3*j];
					g=fxy[i][3*j+1];
					b=fxy[i][3*j+2];

					fxyout[i][3*j]=255-r;
					fxyout[i][3*j+1]=255-g;
					fxyout[i][3*j+2]=255-b;
				}
			}	

}


void pseudo_RGB(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
		double r , g , b;
		unsigned long i , j;
		double hue[1000][1000] , sat[1000][1000] , in[1000][1000];
	//cout<<ImageWidthByte<<endl;
	//cout<<ImageWidth;
	//void rgb2hsi(float r,float g,float b,float *h,float *s,float *i)
    for( i = 0 ; i < ImageLength ; i++ )
	{
		for( j = 0 ; j < ImageWidth ; j++ )
		{
			r = fxy[i][3*j];
			g = fxy[i][3*j+1];
			b = fxy[i][3*j+2];
			float min, max;              /* minimum and maximum RGB values */
			float angle;                 /* temp variable used to compute Hue */
			if((r<=g) && (r<=b))
				min = r;
			else if((g<=r) && (g<=b))
				min = g;
			else
				min = b;

			/* compute intensity */
			in[i][j] = (r + g + b) / 3.0;

			/* compute hue and saturation */
			if((r==g) && (g==b))  /* gray-scale */
			{
				sat[i][j] = 0.0;
				hue[i][j] = 0.0;
				//return;
			}
			else
			{
				sat[i][j] = 1.0 - (3.0 / (float)(r + g + b)) * min;
				angle = (0.5*(2*r - g - b)) / sqrt((r - g) * (r - g)+(r - b) * (g - b));
				hue[i][j] = acos(angle);
				hue[i][j] *= 57.27272727272727;          /* convert to degrees */
			}
			if( b > g )
				hue[i][j] = 360.0 - hue[i][j];
			//cout<<"r-"<<r*255<<"\t g-"<<g*255<<"\t b-"<<b*255<<"\th-"<<*h<<"\ts-"<<*s<<"\tI"<<*i*255<<endl;
//			getch();
		}
	}
	//pseudo color processing on intensity component
	for ( i = 0 ; i < ImageLength ; i++ )
	{
		for ( j = 0 ; j < ImageWidth ; j++ )
		{
			if( in[i][j] >= 0 && in[i][j] <= 100 )
			{
				fxyout[i][3*j] = 255;
				fxyout[i][3*j+1] = 0;
				fxyout[i][3*j+2] = 0;
			}
			else if ( in[i][j] >100 && in[i][j] <=200)
			{
				fxyout[i][3*j] = 0;
				fxyout[i][3*j+1] = 255;
				fxyout[i][3*j+2] = 0;
			}
			else
			{
				fxyout[i][3*j] = 0;
				fxyout[i][3*j+1] = 0;
				fxyout[i][3*j+2] = 255;
			}
		}
	}


}




void Order_Stat(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
			
			int M,N,i,j,d;
			M=ImageLength;
			N=ImageWidthByte;
//			float sum;
			int m,n,a,b,x,y,xps,ypt,s,t,choice,sum;
			int arr[9];   //by default 3*3 filter
			printf("Enter the filter size");
			scanf("%d%d",&m,&n);
			a=(m-1)/2;
			b=(n-1)/2;
			printf("\nEnter the choice: \nEnter 1 for Median filter: \n\nEnter 2 for Max filter: \nEnter 3 for Min filter: \nEnter 4 for Alpha Trimmed Mean:");
			scanf("%d",&choice);
			if(choice==4)
			{
				printf("Enter value of d from 0 to mn-1:");
				scanf("%d",&d);
			}			

			for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						sum=0;
				
						for(s=-a;s<=a;s++)
						{
							for(t=-b;t<=b;t++)
							{
									xps=x+s;
									if(xps<0)
									xps=0;
									if(xps>=M)
									xps=M-1;
								
									ypt=y+t;
									if(ypt<0)
									ypt=0;
									if(ypt>=N)
									ypt=N-1;
									arr[sum++]=fxy[xps][ypt];
								}
						}
					//	printf("sum:%d",sum);
					//	getch();

					//		for(n=0;n<9;n++)

					//			printf("%d\t",arr[n]);
					//		getch();

					
			
						int min=arr[0];
						int max=arr[0];
					

						switch(choice)
						{
							case 1:
								//Bubble sort.
								for(m=0;m<=7;m++)
								{
									for(n=0;n<=sum-m-1;n++)
									{
										if(arr[n]>arr[n+1])
										{
											int temp;
											temp=arr[n];
											arr[n]=arr[n+1];
											arr[n+1]=temp;
										}
									}
								}
								
								fxyout[x][y]=arr[4];
								break;
							case 2:
								
								for(m=0;m<9;m++)
								{
										if(arr[m]>max)
										{
											max=arr[m];
										}
								}
								fxyout[x][y]=max;
								break;
							case 3:
								for(m=0;m<9;m++)
								{
										if(arr[m]<min)
										{
											min=arr[m];
										}
								}
								fxyout[x][y]=min;

							//	printf("Minimum:%d",min);
							//	getch();
								break;

							case 4:
							/*		for(int h=0;h<9;h++)
								printf("%d\t",arr[h]);
								getch();
							*/
								for(m=1;m<=8;m++)
								{
									for(n=0;n<sum-m-1;n++)
									{
										if(arr[n]>arr[n+1])
										{
											int temp;
											temp=arr[n];
											arr[n]=arr[n+1];
											arr[n+1]=temp;
										}
									}
								}
							//	for( h=0;h<9;h++)
							//	printf("%d\t",arr[h]);
							//	getch();

								//int vald=d/2;
								//printf("D:%d",vald);
							///	getch();
								int sum1=0;
							
								for(int r=d/2;r<=(m*n)-d/2;r++)
								{
									sum1=sum1+arr[r];

								}
								fxyout[x][y]=sum1/((m*n)-d);

							/*	int no=9;
								int d=5;
								for(int l=0;l<d/2;l++)
								{
									for(int p=0;p<no;p++)
										arr[p]=arr[p+1];
									no=no-1;
									
								}
								no=no-(d/2);
								float sum2=0.0;
								for(l=0;l<no;l++)
									sum2=sum2+arr[l];
								fxyout[x][y]=(unsigned char) sum2/no;
								*/					
								break;

						}
					}
			}
		
}


void Adaptive_LNR( unsigned long ImageLength, unsigned long ImageWidthByte, unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{


			int M,N,k,nv=1000;
			M=ImageLength;
			N=ImageWidthByte;
			double lm,lv;
			int sum;
			long x,y,xps,ypt,totalsum=0,s,t,a,b,m,n;
			
			printf("Enter the filter size :");

			scanf("%d%d",&m,&n);
			a=(m-1)/2;
			b=(n-1)/2;


			
				for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{
						k=0;
						lm=0;
						for(s=-a;s<=a;s++)
						{
							xps=x+s;
							if(xps<0)
								xps=0;
							if(xps>=M)
								xps=M-1;
							for(t=-a;t<=a;t++)
							{
									ypt=y+t;
									if(ypt<0)
										ypt=0;
									if(ypt>=N)
										ypt=N-1;
								k=k+fxy[xps][ypt];
							}
						}
						lm=double(k/(m*n));

					//	printf("Local Mean: %d",lm);


						lv=0;

						for(s=-a;s<=a;s++)
						{
							xps=x+s;
							if(xps<0)
								xps=0;
							if(xps>=M)
								xps=M-1;
							for(t=-a;t<=a;t++)
							{
									ypt=y+t;
									if(ypt<0)
										ypt=0;
									if(ypt>=N)
										ypt=N-1;
								    lv=lv+((fxy[xps][ypt]-lm)*(fxy[xps][ypt]-lm));
							}
						}
						lv=lv/(m*n);

					//	printf("Local Variance: %d",lv);

						if(nv>lv)
							fxyout[x][y]=fxy[x][y]-(fxy[x][y] - lm);
						else
							fxyout[x][y]=fxy[x][y]-(nv/lv)*(fxy[x][y]-lm);


				}
			}

}

void Adaptive_Median( unsigned long ImageLength, unsigned long ImageWidthByte, unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{



	
			int M,N,k;
			M=ImageLength;
			N=ImageWidthByte;
			
			int arr[50],med,min,max,Smax=7;
			int x,y,xps,ypt,totalsum=0,s,t,a,b,m,n;
			
			printf("Enter the filter size :");

			scanf("%d%d",&m,&n);
		//	a=(m-1)/2;
		//	b=(n-1)/2;


			
				for(x=0; x<M; x++)
				{	
					for(y=0; y<N; y++)
					{

						m=n=3;
						stagea:

						k=0;
						a=(m-1)/2;
						b=(n-1)/2;
						
						for(s=-a;s<=a;s++)
						{
							xps=x+s;
							if(xps<0)
								xps=0;
							if(xps>=M)
								xps=M-1;
							for(t=-a;t<=a;t++)
							{
									ypt=y+t;
									if(ypt<0)
										ypt=0;
									if(ypt>=N)
										ypt=N-1;
								arr[k++]=fxy[xps][ypt];
							}
						}

				/*		for(int q=0;q<k;q++)
							printf("%d\t",arr[q]);
							printf("\n");
						getch();
				*/	
						
						// Sorting elements
						int temp;
						for( int j=1;j<=(m*n)-1;j++)
						{
							for(int l=0;l<=(m*n)-j-1;l++)
							{
								if(arr[l]>arr[l+1])
								{
									temp=arr[l];
									arr[l]=arr[l+1];
									arr[l+1]=temp;
								}

							}
						}

				/*		for( q=0;q<k;q++)
							printf("%d\t",arr[q]);
							printf("\n");
							getch();  */

						min=arr[0];
						max=arr[(m*n)-1];
						med=arr[(m*n)/2];

					//	printf("min:%d,max:%d,med:%d",min,max,med);
					//		printf("\n");
					//		getch();

						//Stage A
					
						
						double a1,a2,b1,b2;
						a1=med-min;
						a2=med-max;

						if(a1>0 && a2<0)
						{
							b1=fxy[x][y]-min;
							b2=fxy[x][y]-max;
							 
							if(b1>0 && b2<0)
								fxyout[x][y]=fxy[x][y];
							else
								fxyout[x][y]=med;
						}
						else
						{
								m=m+2;
								n=n+2;

							//	printf("Size increase::%d",m*n);
							//	getch();
								if(m>Smax)
									fxyout[x][y]=med;
								else if(m<=Smax)
									goto stagea;
									
								
						}
					

						


				


					}
				}




}



void HE_RGB( unsigned long ImageLength, unsigned long ImageWidthByte, unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
	float r[256] = {0.0} , g[256] = { 0.0 } , b[256] = { 0.0 };
	float sum = 0 , temp = 0;
	unsigned int i , j;
	for(i=0; i<ImageLength; i++)
	{
		 //step 1 frequency finding
		for(j=0; j<ImageWidthByte; j++)
		{
			unsigned int index = fxy[i][3*j];
			r[index] = ++r[index];
			index = fxy[i][3*j+1];
			g[index] = ++g[index];
			index = fxy[i][3*j+2];
			b[index] = ++b[index];
		}

	}
	//step 2 probability
	for( i = 0 ; i < 256 ; i++ )
	{
		r[i] = r[i] / (ImageLength * ImageWidthByte);
		g[i] = g[i] / (ImageLength * ImageWidthByte);
		b[i] = b[i] / (ImageLength * ImageWidthByte);
	}
	//cumulative frequecy
	for( i = 1 ; i < 256 ; i++ )
	{
		r[i] += r[i-1];
		r[i-1] *= 255;
		g[i] += g[i-1];
		g[i-1] *= 255;
		b[i] += b[i-1];
		b[i-1] *= 255;
	}
	r[255] *= 255;
	g[255] *= 255;
	b[255] *= 255;
	for(i=0; i<ImageLength; i++)
	{
		for(j=0; j<ImageWidthByte; j++)
		{
			fxyout[i][3*j] = (unsigned char)floor(r[fxy[i][3*j]]+0.5);
			fxyout[i][3*j+1] = (unsigned char)floor(g[fxy[i][3*j+1]]+0.5);
			fxyout[i][3*j+2] = (unsigned char)floor(b[fxy[i][3*j+2]]+0.5);
		}
	}
}

void Power_Spectrum(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{

	//Fourier transform
	double temp , min,max , angle , t1 , t2 , temp1 , phie[1000][1000] = {0};
	unsigned int i , j;
	int u,v,x,y,M=ImageLength,N=ImageWidthByte;	double pi=4.0*atan(1.0);
	pi = pi * 2;
	int MN = ImageLength*ImageWidthByte , flag = 1 ;
	double fr[1000][1000],fi[1000][1000],Fr[1000][1000],Fi[1000][1000],sumr,sumi , res , result[1000][1000];
	cout<<"Enter 1 for power spectrum 2 for phas angle:";
	cin>>flag;
	cout<<"in loop";
	//Forward FT
	for(u=0;u<ImageLength;u++)
	{
		for(v=0;v<ImageWidthByte;v++)
		{
			sumr = 0.0;
			sumi = 0.0;
			for(x=0;x<ImageLength;x++)
			{
				for(y=0;y<ImageWidthByte;y++)
				{
					sumr = sumr+(fxy[x][y] * cos(pi*((double)(u*x)/M+(double)(v*y)/N)));
					sumi = sumi-(fxy[x][y] * sin(pi*((double)(u*x)/M+(double)(v*y)/N)));
				}
			}
			Fr[u][v] = sumr/(double)(MN);
			Fi[u][v] = sumi/(double)(MN);
		}
		cout<<"F";
	}
	switch( flag )
	{
	case 1:
		for(u=0;u<ImageLength;u++)
		{
			for(v=0;v<ImageWidthByte;v++)
			{

				 res = ( Fr[u][v] * Fr[u][v] )  + ( Fi[u][v] * Fi[u][v] );
				 result[u][v] = sqrt( res );
			}
		}
		min = 255;
		max = 0;
		for(i=0; i<ImageLength; i++)
		{
			for(j=0; j<ImageWidthByte; j++)
			{
				temp =	(log(double(1+result[i][j])));
				if(temp<min)
					min = temp;
				if(temp>max)
					max = temp;
			}
		}
		printf("min and max values:%f\t%f",min, max);
		getch();
		for(i=0; i<ImageLength; i++)
		{
			for(j=0; j<ImageWidthByte; j++)
			{
				temp = (log(double(1+result[i][j])));
				fxyout[i][j] =  (unsigned char)0+((double)(255-0)/(double)(max-min))*(double)(temp-min);
			}
		}
	break;
	case 2:
		for(u=0;u<ImageLength;u++)
		{
			for(v=0;v<ImageWidthByte;v++)
			{
			    phie[u][v]=atan(Fi[u][v]/Fr[u][v]);
				if(phie[u][v]<0.0)
					phie[u][v]=phie[u][v]+(2*pi);
					
			}
		}

		double s1,s2,sout1,sout2;
		s1=255;
		s2=0;
		sout1=0;
		sout2=255;
		for(x=0;x<M;x++)
		{
			for(y=0;y<N;y++)
			{	

			  if(s1>phie[x][y])
				  s1=phie[x][y];
			  if(s2<phie[x][y])
				  s2=phie[x][y];
			}
		
		}
		//	cout<<"\n s1="<<s1<<"  s2= "<<s2<<endl;
		for(x=0;x<M;x++)
		{	
			for(y=0;y<N;y++)
			{
				fxyout[x][y]=(unsigned char)(sout1+((sout2-sout1)*(phie[x][y]-s1))/(s2-s1));
				cout<<endl<<(int)fxyout[x][y]<<endl;
			}
		
		}
	break;
	default:
		cout<<"Wrong input.";
	}

}

void ideal_filter(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{

		unsigned int i , j ;
		int x,y,u,v;
		double pi,Fr[MAXSIZE][MAXSIZE],Fi[MAXSIZE][MAXSIZE],sumr,sumi;
		int M,N;
		double t1,t2,temp1;
		int choice;
		M=ImageLength;
		N=ImageWidthByte;

		pi=4.0*atan(1.0);

		double fp[MAXSIZE][MAXSIZE] = { 0 },f1[MAXSIZE][MAXSIZE];
		printf("Enter 1 for ideal low pass filter and 2 for ideal high pass filter:");
		scanf("%d",&choice);
		for(i=0;i<M;i++)
		{
			for(j=0;j<N;j++)
			{
				//if(i<M && j<N)
				//{
					fp[i][j]=fxy[i][j];
				/*}
	            else
				{
					fp[i][j]=0;
				}*/
			}

		}


		for(i=0;i<(2*M);i++)
		{
			for(j=0;j<(2*N);j++)
			{
				fp[i][j]=fp[i][j]*pow(-1, (double)(i+j));
			}
		}



		for(u=0;u<(2*M);u++)
		{
		   for(v=0;v<(2*N);v++)
		   {
				sumr=0.0;
				sumi=0.0;
				for(x=0;x<(2*M);x++)
				{
					for(y=0;y<(2*N);y++)
					{
						t1=(double)(u*x)/(2*M);
						t2=(double)(v*y)/(2*N);
						temp1=(2*pi*(t1+t2));
						
						sumr=sumr+(fp[x][y]*(cos(temp1)));
						sumi=sumi-(fp[x][y]*(sin(temp1)));
						
					}
				}
				Fr[u][v]=sumr;
				Fi[u][v]=sumi;
		         	
		   }
		   cout<<"F"; 
		}

		double d,d1=30;
		double gr[MAXSIZE][MAXSIZE],gi[MAXSIZE][MAXSIZE];
		int f;
		switch( choice )
		{
		case 1:
			for(x=0;x<(2*M);x++)
			{
				for(y=0;y<(2*N);y++)
				{
					d=sqrt((double)((x-M)*(x-M)+(y-N)*(y-N)));
					if(d>d1)
						f=0;
					else
						f=1;

					gr[x][y]=f*Fr[x][y];
					gi[x][y]=f*Fi[x][y];
				}
			}
		break;
		case 2:
			for(x=0;x<(2*M);x++)
			{
				for(y=0;y<(2*N);y++)
				{
					d=sqrt((double)((x-M)*(x-M)+(y-N)*(y-N)));
					if(d>d1)
						f=0;
					else
						f=1;

					gr[x][y]=f*Fr[x][y];
					gi[x][y]=f*Fi[x][y];
				}
			}
		break;
		default:
			cout<<"Wrong choice.";
		}
		for(x=0;x<(2*M);x++)
		{
			for(y=0;y<(2*N);y++)
			{
				sumr=0.0;
				sumi=0.0;
				for(u=0;u<(2*M);u++)
				{
					  for(v=0;v<(2*N);v++)
					  {
						t1=(double)(u*x)/(2*M);
						t2=(double)(v*y)/(2*N);
						temp1=(2*pi*(t1+t2));
						sumr=sumr+(gr[u][v]*(cos(temp1))) - (gi[u][v]*(sin(temp1)));
						sumi=sumi+(gr[u][v]*(sin(temp1))) + (gi[u][v]*(cos(temp1)));
					}
				 }
				f1[x][y]= sumr/(4*M*N);
		
				
			}
					cout<<"I";
		}

		
		for(i=0;i<(2*M);i++)
		{
	        for(j=0;j<(2*N);j++)
			{
	             f1[i][j]=f1[i][j]*pow(-1,(double)(i+j));
			}
		}
	/*	int count1=0;
		int count2=0;
	*/
		for(i=0;i<M;i++)
		{
	          for(j=0;j<N;j++)
			  {
	               //if(i<M && j<N)
				   {
						fxyout[i][j]=f1[i][j];
						/*if(fxyout[i][j]>255)
							fxyout[i][j] = 255;
						else if (fxyout[i][j]<0)
							fxyout[i][j] = 0;*/
				   }
			  }

		}

}




void Butterworth_Filter(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{

		unsigned int i , j ;
		int x,y,u,v;
		double pi,Fr[1500][1500],Fi[1500][1500],sumr,sumi;
		int M,N;
		double t1,t2,temp1;
		int choice;
		M=ImageLength;
		N=ImageWidthByte;

		pi=4.0*atan(1.0);

		double fp[1500][1500] = { 0.0 } ,f1[1500][1500];
		cout<<"Enter 1 for butterworth high pass filter and 2 for butterworth low pass filter:";
		cin>>choice;
		for(i=0;i<M;i++)
		{
			for(j=0;j<N;j++)
			{
					fp[i][j]=fxy[i][j];
			}

		}


		for(i=0;i<(2*M);i++)
		{
			for(j=0;j<(2*N);j++)
			{
				fp[i][j]=fp[i][j]*pow(-1, (double)(i+j));
			}
		}



		for(u=0;u<(2*M);u++)
		{
		   for(v=0;v<(2*N);v++)
		   {
				sumr=0.0;
				sumi=0.0;
				for(x=0;x<(2*M);x++)
				{
					for(y=0;y<(2*N);y++)
					{
						t1=(double)(u*x)/(2*M);
						t2=(double)(v*y)/(2*N);
						temp1=(2*pi*(t1+t2));
						
						sumr=sumr+(fp[x][y]*(cos(temp1)));
						sumi=sumi-(fp[x][y]*(sin(temp1)));
						
					}
				}
				Fr[u][v]=sumr;
				Fi[u][v]=sumi;
		         	
		   }
		   cout<<"F"; 
		}

		double d,d1=10 , f;
		double gr[1500][1500],gi[1500][1500];
		int  n = 2 ;
		switch( choice )
		{
		case 1:
			for(x=0;x<(2*M);x++)
			{
				for(y=0;y<(2*N);y++)
				{
					d=sqrt((double)((x-M)*(x-M)+(y-N)*(y-N)));

					f = 1 / ( 1 + pow( ( d1 / d ) , 2.0 * n )); 

					gr[x][y]=f*Fr[x][y];
					gi[x][y]=f*Fi[x][y];
				}
			}
		break;
		case 2:
			for(x=0;x<(2*M);x++)
			{
				for(y=0;y<(2*N);y++)
				{
					d=sqrt((double)((x-M)*(x-M)+(y-N)*(y-N)));
					f = 1 / ( 1 + pow( ( d / d1 ) , (2.0 * n) ));

					gr[x][y]=f*Fr[x][y];
					gi[x][y]=f*Fi[x][y];
				}
			}
		break;
		default:
			cout<<"Wrong choice.";
		}
		for(x=0;x<(2*M);x++)
		{
			for(y=0;y<(2*N);y++)
			{
				sumr=0.0;
				sumi=0.0;
				for(u=0;u<(2*M);u++)
				{
					  for(v=0;v<(2*N);v++)
					  {
						t1=(double)(u*x)/(2*M);
						t2=(double)(v*y)/(2*N);
						temp1=(2*pi*(t1+t2));
						sumr=sumr+(gr[u][v]*(cos(temp1))) - (gi[u][v]*(sin(temp1)));
						sumi=sumi+(gr[u][v]*(sin(temp1))) + (gi[u][v]*(cos(temp1)));
					}
				 }
				f1[x][y]= sumr/(4*M*N);
		
				
			}
					cout<<"I";
		}

		
		for(i=0;i<(2*M);i++)
		{
	        for(j=0;j<(2*N);j++)
			{
	             f1[i][j]=f1[i][j]*pow(-1,(double)(i+j));
			}
		}
	/*	int count1=0;
		int count2=0;
	*/
		for(i=0;i<M;i++)
		{
	          for(j=0;j<N;j++)
			  {
				   
						fxyout[i][j]=(unsigned char)f1[i][j];
					/*	if(fxyout[i][j]>255)
							fxyout[i][j] = 255;
						else if (fxyout[i][j]<0)
							fxyout[i][j] = 0;
				   */
			  }

		}

}


void Gaussian_Filter(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{


		unsigned int i , j ;
		int x,y,u,v;
		double pi,Fr[1500][1500],Fi[1500][1500],sumr,sumi;
		int M,N;
		double t1,t2,temp1;
		int choice;
		M=ImageLength;
		N=ImageWidthByte;

		pi=4.0*atan(1.0);

		double fp[1500][1500] = {0.0},f1[1500][1500];
		cout<<"Enter 1 for gaussian low pass filter and 2 for gaussian high pass filter:";
		cin>>choice;

		for(i=0;i<M;i++)
		{
			for(j=0;j<N;j++)
			{
					fp[i][j]=fxy[i][j];
			}

		}

		for(i=0;i<(2*M);i++)
		{
			for(j=0;j<(2*N);j++)
			{
				fp[i][j]=fp[i][j]*pow(-1, (double)(i+j));
			}
		}



		for(u=0;u<(2*M);u++)
		{
		   for(v=0;v<(2*N);v++)
		   {
				sumr=0.0;
				sumi=0.0;
				for(x=0;x<(2*M);x++)
				{
					for(y=0;y<(2*N);y++)
					{
						t1=(double)(u*x)/(2*M);
						t2=(double)(v*y)/(2*N);
						temp1=(2*pi*(t1+t2));
						
						sumr=sumr+(fp[x][y]*(cos(temp1)));
						sumi=sumi-(fp[x][y]*(sin(temp1)));
						
					}
				}
				Fr[u][v]=sumr;
				Fi[u][v]=sumi;
		         	
		   }
		   cout<<"F"; 
		}

		double d,d0=5;
		double gr[1500][1500],gi[1500][1500];
		//int  n = 2 ;
		double f ;
		d0 = (d0 * d0) * 2;
		switch( choice )
		{
		case 1:
			for(x=0;x<(2*M);x++)
			{
				for(y=0;y<(2*N);y++)
				{
					d=(double)((x-M)*(x-M)+(y-N)*(y-N));

					f = exp( -(( d ) / d0) ) ; 
					//cout<<f;
					gr[x][y]=f*Fr[x][y];
					gi[x][y]=f*Fi[x][y];
				}
			}
		break;
		case 2:
			for(x=0;x<(2*M);x++)
			{
				for(y=0;y<(2*N);y++)
				{
					d=sqrt((double)((x-M)*(x-M)+(y-N)*(y-N)));
					f = 1 - exp( -( d ) / d0 ) ;

					gr[x][y]=f*Fr[x][y];
					gi[x][y]=f*Fi[x][y];
				}
			}
		break;
		default:
			cout<<"Wrong choice.";
		}
		//getch();
		for(x=0;x<(2*M);x++)
		{
			for(y=0;y<(2*N);y++)
			{
				sumr=0.0;
				sumi=0.0;
				for(u=0;u<(2*M);u++)
				{
					  for(v=0;v<(2*N);v++)
					  {
						t1=(double)(u*x)/(2*M);
						t2=(double)(v*y)/(2*N);
						temp1=(2*pi*(t1+t2));
						sumr=sumr+(gr[u][v]*(cos(temp1))) - (gi[u][v]*(sin(temp1)));
						sumi=sumi+(gr[u][v]*(sin(temp1))) + (gi[u][v]*(cos(temp1)));
					}
				 }
				f1[x][y]= sumr/(4*M*N);
		
				
			}
					cout<<"I";
		}

		
		for(i=0;i<(2*M);i++)
		{
	        for(j=0;j<(2*N);j++)
			{
	             f1[i][j]=f1[i][j]*pow(-1,(double)(i+j));
			}
		}
	/*	int count1=0;
		int count2=0;
	*/
		for(i=0;i<M;i++)
		{
	          for(j=0;j<N;j++)
			  {
				   
						fxyout[i][j]=f1[i][j];
			  }
		}


}


void Laplacian_Filter(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{


	unsigned int i , j ;
	int x,y,u,v;
	double pi,Fr[1500][1500],Fi[1500][1500],sumr,sumi,NM_fxy[MAXSIZE][MAXSIZE];
	int M,N;
	double t1,t2,temp1 , del_max = 0 ;
	int choice , min = 255 , max = 0 ;
	double temp_fxy[MAXSIZE][MAXSIZE] ;
	M=ImageLength;
	N=ImageWidthByte;

	pi=4.0*atan(1.0);

	double fp[1500][1500] = {0.0},f1[1500][1500];

	// To find the maximum and minimum value in the image
	for( i = 0 ; i < M ; i++ )
	{
		for( j = 0 ; j < N ; j++ )
		{
			//temp_fxy[i][j] = fxy[i][j]; 
			if( min > fxy[i][j] )
				min = fxy[i][j];
			if( max < fxy[i][j] )
				max = fxy[i][j];
		}
	}
	cout<<"Values of Min and Max:"<<min<<"\t"<<max;
	getch();
	//To normalize the values in range from 0 to 1
	for( i = 0 ; i < M ; i++ )
	{
		for( j = 0 ; j < N ; j++ )
		{
			temp_fxy[i][j]=(0 + ((double)(1.0)/(max - min)) * (fxy[i][j] - min));
			//cout<<temp_fxy[i][j]<<"\t";
		}
	}
		
		//Extend the image
	for(i=0;i<M;i++)
	{
		for(j=0;j<N;j++)
		{
				fp[i][j]=temp_fxy[i][j];
		}
	
	}
	
	//shift origin to the center
	for(i=0;i<(2*M);i++)
	{
		for(j=0;j<(2*N);j++)
		{
			fp[i][j]=fp[i][j]*pow(-1, (double)(i+j));
		}
	}
	
	
	//forward fourier transformation
	for(u=0;u<(2*M);u++)
	{
	   for(v=0;v<(2*N);v++)
	   {
			sumr=0.0;
			sumi=0.0;
			for(x=0;x<(2*M);x++)
			{
				for(y=0;y<(2*N);y++)
				{
					t1=(double)(u*x)/(2*M);
					t2=(double)(v*y)/(2*N);
					temp1=(2*pi*(t1+t2));
					
					sumr=sumr+(fp[x][y]*(cos(temp1)));
					sumi=sumi-(fp[x][y]*(sin(temp1)));
					
				}
			}
			Fr[u][v]=sumr;
			Fi[u][v]=sumi;
	         	
	   }
	   cout<<"F"; 
	}
	// applying filter
	double d , f;
	double gr[1500][1500],gi[1500][1500];
	//d0 = (d0 * d0) * 2;
	for(x=0;x<(2*M);x++)
	{
		for(y=0;y<(2*N);y++)
		{
			d = ((double)(x-M)*(x-M)+(y-N)*(y-N));
	
			f = -4 * ( pi * pi ) * d ; 
	
			gr[x][y] = f*Fr[x][y];
			gi[x][y] = f*Fi[x][y];
		}
	}
	//double max = 0.0;
	//inverse of an image
	for(x=0;x<(2*M);x++)
	{
		for(y=0;y<(2*N);y++)
		{
			sumr=0.0;
			sumi=0.0;
			for(u=0;u<(2*M);u++)
			{
				  for(v=0;v<(2*N);v++)
				  {
					t1=(double)(u*x)/(2*M);
					t2=(double)(v*y)/(2*N);
					temp1=(2*pi*(t1+t2));
					sumr=sumr+(gr[u][v]*(cos(temp1))) - (gi[u][v]*(sin(temp1)));
					sumi=sumi+(gr[u][v]*(sin(temp1))) + (gi[u][v]*(cos(temp1)));
				}
			 }
			f1[x][y] = sumr/(4*M*N);
			}
				cout<<"I";
	}
			
	/*	int count1=0;
		int count2=0;
	*/
	for(i=0;i<(2*M);i++)
	{
	       for(j=0;j<(2*N);j++)
		{
	            f1[i][j] = f1[i][j]*pow(-1,(double)(i+j));
		}
	}
	
	//dividing delfxy by its maximum
	
	for(i=0;i<M;i++)
	{
	    for(j=0;j<N;j++)
		{
	            if( f1[i][j] > del_max )
				del_max = f1[i][j] ;
		}
	}
	for( i = 0 ; i < M ; i++)
	{
	    for(j=0;j<N;j++)
		{
	            f1[i][j] = f1[i][j] / del_max;
		}
	}
	double min1 = 255 , max1 = 0;
	for(i=0;i<M;i++)
	{
	      for(j=0;j<N;j++)
		  {
				temp_fxy[i][j] = temp_fxy[i][j] - f1[i][j] ;
				if( temp_fxy[i][j] > max1 )
					max1 = temp_fxy[i][j];
				else if( temp_fxy[i][j] < min1 )
					min1 = temp_fxy[i][j];
		  }
	}
	for( i = 0 ; i < M ; i++ )
	{
		for ( j = 0 ; j < N ; j++ )
		{
			fxyout[i][j] =  ((double)(255-0)/(double)(max1-min1))*(double)(temp_fxy[i][j]-min1);
		}
	}
}
/*void Notch_Filter(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
	double fpxy[MAXSIZE][MAXSIZE],real[MAXSIZE][MAXSIZE],imag[MAXSIZE][MAXSIZE],gxy_real[MAXSIZE][MAXSIZE],
gxy_imag[MAXSIZE][MAXSIZE],gxy[MAXSIZE][MAXSIZE],gpxy[MAXSIZE][MAXSIZE];

int u,v,x,y,freq[5],P,Q,i,j,up[5],vp[5],un[5],vn[5];

double h,pi,sum_real,sum_imag,pi2,pi2P,pi2Q,c1,c2,c3,c4,theta,val,val_real,val_imag,
dp,dn,interp,intern,rp,rn; 

int Q1,n1,n2,t;

P=2*M;
Q=2*N;
pi2=2*pi;
pi2P=pi2/P;
pi2Q=pi2/Q;
for(i=0;i<P;i++)
	for(j=0;j<Q;j++)
		fpxy[i][j]=0;

for(i=0;i<M;i++)
	for(j=0;j<N;j++)
		fpxy[i][j]=fxy[i][j];

for(i=0;i<P;i++)
	for(j=0;j<Q;j++)
		fpxy[i][j]=fpxy[i][j]*pow(-1,(i+j));

for(u=0;u<P;u++)
{	
	c1=pi2P*u;
	for(v=0;v<Q;v++)
	{	
		c2=pi2Q*v;
		sum_real=0.0;
		sum_imag=0.0;
		for(x=0;x<P;x++)
		{
			c3=c1*x;
			for(y=0;y<Q;y++)
			{	
				c4=c2*y;
				val=fxy[x][y];
				theta=c3+c4;
				sum_real+=(val*cos(theta));
				sum_imag+=(val*sin(theta));
			}
		}
	real[u][v]=sum_real;
	imag[u][v]=sum_imag;
	}
}
printf("enter the value of Q");
cin>>Q1;
cout<<"\nenter the value of D0";
for(i=0;i<Q1;i++)
cin>>freq1[i];
cout<<"\nenter u,v for"<<Q1<<"regions";

	for(i=0;i<Q1;i++)
	cin>>up[i]>>vp[i];
	for(i=0;i<Q1;i++)
	{
		un[i]=(-1)*up[i];
		vn[i]=(-1)*vp[i];
	}
for(u=0;u<P;u++)
{	
for(v=0;v<Q;v++)
{
	h=1;
	for(t=0;t<Q1;t++)
	{
	interp=(u-M-up[t])*(u-M-up[t])+(v-N-vp[t])*(v-N-vp[t]);
	intern=(u-M-un[t])*(u-M-un[t])+(v-N-vn[t])*(v-N-vn[t]);
	dp=sqrt(interp);
	dn=sqrt(intern);
	rp=freq1[t]/dp;
	rn=freq1[t]/dn;
	h*=(1/(1+(pow(rp,n2))))*(1/(1+pow(rn,n2))));
}
gxy_real[u][v]=real[u][v]*h;

gxy_imag[u][v]=imag[u][v]*h;
}
}
for(x=0;x<P;x++)
{
	c1=pi2P*x;
	for(y=0;y<Q;y++)
	{
		c2=pi2Q*y;
		sum_real=0.0;
		sum_imag=0.0;
		for(u=0;u<P;u++)
		{	c3=c1*u;
			for(v=0;v<Q;v++)
			{	c4=c2*v;
				val_real=gxy_real[u][v];
				val_imag=gxy_imag[u][v];
				theta=c3+c4;
				sum_real+=(val_real*cos(theta))-(val_imag*sin(theta));
				sum_imag+=(val_real*sin(theta))+(val_imag*cos(theta));
			}
		}
		gxy[x][y]=(sum_real)/(P*Q);
	}
}
sign=1;
for(i=0;i<P;i++)
{
	
	for(j=0;j<Q;j++)
	{
		gpxy[i][j]=gxy[i][j]*sign;
		sign=(-1)*sign;
	}
}
for(i=0;i<M;i++)
for(j=0;j<N;j++)
fxyout[i][j]=(unsigned char)gpxy[i][j];
}
*/

/*
void F_T(unsigned long ImageLength, unsigned long ImageWidthByte,unsigned char fxyout[MAXSIZE][3*MAXSIZE],unsigned char fxy[MAXSIZE][3*MAXSIZE])
{


	
			double fr[MAXSIZE][MAXSIZE],fi[MAXSIZE][MAXSIZE];
			int x,y,u,v;
			int M=ImageLength;
			int N=ImageWidthByte;
			double sum_real,sum_img,pi;

			pi=4.0*atan(1.0);
			for(u=0;u<M;u++)
			{
				for(v=0;v<N;v++)
				{
					sum_real=0;
					sum_img=0;
					for(x=0;x<M;x++)
					{
						for(y=0;y<N;y++)
						{
							double c=2*pi*((double)(u*x)/M)+((double)(v*y)/N);
							sum_real=sum_real+fxy[x][y]*cos(c);
							sum_img=sum_img-fxy[x][y]*(sin(c));
						}
					}
					fr[u][v]=sum_real /( M * N);
					fi[u][v]=sum_img /( M * N);
				}
				printf("F");
			}
			for(x=0;x<M;x++)
			{
				for(y=0;y<N;y++)
				{
					sum_real=0;
					sum_img=0;
					for(u=0;u<M;u++)
					{
						for(v=0;v<N;v++)
						{
							double c=cos(2*pi*(((double)(u*x)/M)+(double)(v*y)/N));
							double s=sin(2*pi*(((double)(u*x)/M)+(double)(v*y)/N));
							sum_real=sum_real+(fr[u][v]*c-(fi[u][v]*s));
							sum_img=sum_img+fr[u][v]*s-(fi[u][v]*c);
						}
					}
				//	sum_real=round(sum_real);
					fxyout[x][y]=sum_real;
				}
				printf("I");
			}

}*/

/* Copies the grayscale/color image to a 2D array  */
/*************************************************************************
*                                                                        *
*  Copies the grayscale/color image to a 2D array                                   *
*                                                                        *
**************************************************************************
*/
void copy_to_array(unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char *IB, unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
	   int npixels=0; 
	   unsigned int i, j;
	   for(i=0; i<ImageLength; i++)
	   {
		   for(j=0; j<ImageWidthByte; j++)
		   {
			   npixels++;
			   fxy[i][j]=*IB;
			   IB++;
		   }  //  j-loop
	   }  // i-loop
	   printf("For Original Image : Total pixels=%d\n", npixels);  getch();   
}

/* Copies the array to image output file  */
/*************************************************************************
*                                                                        *
*  Copies the array to image output file                                 *
*                                                                        *
**************************************************************************
*/
void copy_array_to_file(unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE], FILE *outfile_ptr)
{
	   int npixels=0; 
	   unsigned int i, j;
	   unsigned char pic_byte;
	   for(i=0; i<ImageLength; i++)
	   {
		   for(j=0; j<ImageWidthByte; j++)
		   {
			   npixels++; pic_byte=fxyout[i][j];  // R-component
			   fwrite((const void *) &pic_byte, (size_t)sizeof(pic_byte), (size_t)1, 
				   outfile_ptr);
		   }  //  j-loop
	   }  // i-loop
	   printf("For Output Image : Total pixels=%d\n", npixels);  getch();   
}

/* Copies the array to image output file  */
/*************************************************************************
*                                                                        *
*  Write image function values to text file.                             *
*                                                                        *
**************************************************************************
*/
void copy_to_text_file(unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE])
{
	int count=0;   
	unsigned int i, j;
	FILE *outfile; 
   // Open a text file for writing image data in text mode 
   if((outfile = fopen("image_text.out", "w")) ==NULL)
   {
	   printf("can't open file -image_text.out");  getch();
	   exit(0);
   }
   count=0;
   for(i=0; i<ImageLength; i++)
   {
	   for(j=0; j<ImageWidthByte; j++)
	   {
		   count++;
		   fprintf(outfile, "%4d", fxyout[i][j]);
		   if(count==10) { fprintf(outfile, "\n");  count++;  }
	   }  //  j-loop
       fprintf(outfile, "\n"); 
   }  // i-loop
}

/* Routine for displaying the error messages.  */
/*************************************************************************
*                                                                        *
*   Displays error.                                                      *
*                                                                        *
**************************************************************************
*/

void display_error( char *message)
{
	printf("%s\n", message);
	printf("Program stopped !!\n");  getch(); getch();
	exit(0);
}
