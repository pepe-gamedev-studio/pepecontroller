#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <filesystem>
namespace pepebackend
{
	struct URI
	{
		std::string address;
	};
	struct Font
	{
		std::string fontname;
	};
	struct Image
	{
		std::string filename;
	};
	struct Text
	{
		std::string text;
		Font font;
	};
	class Instance
	{
	public:
		Instance(const std::filesystem::path& playlistPath);
		~Instance();
		void Play(const std::filesystem::path& name);
		void Stop();
		std::shared_ptr<Text> DrawText(uint16_t x, uint16_t y, const Text& text);
		void Connect(const URI& StreamURL);
		void Disconnect();
		std::shared_ptr<Image> DrawImage(uint16_t x, uint16_t y, const Image& image);
		std::filesystem::path PlayingFilename();
		std::set<std::filesystem::path> GetPlaylist();
		/*template <typename T, typename C = std::decay_t<decltype(*begin(std::declval<T>()))>,
		typename = std::enable_if_t<std::is_convertible_v<C, storage::models::movie::Movie>>>
		auto AllMoviesFilenames()
		{
			T res;
			std::transform(movies.begin(), movies.end(), std::inserter(res, res.begin()), storage::models::movie::str_to_mv);
			return res;
		}*/
		
	private:
		std::filesystem::path playlistPath;
		std::set<std::filesystem::path> playlist;
		std::filesystem::path playingFilename;
	};
}