#include "transport.h"

std::map<type_of_engine, QString> engine_type_to_string = {
    {Diesel, "Diesel"},
    {Electric, "Electric"},
    {Hybrid, "Hybrid"},
    {Petrol, "Petrol"},
};

std::map<QString, type_of_engine> string_to_engine_type = {
    {"Diesel", Diesel},
    {"Electric", Electric},
    {"Hybrid", Hybrid},
    {"Petrol", Petrol},
};
Transport::Transport() :
    m_brand("Unknown"),
    m_engine_type(Petrol),
    m_axles_count(0) {}

Transport::Transport(std::string brand, type_of_engine engine_type, int axles_count) :
    m_brand(brand),
    m_engine_type(engine_type),
    m_axles_count(axles_count) {}

Transport::Transport(const Transport &second) :
    m_brand(second.m_brand),
    m_engine_type(second.m_engine_type),
    m_axles_count(second.m_axles_count) {}
