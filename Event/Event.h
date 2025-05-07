#include <vector>
#include <functional>
using namespace std;

#pragma once

template<typename TSender, typename TArgument>
class Event
{
	private: vector<function<void(TSender, TArgument)>> _handlers;

	public: Event();

	public: void Invoke(TSender sender, TArgument arg);

	void operator += (function<void(TSender, TArgument)> handler);

	void operator -= (function<void(TSender, TArgument)> handler);
};

template<typename TSender, typename TArgument>
Event<TSender, TArgument>::Event()
{
	_handlers = vector<function<void(TSender, TArgument)>>();
}

template<typename TSender, typename TArgument>
void Event<TSender, TArgument>::Invoke(TSender sender, TArgument arg)
{
	for (int i = 0; i < _handlers.size(); i++)
		_handlers[i](sender, arg);
}

template<typename TSender, typename TArgument>
void Event<TSender, TArgument>::operator += (function<void(TSender, TArgument)> delegate)
{
	_handlers.push_back(delegate);
}

template<typename TSender, typename TArgument>
void Event<TSender, TArgument>::operator -= (function<void(TSender, TArgument)> delegate)
{
	int index = -1;
	for (int i = 0; i < _handlers.size(); i++)
		if (_handlers[i] == delegate)
		{
			index = i;
			break;
		}
	if (index != -1)
		_handlers.erase(_handlers.cbegin() + index);
}