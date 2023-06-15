#pragma once
#include "Address.h"
#include "Client.h"
#include "Driver.h"
#include "DynamicArray.hpp"
#include "UniquePointer.hpp"

// ideqta za enum class orderStatus e vzeta ot yonko
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

	Client* client;
	Driver* driver;
	OrderStatus orderStatus = OrderStatus::created;
	int passengers = 0;
	int minutes = 0;

	DynamicArray<Driver> clossestDrivers;

public:
	Order(Client* client, Driver* driver, const Address& origin, const Address& destination, int passengers);
	Order(Client* client, Driver* driver, Address&& origin, Address&& destination, int passengers);

	void setMinutes(int mins);
	void setStatus(OrderStatus s);
	void setDriver(UniquePointer<Driver>&& driver);

	int getId() const;
	OrderStatus getStatus() const;
	Client* getClient() const;
	Driver* getDriver() const;
	const Address& getDestinaton() const;

	Order(const Order& other) = delete;
	Order& operator=(const Order& other) = delete;

	void print() const;
};
