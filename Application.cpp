#include "Application.h"

#include <fstream>

void Application::save() const
{
	//Save session
	std::ofstream sof("session.dat", std::ios::out | std::ios::binary);
	if (!sof.is_open())
		throw std::runtime_error("Can't open the file!");
	
	int id = 0;
	if (logged == nullptr)
		id = -1;
	else
		id = logged->getId();
	sof.write((const char*)&id, sizeof id);
	sof.write((const char*)&type, sizeof type);
	sof.close();

	//Save clients
	std::ofstream cof("clients.dat", std::ios::out | std::ios::binary);
	if (!cof.is_open())
		throw std::runtime_error("Can't open the file!");
	const int clCount = clients.getSize();
	cof.write((const char*)&clCount, sizeof clCount);
	for (int i = 0; i < clCount; i++)
		clients[i].saveToFile(cof);
	cof.close();

	//Save drivers
	std::ofstream dof("drivers.dat", std::ios::out | std::ios::binary);
	if (!dof.is_open())
		throw std::runtime_error("Can't open the file!");
	const int drCount = drivers.getSize();
	dof.write((const char*)&drCount, sizeof drCount);
	for (int i = 0; i < drCount; i++)
		drivers[i].saveToFile(dof);
	dof.close();

	//Save orders
	std::ofstream oof("orders.dat", std::ios::out | std::ios::binary);
	if (!oof.is_open())
		throw std::runtime_error("Can't open the file!");
	const int ordCount = orders.getSize();
	oof.write((const char*)&ordCount, sizeof ordCount);
	for (int i = 0; i < ordCount; i++)
		orders[i].saveToFile(oof);
	oof.close();
}

void Application::load()
{
	//Load drivers
	std::ifstream dif("drivers.dat", std::ios::in | std::ios::binary);
	if (!dif.is_open())
		throw std::runtime_error("Can't open the file!");
	int drCount = 0;
	dif.read((char*)drCount, sizeof drCount);
	for (int i = 0; i < drCount; i++)
	{
		Driver dr;
		dr.readFromFile(dif);
		drivers.pushBack(std::move(dr));
	}
	dif.close();

	//Load clients
	std::ifstream cif("clients.dat", std::ios::in | std::ios::binary);
	if (!cif.is_open())
		throw std::runtime_error("Can't open the file!");
	int clCount = 0;
	cif.read((char*)&clCount, sizeof clCount);
	for (int i = 0; i < clCount; i++)
	{
		Client cl;
		cl.readFromFile(cif);
		clients.pushBack(std::move(cl));
	}
	cif.close();

	//Load Orders
	std::ifstream oif("orders.dat", std::ios::in | std::ios::binary);
	if (!oif.is_open())
		throw std::runtime_error("Can't open the file!");
	int ordCount = 0;
	oif.read((char*)&ordCount, sizeof ordCount);
	for (int i = 0; i < ordCount; i++)
	{
		Order ord;
		ord.readFromFile(&clients, &drivers, oif);
		orders.pushBack(std::move(ord));
	}
	oif.close();


	//Load Session
	std::ifstream sif("session.dat", std::ios::in | std::ios::binary);
	if (!sif.is_open())
		throw std::exception("File not open.");
	int id = 0;
	sif.read((char*)&id, sizeof id);
	LoggedUserType type;
	sif.read((char*)&type, sizeof type);
	if (type == LoggedUserType::client)
	{
		const int clientsCount = clients.getSize();
		for (int i = 0; i < clientsCount; i++)
		{
			if (clients[i].getId() == id)
				logged = &clients[i];
		}
	}
	else if (type == LoggedUserType::driver)
	{
		const int driversCount = drivers.getSize();
		for (int i = 0; i < driversCount; i++)
		{
			if (drivers[i].getId() == id)
				logged = &drivers[i];
		}
	}
	sif.close();
}

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
				logged = &clients[i];
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
				logged = &drivers[i];
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
	{
		std::cout << "No users in the system!\n";
		return;
	}


	for (int i = 0; i < clientCount; i++)
	{
		if (clients[i].getUsername() == username)
		{
			if (clients[i].isValidPassword(password))
			{
				logged = &clients[i];
				type = LoggedUserType::client;
				return;
			}
			std::cout << "Wrong password!\n";
			return;
		}
	}

	for (int i = 0; i < driverCount; i++)
	{
		if (drivers[i].getUsername() == username)
		{
			if (drivers[i].isValidPassword(password))
			{
				logged = &drivers[i];
				type = LoggedUserType::driver;
				return;
			}
			std::cout << "Wrong password!\n";
			return;
		}
	}
	std::cout << "No such user in the sytem!\n";
}

void Application::logout()
{
	logged = nullptr;
	type = LoggedUserType::none;
}

User* Application::getLoggedUser()
{
	return logged;
}

const User* Application::getLoggedUser() const
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
			orders[i].getDriver()->setFree(true);
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
			if (orders[i].getClient() == getLoggedUser() && orders[i].getStatus() == OrderStatus::completed)
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
			if (orders[i].getDriver() != logged)
				throw std::runtime_error("Not your order!");
			if (orders[i].getStatus() != OrderStatus::created)
				throw std::runtime_error("The order is unavailable.");
			orders[i].setStatus(OrderStatus::accepted);
			orders[i].getDriver()->setFree(false);
			return;
		}
	}
	throw  std::runtime_error("No such order in the system!");
}

void Application::declineOrder(int id)
{
	const int count = orders.getSize();
	for (int i = 0; i < count; i++)
	{
		if (orders[i].getId() == id)
		{
			orders[i].addDeclinedId(orders[i].getDriver()->getId());
			orders[i].setDriver(getClosestDriver(orders[i], orders[i].getOrigin().getX(), orders[i].getOrigin().getY()));
		}
	}
	throw  std::runtime_error("No such order in the system!");
}

void Application::finishOrder(int id)
{
	const int count = orders.getSize();
	for (int i = 0; i < count; i++)
	{
		if (orders[i].getId() == id)
		{
			if (orders[i].getDriver() != logged)
				throw std::runtime_error("Not your order.");
			if (orders[i].getStatus() != OrderStatus::accepted)
				throw std::runtime_error("You cant finish this order!");
			orders[i].setStatus(OrderStatus::completed);
			orders[i].getDriver()->setAddress(orders[i].getDestinaton());
			orders[i].getDriver()->setFree(true);
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

void Application::checkMessages() const
{
	const int ordCount = orders.getSize();
	bool match = false;

	if (getType() == LoggedUserType::client)
	{
		const Client* cl = dynamic_cast<Client*>(logged);
		for (int i = 0; i < ordCount; i++)
		{
			Order order = orders[i];
			if (order.getClient() == cl && order.getStatus() == OrderStatus::accepted)
			{
				const Driver& driver = *order.getDriver();

				std::cout << "Your driver " << driver.getFirstName() << " " << driver.getLastName() << " will arrive in " << order.getMinutes() << " minutes!\n";
				return;
			}
		}
	}
	else if(getType() == LoggedUserType::driver)
	{
		const Driver* dr = dynamic_cast<Driver*>(logged);
		for (int i = 0; i < ordCount; i++)
		{
			Order order = orders[i];
			if (order.getDriver() == dr && order.getStatus() == OrderStatus::created)
			{
				const Client& client = *order.getClient();
				const Address& origin = order.getOrigin();
				const Address& dest = order.getDestinaton();


				std::cout << client.getFirstName() << " " << client.getLastName() << " has made na order from:\n";
				std::cout << origin.getName() << " " << origin.getDescr() << " to:\n";
				std::cout << dest.getName() << dest.getDescr() << std::endl;

				match = true;
			}
		}
	}


	if (!match)
		std::cout << "No messages!\n";
}

double Application::getDist(int x1, int y1, int x2, int y2) const
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void Application::exitApp() const
{
	save();
	exit(EXIT_SUCCESS);
}

Driver* Application::getClosestDriver(const Order& order, int x, int y)
{
	const int drcount = drivers.getSize();
	if (drcount == 0)
		throw std::runtime_error("No drivers available.");

	double minDist = 0;
	Driver* currMin = nullptr;

	for (int i = 0; i < drcount; i++)
	{
		if (drivers[i].isFree() && !order.getDeclinedDriversIds().contains(drivers[i].getId()))
		{
			const double dist = getDist(x, y, drivers[i].getAddress().getX(), drivers[i].getAddress().getY());
			if (dist < minDist)
			{
				minDist = dist;
				currMin = orders[i].getDriver();
			}
		}
	}

	return currMin;
}

Driver* Application::getClosestDriver(int x, int y)
{
	const int drcount = drivers.getSize();
	if (drcount == 0)
		throw std::runtime_error("No drivers available.");

	double minDist = 0;
	Driver* currMin = nullptr;

	for (int i = 0; i < drcount; i++)
	{
		if (drivers[i].isFree())
		{
			const double dist = getDist(x, y, drivers[i].getAddress().getX(), drivers[i].getAddress().getY());
			if (dist <= minDist)
			{
				minDist = dist;
				currMin = orders[i].getDriver();
			}
		}
	}

	return currMin;
}



