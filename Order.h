#pragma once
#include "Address.h"
#include "Client.h"
#include "Driver.h"
#include "DynamicArray.hpp"

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

	int id;
	Address origin;
	Address destination;

	Client client;
	Driver driver;
	int passengers = 0;
	OrderStatus orderStatus = OrderStatus::created;

	DynamicArray<Driver> declinedDrivers;

public:
	Order(Client* client, Driver* driver, const Address& origin, const Address& destination, int passengers);
	Order(Client* client, Driver* driver, Address&& origin, Address&& destination, int passengers);

	int getId() const;
	void setDriver();

	Order(const Order& other) = delete;
	Order& operator=(const Order& other) = delete;

	void print() const;
};
