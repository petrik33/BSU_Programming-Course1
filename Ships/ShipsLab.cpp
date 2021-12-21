#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
using namespace std;

template <typename T>
string dequeRead(deque <T> q)
{
    string out;
    if (!q.empty())
    {
        int qSize = q.size();
        for (int i = 0; i < qSize; i++)
        {
            out += q[i];
            if (i != qSize - 1)
            {
                out += "\n";
            }
        }
        return out;
    }
    else
    {
        return "Queue is empty.";
    }
}

template <typename T>
int VecFindFirst(vector <T> vec, T value)
{
    for (int i = 0; i < vec.size();i++)
    {
        if (vec[i] == value)
        {
            return i;
        }
    }
    return -1;
}

string EventShipArrived(string in,vector <bool> &docksFree, vector <string> &docksInfo, deque <string> &raidQ) {
    string shipName = in.substr(2, in.size() - 2);
    int freeDockID = VecFindFirst(docksFree, true);
    if (freeDockID != -1)
    {
        docksInfo[freeDockID] = shipName;
        docksFree[freeDockID] = false;
        string out;
        out = "Ship " + shipName + " goes to the dock №" + to_string(freeDockID+1);
        return out;
    }
    else
    {
        raidQ.push_back(shipName);
        string out;
        out = "Ship " + shipName + " goes to the raid deque.";
        return out;
    }
}

string EventDockFreed(string in, vector <bool>& docksFree, vector <string>& docksInfo, deque <string>& raidQ) {
    int freedDockID = stoi(in.substr(2,in.size()-2));
    if (!raidQ.empty())
    {
        string shipName = raidQ.front();
        raidQ.pop_front();
        docksInfo[freedDockID-1] = shipName;
        string out;
        out = "Ship " + shipName + " from the raid deque goes to just freed dock №" + to_string(freedDockID);
        return out;
    }
    else
    {
        docksFree[freedDockID-1] = true;
        string out;
        out += "Dock №" + to_string(freedDockID) + " gets free. As the raid deque is empty noone takes it.";
        return out;
    }
}

string EventRaidOutput(string in, const deque <string>& raidQ) {
    string out;
    if (!raidQ.empty())
    {
        out += "Current raid deque is:\n" + dequeRead(raidQ);
        return out;
    }
    else
    {
        return "Raid deque is empty at the moment.";
    }
}

string EventDocksOutput(string in,const vector <bool>& docksFree, const vector <string>& docksInfo) {
    string out;
    out += "Current state of docks is:\n";
    for (int i = 0; i < docksInfo.size(); i++)
    {
        out += "Dock №" + to_string(i + 1) + " : ";
        if (docksFree[i])
        {
            out += "free";
        }
        else
        {
            out += docksInfo[i];
        }
        if(i != docksInfo.size() - 1) out += "\n";
    }
    return out;
}

int main()
{
    ifstream fin;
    fin.open("SHIPS.IN");
    ofstream fout;
    fout.open("SHIPS.OUT");

    if (!fin)
    {
        fout << "Trying to open a non-existing file. Check the integrity of your source files.\n";
    }
    else
    {
        string in;
        if (!getline(fin, in))
        {
            fout << "Source file is empty. Fill it with some data, please.\n";
        }
        else
        {
            int docksNumber = stoi(in);
            vector <bool> docksFree(docksNumber, 1);
            vector <string> docksInfo(docksNumber,"");
            deque <string> raidQ;

            while (getline(fin, in))
            {
                string out;
                switch (stoi(in.substr(0,1)))
                {
                    case 1://Ship Arrived
                        out = EventShipArrived(in, docksFree, docksInfo, raidQ);
                            break;
                    case 2://Dock Freed
                        out = EventDockFreed(in, docksFree, docksInfo, raidQ);
                        break;
                    case 3://Queue State Output
                        out = EventRaidOutput(in, raidQ);
                        break;
                    case 4://Docks State Output
                        out = EventDocksOutput(in, docksFree, docksInfo);
                        break;
                    default:
                        out = "Unknown event type.";
                        break;
                }
                fout << out << "\n";
            }
        }
    }
    fout.close();
}
