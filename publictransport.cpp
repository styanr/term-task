#include "publictransport.h"
#include <QTextStream>
#include <QStringList>

PublicTransport::PublicTransport() : Transport::Transport(),
    m_passengers_count(0),
    m_seats_count(0),
    m_doors_count(0),
    m_horsepower(0),
    m_low_floor(false) {}

PublicTransport::PublicTransport(std::string brand,
                type_of_engine engine_type,
                int axles_count,
                int passengers_count,
                int seats_count,
                int doors_count,
                int horsepower,
                bool low_floor) :
    Transport::Transport(brand, engine_type, axles_count),
    m_passengers_count(passengers_count),
    m_seats_count(seats_count),
    m_doors_count(doors_count),
    m_horsepower(horsepower),
    m_low_floor(low_floor){}

PublicTransport::PublicTransport(const PublicTransport &second) :
    Transport::Transport(second),
    m_passengers_count(second.m_passengers_count),
    m_seats_count(second.m_seats_count),
    m_doors_count(second.m_doors_count),
    m_horsepower(second.m_horsepower),
    m_low_floor(second.m_low_floor){}

std::string PublicTransport::get_brand() const {
    return m_brand;
}
type_of_engine PublicTransport::get_engine_type() const {
    return m_engine_type;
}
int PublicTransport::get_axles_count() const {
    return m_axles_count;
}
int PublicTransport::get_passengers_count() const {
    return m_passengers_count;
}
int PublicTransport::get_seats_count() const {
    return m_seats_count;
}
int PublicTransport::get_doors_count() const {
    return m_doors_count;
}
int PublicTransport::get_horsepower() const {
    return m_horsepower;
}
bool PublicTransport::has_low_floor() const {
    return m_low_floor;
}

QTextStream& operator>>(QTextStream &in, PublicTransport &transport) {
    if (!in.atEnd()) {
        QString line = in.readLine();
        QStringList args = line.split(",");
        if(args.size() == 8) {
            transport.m_brand = args[0].toLatin1();
            transport.m_engine_type = static_cast<type_of_engine>(args[1].toInt());
            transport.m_axles_count = args[2].toInt();
            transport.m_passengers_count = args[3].toInt();
            transport.m_seats_count = args[4].toInt();
            transport.m_doors_count = args[5].toInt();
            transport.m_horsepower = args[6].toInt();
            transport.m_low_floor = args[7].toInt();
        }
    }
    return in;
}
QTextStream& operator<<(QTextStream &out, const PublicTransport &transport) {
    QStringList args = {QString::fromStdString(transport.m_brand),
                        QString::number(transport.m_engine_type),
                        QString::number(transport.m_axles_count),
                        QString::number(transport.m_passengers_count),
                        QString::number(transport.m_seats_count),
                        QString::number(transport.m_doors_count),
                        QString::number(transport.m_horsepower),
                        QString::number(transport.m_low_floor)};
    out << args.join(",") << "\n";
    return out;
}

PublicTransport& PublicTransport::operator=(const PublicTransport &second) {
    m_brand = second.get_brand();
    m_engine_type = second.get_engine_type();
    m_axles_count = second.get_axles_count();
    m_passengers_count = second.get_passengers_count();
    m_seats_count = second.get_seats_count();
    m_doors_count = second.get_doors_count();
    m_horsepower = second.get_horsepower();
    m_low_floor = second.has_low_floor();
    return *this;
}
