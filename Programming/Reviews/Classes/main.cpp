#include <iostream>
#include <list>

using namespace std;

// Create a class, and 4 attributes (properties)
class YouTubeChannel{ // All member of my class are private by default
private: // Base Class
    string Name;
    int SubscriberCounter;
    list<string> PublishVideoTitles;

protected:; // Access modifier -> How to make certain attribute to be accessible, but still private?
    string OwnerName; // -> protected
    int ContentQuality;

public:
    YouTubeChannel(string name, string ownerName){ // This is the constructor
        Name = name;
        OwnerName = ownerName;
        SubscriberCounter = 0;
        ContentQuality = 0;
    }
    void GetInfo(){ // This is an ex of class method
        cout << "Name: " << Name << endl;
        cout << "OwnerName: " << OwnerName << endl;
        cout << "SubscribersCount: " << SubscriberCounter << endl;
        cout << "Video: " << endl;
        // Need to use a loop -> traverse though a list
        for (const string& videoTitle : PublishVideoTitles) { // for videoTitle (var) inside ytChannel.PublishVideoTitles
            cout << videoTitle << endl;
        }
        cout << "\n--------------"<< endl;

    }
    void Subscribe(){
        SubscriberCounter++;
    }
    void Unsubscribe(){
        if(SubscriberCounter > 0){
            SubscriberCounter--;
        }
    }
    void PublishVideo(string title){
        PublishVideoTitles.push_back(title);
    }
    void CheckAnalytics(){
        if(ContentQuality < 5){
            cout << Name << " has bad quality content." << endl;
        }
        else{
            cout << Name << " has great content." << endl;
        }
    }

    string GetName(){
        return Name;
    } // Creating a Getter and Setter to read or write the Name attribute
    void SetName(string name){
        this->Name = name;
    }
};

// Inheritance Class
class CookingYouTubeChannel:public YouTubeChannel { // Inheritance: Able to use and access all the stuff from YouTubeChannel
public:
    CookingYouTubeChannel(string name, string ownerName):YouTubeChannel(name, ownerName){ // ":" invoke

    }
    void Practice(){
        cout << OwnerName << " is practicing cooking, learning new recipes, experimenting w/ spices..." << endl;
        ContentQuality++;
    }
};

class SingersYouTubeChannel:public YouTubeChannel { // Inheritance: Able to use and access all the stuff from YouTubeChannel
public:
    SingersYouTubeChannel(string name, string ownerName):YouTubeChannel(name, ownerName){ // ":" invoke

    }
    void Practice(){
        cout << OwnerName << " is taking singing classes, learning new songs, learning how to dance..." << endl;
        ContentQuality++;
    }
};

int main()
{
    CookingYouTubeChannel cookingYtChannel("Amy's Kitchen", "Amy");
    SingersYouTubeChannel singerYtChannel("AnSing", "An");
;
    cookingYtChannel.Practice(); // This is a local method only for cookingYtChannel
    singerYtChannel.Practice();
    singerYtChannel.Practice();
    singerYtChannel.Practice();
    singerYtChannel.Practice();
    singerYtChannel.Practice();

    // How to use CheckAnalytics? -> Use Pointers
    YouTubeChannel* yt1 = &cookingYtChannel; // Create ptr yt1 -> point to address of cooking
    YouTubeChannel* yt2 = &singerYtChannel;

    yt1->CheckAnalytics(); // "->" are use for pointer
    yt2->CheckAnalytics();

    cin.get();
}

// Next: How to make this more efficient?
/* -> Use Constructor
 *
 * How?
 *  -> Remember the two rules
 *  1. Same name as my class
 *  2. Does not have return type
 *
 *
 *  What is class method?
 *      Describe the behavior (function) of a class
 *
 *  3. Encapsulation:
 *      What?
 *      -> The attribute suppose to be private instead of public
 *      In order to access these attribute, I'm need to write the method
 *      to get them myself
 *
 *  4. Inheritance
 *      Syntax: class CookingYouTubeChannel:public YouTubeChannel { // Inheritance: Able to use and access all the stuff from YouTubeChannel
 *      Benefit: Don't need to rewrite everything method from scratch
 *      How to use it?
 *          -> Just create a constructor -> Call it in Main and use it like the base class
 *
 * 5. Polymorphism:
 *      What?
 *      -> Different implementation, but the same method name being used
 *      -> How to use ptr to point to obj of derived class and store it in based class
 */