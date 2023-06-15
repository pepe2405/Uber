#include "Order.h"

int Order::currId = 1;

Order::Order(Client* client, Driver* driver, const Address& origin, const Address& destination, int passengers)
{
	this->client = client;
	this->driver = driver;
	this->origin = origin;
	this->destination = destination;
	this->passengers = passengers;
	id = currId;
	currId++;
}

Order::Order(Client* client, Driver* driver, Address&& origin, Address&& destination, int passengers)
{
	this->client = client;
	this->driver = driver;
	this->origin = std::move(origin);
	this->destination = std::move(destination);
	this->passengers = passengers;
	id = currId;
	currId++;
}

int Order::getId() const
{
	return id;
}

Client* Order::getClient() const
{
	return client;
}

Driver* Order::getDriver() const
{
	return driver;
}

OrderStatus Order::getStatus() const
{
	return orderStatus;
}

void Order::setDriver(UniquePointer<Driver>&& driver)
{
	this->driver = std::move(driver);
}

void Order::setMinutes(int mins)
{
	if (mins < 1)
	{
		mins = 0;
	}
	minutes = mins;
}

void Order::setStatus(OrderStatus s)
{
	orderStatus = s;
}

void Order::print() const
{
	std::cout << "Order status: ";
	switch (orderStatus)
	{
	case orderStatus == OrderStatus::created: std::cout << "Created" << std::endl; break;
	case orderStatus == OrderStatus::accepted: std::cout << "Accepted" << std::endl; break;
	case orderStatus == OrderStatus::canceled: std::cout << "Canceled" << std::endl; break;
	case orderStatus == OrderStatus::completed: std::cout << "Completed" << std::endl; break;
	default: break;
	}
	if (this->driver.operator->() != nullptr)
	{
		this->driver->print();
	}
}

const Address& Order::getDestinaton() const
{
	return destination;
}






