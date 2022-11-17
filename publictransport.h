#ifndef PUBLICTRANSPORT_H
#define PUBLICTRANSPORT_H
#include "transport.h"

class PublicTransport : public Transport {
public:
    PublicTransport();
    PublicTransport(std::string brand,
                    type_of_engine engine_type,
                    int axles_count,
                    int passengers_count,
                    int seats_count,
                    int doors_count,
                    int horsepower,
                    bool low_floor);
    PublicTransport(const PublicTransport &second);
    std::string get_brand() const override;
    type_of_engine get_engine_type() const override;
    int get_axles_count() const override;
    int get_passengers_count() const;
    int get_seats_count() const;
    int get_doors_count() const;
    int get_horsepower() const;
    bool has_low_floor() const;
    friend QTextStream& operator>>(QTextStream &in, PublicTransport &transport);
    friend QTextStream& operator<<(QTextStream &out, const PublicTransport &transport);
    PublicTransport& operator=(const PublicTransport &second);
private:
    int m_passengers_count;
    int m_seats_count;
    int m_doors_count;
    int m_horsepower; // 235 - 450
    bool m_low_floor;
};

QTextStream& operator>>(QTextStream &in, PublicTransport &transport);
QTextStream& operator<<(QTextStream &out, const PublicTransport &transport);

#endif // PUBLICTRANSPORT_H
