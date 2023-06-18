#include "Order.h"

#include <fstream>

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

void Order::setDriver(Driver* driver)
{
	this->driver = driver;
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
	case OrderStatus::created: std::cout << "Created" << std::endl; break;
	case OrderStatus::accepted: std::cout << "Accepted" << std::endl; break;
	case OrderStatus::canceled: std::cout << "Canceled" << std::endl; break;
	case OrderStatus::completed: std::cout << "Completed" << std::endl; break;
	}
	if (this->driver != nullptr)
	{
		//this->driver->print();
	}
}

const Address& Order::getDestinaton() const
{
	return destination;
}

const Address& Order::getOrigin() const
{
	return origin;
}

void Order::addDeclinedId(int id)
{
	declinedDriversIds.pushBack(id);
}

DynamicArray<int> Order::getDeclinedDriversIds() const
{
	return declinedDriversIds;
}

int Order::getMinutes() const
{
	return minutes;
}

void Order::saveToFile(std::ofstream& ofs) const
{
	if (client == nullptr || driver == nullptr)
	{
		throw std::runtime_error("Unknown order.");
	}


	ofs.write((const char*)&id, sizeof id);

	const int clientId = client->getId();
	ofs.write((const char*)&clientId, sizeof clientId);

	const size_t driverId = driver->getId();
	ofs.write((const char*)&driverId, sizeof driverId);

	origin.saveToFile(ofs);
	destination.saveToFile(ofs);

	ofs.write((const char*)&passengers, sizeof passengers);
	ofs.write((const char*)&orderStatus, sizeof orderStatus);

	const size_t declinedIdsCount = declinedDriversIds.getSize();
	ofs.write((const char*)&declinedIdsCount, sizeof declinedIdsCount);
	for (size_t i = 0; i < declinedIdsCount; i++)
	{
		ofs.write((const char*)&this->declinedDriversIds[i], sizeof this->declinedDriversIds[i]);
	}
}

void Order::readFromFile(DynamicArray<Client>* clientsPtr, DynamicArray<Driver>* driversPtr, std::ifstream& ifs)
{
	ifs.read((char*)&id, sizeof id);

	int clientId = 0;
	ifs.read((char*)&clientId, sizeof clientId);
	const int clientsCount = clientsPtr->getSize();
	for (int i = 0; i < clientsCount; i++)
	{
		if ((*clientsPtr)[i].getId() == clientId)
		{
			client = &clientsPtr->operator[](i);
		}
	}

	int driverId = 0;
	ifs.read((char*)&driverId, sizeof driverId);
	const int driversCount = driversPtr->getSize();
	for (int i = 0; i < driversCount; i++)
	{
		if ((*driversPtr)[i].getId() == driverId)
		{
			driver = &driversPtr->operator[](i);
		}
	}

	origin.readFromFile(ifs);
	destination.readFromFile(ifs);
	ifs.read((char*)&passengers, sizeof passengers);
	ifs.read((char*)&orderStatus, sizeof orderStatus);

	size_t declinedIdsCount = 0;
	ifs.read((char*)&declinedIdsCount, sizeof declinedIdsCount);
	for (size_t i = 0; i < declinedIdsCount; i++)
	{
		ifs.read((char*)&this->declinedDriversIds[i], sizeof this->declinedDriversIds[i]);
	}
}
