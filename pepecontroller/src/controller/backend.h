#pragma once
#include <iostream>
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
	private:
	};
}