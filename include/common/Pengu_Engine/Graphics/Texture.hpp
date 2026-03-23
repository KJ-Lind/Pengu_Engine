#ifndef TEXTURE_HPP
#define TEXTURE_HPP 1

#include <string>
namespace Pengu::Graphics {

	class Texture {
	public:
		bool LoadFromFile(const std::string& path);
		void Bind(unsigned int slot = 0);
		const std::string& path() const { return t_path_; }
		~Texture();

	private:
		unsigned int t_id_ = 0;
		int t_width_ = 0;
		int t_height_ = 0;
		std::string t_path_;
	};
}//Pengu::Graphics::Texture

#endif // !TEXTURE_HPP
