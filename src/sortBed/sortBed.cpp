/*****************************************************************************
  sortBed.cpp

  (c) 2009 - Aaron Quinlan
  Hall Laboratory
  Department of Biochemistry and Molecular Genetics
  University of Virginia
  aaronquinlan@gmail.com

  Licenced under the GNU General Public License 2.0+ license.
******************************************************************************/
#include "lineFileUtilities.h"
#include "sortBed.h"

//
// Constructor
//
BedSort::BedSort(string &bedFile) {
	this->bedFile = bedFile;
	this->bed = new BedFile(bedFile);
}

//
// Destructor
//
BedSort::~BedSort(void) {
}


void BedSort::SortBed() {

	// load the "B" bed file into a map so
	// that we can easily compare "A" to it for overlaps
	bed->loadBedFileIntoMapNoBin();

	// loop through each chromosome and merge their BED entries
	for (masterBedMapNoBin::iterator m = bed->bedMapNoBin.begin(); m != bed->bedMapNoBin.end(); ++m) {

		// bedList is already sorted by start position.
		vector<BED> bedList = m->second; 

		for (unsigned int i = 0; i < bedList.size(); ++i) {
			bed->reportBedNewLine(bedList[i]);
		}
	}
}


void BedSort::SortBedBySizeAsc() {

	// load the "B" bed file into a map so
	// that we can easily compare "A" to it for overlaps
	bed->loadBedFileIntoMapNoBin();

	vector<BED> masterList;
	masterList.reserve(1000000);
	
	// loop through each chromosome and merge their BED entries
	for (masterBedMapNoBin::iterator m = bed->bedMapNoBin.begin(); m != bed->bedMapNoBin.end(); ++m) {

		// bedList is already sorted by start position.
		vector<BED> bedList = m->second; 

		// add the entries from this chromosome to the current list
		for (unsigned int i = 0; i < m->second.size(); ++i) {
			masterList.push_back(m->second[i]);
		}
	}
	
	// sort the master list by size (asc.)
	sort(masterList.begin(), masterList.end(), sortBySizeAsc);
	
	// report the entries in ascending order
	for (unsigned int i = 0; i < masterList.size(); ++i) {
		bed->reportBedNewLine(masterList[i]);
	}
}


void BedSort::SortBedBySizeDesc() {

	// load the "B" bed file into a map so
	// that we can easily compare "A" to it for overlaps
	bed->loadBedFileIntoMapNoBin();

	vector<BED> masterList;
	masterList.reserve(1000000);
	
	// loop through each chromosome and merge their BED entries
	for (masterBedMapNoBin::iterator m = bed->bedMapNoBin.begin(); m != bed->bedMapNoBin.end(); ++m) {

		// bedList is already sorted by start position.
		vector<BED> bedList = m->second; 

		// add the entries from this chromosome to the current list
		for (unsigned int i = 0; i < m->second.size(); ++i) {
			masterList.push_back(m->second[i]);
		}
	}
	
	// sort the master list by size (asc.)
	sort(masterList.begin(), masterList.end(), sortBySizeDesc);
	
	// report the entries in ascending order
	for (unsigned int i = 0; i < masterList.size(); ++i) {
		bed->reportBedNewLine(masterList[i]);
	}
}

void BedSort::SortBedByChromThenSizeAsc() {

	// load the "B" bed file into a map so
	// that we can easily compare "A" to it for overlaps
	bed->loadBedFileIntoMapNoBin();

	// loop through each chromosome and merge their BED entries
	for (masterBedMapNoBin::iterator m = bed->bedMapNoBin.begin(); m != bed->bedMapNoBin.end(); ++m) {

		// bedList is already sorted by start position.
		vector<BED> bedList = m->second; 
		sort(bedList.begin(), bedList.end(), sortBySizeAsc);
		
		for (unsigned int i = 0; i < bedList.size(); ++i) {
			bed->reportBedNewLine(bedList[i]);
		}
	}
}


void BedSort::SortBedByChromThenSizeDesc() {

	// load the "B" bed file into a map so
	// that we can easily compare "A" to it for overlaps
	bed->loadBedFileIntoMapNoBin();

	// loop through each chromosome and merge their BED entries
	for (masterBedMapNoBin::iterator m = bed->bedMapNoBin.begin(); m != bed->bedMapNoBin.end(); ++m) {

		// bedList is already sorted by start position.
		vector<BED> bedList = m->second; 

		sort(bedList.begin(), bedList.end(), sortBySizeDesc);
		
		for (unsigned int i = 0; i < bedList.size(); ++i) {
			bed->reportBedNewLine(bedList[i]);
		}
	}
}


void BedSort::SortBedByChromThenScoreAsc() {

	// load the "B" bed file into a map so
	// that we can easily compare "A" to it for overlaps
	bed->loadBedFileIntoMapNoBin();

	if (bed->bedType >= 5) {
		// loop through each chromosome and merge their BED entries
		for (masterBedMapNoBin::iterator m = bed->bedMapNoBin.begin(); m != bed->bedMapNoBin.end(); ++m) {

			// bedList is already sorted by start position.
			vector<BED> bedList = m->second; 
			sort(bedList.begin(), bedList.end(), sortByScoreAsc);
			
			for (unsigned int i = 0; i < bedList.size(); ++i) {
				bed->reportBedNewLine(bedList[i]);
			}
		}
	}
	else {
		cerr << "Error: Requested a sort by score, but your BED file does not appear to be in BED 5 format or greater.  Exiting." << endl;
		exit(1);
	}
}


void BedSort::SortBedByChromThenScoreDesc() {

	// load the "B" bed file into a map so
	// that we can easily compare "A" to it for overlaps
	bed->loadBedFileIntoMapNoBin();

	if (bed->bedType >= 5) {
		// loop through each chromosome and merge their BED entries
		for (masterBedMapNoBin::iterator m = bed->bedMapNoBin.begin(); m != bed->bedMapNoBin.end(); ++m) {

			// bedList is already sorted by start position.
			vector<BED> bedList = m->second; 
			sort(bedList.begin(), bedList.end(), sortByScoreDesc);
		
			for (unsigned int i = 0; i < bedList.size(); ++i) {
				bed->reportBedNewLine(bedList[i]);
			}
		}
	}
	else {
		cerr << "Error: Requested a sort by score, but your BED file does not appear to be in BED 5 format or greater.  Exiting." << endl;
		exit(1);
	}
}

