#pragma once

enum class ResourceType
{
	None = -1,
	Image,


	End,
};

enum
{
	ResourceTypeCount = static_cast<uint8>(ResourceType::End),
};

class ResourceBase
{
public:
	ResourceBase(ResourceType type);
	virtual ~ResourceBase() {};

public:
	virtual void Save(const std::string& path) {};
	virtual void Load(const std::string& path) {};

public:
	ResourceType GetType() { return _type; };

public:
	void SetType(ResourceType type) { _type = type; };

private:
	ResourceType _type = ResourceType::None;
};

