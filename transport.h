#ifndef TRANSPORT_H
#define TRANSPORT_H
#include <string>
#include <QTextStream>
#include <map>

enum type_of_engine {Diesel, Electric, Hybrid, Petrol};

extern std::map<type_of_engine, QString> engine_type_to_string;
extern std::map<QString, type_of_engine> string_to_engine_type;

class Transport { //abstract class
public:
    Transport();
    Transport(std::string brand, type_of_engine engine_type, int axles_count);
    Transport(const Transport &second);
    ~Transport() = default;
    virtual std::string get_brand() const = 0;
    virtual type_of_engine get_engine_type() const = 0;
    virtual int get_axles_count() const = 0;
protected:
    std::string m_brand;
    type_of_engine m_engine_type;
    int m_axles_count; //кількість осей
};

#endif // TRANSPORT_H
