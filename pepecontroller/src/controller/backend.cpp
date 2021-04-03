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
	//void Instance::Play(int64_t id)
	//{
	//}
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
	std::string Instance::CurrentMovieFilename()
	{
		return _currentMovieFilename;
	}
	void Instance::Play(std::string& name)
	{
		_currentMovieFilename = name;
		// play filename
	}
	//void Instance::Play(storage::models::movie::Movie* mv)
	//{
	//	_currentMovie = mv;
	//	if (_currentMovie != nullptr)
	//	{
	//		//play mv
	//	}
	//}
	//void Instance::Volume(uint8_t n)
	//{
	//}
	void Instance::Stop()
	{
	}
	//void Instance::callOverlay()
	//{
	//}
	
}