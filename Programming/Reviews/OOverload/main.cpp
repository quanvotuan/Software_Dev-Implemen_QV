#include <iostream>
#include <string>
#include <list>

using namespace std;

struct YouTubeChannel{
    string Name;
    int SubscribersCount;

    YouTubeChannel(string name, int subscribersCount){ // Constructor
        Name = name;
        SubscribersCount = subscribersCount;
    }

    // I need to make the operator == to const
    // -> Swear to the compiler that I won't change the parameter
    bool operator == (const YouTubeChannel& channel) const{
        return this->Name==channel.Name;
    }
};

ostream& operator<<(ostream& COUT, YouTubeChannel& ytChannel){ // Global function
    COUT << "Name: " << ytChannel.Name << endl;
    COUT << "Subscribers: " << ytChannel.SubscribersCount << endl;
    return COUT;
}

// Ex with others operators
struct MyCollection {
    list<YouTubeChannel>myChannels;

    void operator+=(YouTubeChannel& channel){ // Local function
        this->myChannels.push_back(channel); // this == myCollection in main
    }

    void operator-=(YouTubeChannel& channel){ // Local function
        this->myChannels.remove(channel);
    }
};

ostream& operator<<(ostream& COUT, MyCollection& myCollection){
    for (YouTubeChannel ytChannel:myCollection.myChannels) { // For each YouTube channel inside my collection.myChannels
        COUT << ytChannel << endl;
    }
    return COUT;
}



int main()
{
    YouTubeChannel yt1 = YouTubeChannel("CodeBeauty", 75000);
    YouTubeChannel yt2 = YouTubeChannel("My 2nd Channel", 80000);
    MyCollection myCollection;
    myCollection += yt1;
    myCollection += yt2;
    myCollection -= yt2; // Remove element from myCollection
    cout << myCollection;

    cin.get();

}

/*
 * Insertion operator: <<
 *
 *
 * // Why am I passed COUT and ytChannel as reference?
 * // -> because we want the original object, to save the cost of copying the data
 * Cheap to copy: #, int
 * Expensive to copy: string, array,
 *
 * 1st Ex:
    * cout << yt1;
    * void operator<<(ostream& COUT, YouTubeChannel& ytChannel){
    COUT << "Name: " << ytChannel.Name;
    COUT << "Subscribers: " << ytChannel.SubscribersCount;
}
 *
 * 2nd Ex:
    * cout << yt1 << yt2;
    * ostream& operator<<(ostream& COUT, YouTubeChannel& ytChannel){
    COUT << "Name: " << ytChannel.Name << endl;
    COUT << "Subscribers: " << ytChannel.SubscribersCount << endl;
    return COUT;
}

 cout << yt1 == operator<<(cout, yt1);

 * 3rd Ex: MyCollection
 *      Why does MyCollection required only one parameter compare to ostream& operator <<?
 *          -> because MyCollection is local -> it already have the parameter on the left side by default
 */
