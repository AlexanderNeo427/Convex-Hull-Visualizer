#ifndef _DROPDOWN_EXTENDED_
#define _DROPDOWN_EXTENDED_

#include <raylib-cpp.hpp>
#include <unordered_map>
#include <type_traits>
#include <string>

template<class T>
class DropdownExtended
{
public:
	explicit DropdownExtended() 
	{
		static_assert(std::is_enum<T>::val, "T must be of type enum");
	}

	bool Draw()
	{
	}

	void Add(const T& val, const std::string& elemName)
	{
		m_elemStr.append(";").append(elemName);
	}
private:
	std::string m_elemStr;
};

#endif
