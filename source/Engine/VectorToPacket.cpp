#include "..\..\include\Irrlicht\irrlicht.h"
#include "..\..\include\SFML\Network.hpp"

sf::Packet& operator <<(sf::Packet &out, const irr::core::vector3df &in)
{
	return out << in.X << in.Y << in.Z;
}

sf::Packet& operator >>(sf::Packet& in, irr::core::vector3df& out)
{
	return in >> out.X >> out.Y >> out.Z;
}

sf::Packet& operator <<(sf::Packet& out, const irr::core::vector2df& in)
{
	return out << in.X << in.Y;
}

sf::Packet& operator >>(sf::Packet& in, irr::core::vector2df& out)
{
	return in >> out.X >> out.Y;
}