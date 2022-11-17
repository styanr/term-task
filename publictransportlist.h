#ifndef PUBLICTRANSPORTLIST_H
#define PUBLICTRANSPORTLIST_H
#include "publictransport.h"
#include "customexception.h"
#include <vector>

class PublicTransportList
{
public:
    PublicTransportList() = default;
    template<typename T>
    void sort(T comparator);
    void clear();
    void append(const PublicTransport &new_transport);
    int size() const;
    double average_horsepower() const;
    std::size_t most_powerful_electric() const;
    std::vector<std::size_t> more_powerful_than_avg_more_than_4_axles() const;
    std::vector<std::size_t> more_than_4_doors_has_low_floor_more_than_40_standing_passengers() const;
    PublicTransport& operator[](std::size_t idx);
    const PublicTransport& operator[](std::size_t idx) const;
    friend QTextStream& operator>>(QTextStream &in, PublicTransportList &list);
    friend QTextStream& operator<<(QTextStream &out, const PublicTransportList &list);
private:
    std::vector<PublicTransport> list;
};

QTextStream& operator>>(QTextStream &in, PublicTransportList &list);
QTextStream& operator<<(QTextStream &out, const PublicTransportList &list);

template<typename T>
void PublicTransportList::sort(T comparator) { //shell sort
    /* Sorts the list using
     * Shell sort algorithm.
     * Takes a lambda expression as argument
     * The lambda expression takes
     * two arguments of type PublicTransport
     * and returns a bool value, using which
     * the list will be sorted
     */
    if(!list.size())
        throw CustomException("The list is empty! Please fill in the list.");
    for(int gap = list.size() / 2; gap > 0; gap /=2) {
        for(int i = gap; i < list.size(); i++) {
            PublicTransport temp = list[i];
            int j = 0;
            for(j = i; j >= gap && comparator(temp, list[j - gap]); j -= gap)
                list[j] = list[j - gap];
            list[j] = temp;
        }
    }
}


#endif // PUBLICTRANSPORTLIST_H
