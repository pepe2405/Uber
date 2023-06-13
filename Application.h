#pragma once
#include "Client.h"
#include "Driver.h"
#include "DynamicArray.hpp"
#include "Order.h"
#include "UniquePointer.hpp"
#include "User.h"

enum class LoggedUserType
{
	driver,
	client,
	none
};

enum class clientActions
{
	order,
	check_order,
	cancel_order,
	pay,
	rate,
	add_money
};

enum class driverActions
{
	change_address,
	check_messages,
	accept_order,
	decline_order,
	finish_order,
	accept_payment
};

class Application
{
	UniquePointer<User> logged = nullptr;
	LoggedUserType type = LoggedUserType::none;

	DynamicArray<Client> clients;
	DynamicArray<Driver> drivers;
	DynamicArray<Order> orders;

	Application();
	Application(const Application& other) = delete;
	Application& operator=(const Application& other) = delete;

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

	const UniquePointer<User>& getLoggedUser() const;
	LoggedUserType getType() const;
	UniquePointer<User>& getLoggedUser();

	void addClient(const Client& client);
	void addClient(Client&& client);
	void addDriver(const Driver& driver);
	void addDriver(Driver&& driver);
	void addOrder(Order&& order);

	void cancelOrder(size_t orderId);
	void pay(size_t orderId, double amount);

	Driver* getClosestDriver(int x, int y);
};

