#pragma once

namespace gr
{
	namespace base {
		class Texture
		{
		public: unsigned int ID;

		public:
			Texture();

			void Load(const char* path);
			void setTexParameteri(unsigned int target, unsigned int option, unsigned int param);
			void Activate(unsigned int TEXTURE);

			void Bind();
			void UnBind();
			void Delete();
		};
	}
}

