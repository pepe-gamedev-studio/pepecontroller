#pragma once
#include <iostream>
#include <vector>
#include <set>
#include "../storage/models/movie.h"
#include "../helper.h"
namespace backend
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
		Instance();
		~Instance();
		void Play(uint16_t id);
		void Play(std::string& name);
		void Volume(uint8_t n);
		void Stop();
		void callOverlay();
		std::shared_ptr<Text> DrawText(uint16_t x, uint16_t y, const Text& text);
		void Connect(URI& StreamURL);
		void Disconnect();
		std::shared_ptr<Image> DrawImage(uint16_t x, uint16_t y, const Image& image);
		storage::models::movie::Movie getMovie();
		template <typename T, typename C = std::decay_t<decltype(*begin(std::declval<T>()))>,
		typename = std::enable_if_t<std::is_convertible_v<C, storage::models::movie::Movie>>>
		auto getAllMovies()
		{
			T res;
			std::transform(_movies.begin(), _movies.end(), std::inserter(res, res.begin()), storage::models::movie::str_to_mv);
			return res;
		}
		
	private:
		const std::string _moviesPath;
		std::set<std::string> _movies;

	};
}