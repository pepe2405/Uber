#include "Application.h"

Application& Application::getInstance()
{
	static Application app;
	return app;
}

const DynamicArray<Client>& Application::getClients() const
{
	return this->clients;
}

const DynamicArray<Driver>& Application::getDrivers() const
{
	return this->drivers;
}

const DynamicArray<Order>& Application::getOrders() const
{
	return this->orders;
}

void Application::registerClient(Client&& client)
{
	const int clientsCount = clients.getSize();

	for (int i = 0; i < clientsCount; i++)
	{
		if (clients[i].getUsername() == client.getUsername())
			throw std::runtime_error("User already exist.");
	}

	const int driversCount = drivers.getSize();

	for (int i = 0; i < driversCount; i++)
	{
		if (drivers[i].getUsername() == client.getUsername())
			throw std::runtime_error("User already exist.");
	}
	clients.pushBack(std::move(client));
}

void Application::registerDriver(Driver&& driver)
{
	const int clientsCount = clients.getSize();

	for (int i = 0; i < clientsCount; i++)
	{
		if (clients[i].getUsername() == driver.getUsername())
			throw std::runtime_error("User already exist.");
	}

	const int driversCount = drivers.getSize();

	for (int i = 0; i < driversCount; i++)
	{
		if (drivers[i].getUsername() == driver.getUsername())
			throw std::runtime_error("User already exist.");
	}
	drivers.pushBack(std::move(driver));
}

void Application::login(const MyString& username, const MyString& password)
{
	const int clientCount = clients.getSize();
	const int driverCount = drivers.getSize();
	if (driverCount == 0 && clientCount == 0)
		throw std::runtime_error("No users in the system!");


	for (int i = 0; i < clientCount; i++)
	{
		if (clients[i].getUsername() == username)
		{
			if (clients[i].isValidPassword(password))
			{
				logged = UniquePointer<User>{ &clients[i] };
				type = LoggedUserType::client;
				return;
			}
			throw std::runtime_error("Wrong password");
		}
	}

	for (int i = 0; i < driverCount; i++)
	{
		if (drivers[i].getUsername() == username)
		{
			if (drivers[i].isValidPassword(password))
			{
				logged = UniquePointer<User>{ &drivers[i] };
				type = LoggedUserType::driver;
				return;
			}
			throw std::runtime_error("Wrong password");
		}
	}
	throw std::runtime_error("No such username in the system.");
}

void Application::login(MyString&& username, MyString&& password)
{
	const int clientCount = clients.getSize();
	const int driverCount = drivers.getSize();
	if (driverCount == 0 && clientCount == 0)
		throw std::runtime_error("No users in the system!");


	for (int i = 0; i < clientCount; i++)
	{
		if (clients[i].getUsername() == username)
		{
			if (clients[i].isValidPassword(password))
			{
				logged = UniquePointer<User>{ &clients[i] };
				type = LoggedUserType::client;
				return;
			}
			throw std::runtime_error("Wrong password");
		}
	}

	for (int i = 0; i < driverCount; i++)
	{
		if (drivers[i].getUsername() == username)
		{
			if (drivers[i].isValidPassword(password))
			{
				logged = UniquePointer<User>{ &drivers[i] };
				type = LoggedUserType::driver;
				return;
			}
			throw std::runtime_error("Wrong password");
		}
	}
	throw std::runtime_error("No such username in the system.");
}

void Application::logout()
{
	logged = nullptr;
	type = LoggedUserType::none;
}

UniquePointer<User>& Application::getLoggedUser()
{
	return logged;
}

const UniquePointer<User>& Application::getLoggedUser() const
{
	return logged;
}

LoggedUserType Application::getType() const
{
	return type;
}

void Application::addClient(const Client& client)
{
	clients.pushBack(client);
}

void Application::addClient(Client&& client)
{
	clients.pushBack(std::move(client));
}

void Application::addDriver(const Driver& driver)
{
	drivers.pushBack(driver);
}

void Application::addDriver(Driver&& driver)
{
	drivers.pushBack(std::move(driver));
}

void Application::addOrder(Order&& order)
{
	orders.pushBack(std::move(order));
}

void Application::cancelOrder(int orderId)
{
	const int count = orders.getSize();

	for (int i = 0; i < count; i++)
	{
		if (orders[i].getId() == orderId)
		{
			orders[i].setStatus(OrderStatus::canceled);
			return;
		}
	}
	throw std::runtime_error("No such order in the system.");

}

void Application::pay(int orderId, double amount)
{
	const int count = orders.getSize();
	for (int i = 0; i < count; i++)
	{
		if (orders[i].getId() == orderId && orders[i].getStatus() == OrderStatus::completed)
		{
			Client* client = orders[i].getClient();
			Driver* driver = orders[i].getDriver();
			if (client->getBalance() < amount)
				throw std::logic_error("Not enough money.");
			client->addMoney(-amount);
			driver->addMoney(amount);
		}
	}
	throw std::runtime_error("No such order in the system.");
}

void Application::rateDriver(const MyString& username, double rating)
{
	const int count = orders.getSize();
	for (int i = 0; i < count; i++)
	{
		if (orders[i].getDriver()->getUsername() == username)
		{
			if (orders[i].getClient() == getLoggedUser().operator->() && orders[i].getStatus() == OrderStatus::completed)
			{
				orders[i].getDriver()->rate(rating);
				return;
			}
		}
	}
	throw std::runtime_error("Couldn't rate the draver!");
}

void Application::acceptOrder(int id)
{
	const int count = orders.getSize();
	for (int i = 0; i < count; i++)
	{
		if (orders[i].getId() == id)
		{
			if (orders[i].getDriver() != logged.operator->())
				throw std::runtime_error("Not your order!");
			if (orders[i].getStatus() != OrderStatus::created)
				throw std::runtime_error("The order is unavailable.");
			orders[i].setStatus(OrderStatus::accepted);
			orders[i].getDriver()->setFreedom(false);
		}
	}
	throw  std::runtime_error("No such order in the system!");
}

void Application::declineOrder(int id)
{
	//TODO:
}

void Application::finishOrder(int id)
{
	const int count = orders.getSize();
	for (int i = 0; i < count; i++)
	{
		if (orders[i].getId() == id)
		{
			if (orders[i].getDriver() != logged.operator->())
				throw std::runtime_error("Not your order.");
			if (orders[i].getStatus() != OrderStatus::accepted)
				throw std::runtime_error("You cant finish this order!");
			orders[i].setStatus(OrderStatus::completed);
			orders[i].getDriver()->setAddress(orders[i].getDestinaton());
			orders[i].getDriver()->setFreedom(true);

			orders.removeAt(i);
			return;
		}
	}
	throw std::runtime_error("No such order in the system!");
}

void Application::setMinutes(int id, int minutes)
{
	const int count = orders.getSize();
	for (int i = 0; i < count; i++)
	{
		if (orders[i].getId() == id)
		{
			orders[i].setMinutes(minutes);
			return;
		}
	}
	throw std::runtime_error("No such order in the system");
}

double Application::getDist(int x1, int y1, int x2, int y2) const
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

Driver* Application::getClosestDriver(int x, int y)
{
	const int drcount = drivers.getSize();
	if (drcount == 0)
		throw std::runtime_error("No drivers available.");

	double minDist = 0;
	Driver* currMin = nullptr;

	const int ordCount = orders.getSize();
	for (int i = 0; i < ordCount; i++)
	{
		if (orders[i].getStatus() != OrderStatus::accepted)
		{
			const double dist = getDist(x, y, orders[i].getDriver()->getAddress().getX(), orders[i].getDriver()->getAddress().getY());
			if (dist < minDist)
			{
				minDist = dist;
				currMin = orders[i].getDriver();
			}
		}
	}

	return currMin;
}

