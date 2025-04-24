#pragma once
#include <vector>
#include <functional>
#include <cmath>
#include <iostream>

template<typename T, 
	class Hash = std::hash<T>,
	class KeyEqual = std::equal_to<T>
>
class MyHash
{
	enum class EntryState { EMPTY, OCCUPIED, DELETED };
	struct Bucket
	{
		T val;
		EntryState st = EntryState::EMPTY;
		
	};

	friend std::ostream& operator<<(std::ostream& os, Bucket b)
	{
		switch (b.st)
		{
		case EntryState::EMPTY: os << "EMPTY";
			break;
		case EntryState::OCCUPIED: os << "OCCUPIED";
			break;
		case EntryState::DELETED: os << "DELETED";
			break;
		}
		return os;
	}

	std::vector<Bucket> _table;
	double _alpha{ 0.7 };
	size_t _size{ 0 };
	size_t _capacity{ 0 };

	Hash outHash;
	KeyEqual comp;

	size_t inHash(T val) const
	{
		//size_t hash = outHash(val);
		//return std::floor(_capacity * std::fmod(hash * 0.618, 1));
		const size_t hash = outHash(val);
		const uint64_t golden_ratio = 0x9E3779B97F4A7C15;

		// Fixed-point multiplication
		const uint64_t product = hash * golden_ratio;

		// Take top bits for mixing
		const uint32_t mixed = product >> 32;

		// Final modulo
		return mixed % _capacity;
	}

	void rehash()
	{
		_capacity *= 2;
		std::vector<Bucket> _oldTable = _table;
		_table = std::vector<Bucket>(_capacity);
		_size = 0;
		for (auto x : _oldTable)
		{
			auto ind = inHash(x.val);
			bool inserted = false;
			int i = 1;
			while (_table[ind].st == EntryState::OCCUPIED)
			{
				if (comp(_table[ind].val, x.val))
				{
					break;
				}
				else
				{
					ind = (ind + i * i) % _capacity;
					i++;
				}
			}
			_table[ind].val = x.val;
			_table[ind].st = EntryState::OCCUPIED;
			_size++;
		}
	}


public: 

	using iterator = typename std::vector<Bucket>::iterator;

	MyHash(size_t startCap = 16,Hash outH = Hash(), KeyEqual k = KeyEqual()):_table(startCap),_capacity(startCap),outHash(outH),comp(k)
	{
		
	}

	size_t size()
	{
		return _size;
	}

	size_t capacity()
	{
		return _capacity;
	}

	std::pair<iterator, bool> insert(T val)
	{
		if (_size + 1 > _capacity * _alpha)
		{
			rehash();
		}
		auto ind = inHash(val);
		bool inserted = false;
		int i = 1;
		while (_table[ind].st == EntryState::OCCUPIED)
		{
			if (comp(_table[ind].val,val))
			{
				return std::make_pair(_table.begin() + ind, false);
			}
			else
			{
				ind = (ind + i * i) % _capacity;
				i++;
			}
		}
		_table[ind].val = val;
		_table[ind].st = EntryState::OCCUPIED;
		_size++;
		return std::make_pair(_table.begin() + ind, true);
	}

	bool contains(const T& val) const
	{
		if (_size == 0) return false;

		size_t ind = inHash(const_cast<T&>(val));
		size_t original_ind = ind;
		int i = 1;

		while (_table[ind].st != EntryState::EMPTY)
		{
			if (_table[ind].st == EntryState::OCCUPIED && _table[ind].val == val)
			{
				return true;
			}
			ind = (original_ind + i * i) % _capacity;
			i++;
			if (ind == original_ind)
			{
				return false;
			}
		}
		return false;
	}

	bool erase(const T& val)
	{
		if (_size == 0) return false;

		size_t ind = inHash(const_cast<T&>(val));
		size_t original_ind = ind;
		int i = 1;
		while (_table[ind].st != EntryState::EMPTY)
		{
			if (_table[ind].st == EntryState::OCCUPIED && comp(_table[ind].val, val))
			{
				_table[ind].st = EntryState::DELETED;
				_size--;
				return true;
			}
			ind = (ind + (i * i)) % _capacity;
			i++;
		}
		return false;
	}

	friend std::ostream& operator<<(std::ostream& os, MyHash<T> hs)
	{
		os << "[ind,val,stat,hash]\n";
		for (auto i = 0; i < hs._table.size();i++)
		{
			auto h = hs.inHash(hs._table[i].val);
			os << "[" << i << ", " << hs._table[i].val <<", " << hs._table[i] <<"," << h <<"]" << "\n";
		}
		return os;
	}
};
