#include "backend.h"
#include <filesystem>
namespace backend
{


	Instance::Instance() : _moviesPath("./movies")
	{
		for (const auto& entry : std::filesystem::directory_iterator(_moviesPath))
			_movies.insert(entry.path().filename().u8string());
	}
	Instance::~Instance()
	{
	}
	void Instance::Connect(URI& StreamURL)
	{
	}
	void Instance::Disconnect()
	{
	}
	std::shared_ptr<Text> Instance::DrawText(uint16_t x, uint16_t y, const Text& text)
	{
		return std::make_shared<Text>(text);
	}
	std::shared_ptr<Image> Instance::DrawImage(uint16_t x, uint16_t y, const Image& image)
	{
		return std::make_shared<Image>(image);
	}
	storage::models::movie::Movie Instance::getMovie()
	{
		return storage::models::movie::Movie();
	}
	void Instance::Play(uint16_t id)
	{
	}
	void Instance::Play(std::string& name)
	{
	}
	void Instance::Volume(uint8_t n)
	{
	}
	void Instance::Stop()
	{
	}
	void Instance::callOverlay()
	{
	}
	
}