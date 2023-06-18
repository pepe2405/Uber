#pragma once
#include "Address.h"
#include "Client.h"
#include "Driver.h"
#include "DynamicArray.hpp"

//Ot Yonko
enum class OrderStatus
{
	created,
	accepted,
	completed,
	canceled
};

class Order
{
	static int currId;

	int id = 0;
	Address origin;
	Address destination;

	Client* client = nullptr;
	Driver* driver = nullptr;
	OrderStatus orderStatus = OrderStatus::created;
	int passengers = 0;
	int minutes = 0;

	//Ot Yonko pak
	DynamicArray<int> declinedDriversIds;

public:
	Order() = default;
	Order(Client* client, Driver* driver, const Address& origin, const Address& destination, int passengers);
	Order(Client* client, Driver* driver, Address&& origin, Address&& destination, int passengers);

	void setMinutes(int mins);
	void setStatus(OrderStatus s);
	void setDriver(Driver* driver);

	int getId() const;
	OrderStatus getStatus() const;
	Client* getClient() const;
	Driver* getDriver() const;
	const Address& getDestinaton() const;
	const Address& getOrigin() const;
	DynamicArray<int> getDeclinedDriversIds() const;
	int getMinutes() const;

	void addDeclinedId(int id);

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(DynamicArray<Client>* clientsPtr, DynamicArray<Driver>* driversPtr, std::ifstream& ifs);
	void print() const;
};
