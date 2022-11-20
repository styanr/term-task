#include "publictransportlist.h"
#include "qdebug.h"
#include <algorithm>
#include <exception>

void PublicTransportList::clear() {
    list.clear();
}

void PublicTransportList::append(const PublicTransport &new_transport) {
    /* appends an item to the end of the list*/
    list.push_back(new_transport);
}

int PublicTransportList::size() const {
    return list.size();
}

double PublicTransportList::average_horsepower() const {
    /* returns average horsepower in the list */
    double sum = 0;
    for (const PublicTransport &transport : list)
        sum += transport.get_horsepower();
    return sum / list.size();
}

std::size_t PublicTransportList::most_powerful_electric() const {
    /* returns the most powerful electric transport
     * with seats count being between 20 and 26
     * Throws an exception if list is empty.
     */
    if(!list.size())
        throw CustomException("The list is empty! Please fill in the list.");
    int max_idx = 0;
    while(max_idx < list.size())
        if(!(list[max_idx].get_engine_type() == Electric && list[max_idx].get_seats_count() > 20
                && list[max_idx].get_seats_count() < 26)) {
            max_idx++;
        }
        else break;
    if(max_idx == list.size())
        throw CustomException("There are no elements that fit the criteria! Please try again with another list.");
    for(int i = 0; i < list.size(); i++) {
        int seats_count = list[i].get_seats_count();
        if(list[i].get_engine_type() == Electric && seats_count > 20 && seats_count < 26
                && list[i].get_horsepower() > list[max_idx].get_horsepower()) {
            max_idx = i;
        }
    }
    return max_idx;
}

std::vector<std::size_t> PublicTransportList::more_powerful_than_avg_more_than_4_axles() const {
    /* returns a vector of indices of items
     * that are more powerful than average
     * and have more than 4 axles.
     * Throws an exception if list is empty.
     */
    if(!list.size())
        throw CustomException("The list is empty! Please fill in the list.");
    std::vector<std::size_t> indices;
    double average = average_horsepower();
    for(std::size_t i = 0; i < list.size(); i++)
        if(list[i].get_axles_count() > 4 && list[i].get_horsepower() > average)
            indices.push_back(i);
    return indices;
}

std::vector<std::size_t> PublicTransportList::more_than_4_doors_has_low_floor_more_than_40_standing_passengers() const {
    /* returns a list of indices of items
     * than have more than 4 doors,
     * have low floor and
     * have more than 40 standing passengers
     * Throws an exception if list is empty.
     */
    if(!list.size())
        throw CustomException("The list is empty! Please fill in the list.");
    std::vector<std::size_t> indices;
    for(std::size_t i = 0; i < list.size(); i++)
        if(list[i].get_doors_count() > 4 && list[i].has_low_floor()
                && (list[i].get_passengers_count() - list[i].get_seats_count()) > 40)
            indices.push_back(i);
   return indices;
}


PublicTransport& PublicTransportList::operator[](std::size_t idx) {
    return list[idx];
}

const PublicTransport& PublicTransportList::operator[](std::size_t idx) const {
    /* const getter in case a list is const*/
    return list[idx];
}

QTextStream& operator>>(QTextStream &in, PublicTransportList& transport_list) {
    /* reads a file and creates a list.
     * throws an exception if file is formatted incorrectly
     */
    while(!in.atEnd()) {
        PublicTransport new_transport;
        in >> new_transport;
        if(new_transport.get_brand() != "Unknown")
            transport_list.list.push_back(new_transport);
    }
    if(!transport_list.size())
        throw CustomException("The file that you have chosen is formatted incorrectly. Please choose another file.");
    return in;
}

QTextStream& operator<<(QTextStream &out, const PublicTransportList& transport_list) {
    for (const auto &x : transport_list.list)
        out << x;
    return out;
}
