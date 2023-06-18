#pragma once
#include "Client.h"
#include "Driver.h"
#include "DynamicArray.hpp"
#include "Order.h"
#include "User.h"

enum class LoggedUserType
{
	driver,
	client,
	none
};

class Application
{
	User* logged = nullptr;
	LoggedUserType type = LoggedUserType::none;

	DynamicArray<Client> clients;
	DynamicArray<Driver> drivers;
	DynamicArray<Order> orders;

	Application() = default;
	Application(const Application& other) = delete;
	Application& operator=(const Application& other) = delete;

	void save() const;
	void load();

public:
	static Application& getInstance();

	const DynamicArray<Client>& getClients() const;
	const DynamicArray<Driver>& getDrivers() const;
	const DynamicArray<Order>& getOrders() const;

	void registerClient(Client&& client);
	void registerDriver(Driver&& driver);

	void login(const MyString& username, const MyString& password);
	void login(MyString&& username, MyString&& password);
	void logout();

	const User* getLoggedUser() const;
	User* getLoggedUser();
	LoggedUserType getType() const;

	void addClient(const Client& client);
	void addClient(Client&& client);
	void addDriver(const Driver& driver);
	void addDriver(Driver&& driver);
	void addOrder(Order&& order);

	void cancelOrder(int orderId);
	void pay(int orderId, double amount);
	void rateDriver(const MyString& username, double rating);

	void acceptOrder(int id);
	void declineOrder(int id);
	void finishOrder(int id);
	void setMinutes(int id, int minutes);
	void checkMessages() const;

	Driver* getClosestDriver(int x, int y);
	Driver* getClosestDriver(const Order& order, int x, int y);

	double getDist(int x1, int y1, int x2, int y2) const;

	void exitApp() const;
};

