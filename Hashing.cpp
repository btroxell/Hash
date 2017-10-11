#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

class Hash{

private:

    static const int tableSize = 26; //initialize the tablesize that is

    struct wordItem{
        string word;
        wordItem* next;
    };

    wordItem* HashTable[tableSize];

public:

    Hash();//no args constuctor
    void addWord(string word);
    bool lookup(int index, string word);
    void testPrint();
    int hashFunc(string key);
    int testRun(int index);



};

Hash::Hash(){

    for(int i=0; i<tableSize; i++){ //for loop to initialize the hashtable

        HashTable[i] = new wordItem; //gives the index of the hashtable a new worditem
        HashTable[i]->word = "nil"; //default value for the an unhashed spot
        HashTable[i]->next = NULL; //gives the pointer to point at null
    }//end for

}//end hash constructor

//int Hash::testRun(int index){

//    int counter = 0;

//    if(HashTable[index]->word == "nil"){
//        return counter;
//    }//end if
//    else{

//        counter++;
//        wordItem* wdPtr = HashTable[index];
//        while(wdPtr != NULL){
//            counter++;
//            wdPtr = wdPtr->next;
//        }//end while

//    }//end else

//    return counter;

//}//end testrun

bool Hash::lookup(int index, string theWord){

    //cout << index << endl;
    bool inBucket = false;

    wordItem* wdPtr = HashTable[index];

    int N = theWord.length();
    //cout << "length of word = " << N << endl;
    int i = 0;

    while(wdPtr != NULL){
        if(theWord[i+1] == wdPtr->word[i+1]){
            inBucket = true;
            cout << wdPtr->word << endl;
            wdPtr = wdPtr->next;
        }//end if
        else{
            wdPtr = wdPtr->next;
        }//end else
        return inBucket;
    }//end while
}//end lookup function

int Hash::hashFunc(string key){//hash function definition

    int index = (int)key[0];//hash goes by the ASCII value of the first letter of the word

    index = index % tableSize;//index gets updated to the ASCII value of the first letter of the word and mods it by the table size
                              //ensures that any new word added can be hashed and added to the hash table if it has not been hashed

    return index;//allow to use this value in other places

}//end hash function

void Hash::addWord(string word){

    int index = hashFunc(word);//index variable of hashtable that hashes the word passed through

    if(HashTable[index]->word == "nil"){//conditional statement if the word in the index does not contain anything of the value of the hashed word

        HashTable[index]->word = word;//then store the word in to that index of the hashtable

    }//end if statement
    else{//if the index is not empty then else conditional

        wordItem* indexPtr = HashTable[index];//word item pointer that points to the hashtable
        wordItem* newWdPtr = new wordItem;//creates a new wordItem that has a pointer to it
        newWdPtr->word = word;//takes the added word and places the word in there
        newWdPtr->next = NULL;//places the pointer to null

        while(indexPtr->next != NULL){//traverse through the list and if the next pointer is not pointing to null

            indexPtr = indexPtr->next;//update the index pointer to next

        }//end while

        indexPtr->next = newWdPtr;//if it is null then the indexPtr which points to the hashtable index that points to the next word will point to the word

    }//end else

}//end add word function

//void Hash::testPrint(){

//    int numTestRun;
//    for(int i=0; i<tableSize; i++){

//        numTestRun = testRun(i);
        //cout << "index = " << i << endl;
//        cout << HashTable[i]->word << endl;
        //cout << "number of words = " << numTestRun << endl;
//    }//end for loop
//}//end test print

/*
--------------------------------- Simple Timer --------------------------------------------

- Vachik Dave
*/

#include <sys/time.h>
#include <cstddef>

/*struct timeval{
long    tv_sec;         // seconds
long    tv_usec;        // microseconds
};
*/
class TimeInterval{
public:
	timeval start_time;
	timeval end_time;
	public:
		TimeInterval();
		void start();
		void stop();
		float GetInterval();
};

TimeInterval::TimeInterval(){}

void TimeInterval::start()
{
	gettimeofday(&this->start_time, NULL);
}

void TimeInterval::stop()
{
	gettimeofday(&this->end_time, NULL);
}

float TimeInterval::GetInterval()
{
	float t =(float)(end_time.tv_sec-start_time.tv_sec)*1000000.0+(float)(end_time.tv_usec-start_time.tv_usec);	// in micro-sec

//	t = t / 1000000.0		// in sec

	return t;
}




int main(int argc, char *argv[]){


    string userFile;
    string word;
    string findWord;
    TimeInterval newTI;
    Hash newHash;


    char *inFile;
    if(argc<2 || argc == 1){
        cout << "Give input file name" << endl;

        inFile = argv[1];
        ifstream file;
        file.open(inFile);

        char ln[100];
        if(file.is_open()){

            int i = 1;
            while(!file.eof()){

                file >> ln;
                //if(strlen(ln)==0){
                //    break;
                //    cout << ln << "\n" << endl;
                //}
                if(i%3 == 0){
                getline(file, word);
                //cout << word << endl;

                newHash.addWord(word);
                }//end if
                ln[0] = '\0';
                i++;
            }//end while loop
        }//end if
        file.close();
        //inter.stop();
    }//end if
    else{
        cout << "Unable to open file" << endl;
        return 0;
    }

    //TimeInterval newTI;
    //Hash newHash;

    //ifstream fileName;
    //fileName.open("dictionary.txt");

    //while(!fileName.eof()){
    //    getline(fileName, word);
        //cout << word << endl;

    //    newHash.addWord(word);
    //}//end while loop

    cout << "Enter your word" << endl;
    cin >> findWord;

    newTI.start();

    int findWordIndex = newHash.hashFunc(findWord);

    newHash.lookup(findWordIndex, findWord);

    newTI.stop();
    cout << newTI.GetInterval() << " microseconds" << endl;
    //newHash.testPrint();

}//end main
