#include <cstdint>
#include <iostream>
#include <map>
#include <queue>
const std::int64_t DAY_SIZE = 86400;

struct Booking 
{
    std::int64_t time;
    int id;
    int room_counter;
};

class Info 
{
public:
    void Book(const Booking& booking) 
    {
        bookings_.push(booking);
        room_counter_ += booking.room_counter;
        ++clients_to_qanity[booking.id];
    }

    int ClientCount(const std::int64_t& current_time)
    {
        RemoveOldBookings(current_time);
        return clients_to_qanity.size();
    }

    int RoomCount(const std::int64_t& current_time)
    {
        RemoveOldBookings(current_time);
        return room_counter_;
    }

private:
    std::queue<Booking> bookings_;
    int room_counter_ = 0;
    std::map<int, int> clients_to_qanity;

    void RemoveOldBookings(const std::int64_t& current_time)
    {
        while (!bookings_.empty() && bookings_.front().time <= current_time - DAY_SIZE)
        {
            const Booking& booking = bookings_.front();

            room_counter_ -= booking.room_counter;

            const auto it = clients_to_qanity.find(booking.id);
            if (--it->second == 0)
            {
                clients_to_qanity.erase(it);
            }
            bookings_.pop();
        }
    }
};

class Manager 
{
public:
    void Book(const int64_t& time, const std::string& hotel_name, int client_id, int room_count) 
    {
        current_time_ = time;
        hotels_[hotel_name].Book({ time, client_id, room_count });
    }
    int ClientCount(const std::string& hotel_name) {
        return hotels_[hotel_name].ClientCount(current_time_);
    }
    int RoomCount(const std::string& hotel_name) {
        return hotels_[hotel_name].RoomCount(current_time_);
    }

private:
    int64_t current_time_ = 0;
    std::map<std::string, Info> hotels_;
};


int main() 
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Manager manager;

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        std::string type;
        std::cin >> type;

        if (type == "BOOK")
        {
            int64_t time;
            std::cin >> time;
            std::string hotel;
            std::cin >> hotel;
            int id, room_counter;
            std::cin >> id >> room_counter;
            manager.Book(time, hotel, id, room_counter);
        }
        else 
        {
            std::string hotel_name;
            std::cin >> hotel_name;
            if (type == "CLIENTS")
            {
                std::cout << manager.ClientCount(hotel_name) << '\n';
            }
            else if (type == "ROOMS")
            {
                std::cout << manager.RoomCount(hotel_name) << '\n';
            }
        }
    }

    return 0;
}
