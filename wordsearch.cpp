#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>

#include "inErr.h"

using namespace std;

int main() {
    //Var init
    const short MAX_TRIES = 10000; 
    ifstream dataFile;
    string fileName;
    unsigned short wordCount, lines, points = 0;
    size_t maxLength = 0;
    
    //File Opening Process
    cout << "\tHello! Welcome to Wordsearch!\n"
            "Please enter the name of your data file:  ";
    getline(cin, fileName);
    
    //Opening
    cout << "Opening...\n";
    dataFile.open(fileName);
    while (!dataFile) {
        dataFile.close();
        dataFile.clear();
        cout << "\nCould not open '" << fileName << "'\n"
                "Please try a different file:  ";
        getline(cin, fileName);
        dataFile.open(fileName);
        cout << "Opening...\n";
    }



    //Processing
    cout << "Configuring...\n";
    dataFile >> ws;
    //Configuration
    cout << "How many words would you like in your wordsearch?\n";
    InErr(wordCount);
    string * wordList{new(nothrow) string[wordCount]};
    string * parr = nullptr;

    //Random word Selection
    while (dataFile.ignore(INF_STREAM,'\n')) {
        lines++;
    }

    dataFile.clear();
    dataFile.seekg(0,ios::beg);
    string * fileList{new(nothrow) string[lines]};
    for (parr = fileList; parr != fileList+lines; parr++) {
        getline(dataFile,*parr);
    }


    srand(static_cast<unsigned int>(time(0)));
    //srand(0);
    for (parr = wordList; parr != wordList+wordCount; parr++) {
        *parr = fileList[rand() % (lines - 1)];
        if (parr->length() > maxLength) {
            maxLength = parr->length();
        }
    }
    dataFile.close();
    dataFile.clear();
    delete[] fileList;
    parr = nullptr;

    cout << "Creating Wordsearch...\n";

    // allocation

    
    //2D Array allocation and modification
    size_t width = maxLength + 4;

    //Debugging code to test nothrow
    //size_t width = 200000000000000;

    char ** arr2D = new(nothrow) char*[width];
    char * arr1D{new(nothrow) char[width*width]};
    
    if (!arr2D || !arr1D)  {
        cout << "\nSorry, not enough storage available to do that :/\n" 
                "Goodbye!\n";
        return 1;    
    }
    
    if (arr2D  && arr1D) {
        for (size_t r = 0; r != width; r++)    
        {
            arr2D[r] = arr1D + r*width;
            for (size_t c = 0; c < width; c++) {
                arr2D[r][c] = '_';
            }
        } 
    }
    
    cout << "Placing words...\n";
    //The large Block of Code that puts in words
    for (parr = wordList; parr != wordList+wordCount; parr++) {
        bool placed = false, isReversed = false;
        if (rand()%2 == 1) {
            reverse(parr->begin(),parr->end());
            isReversed = true;
        }
        for (short i = 0; i < MAX_TRIES && !placed; i++) {
            
            size_t r, c;
            r = rand() % width;
            c = rand() % width;

            switch (rand()%4) {

                case 0: {
                    if (r + parr->length() < width - r) {
                        bool isValid = true;
                        for (size_t j = 0; j < parr->length() 
                                                && isValid; j++) {
                            if (arr2D[r+j][c] != '_' && 
                                arr2D[r+j][c] != (*parr)[j]) {
                                isValid = false;
                            }
                        }
                        if (isValid) {
                            for (size_t j = 0; j < parr->length(); j++){
                                arr2D[r+j][c] = (*parr)[j];
                                placed = true;
                            }
                        }
                    }
                } break;
                case 1: {
                    if (c + parr->length() < width - c) {
                        bool isValid = true;
                        for (size_t j = 0; j < parr->length() 
                                                && isValid; j++) {
                            if (arr2D[r][c+j] != '_' && 
                                arr2D[r][c+j] != (*parr)[j]) {
                                isValid = false;
                            }
                        }
                        if (isValid) {
                            for (size_t j = 0; j < parr->length(); j++){
                                arr2D[r][c+j] = (*parr)[j];
                                placed = true;
                            }
                        }
                    }

                } break;
                case 2: {
                    if (r + parr->length() < width - r && 
                        c + parr->length() < width - c) {
                        bool isValid = true;
                        for (size_t j = 0; j < parr->length() 
                                                && isValid; j++) {
                            if (arr2D[r+j][c+j] != '_' && 
                                arr2D[r+j][c+j] != (*parr)[j]) {
                                isValid = false;
                            }
                        }
                        if (isValid) {
                            for (size_t j = 0; j < parr->length(); j++){
                                arr2D[r+j][c+j] = (*parr)[j];
                                placed = true;
                            }
                        }
                    }
                } break;
                case 3: {
                    if (r - parr->length() < r - width && 
                        c + parr->length() < width - c) {
                        bool isValid = true;
                        for (size_t j = 0; j < parr->length() 
                                                && isValid; j++) {
                            if (arr2D[r-j][c] != '_' && 
                                arr2D[r-j][c] != (*parr)[j]) {
                                isValid = false;
                                
                            }
                        }
                        if (isValid) {
                            for (size_t j = 0; j < parr->length(); j++){
                                arr2D[r-j][c+j] = (*parr)[j];
                                placed = true;
                                
                            }
                        }
                    }
                } break;

            }
        }
        if (isReversed) {
            reverse(parr->begin(),parr->end());
        }
        if (!placed) {
            cout << "\nCould not place " << *parr << "\n";
        }
    }


    while (wordCount > 0) {

        const char letters[] = "abcdefghijklmnopqrstuvwxyz";
        cout << "     ";
        for (size_t c = 0; c < width; c++) {
            cout << setw(3) << setfill(' ') << left << c;
        }  
        cout << "\n";
        for (size_t r = 0; r < width; r++) {
            cout << setw(3) << setfill(' ') << right << r << ": ";
            for (size_t c = 0; c < width; c++) {
                if (arr2D[r][c] == '_') {
                    arr2D[r][c] = letters[rand() % 26];
                } 
                cout << arr2D[r][c];                
                cout << "  ";
            }
            cout << "\n";
        }
            
        cout << "\nWord List:\n";
        for (parr = wordList; parr != wordList + wordCount; parr++) {
            cout << *parr << "\n";
    
        }


        // Gameplay portion!
        size_t startr, startc, endr, endc;
        char dum;
        cout << "\nEnter coordinates of first letter (x,y):\n"
                "(Starting at (0,0) in the top left)\n";
        cin >> dum >> startc >> dum >> startr >> dum;
        while (cin.fail() || startc >= width || startr >= width) {
            cin.clear();
            cin.ignore(INF_STREAM, '\n');
            cerr << "\nInvalid Coordinates, try again:\n";
            cin >> dum >> startc >> dum >> startr >> dum;
        }
        cout << "\nEnter coordinates of last letter(x,y):\n"
                "(Starting at (0,0) in the top left)\n";
        cin >> dum >> endc >> dum >> endr >> dum;
        while (cin.fail() || endc >= width || endr >= width) {
            cin.clear();
            cin.ignore(INF_STREAM, '\n');
            cerr << "\nInvalid Coordinates, try again:\n";
            cin >> dum >> endc >> dum >> endr >> dum;
        }
        //Coordinates Gathered


    
        //Collect string from Arr2D
        string answr;
        short xAxis, yAxis, len;
        if (startc == endc) {
            xAxis = 0;
        } else if (startc > endc) {
            xAxis = -1;
            len = static_cast<short>(startc - endc);
        } else {
            xAxis = 1;
            len = static_cast<short>(startc - endc);
        }
        if (startr == endr) {
            yAxis = 0;
        } else if (startr > endr) {
            yAxis = -1;
            len = static_cast<short>(startr - endr);
        } else {
            yAxis = 1;
            len = static_cast<short>(startr - endr);
        }
        len = abs(len);
        len++;
        
        //Gather Chars
        for (short i = 0; i < len;i++) {
            answr += 
                static_cast<char>(tolower
                    (arr2D[startr+yAxis*i][startc+xAxis*i]));
        }

        //See if the word is on our list
        bool isFound = false;
        for (parr = wordList; parr != wordList + wordCount 
                                    && !isFound;parr++) {
            if (answr == *parr) {
                isFound = true;
                if (wordCount > 1) {
                    for (string * jparr = parr; 
                        jparr != wordList + wordCount - 1; jparr++) {
                        *jparr = jparr[1];
                    }
                }
                wordCount--;
            }
        }
        if (isFound) {
            for (short i = 0; i < len;i++) {
                arr2D[startr+yAxis*i][startc+xAxis*i] = 
                static_cast<char>(toupper(
                    arr2D[startr+yAxis*i][startc+xAxis*i]));
            }
            points += static_cast<unsigned short>(len);
            cout << "You found a word!\n[+" << len << " points]\n";
        } else {
            cout << "Are you sure you have that right?\nTry Again:\n";
        }
    
    }
    //Gameplay Loop End
    cout << "\nWow!\nYou found all the words!\n"
            "[Total Points: " << points << "]\n";
    // deallocation
    delete [] arr2D;
    delete [] arr1D;


    return 0;
}
