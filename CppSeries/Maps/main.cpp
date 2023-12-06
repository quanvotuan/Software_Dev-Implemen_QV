#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <cstdint>

struct CityRecord
{
    std::string Name;
    uint64_t Population;
    double Latitude, Longitude;

    // Need to create a Constructor for emplace to work:

};

// How to create a hash func to hash the CityRecord data Type?

namespace std {

    template<>
    struct hash<CityRecord>
    {
        size_t operator()(const CityRecord& key)
        {
            return hash<std::string>()(key.Name); // Call the hash std C library to hash a string
        }
    };
}

int main() {

    // Example of using Vector instead of map
//    std::vector<CityRecord> cities;

//    cities.emplace_back("Melbourne", 5000000, 2.4, 9.4);
//    cities.emplace_back("Lol-town", 5000000, 2.4, 9.4);
//    cities.emplace_back("Berlin", 5000000, 2.4, 9.4);
//    cities.emplace_back("Paris", 5000000, 2.4, 9.4);
//    cities.emplace_back("London", 5000000, 2.4, 9.4);
//
//    for (const auto& city : cities)
//    { // Finding Berlin
//        if(city.Name == "Berlin")
//        {
//            city.Population; // Berlin
//            break;
//        }
//    }

    std::unordered_map<CityRecord, uint32_t> foundedMap;

    foundedMap[CityRecord { "Melbourne", 5000000, 2.4, 9.4}] = 1850;


    std::unordered_map<std::string, CityRecord> cityMap;
    cityMap ["Melbourne"] = CityRecord { "Melbourne", 5000000, 2.4, 9.4};
    cityMap ["Lol-town"] = CityRecord { "Lol-town", 5000000, 2.4, 9.4};
    cityMap ["Berlin"] = CityRecord { "Berlin", 5000000, 2.4, 9.4};
    cityMap ["Paris"] = CityRecord { "Paris", 5000000, 2.4, 9.4};
    cityMap ["London"] = CityRecord { "London", 5000000, 2.4, 9.4};

    // How to access my cityMap
    CityRecord& berlinData = cityMap["Berlin"];
    std::cout << berlinData.Population << std::endl;

}


// ----------------------------------------------------------- //
/* Note:
 * Order Map = Map
 *  Implementation: Self Balancing BST
 *      Black and White Binary tree
 *      The data are being sorted
 *
 * Unordered Map = Hash Table
 *  Implementation: Use Hash function to generated an index
 *  -> Use that index to stored the data
 */
