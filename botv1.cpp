#include <iostream>
#include <vector>
using namespace std;

#define minBet 10
#define WIN 1
#define LOSE 0
#define GREEN 3
#define BLACK 1
#define RED 2
#define ERROR -1
#define INSUFFICIENT_BALANCE -2
#define DONTCARE -3
#define TREND_THRESHOLD 1
#define DEBUG false

vector<int> DATA = {1, 1};
vector<int> newData = {1, 2, 3, 1, 2, 3, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2};
int ptr = 0;
int profit = 0;
int initialBalance = 640;
int targetProfit = 200;
int Balance = initialBalance;
int winCount = 0;
int lossCount = 0;


int trend(vector<int> &data) {
    int n = data.size();
    int trendSize = 1;
    int last = data[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        if (data[i] == last) {
            trendSize++;
        } else {
            break;
        }
    }
    return trendSize;
}

int lastColour(vector<int> &data) {
    int n = data.size();
    if (data[n - 1] == GREEN) {
        return GREEN;
    } else if (data[n - 1] == BLACK) {
        return BLACK;
    } else if (data[n - 1] == RED) {
        return RED;
    } else {
        cout << "Error: Invalid colour\n";
        return ERROR;
    }
}

int betColor(int col) {
    if (col == BLACK) {
        return RED;
    } else if (col == RED) {
        return BLACK;
    } else {
        cout << "Error: Invalid colour code passed in betColor func\n";
        return ERROR;
    }
}


int gameSimulator(int betCol, int betAmt, bool betMade = true) {
    if(DEBUG && betMade) cout << "Bet amount: " << betAmt << " Bet color: " << betCol << endl;
    if (ptr == newData.size()) {
        cout << "Error: End of data\n";
        return ERROR;
    }
    DATA.push_back(newData[ptr]);
    if (Balance < betAmt) {
        cout << "Error: Insufficient balance\n";
        return INSUFFICIENT_BALANCE;
    }
    if (!betMade) {
        ptr++;
        return DONTCARE;
    }
    if(DEBUG){
        cout<<"Ball landed on : ";
        if(newData[ptr] == GREEN) cout<<"GREEN\n";
        else if(newData[ptr] == BLACK) cout<<"BLACK\n";
        else cout<<"RED\n";
    }
    if (newData[ptr] == GREEN) {
        Balance -= betAmt;
        ptr++;
        lossCount++;
        cout << "Lost " << betAmt <<"\nCurrent balance : "<<Balance<<endl<<endl;
        return GREEN;
    }
    if (newData[ptr] == betCol) {
        Balance += betAmt;
        ptr++;
        winCount++;
        cout << "Won " << betAmt <<"\nCurrent balance : " <<Balance<<endl<<endl;
        return WIN;
    } else {
        Balance -= betAmt;
        ptr++;
        lossCount++;
        cout << "Lost " << betAmt <<"\nCurrent balance : "<<Balance<<endl<<endl;
        return LOSE;
    }
}


bool hasTrend(vector<int> &data) {
    return trend(data) > TREND_THRESHOLD && lastColour(data) != GREEN;
}


int stateMachine() {
    int currState = 0;
    int t = 0, betAmt = 0, betCol = 0;
    int result = 0; 

    while (currState != 4) {
        if (DEBUG){
            cout << "Current state: " << currState << endl;
            cout << "Current balance: " << Balance << endl;
            cout << "Last trend size: " << t << endl<<endl;
        }

        // Check if Balance is negative or insufficient to continue betting
        if (Balance - betAmt <= 0) {
            cout << "Error: Balance depleted. Cannot continue betting.\n";
            break; // Exit the loop
        }
        
        if (ptr == newData.size()) {
            cout << "End of data reached\n";
            break; // Exit the loop
        }

        

        switch (currState) {
            case 0: 
                if(DEBUG) cout << "Waiting for a trend. Current ptr : "<< ptr << endl;
                if (hasTrend(DATA)) {
                    if(DEBUG) cout << "Trend found\n";
                    currState = 1;
                } else {
                    gameSimulator(betCol, betAmt, false);
                    
                }
                break;

            case 1: 
                betAmt = minBet;
                betCol = betColor(lastColour(DATA));
                t = trend(DATA);
                result = gameSimulator(betCol, betAmt);
                if (result == WIN && Balance - initialBalance >= targetProfit) {
                    currState = 4;
                } else {
                    currState = (result == WIN ? 0 : (result == GREEN ? 2 : 3));
                }
                break;

            case 2: 
                if(DEBUG) cout << "Waiting for a trend. Current ptr : "<< ptr << endl;
                if (trend(DATA) >= t && lastColour(DATA) != GREEN) {
                    currState = 3;
                }
                else {
                    gameSimulator(betCol, betAmt, false);
                    
                }
                break;

            case 3: 
                betAmt *= 2;
                betCol = betColor(lastColour(DATA));
                t = trend(DATA);
                result = gameSimulator(betCol, betAmt);
                
                if (result == WIN && Balance - initialBalance >= targetProfit) {
                    currState = 4;
                } else {
                    currState = (result == WIN ? 0 : (result == GREEN ? 2 : 3));
                }
                break;

            case 4: 
                cout << "Target profit reached\n";
                cout << "Final balance: " << Balance << endl;
                cout << "Win count: " << winCount << endl;
                cout << "Loss count: " << lossCount << endl;
                return 0;

            default:
                cout << "Error: Invalid state\n";
                return ERROR;
        }
    }

    
    cout << "State machine terminated.\n";
    cout << "Final balance: " << Balance << endl;
    cout << "Win count: " << winCount << endl;
    cout << "Loss count: " << lossCount << endl;
    return 0;
}

int main() {
    stateMachine();
    return 0;
}

