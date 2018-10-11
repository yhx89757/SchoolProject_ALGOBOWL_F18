// Author: Haoxuan Yang
// Project: AlgoBowl Project
//*******************format*******************
// n = [0,1000], m = 3, available time = [0,50], task time = [1,50]
//****************Some thoughts***************
// if we use map to store the jobs it will be better, because it
// is sorted by key in ascending order.(key is length, value is job index) So 
// the time for looking for a max length is O(1)? Actually vector can be sorted by
// using a sort function which will also save time.

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>  // For srand() and rand()
#include <ctime>
#include <iomanip>
#include <stdio.h>
#include <ctime>

using namespace std;


class Solution{
    public:
        void algobowl(const int n, const int m, int arr[][4]){
            // output array
            int out[n][m*2];
            int best_out[n][m*2]; // (simulated annealing)
            // initialization
            for(int i = 0; i < n; i++){
                for(int j = 0; j < 2*m; j++){
                    out[i][j] = 0;
                    best_out[i][j] = 0;
                }
            }
            // int (*out)[3] = new int[n][3];
            // output the total completion time 
            static int total = 0; 
            static int best_total = 0; // (simulated annealing)
            //super outer loop for simulated annealing!
            for(int super = 0; super < 1; super++){ // you can adjust loop time
                // reset
                total = 0;
                // reset
                for(int i = 0; i < n; i++){
                    for(int j = 0; j < 2*m; j++){
                        out[i][j] = 0;
                    }
                }
                // loop between 3 workstations
                for(int ws = 0; ws < m; ws++){ // from 0 to 2 !!!
                    // to keep track on the current time
                    int cur_t = 0;
                    // to store how many jobs we have to do, remove 1 job each time
                    vector<int> jobs;
                    // push the job index into it
                    for(int i = 0; i < n; i++){
                        jobs.push_back(i);
                    }
                    // to figure out the biggest available job n fill it in the ws
                    while(jobs.size() >= 1){
                        // to store the decision of which job we should do at this time (default=-1)
                        int cur_j = -1;
                        // we create it for storing the biggest length
                        int cur_len = 0;
                        // a flag to record if we already found an available job (simulated annealing)
                        int found = 0;
                        // going through rest of the jobs
                        for(int j = 0; j < jobs.size(); j++){
                            // if we already have one job acceptable, there is a chance to exit the loop (simulated annealing)
                            srand((unsigned)time(0));
                            int dice = rand() % 100;
                            if(dice > 80 && found == 1){
                                found = 0; //reset
                                // cout << "123" << endl;
                                break;
                            }
                            // we create it temporarily for going through each job
                            int temp_j = jobs[j];
                            // just to set a flag for the overlap between workstations (auto reset)
                            int flag = 0;
                            if(arr[temp_j][0] <= cur_t){ // available time <= current time
                                // if there is any overlap between workstations then pass this job
                                for(int p = 0; p <= ws; p++){ 
                                    if(!((cur_t + arr[temp_j][ws+1] <= out[temp_j][2*p]) ||
                                    (cur_t >= out[temp_j][2*p+1]))){ 
                                        flag = -1; // we have overlap
                                        break;
                                    }
                                }
                                if(arr[temp_j][ws+1] > cur_len && flag != -1){ // store the biggest len
                                    found = 1;
                                    cur_len = arr[temp_j][ws+1];
                                    cur_j = temp_j;
                                }
                            }
                        }
                        // check if all the jobs are not available at this time
                        if(cur_j == -1){
                            cur_t++;
                        }else{ // if we find a job to do
                            // remove it from vector
                            vector<int>::iterator iter=find(jobs.begin(),jobs.end(),cur_j); // find that index
                            if(iter!=jobs.end()) jobs.erase(iter); // delete content of that index
                            // write it into the output table
                            out[cur_j][2*ws] = cur_t;
                            // compute the ending time and store it in cur_t n output table
                            cur_t += arr[cur_j][ws+1];
                            out[cur_j][2*ws+1] = cur_t;
                        }
                    }
                    if(total < cur_t) total = cur_t;
                }
                if(super == 0){
                    best_total = total;
                    for(int i = 0; i < n; i++){
                        for(int j = 0; j < m*2; j++){
                            best_out[i][j] = out[i][j];
                        }
                    }
                }
                // compare total and best_total
                if(total > best_total){
                    best_total = total;
                    for(int i = 0; i < n; i++){
                        for(int j = 0; j < m*2; j++){
                            best_out[i][j] = out[i][j];
                        }
                    }
                }
            }
            // print the output
            // cout << "This is the output: " << endl;
            cout << best_total << endl;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m*2; j += 2){
                    cout << best_out[i][j];
                    if(j < m*2-2){
                        cout << " ";
                    }
                }
                cout << endl;
            }
        }
};
int main()
{
    int n = 0, m = 0;
    cin >> n >> m;
    if(n == 0){
        // cout << "No job detected!" << endl;
        cout << 0 << endl;
    }
    int arr[n][4];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m+1; j++)
        cin >> arr[i][j];
    }
    Solution b;
    b.algobowl(n,m,arr);
}




