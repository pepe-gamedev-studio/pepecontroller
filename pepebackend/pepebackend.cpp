#include "pepebackend.h"
namespace pepebackend
{

	Instance::Instance(const std::filesystem::path& playlistPath) : playlistPath(playlistPath) // path where located files to be played
	{
		try
		{
			for (const auto& entry : std::filesystem::directory_iterator(playlistPath))
				playlist.insert(entry.path().filename().u8string());
		}
		catch (const std::exception&)
		{
			std::filesystem::create_directory(playlistPath);
		}
	}
	Instance::~Instance()
	{
	}
	void Instance::Connect(const URI& StreamURL)
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
	std::filesystem::path Instance::PlayingFilename()
	{
		return playingFilename;
	}
	std::set<std::filesystem::path> Instance::GetPlaylist()
	{
		return playlist;
	}
	void Instance::Play(const std::string& name)
	{
		playingFilename = name;
		// play filename
	}
	void Instance::Stop()
	{
	}
	
}