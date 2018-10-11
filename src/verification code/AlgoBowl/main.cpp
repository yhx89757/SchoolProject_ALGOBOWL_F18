//VERIFICATION FILE
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <algorithm>


using namespace std;

bool isValidInput = false;
string inputFile = "input_gourp1.txt";
string outputFile = "output_group1.txt";
int numJobs;
int numWorkStations;
vector<vector<int>> taskLengths;
vector<vector<int>> taskStarts;
int theirMax;

bool checkMax(){
    bool oneEquals = false;
    bool allLessThan = false;
    for(int i = 0; i < numWorkStations; i++){ //workstations 0, 1, 2
        int maxStartTime = 0;
        int maxStartLength = 0;
        for(int j = 0; j < numJobs; j++){
            if(taskStarts[j][i] > maxStartTime){
                maxStartTime = taskStarts[j][i];
                maxStartLength = taskLengths[j][i+1];
            }
        }
        if(maxStartTime+maxStartLength <= theirMax){
            allLessThan = true;
            if(maxStartTime+maxStartLength == theirMax){
                oneEquals = true;
            }
        }
    }
    if(allLessThan && oneEquals){
        return true;
    }
    return false;
}

bool checkJobOverlap(){
    for(int i = 0; i < numJobs; i++){
        vector<int> timeOverlaps(theirMax);
        for(int j = 0; j < numWorkStations; j++){
            for(int k = 0; k < taskLengths[i][j+1]; k++){
                timeOverlaps[taskStarts[i][j] + k]++;    
            }
        }
        for(int j = 0; j < timeOverlaps.size(); j++){
            if(timeOverlaps[j] > 1){
                cout << timeOverlaps[j] << endl;
                return false;
            }
        }
    }
    return true;
}

bool checkStartTimes(){
    for(int i = 0; i < numJobs; i++){
        for(int j = 0; j < numWorkStations; j++){
            if(taskStarts[i][j] < taskLengths[i][0]){
                return false;
            }
        }
    }
    return true;
}

bool checkWSOverlap() {
	for (int i = 0; i < numWorkStations; i++) {
		vector<int> timeLengths;
		for (int j = 0; j < numJobs; j++) {
			timeLengths.push_back(taskLengths[j][i + 1]);
		}
		vector<int> startTimes;
		vector<int> startTimesSort;
		for (int j = 0; j < numJobs; j++) {
			startTimes.push_back(taskStarts[j][i]);
			startTimesSort.push_back(taskStarts[j][i]);
		}
		sort(startTimesSort.begin(), startTimesSort.end());

		for (int j = 0; j < numJobs - 1; j++) {
			int job = distance(startTimes.begin(), find(startTimes.begin(), startTimes.end(), startTimesSort[j]));
			if (startTimesSort[j] + timeLengths[job] > startTimesSort[j + 1]) {
				return false;
			}
		}

	}
	return true;
}

void readFiles(){
    ifstream inFile;
    inFile.open(inputFile);
    if(!inFile){
        cerr << "Unable to open file " << inputFile;
        exit(1);
    }
    inFile >> numJobs;
    inFile >> numWorkStations;
    while(!inFile.eof()){
        vector<int> temp;
        int t;
        inFile >> t;
        temp.push_back(t);
        inFile >> t;
        temp.push_back(t);
        inFile >> t;
        temp.push_back(t);
        inFile >> t;
        temp.push_back(t);
        taskLengths.push_back(temp);
    }
    inFile.close();
    ifstream inFile2;
    inFile2.open(outputFile);
    if(!inFile2){
        cerr << "Unable to open file " << outputFile;
        exit(1);
    }
    inFile2 >> theirMax;
    while(!inFile2.eof()){
        vector<int> temp;
        int t;
        inFile2 >> t;
        temp.push_back(t);
        inFile2 >> t;
        temp.push_back(t);
        inFile2 >> t;
        temp.push_back(t);
        taskStarts.push_back(temp);
    }
    
}


int main(){
    readFiles();
    isValidInput = checkMax();
    if(isValidInput){
        isValidInput = checkJobOverlap();
        if(isValidInput){
            isValidInput = checkStartTimes();
            if (isValidInput) {
				isValidInput = checkWSOverlap();
			}
        }
    }
    cout << isValidInput << endl;
    
    return 0;
}