#include <cstddef>
#include "Particle.h"

std::vector<StructProperty> Particle::GetProperties()
{
	std::vector<StructProperty> properties;
	properties.push_back(StructProperty("type", StructProperty::ParticleType, offsetof(Particle, type)));
	properties.push_back(StructProperty("life", StructProperty::ParticleType, offsetof(Particle, life)));
	properties.push_back(StructProperty("co-type", StructProperty::ParticleType, offsetof(Particle, ctype)));
	properties.push_back(StructProperty("carbons", StructProperty::ParticleType, offsetof(Particle, carbon)));
	properties.push_back(StructProperty("hydrogens", StructProperty::ParticleType, offsetof(Particle, hydrogen)));
	properties.push_back(StructProperty("double/triple bond location", StructProperty::ParticleType, offsetof(Particle, bond)));
	properties.push_back(StructProperty("chlorines", StructProperty::ParticleType, offsetof(Particle, chlorine)));
	properties.push_back(StructProperty("alcohols", StructProperty::ParticleType, offsetof(Particle, alcohol)));
	properties.push_back(StructProperty("quark flavour", StructProperty::ParticleType, offsetof(Particle, subFlavour)));
	//properties.push_back(StructProperty("x", StructProperty::Float, offsetof(Particle, x)));
	//properties.push_back(StructProperty("y", StructProperty::Float, offsetof(Particle, y)));
	properties.push_back(StructProperty("x velocity", StructProperty::Float, offsetof(Particle, vx)));
	properties.push_back(StructProperty("y velocity", StructProperty::Float, offsetof(Particle, vy)));
	properties.push_back(StructProperty("temperature", StructProperty::Float, offsetof(Particle, temp)));
	//properties.push_back(StructProperty("flags", StructProperty::UInteger, offsetof(Particle, flags)));
	//properties.push_back(StructProperty("tmp", StructProperty::Integer, offsetof(Particle, tmp)));
	//properties.push_back(StructProperty("tmp2", StructProperty::Integer, offsetof(Particle, tmp2)));
	//properties.push_back(StructProperty("deco colour", StructProperty::UInteger, offsetof(Particle, dcolour)));
	return properties;
}
