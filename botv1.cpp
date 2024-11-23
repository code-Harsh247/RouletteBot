#include "botv1.h"
using namespace std;

int trend(vector<int> &data)
{
    int n = data.size();
    int trendSize = 1;
    int last = data[n - 1];
    for(int i = n - 2; i >= 0; i--)
    {
        if (data[i] == last)
        {
            trendSize++;
        }
        else
        {
            break;
        }
    }
    return trendSize;
}

int lastColour(vector<int> &data)
{
    int n = data.size();
    if (data[n - 1] == 0)
    {
        return GREEN;
    }
    else if (data[n - 1] == 1)
    {
        return BLACK;
    }
    else
    {
        return RED;
    }
}

int main()
{
    vector<int> data = {1, 1, 1, 0, 0, 0, 1, 0, 0};
    
    int trendSize = trend(data);
    cout << "Trend size: " << trendSize << endl;
    
    int colour = lastColour(data);
    cout << "Last colour: " << (colour == GREEN ? "Green" : (colour == BLACK ? "Black" : "Red")) << endl;
    
    return 0;
}