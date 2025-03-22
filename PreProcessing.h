#pragma once

enum class PreProcessingType 
{
	None = -1,
	Image,
	Video,
};

class PreProcessing
{
public:
	PreProcessing(PreProcessingType type);
	virtual ~PreProcessing() {};

public:
	virtual void Execute() {};

private:
	PreProcessingType _type = PreProcessingType::None;

};

