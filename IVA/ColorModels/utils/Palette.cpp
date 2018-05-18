/*
 * Palette.cpp
 *
 *  Created on: 13 sept. 2010
 *      Author: David Roussel
 */

#include <iostream>		// pour cout & cerr
#include <fstream>		// pour l'ifstream
#include <string>		// pour les string
using namespace std;

#include "Palette.h"

const size_t Palette::CMAPSIZE = 256;

const size_t Palette::COMPSIZE = 3;

/*
 * Constructor from bidimensional array
 * @param map bidimensional array containing palette values
 * @param minimum value in the palette (default is 0)
 * @param maximum value in the palette (default is 255)
 */
Palette::Palette(unsigned char map[][3], int min, int max) :
	colormap(COMPSIZE),
	minValue(min),
	maxValue(max),
	BGRChannels(COMPSIZE),
	channelsAllocated(false)
{
	// initialize colormaps
	for (size_t i=0; i < colormap.size(); i++)
	{
		colormap[i].create(CMAPSIZE,1,CV_8UC1);
	}

	// fill colormap with values
	for (size_t c = 0; c < COMPSIZE; c++)
	{
		for (size_t i=0; i < CMAPSIZE; i++)
		{
			colormap[c].at<uchar>(i, 0) = map[i][c];
		}
	}
}

/*
 * Constructor from file name.
 * List of operations :
 * 	- opens the file
 * 	- if file is correctly opened, then reads each line (ignoring lines
 * 	starting with a "#" which indicates a comment line)
 * 	- each line should contain 3 bytes : e.g. 127 0 255
 * @param filename the name of the file to read
 * @param minimum value in the palette (default is 0)
 * @param maximum value in the palette (default is 255)
 */
Palette::Palette(const char * const filename, int min, int max) :
	colormap(COMPSIZE),
	minValue(min),
	maxValue(max),
	BGRChannels(COMPSIZE),
	channelsAllocated(false)
{
	// initialize colormaps
	for (size_t i=0; i < colormap.size(); i++)
	{
		colormap[i].create(CMAPSIZE,1,CV_8UC1);
	}

	unsigned int lineCount = 0;
	unsigned int dataLineCount = 0;

	if (filename != NULL)
	{
		ifstream inputFile(filename);

		if (inputFile.is_open())
		{
			string currentLine;
			istringstream lineStream;
			size_t searchComment;
			int readValues[COMPSIZE];

			while (!inputFile.eof())
			{
				getline(inputFile, currentLine);

				lineCount++;

				if (currentLine.length() > 0)
				{
					// checks for # character at the beginning of the line
					searchComment = currentLine.find('#');

					if ((searchComment == string::npos) &&
						((int)searchComment != 0))
						// no leading comment found : data line
					{
						// set current line into input string stream
						lineStream.str(currentLine);

						for (size_t i=0; i < COMPSIZE; i++)
						{
							// reads single value from input string stream
							lineStream >> readValues[i];
							if (lineStream.fail())
							{
								cerr << "Error reading RGB value index " << i
								     <<" at line " << lineCount << endl;
								exit(EXIT_FAILURE);
							}
							else
							{
								// checks invalid values
								if (readValues[i] > maxValue)
								{
									readValues[i] = maxValue;
								}
								if (readValues[i] < minValue)
								{
									readValues[i] = minValue;
								}
							}

							// Fill colormap with value
							colormap[i].at<uchar>((int)dataLineCount,0)
								= (uchar)readValues[i];
						}

						lineStream.clear();

//						cout << "line " << lineCount << "[" << dataLineCount
//							 << "] contains : \"" << currentLine << "\" data are "
//							 << readValues[0] << ", " << readValues[1]
//							 << ", " << readValues[2] << endl;

						dataLineCount++;
					}
//					else // comment found at pos 0
//					{
//						cout << "comment line at line " << lineCount
//						     << " : " << currentLine << endl;
//					}
				}
//				else // empty line : skip
//				{
//					cout << "empty line at line " << lineCount << endl;
//				}
			}

			if (dataLineCount != CMAPSIZE)
			{
				cerr << "Wrong number of datalines in the colormap : "
				     << dataLineCount << endl;
				exit(EXIT_FAILURE);
			}
//			else
//			{
//				cout << "Correctly read "<< CMAPSIZE <<" data lines" << endl;
//			}

			inputFile.close();
		}
		else // inputFile is not opened
		{
			cerr << "Palette::Palette(" << filename << ") : unable to open file"
			     << endl;
			exit(EXIT_FAILURE);
		}
	}
	else // filename is NULL
	{
		cerr << "Palette::Palette(NULL filename) : empty file name" << endl;
		exit(EXIT_FAILURE);
	}
}

/*
 * Palette destructor.
 * Relese all images and clear vectors
 */
Palette::~Palette()
{
	// Release matrices
	for (size_t i=0; i < colormap.size(); i++)
	{
		colormap[i].release();
		BGRChannels[i].release();
	}

	// Clear vectors
	colormap.clear();
	BGRChannels.clear();
}

/*
 * Apply the colormap on the single channel source image to build
 * a destination 3 channels color image.
 * @param src source mono-channel image
 * @param dst destination BGR-BGRChannels image
 */
void Palette::applyPalette(const Mat & src, Mat & dst)
{
	const size_t BGR2RGB[CMAPSIZE] = {2,1,0};

	// checks if source has only one channel
	if (src.channels() == 1)
	{
		if (!channelsAllocated) // BGRChannels should be allocated first
		{
			for (size_t i=0; i < BGRChannels.size(); i++)
			{
				BGRChannels[i].create(src.size(),CV_8UC1);
			}
			channelsAllocated = true;
		}

		if (src.size() != BGRChannels[0].size()) // BGRChannels should be reallocated
		{
			for (size_t i=0; i < BGRChannels.size(); i++)
			{
				BGRChannels[i].release();
				BGRChannels[i].create(src.size(),CV_8UC1);
			}
		}

		// Apply Look Up Table on each channel
		for (size_t i=0; i < COMPSIZE; i++)
		{
			LUT(src,colormap[BGR2RGB[i]],BGRChannels[i]);
		}

		// then merge all the BGRChannels into a BGR image
		merge(BGRChannels, dst);
	}
	else // source has multiple channels
	{
		cerr << "Palette::applyColormap(...) : source has " << src.channels()
		     << " channels" << endl;
	}
}
